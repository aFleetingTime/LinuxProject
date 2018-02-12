#include <iostream>
#include <string>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>

using namespace std;

int main()
{
	int i = 0;
	while(i < 5)
	{
		if(!fork())
			break;
		++i;
	}
	if(i < 5)
	{
		cout << "child num:" << i << " pid:" << getpid() << " ppid:" << getppid() << endl;
		while(1);
	}
	pid_t pid = 0;
	int status = 0;
	while((pid = wait(&status)) != -1)
	{
		cout << "wait num:" << pid;
		if(WIFEXITED(status))
			cout << " exiten:" << WEXITSTATUS(status) << endl;
		else if(WIFSIGNALED(status))
			cout << " signaled:" << WTERMSIG(status) << endl;
	}
	return 6;
}
