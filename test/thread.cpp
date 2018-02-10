#include <iostream>
#include <unistd.h>
#include <cstdlib>

using namespace std;

int main()
{
	cout << "fork" << endl;
	fork();
	sleep(1);	
	cout << "pid = " << getpid() << endl;
	cout << "ppid = " << getppid() << endl;
	return 0;
}
