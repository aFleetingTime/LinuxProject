#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <cstring>

using namespace std;

int main()
{
	int pfd[2]{};
	pipe(pfd);

	char buf[8193]{};
	memset(buf, 'a', 8192);

	write(pfd[1], buf, 8192);
	cout << "buf size:" << fpathconf(pfd[1], _PC_PIPE_BUF) << endl;

	memset(buf, '\0', 8192);
	read(pfd[0], buf, 8192);
	cout << strlen(buf) << endl;
	sleep(1);
	cout << buf << endl;

	close(pfd[1]);
	close(pfd[0]);

	return 0;
}
