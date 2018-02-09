#include <map>
#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <dirent.h>
#include <cstring>
#include <string>
#include <iomanip>

using namespace std;

void countFile(string , map<unsigned char, size_t>&);

int main(int argc, char *argv[])
{
	string path(argv[1]);
	if(argc != 2)
	{
		cout << "参数格式:count <dirpath>" << endl;
		return -1;
	}
	else if(access(path.c_str(), F_OK))
	{
		cout << "目录不存在!" << endl;
		return -2;
	}

	map<unsigned char, size_t> cmap;

	if(path.back() == '/')
		path.pop_back();
	countFile(path.c_str(), cmap);

	cout <<	setw(14) << "普通文件(f):" << cmap[DT_REG] << endl; 
	cout <<	setw(14) << "目录(d):" << cmap[DT_DIR] << endl; 
	cout <<	setw(15) << "软链接(l):" << cmap[DT_LNK] << endl; 
	cout <<	setw(15) << "块设备(b):" << cmap[DT_BLK] << endl; 
	cout <<	setw(14) << "字符设备(c):" << cmap[DT_CHR] << endl; 
	cout <<	setw(14) << "管道(p):" << cmap[DT_FIFO] << endl; 
	cout <<	setw(15) << "套接字(s):" << cmap[DT_SOCK] << endl; 
	cout <<	setw(14) << "未知文件(u):" << cmap[DT_UNKNOWN] << endl; 
	return 0;
}

void countFile(string dirPath, map<unsigned char, size_t> &cmap)
{
	DIR *dir = opendir(dirPath.c_str());
	if(!dir)
		return;
	dirent *temp = nullptr;
	while(temp = readdir(dir))
	{
		if(!strcmp(temp->d_name, ".") || !strcmp(temp->d_name, ".."))
			continue;
		++cmap[temp->d_type];
		if(temp->d_type == DT_DIR)
			countFile(dirPath + "/" + temp->d_name, cmap);
	}
	closedir(dir);
}
