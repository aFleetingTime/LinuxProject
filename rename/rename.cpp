#include <string>
#include <iostream>
#include <fstream>
#include <stdexcept>

using namespace std;

int main(int argc, char *argv[])
{
	string path[2];

	try
	{
		if(argc != 3)
			throw new invalid_argument("参数格式:rn <oldname> <newname>");

		path[0].assign(argv[1]);
		path[1].assign(argv[2]);

		if(rename(path[0].c_str(), path[1].c_str()))
			throw new domain_error("对应的文件不存在!");
	}
	catch(exception *exp)
	{
		cout << exp->what() << endl;
		delete exp;
		return -1;
	}

	int pos = 0;
	for(int i = 0; i != 2; ++i)
	{
		if((pos = path[i].rfind('/')) != string::npos)
			path[i].erase(0, pos);
	}

	cout << path[0] << "文件已更名为:" << path[1] << endl;
	
	return 0;
}
