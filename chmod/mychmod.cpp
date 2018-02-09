#include <unistd.h>
#include <iostream>
#include <sys/stat.h>

using namespace std;

int main(int argc, char *argv[])
{
	if(argc != 3)
	{
		cout << "mychmod <filename> <power>" << endl;
		return -1;
	}
	if(access(argv[1], F_OK))
	{
		cout << "该文件不存在！" << endl;
		return -2;
	}
	long int power = strtol(argv[2], nullptr, 8);
	if(chmod(argv[1], power))
	{
		cout << "更改权限失败:需要管理员权限！" << endl;
		return -3;
	}
	return 0;
}
