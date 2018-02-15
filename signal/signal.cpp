#include <iostream>
#include <string>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include <cstdio>

using namespace std;

int main()
{
	if(fork())
	{
		while(wait(nullptr) != -1);
	}
	else
	{
		if(!kill(getppid(), SIGKILL))
		{
			cout << "成功杀死目标进程" << endl;
		}
		else
		{
			perror("kill");
			return -1;
		}
	}
	return 0;
}
