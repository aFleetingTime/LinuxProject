#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>

using namespace std;

int main(int args, char *argv[])
{
#if true
	if(fork())
	{
		int status = 0;
		pid_t pid = wait(&status);
		cout << "child process pid:" << pid << endl;
		if(WIFEXITED(status))
			cout << "exit:" << WEXITSTATUS(status) << endl;
		else if(WIFSIGNALED(status))
			cout << "signal:" << WTERMSIG(status) << endl;
	}
	else
	{
		abort();
	}
#endif
#if 0
	abort();
#endif
	return 0;
}
