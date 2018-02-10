#include <iostream>
#include <unistd.h>

using namespace std;

class Test
{
public:
	Test()
	{
		cout << "class Test() create..." << endl;
		mTest = new char('t');
	}
	~Test()
	{
		cout << "class ~Test()..." << endl;
		delete mTest;
	}
	char *mTest;
}test;

int main()
{
	if(fork())
	{
		sleep(1);
		cout << *test.mTest << endl;
	}
	else
	{
		*test.mTest = 'a';
		cout << *test.mTest << endl;
	}
	return 0;
}
