/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhan <xhan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 09:18:01 by xhan              #+#    #+#             */
/*   Updated: 2024/09/28 10:35:01 by xhan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
信号 是一种软件中断，用于在进程运行时中断其正常流程，以执行特定的处理。
例如，当你按下 Ctrl+C 时，会发送 SIGINT 信号中断正在运行的程序。

常见的信号包括：
SIGINT：中断信号，通常由 Ctrl+C 触发。
SIGABRT：异常终止信号。
SIGQUIT：退出信号，通常由 Ctrl+\ 触发。
SIGUSR1 和 SIGUSR2：用户自定义信号，可用于进程间通信。
例如，在客户端代码中，根据接收到的是 SIGUSR1 还是 SIGUSR2，
采取不同的处理动作，如设置控制变量或退出进程。
当信号被触发时，内核会调用相应的信号处理函数 (sig_handler)，处理方式有三种：

忽略 (SIG_IGN)：进程不处理该信号。
捕获 (catch)：进程定义一个函数来处理该信号。
默认处理 (SIG_DFL)：采用信号的默认处理方式。

When a signal is activated, the process sends a signal to the kernel, 
which then utilizes the sig_handler() function to perform one of three
possible actions: ignore, catch, or default.

* If a signal is ignored
It means that the process has no response to the interruption, 
although it should be noted that certain signals cannot be ignored, 
such as SIGKILL and SIGSTOP. 
* If a signal is caught
The process registers a function with the kernel to handle the interruption. 
* If a signal executes
Its default behavior, it indicates that the process is using the SIG_DFL signal. 

* igaction is an alternative and more modern way of handling signals.
虽然使用 signal 函数可以更简洁地设置信号处理，但 sigaction 提供了更强大和安全的功能。主要区别包括：

We will be using the killsystem call. 
The first argument is the process ID of the intended recipient of the signal. 
For the second, you usually use a predefined constant like SIGINT.

为了通过信号逐位发送字符，需要将字符转换为二进制位进行处理。
示例：字符 'H' 的 ASCII 码是 72，二进制表示为 01001000。
使用位移操作，可以逐位获取字符的二进制表示：
右移操作 (>>)：将字符的二进制位右移，取最右边的位。
按位与操作 (&)：与 1 进行按位与操作，获取最低位的值。

处理负数和 Unicode 字符
对于 Unicode 字符（如表情符号），可能会遇到多字节字符，甚至负数值。
处理负数时，需要考虑补码表示：
最高位为符号位：0 表示正数，1 表示负数。
负数的二进制表示：对正数取反加一。
示例：将 -16 转换为二进制：

正数部分：16 的二进制为 00010000。
取反：11101111。
加一：11110000。

Minitalk 包含两个进程：
服务器 (server)：等待并接收来自客户端的信号，重构消息。
客户端 (client)：将消息逐位发送给服务器。
关键点：
客户端使用 kill 函数向服务器发送信号：
int kill(pid_t pid, int sig);
服务器设置信号处理函数，异步接收信号。
*/

#include "./minitalk.h"

void	sig_usr(int sig, siginfo_t *info, void *context)
{
	static char	c = 0;
	static int	bit = -1;

	(void)context;
	if (kill(info->si_pid, 0) < 0)
	{
		ft_printf("ERROR : cant send sig to pid : %d\n", info->si_pid);
		exit(EXIT_FAILURE);
	}
	if (bit < 0 && !c)
		ft_printf("\nClient say : ");
	if (bit < 0)
		bit = __CHAR_BIT__ * sizeof(c) - 1;
	if (sig == SIGUSR1)
		c |= 1 << bit;
	else if (sig == SIGUSR2)
		c &= ~(1 << bit);
	if (!bit && c)
		ft_putchar_fd(c, 1);
	else if (!bit && !c)
		kill(info->si_pid, SIGUSR2);
	bit--;
	kill(info->si_pid, SIGUSR1);
}
/*
sig_usr 是服务器的信号处理函数，用于逐位接收客户端发送的字符。
使用静态变量 c 保存当前接收的字符，bit 用于跟踪字符的位。
每次接收 SIGUSR1 或 SIGUSR2 后，服务器更新 c 的相应位：
如果是 SIGUSR1，设置该位为 1。
如果是 SIGUSR2，设置该位为 0。
当位数达到 0 且 c 不为 0 时，表示完整字符已接收，输出字符。如果 c == 0，表示消息结束，向客户端发送 SIGUSR2。

sig: 表示接收到的信号类型，可能是 SIGUSR1 或 SIGUSR2。SIGUSR1 表示当前位是 1，SIGUSR2 表示当前位是 0。
info: 是一个 siginfo_t 结构体指针，包含有关信号的详细信息，包括哪个进程发送了信号
（通过 info->si_pid 可获取发送信号的进程 PID）。
context: 用来保存信号发生时的上下文信息，在这里未使用，所以通过 (void)context 来忽略该参数。

static 变量 c 和 bit 保证在每次调用 sig_usr 时，这两个变量的值不会被重置，它们会保持之前的状态，确保信号逐位接收和处理。
c: 保存接收的字符，通过每次接收到的位来逐步构建完整的字符。
bit: 代表字符的当前位索引，从高位向低位处理。当 bit 为 -1 时，表示需要开始接收新的字符。

kill(info->si_pid, 0): 通过发送信号 0 来检查 info->si_pid 代表的进程是否存在。
这种调用不会实际发送信号，但如果进程不存在，函数将返回 -1。

当 bit 小于 0 时，表示前一个字符已经完全接收完毕，准备接收一个新字符。此时将 bit 重新设置为 7
（如果是 8 位字符的话，bit 的值就是 7，因为字符从第 7 位到第 0 位逐步接收）。8 * 1 - 1 = 7。

sig == SIGUSR1: 如果接收到 SIGUSR1，表示当前位是 1。通过位运算 c |= 1 << bit，将字符 c 的第 bit 位设置为 1。
1 << bit：通过左移操作，将 1 移动到对应的位位置。
c |= 1 << bit：将字符 c 的第 bit 位设置为 1（OR 操作）。

sig == SIGUSR2: 如果接收到 SIGUSR2，表示当前位是 0。通过 c &= ~(1 << bit)，将字符 c 的第 bit 位设置为 0。
~(1 << bit)：将对应位的位置设置为 0，其余位置保持不变。
c &= ~(1 << bit)：将字符 c 的第 bit 位设置为 0（AND 操作）。

bit--：处理完一位后，递减 bit，准备接收下一个位。bit 最终会递减到 -1，表示一个完整的字符已经接收完毕。
kill(info->si_pid, SIGUSR1)：向客户端发送 SIGUSR1，表示服务器已经成功接收到并处理了该位，客户端可以继续发送下一个位。
*/

int	main(void)
{
	init_sig(SIGUSR1, &sig_usr);
	init_sig(SIGUSR2, &sig_usr);
	ft_printf("pid: %d", getpid());
	while (1)
		sleep(1);
}
/*
这两行代码分别为 SIGUSR1 和 SIGUSR2 信号注册信号处理程序 sig_usr。init_sig 通过 sigaction 为指定信号设置处理函数。
&sig_usr是指向信号处理函数sig_usr的指针。当 server 接收到 SIGUSR1/SIGUSR2 时，它会调用 sig_usr 函数处理这些信号。
获取当前进程的 PID（进程标识符）。
进入一个无限循环，表示 server 会一直运行，直到手动终止。
server 每次休眠 1 秒钟，防止进程过度占用 CPU。它不会实际做任何工作，
直到接收到信号时，信号处理函数 sig_usr 才会被唤醒并执行。
*/