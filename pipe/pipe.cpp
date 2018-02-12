#include <iostream>
#include <cstdio>
#include <string>
#include <sys/stat.h>
#include <sys/types.h>
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
	if(fork())
	{
		string text("pipe test aaa");
		sleep(2);
		write(pfd[1], text.c_str(), text.size());
	}
	else
	{
		char buf[512]{};
		read(pfd[0], buf, 512);
		cout << buf << endl;
	}


	close(pfd[0]);
	close(pfd[1]);

	return 0;
}
