#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

using namespace std;

int main()
{
	int num = 0;
	alarm(1);
	while(true)
		cout << ++num << '\n';
	return 0;
}
