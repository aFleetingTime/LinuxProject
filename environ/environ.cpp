#include <iostream>

using namespace std;

extern char **environ;

int main()
{
	int index = 0;
	while(environ[index])
	{
		cout << environ[index++] << endl;
	}

	return 0;
}
