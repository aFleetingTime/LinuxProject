#include <iostream>
#include <cstdlib>

using namespace std;

int main(int args, char *argv[])
{
	char *value = secure_getenv(argv[1]);
	if(value != nullptr)
		cout << value << endl;
	return 0;
}
