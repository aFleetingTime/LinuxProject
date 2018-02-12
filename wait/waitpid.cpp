#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <iostream>
#include <unistd.h>

using namespace std;

constexpr int size = 3;

int main()
{
	int pid[size]{};
	int	i = 0;
	while(i < size)
	{
		if(!(pid[i] = fork()))
			break;
		++i;
	}
	if(!i)
	{
		cout << "进程" << i << "段错误" << endl;
		*((int*)nullptr) = 1;
	}
	else if(i == 1)
	{
		cout << "进程" << i << "调用自定义程序" << endl;
		execlp("ls", "ls", nullptr);
		cout << "调用自定义程序失败!" << endl;
	}
	else if(i == 2)
	{
		cout << "进程" << i << "进入死循环 PID:" << getpid() << endl;
		while(1);
	}
	else
	{
		sleep(3);
		int status = 0;
		for(int i = 0; i < size; ++i)
		{
			pid_t tpid = waitpid(pid[i], &status, WNOHANG);
			if(tpid > 0)
			{ 
IF:
				cout << "子进程:" << tpid;
				if(WIFEXITED(status))
					cout << "正常退出:" << WEXITSTATUS(status) << endl;
					//cout << "正常退出:" << (status) << endl;
				else if(WIFSIGNALED(status))
					cout << "被信号杀死:" << WTERMSIG(status) << endl;
					//cout << "被信号杀死:" << (status) << endl;
			}
			else if(!tpid)
			{
				cout << "子进程:" << pid[i] << "正在运行" << endl;
				tpid = waitpid(pid[i], &status, 0);
				goto IF;
			}
			else
			{
				cout << "没有子进程!" << endl;
			}
		}
	}

	return 0;
}

