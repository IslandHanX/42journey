/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhan <xhan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 09:18:01 by xhan              #+#    #+#             */
/*   Updated: 2024/09/28 11:11:44 by xhan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minitalk.h"

/*
sigaction 的结构体主要包含以下成员：

sa_handler 或 sa_sigaction：指定信号处理函数。
sa_mask：在处理信号时需要被阻塞的信号集合。
sa_flags：控制信号处理的行为，例如 SA_RESTART 可自动重启被中断的系统调用，SA_SIGINFO 可提供更详细的信号信息。

The function member of sa_sigaction is always invoked with 
the following arguments:
void handler(int signo, siginfo_t *info, void *other)

The sigaction structure is defined as something like:

struct sigaction {
	void     (*sa_handler)(int);
*	void     (*sa_sigaction)(int, siginfo_t *, void *);
*	sigset_t   sa_mask;
*	int        sa_flags;
	void     (*sa_restorer)(void);
};

If SA_SIGINFO is specified in sa_flags, then sa_sigaction 
(instead of sa_handler) 
specifies the signal-handling function for signum.
*	void     (*sa_sigaction)(int sig, siginfo_t *info, void *ucontext); 
	Three arguments are as follows:

	sig    The number of the signal that caused invocation调用 of the
			handler.

	info   A pointer to a siginfo_t
		包含了关于信号的详细信息，例如发送信号的进程 ID (si_pid)，信号的来源等。

	ucontext
			This is a pointer to a ucontext_t structure, cast to
			void *.  The structure pointed to by this field contains
			signal context information that was saved on the user-
			space stack by the kernel.

Sa_mask specifies a mask of signals which should be blocked.

Sa_flags specifies a set of flags which modify the behavior of the signal.
*/

/*
init_sig 函数用于设置信号处理程序。它使用 sigaction 而不是传统的 signal 函数，
因为 sigaction 更强大且行为一致。
sigaction 可以在处理信号时阻塞其他信号，防止信号处理函数被嵌套调用。
sigaction 不会像 signal 那样在处理后自动重置为默认处理器。
sigaction 的行为在不同系统间更一致，而 signal 的行为可能会有差异。

函数参数包括信号类型 (sig) 和信号处理程序 (handler)。
sigaction 结构体 susr 允许指定信号处理方式。
susr.sa_sigaction：指向处理信号的函数。
susr.sa_flags：使用了 SA_SIGINFO 来传递信号详细信息，
SA_SIGINFO：启用 sa_sigaction，使得处理信号时可以获得附加的信号信息。
启用该标志后，信号处理函数会接收到额外的参数，比如发送信号的进程 ID (si_pid)，从而可以实现更复杂的信号处理逻辑。
如果不设置该标志，信号处理函数只能接收信号的类型，没有额外的上下文信息。

SA_RESTART 标志的作用是在信号处理完成后自动重启被信号中断的系统调用。没有 SA_RESTART 的情况下，
如果一个系统调用被信号中断，它可能会返回错误，需要手动重新启动。

在client 和 server 之间传递信号的过程中，进程会频繁接收 SIGUSR1 和 SIGUSR2，例如：
client 发送一个位时，会等待 server 发送回确认信号 (SIGUSR1) 或消息完成信号 (SIGUSR2)。
server 在接收到信号后，需要回复 client。
在这种情形下，client 或 server 可能在系统调用（比如 sleep 或 usleep）时接收到信号。
这些系统调用用于等待一定的时间，而信号可能会中断这些调用。为了避免这些系统调用因信号而中断，可以使用 SA_RESTART。
client 发送一个位后，会通过 usleep(10) 短暂停止，以等待 server 返回确认信号。如果没有 SA_RESTART，
usleep 可能会因为接收到信号而提前返回，导致程序误判为信号尚未到达。这会导致不稳定的通信行为。
有了 SA_RESTART，即使 usleep 被信号中断，系统会自动重新启动 usleep，确保 client 正确等待服务器的确认信号。
这可以防止程序在信号到达之前过早结束等待。

SA_NODEFER：SA_NODEFER 的作用是防止在处理信号时自动屏蔽相同类型的信号。
默认情况下，当某个信号处理程序正在运行时，相同类型的信号（比如再次接收到 SIGUSR1）会被阻塞，直到处理程序返回后才会被处理。
启用了 SA_NODEFER 后，即使信号处理程序尚未完成，相同类型的信号仍可以继续触发处理。
如果没有 SA_NODEFER，server 在处理第一个 SIGUSR1 时会阻塞后续的 SIGUSR1，只有当处理完毕后，新的信号才能被处理。
这种行为可能导致延迟或缓慢响应。使用 SA_NODEFER 后，server 即使在处理中，仍能立即接收到相同类型的信号，并继续处理。
这样可以提高信号处理的实时性，避免延迟。

sigemptyset(&susr.sa_mask) 是用于清空信号处理时的屏蔽信号集。

在处理信号时，可以通过 sa_mask 来定义哪些信号在处理当前信号时会被屏蔽（阻塞）。默认情况下，进程在处理一个信号时，
不会处理其他信号。如果希望在处理某个信号时不阻塞其他信号（即让所有信号都能被正常接收），就可以使用 sigemptyset 清空屏蔽集。

作用：sigemptyset 将屏蔽集初始化为空集，意味着在处理信号时，不阻塞任何其他信号。
使用 sigemptyset 可以让信号处理程序在处理某个信号时，不阻塞任何其他信号，从而允许多个信号同时被处理。

示例： 如果没有调用 sigemptyset，处理信号 SIGUSR1 时，可能会阻塞 SIGUSR2，直到 SIGUSR1 处理完毕。
但通过清空屏蔽集，可以同时处理多个信号而不受影响。

假设 client 在发送最后一个字符后，会发送一个 SIGUSR2 表示消息传递完成：
如果 server 在处理 SIGUSR1 时没有清空屏蔽集，它可能会阻塞 SIGUSR2，直到当前处理完成。这可能导致 server 
未及时接收到 SIGUSR2，导致通信延迟或者逻辑错误。
通过 sigemptyset 清空屏蔽集，server 在处理 SIGUSR1 时仍然可以接收到 SIGUSR2，从而及时响应 client，告知消息传递完成。

sigaction 注册 SIGUSR1 或 SIGUSR2 的信号处理函数。
*/

