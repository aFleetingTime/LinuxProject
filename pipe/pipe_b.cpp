#include <iostream>
#include <cstdio>
#include <string>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

using namespace std;

int main()
{
	int pfd[2]{};

	if(pipe(pfd) == -1)
	{
		perror("pipe:");
		return -1;
	}

	//cout << "pfd[0]:" << pfd[0] << endl << "pfd[1]:" << pfd[1] << endl;
	if(fork())
	{
		close(pfd[0]);
		close(pfd[1]);
		int status = 0;
		while(waitpid(-1, &status, 0) != -1)
		{
			if(WIFEXITED(status))
				cout << "exited:" << WEXITSTATUS(status) << endl;
			else if(WIFSIGNALED(status))
				cout << "signaled:" << WTERMSIG(status) << endl;
		}
	}
	else
	{
		if(fork())
		{
			close(pfd[0]);
			dup2(pfd[1], STDOUT_FILENO);
			execlp("ps", "ps", "aux", nullptr);
			perror("ps");
		}
		else
		{
			close(pfd[1]);
			dup2(pfd[0], STDIN_FILENO);
			execlp("grep", "grep", "--color=auto", "bash", nullptr);
			perror("grep");
		}
	}
	return 0;
}
