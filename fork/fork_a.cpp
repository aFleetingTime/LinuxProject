#include <iostream>
#include <unistd.h>

using namespace std;

int num = 100;

int main()
{
	if(fork())
	{
		sleep(1);
		cout << "1num = " << num << endl;
	}
	else
	{
		num = 200;
		cout << "2num = " << num << endl;
	}

	return 0;
}
