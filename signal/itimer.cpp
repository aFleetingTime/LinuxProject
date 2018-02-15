#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <unistd.h>

using namespace std;

int main()
{
	itimerval timeval{ 1, 5, 2, 5 };
	setitimer(ITIMER_REAL, &timeval, nullptr);

	while(true)
	{
		cout << "test" << endl;
		sleep(1);
	}
	
	return 0;
}
