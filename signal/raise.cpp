#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <sstream>

using namespace std;

int main(int args, char *argv[])
{
	if(args != 2)
	{
		cout << "raise <signal>" << endl;
		return -1;
	}
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
		stringstream ss(argv[1]);
		int sig = 0;
		ss >> sig;
		ss.clear();
		raise(sig);
	}
	return 0;
}
