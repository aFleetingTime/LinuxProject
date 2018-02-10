#include <iostream>
#include <unistd.h>
#include <sys/types.h>

using namespace std;

int main()
{
	cout << getuid() << endl;
	cout << geteuid() << endl;
	return 0;
}