void	init_sig(int sig, void (*handler)(int, siginfo_t *, void *))
{
	struct sigaction	susr;

	susr.sa_sigaction = handler;
	susr.sa_flags = SA_SIGINFO | SA_RESTART | SA_NODEFER;
	sigemptyset(&susr.sa_mask);
	if (sig == SIGUSR1)
		sigaction(SIGUSR1, &susr, 0);
	else if (sig == SIGUSR2)
		sigaction(SIGUSR2, &susr, 0);
}
/*
这是在分别为 SIGUSR1 和 SIGUSR2 信号注册信号处理程序。
sigaction() 函数用于改变指定信号（如 SIGUSR1 或 SIGUSR2）的行为，设置自定义的信号处理方式。
该函数有三个参数：
第一个参数 (SIGUSR1 或 SIGUSR2)：指定要处理的信号类型。这里的代码意思是根据 sig 的值，
分别处理 SIGUSR1 或 SIGUSR2 信号。
第二个参数 (&susr)：指向一个 struct sigaction 类型的结构体，该结构体定义了如何处理这个信号。
susr 结构体中包含了处理信号的函数指针和其他行为控制标志（例如 sa_flags 和 sa_mask）。
在前面代码中通过 susr 设置了具体的信号处理函数。
第三个参数 (0)：通常用于保存旧的信号处理配置，这里为 0，表示忽略旧的配置。

作用机制：
当传入 sig 为 SIGUSR1 时，执行 sigaction(SIGUSR1, &susr, 0);，
即将 susr 中定义的处理函数和行为应用于 SIGUSR1 信号。
当传入 sig 为 SIGUSR2 时，执行 sigaction(SIGUSR2, &susr, 0);，
即将 susr 中的设置应用于 SIGUSR2 信号。
*/
