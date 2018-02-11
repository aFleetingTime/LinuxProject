#include <iostream>
#include <unistd.h>

using namespace std;

class Test
{
public:
	~Test()
	{
		cout << "~Test" << endl;
	}
}test;

int main()
{
End:
	if(!fork())
	{
		goto End;
		execl("/bin/ls", "i", "-l", "./", nullptr);
	}
	else
		sleep(1);
	return 0;
}
