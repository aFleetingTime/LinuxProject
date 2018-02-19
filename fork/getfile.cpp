#include <fstream>
#include <random>

using namespace std;

int main()
{
	ofstream ofs("./file.txt", ios::out | ios::trunc);
	random_device random;
	int num = random() % 10240000 + 1024000;
	for(int i = 0; i < num; ++i)
		ofs << ('a' + random() % 26);
	ofs.close();
	return 0;
}
