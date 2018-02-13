#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <array>

using namespace std;

int main()
{
	int fd = open("./test.p", O_RDONLY);
	if(fd == -1)
	{
		perror("read open");
		return -1;
	}
	array<char, 512> buf{};
	read(fd, buf.data(), buf.size());
	cout << "read:" << buf.data() << endl;
	close(fd);
	return 0;
}
