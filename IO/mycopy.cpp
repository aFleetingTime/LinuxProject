#include "MyIOstream.cpp"
#include <iostream>
#include <cstdio>

using namespace std;

constexpr size_t bufSize = 512;

int main(int args, char *argv[])
{
	if(args != 3)
	{
		cout << "参数格式错误！" << endl;
		return -1;
	}
	MyIOstream rio;
	MyIOstream wio;
	int ret = rio.openFile(argv[1], O_RDONLY);
	if(ret == -1)
	{
		perror("open read file");
		return -2;
	}
	ret = wio.openFile(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if(ret == -1)
	{
		perror("open write file");
		return -2;
	}

	char buf[bufSize]{};
	int readSize = 0;

	while((readSize = rio.readFile(buf, bufSize)) > 0)
	{
		if(wio.writeFile(buf, readSize) == -1)
		{
			perror("write");
			return -3;
		}
	}

	return 0;
}
