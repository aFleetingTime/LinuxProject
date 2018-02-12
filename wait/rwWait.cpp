#include <iostream>
#include <string>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>

using namespace std;

int main()
{
	string path("./temp.txt");
	int fd = open(path.c_str(), O_RDWR | O_CREAT, 0664);
	unlink(path.c_str());

	if(fork())
	{
		string text("Test file...");
		write(fd, text.c_str(), text.size());
		pid_t pid = 0;
		int status = 0;
		if(pid = wait(&status))
		{
			if(WIFEXITED(status))
				cout << "已回收子进程:" << pid << " exited:" << WEXITSTATUS(status) << endl;
			else if(WIFSIGNALED(status))
				cout << "已回收子进程:" << pid << " termsig:" << WTERMSIG(status) << endl;
		}
		close(fd);
	}
	else
	{
		sleep(1);

		constexpr int size = 512;
		char buf[size]{};

		lseek(fd, 0, SEEK_SET);

		read(fd, buf, size);
		cout << buf << endl;
		close(fd);
	}

	return 0;
}
