/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhan <xhan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 09:18:01 by xhan              #+#    #+#             */
/*   Updated: 2024/09/28 11:11:37 by xhan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
客户端的实现主要步骤：

1. 设置全局变量：用于同步信号的接收。
2. 信号处理函数：更新全局变量，处理服务器的响应。
3. 字符转换为二进制并发送：
	对每个字符的每一位，发送 SIGUSR1（表示 1）或 SIGUSR2（表示 0）。
	在发送下一位之前，等待服务器的确认。
4. 主函数：解析命令行参数，设置信号处理，循环发送消息。

kill 是一个系统调用函数，主要用于向进程发送信号。
*/

#include "./minitalk.h"

int	g_bit_control;
/*
g_bit_control 是全局变量，用于同步客户端和服务器的信号传输过程。服务器响应后，客户端会通过该变量确认位的发送。
*/

void	send_char(char c, pid_t pid)
{
	int	bit;

	bit = __CHAR_BIT__ * sizeof(c) - 1;
	while (bit >= 0)
	{
		if (kill(pid, 0) < 0)
		{
			ft_printf("ERROR : cannot send sig to pid : %d\n", pid);
			exit(EXIT_FAILURE);
		}
		g_bit_control = 0;
		if (c & (1 << bit))
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		bit--;
		while (g_bit_control != 1)
			usleep(10);
	}
}
/*
send_char 函数逐位发送字符 c 的二进制表示，目标进程的 PID 是 pid。
bit = __CHAR_BIT__ * sizeof(c) - 1：确定字符的位数（通常是 8 位），用 __CHAR_BIT__ 获取每个字节的位数。
通过 if (c & (1 << bit)) 判断字符的每一位是否为 1，如果是 1，则发送 SIGUSR1，否则发送 SIGUSR2。
在每次发送位之后，等待 g_bit_control 被服务器更新，表示服务器已确认接收该位。

g_bit_control != 1：这个循环是为了等待服务器确认当前位已经成功接收。
client 通过接收 SIGUSR1 信号，由信号处理函数将 g_bit_control 设为 1，表示服务器已接收到并处理完了当前位。
usleep(10)：暂停 10 微秒（1 微秒 = 10⁻⁶ 秒），避免程序频繁占用 CPU 资源。通过 usleep，
client 进入一种等待状态，每隔 10 微秒检查一次 g_bit_control 的值是否变为 1。
*/

void	send_str(char *str, pid_t pid)
{
	int	cur;

	cur = 0;
	while (str[cur])
	{
		send_char(str[cur], pid);
		cur++;
	}
	send_char(0, pid);
}
/*
send_str 函数逐个字符地调用 send_char 将字符串发送给服务器。字符串结束后，发送一个 0 表示消息的结束。
*/

void	sig_usr(int sig)
{
	if (sig == SIGUSR1)
		g_bit_control = 1;
	else if (sig == SIGUSR2)
	{
		ft_printf("Message received !\n");
		exit(EXIT_SUCCESS);
	}
}
/*
sig_usr 函数是客户端的信号处理程序。
当接收到 SIGUSR1 时，设置 g_bit_control = 1，表示服务器已成功接收了一位，客户端可以继续发送下一位。
当接收到 SIGUSR2 时，表示服务器已接收到完整消息，客户端退出。
*/

int	main(int argc, char **argv)
{
	pid_t	pid;

	if (argc != 3)
	{
		ft_printf("Usage : ./client <pid> <string to send>\n");
		exit(EXIT_FAILURE);
	}
	signal(SIGUSR1, &sig_usr);
	signal(SIGUSR2, &sig_usr);
	pid = ft_atoi(argv[1]);
	if (!pid)
	{
		ft_printf("%s is an invalid pid\n", argv[1]);
		exit(EXIT_FAILURE);
	}
	send_str(argv[2], pid);
	while (1)
		sleep(1);
}
/*
main 函数处理命令行输入参数，注册信号处理函数，并调用 send_str 向服务器发送字符串。
检查输入参数是否为 3 个（./client <pid> <string to send>），否则退出。
通过 signal 注册 SIGUSR1 和 SIGUSR2 的处理函数。
将 PID 字符串转换为整型，确保有效性。
进入死循环，等待服务器确认接收的消息。

为什么客户端使用 signal：
void (*signal(int signum, void (*handler)(int)))(int);
简单的信号处理需求：客户端只需要在收到 SIGUSR1 时更新全局变量，或在收到 SIGUSR2 时确认消息发送完成，
然后退出程序。这是一种非常简单的信号处理，不涉及复杂的信号信息或对系统调用的影响。
signal 的作用：signal 函数的主要作用是设置简单的信号处理程序。它可以捕获信号并调用指定的处理函数，
但不提供更复杂的控制功能，如屏蔽其他信号或获取发送信号的进程 ID 等。
signal(SIGUSR1, &sig_usr)：当 client 收到 SIGUSR1 时，调用 sig_usr 函数进行处理。
signal(SIGUSR2, &sig_usr)：当 client 收到 SIGUSR2 时，调用 sig_usr 函数处理。
*/