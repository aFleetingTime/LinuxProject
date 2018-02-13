#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <array>

using namespace std;

int main()
{
	int pfd[2]{};
	pipe(pfd);

	fcntl(pfd[0], F_SETFL, fcntl(pfd[0], F_GETFL) | O_NONBLOCK);
	fcntl(pfd[1], F_SETFL, fcntl(pfd[1], F_GETFL) | O_NONBLOCK);

	switch(fork())
	{
	case -1:
		perror("fork");
		return -1;
	case 0:
		close(pfd[0]);
		write(pfd[1], "test text...", 12);
	default:
		close(pfd[1]);
		sleep(1);
		array<char, 512> buf{};
		read(pfd[0], buf.data(), buf.size());
		cout << buf.data() << endl;
	}
	
	return 0;
}
