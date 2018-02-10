#include <iostream>
#include <unistd.h>

using namespace std;

static int num = 100;

int main()
{
	num = 200;
	if(fork())
	{
		sleep(1);
		num = 999;
		cout << "1num = " << num << endl;
		cout << "&1num = " << &num << endl;
	}
	else
	{
		cout << "2num = " << num << endl;
		cout << "&2num = " << &num << endl;
	}

	return 0;
}
