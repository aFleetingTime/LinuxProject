#include <iostream>
#include <unistd.h>

using namespace std;

int main()
{
	cout << "P process run..." << endl;
	for(int i = 0; i < 10; ++i)
	{
		if(!fork())
			break;
		sleep(1);
	}
	cout << "pid:" << getpid() << endl << "ppid:" << getppid() << endl;

	return 0;
}
