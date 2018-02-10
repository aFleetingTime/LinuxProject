#include <iostream>

using namespace std;

int main()
{
	char *t = nullptr;
	cout << static_cast<char*>(nullptr) << endl;
	cout << t << endl;
	return 0;
}
