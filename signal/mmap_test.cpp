#include <iostream>
#include <sstream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <fstream>

using namespace std;

int main()
{
	ofstream ofs("./temp", ios::out);
	alarm(1);
	int num = 0;
	while(ofs << ++num << '\n');
	//while(ofs << ++num << endl);
	ofs.close();
	return 0;
}
