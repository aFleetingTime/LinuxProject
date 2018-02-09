#include <sys/types.h>
#include <string>
#include <ctime>
#include <grp.h>
#include <cstdio>
#include <pwd.h>
#include <sys/stat.h>
#include <unistd.h>
#include <cstdlib>

using namespace std;

int main(int argc, char *argv[])
{
	if(argc < 2)
	{
		printf("参数错误:myls <filename...>\n");
		return -1;
	}
	for(int i = 1; i < argc; ++i)
	{
		struct stat info;

		if(lstat(argv[i], &info))
		{
			char errorInfo[52]{};
			sprintf(errorInfo, "查询第%d个文件时发生错误！\n", i);
			perror(errorInfo);
		}

		string power;
		switch(info.st_mode & S_IFMT)
		{
		case S_IFREG:
			power.push_back('-');
			break;
		case S_IFDIR:
			power.push_back('d');
			break;
		case S_IFLNK:
			power.push_back('l');
			break;
		case S_IFBLK:
			power.push_back('b');
			break;
		case S_IFCHR:
			power.push_back('c');
			break;
		case S_IFIFO:
			power.push_back('p');
			break;
		case S_IFSOCK:
			power.push_back('s');
			break;
		}

		power.push_back((info.st_mode & S_IRUSR) ? 'r' : '-');
		power.push_back((info.st_mode & S_IWUSR) ? 'w' : '-');
		power.push_back((info.st_mode & S_IXUSR) ? 'x' : '-');
		power.push_back((info.st_mode & S_IRGRP) ? 'r' : '-');
		power.push_back((info.st_mode & S_IWGRP) ? 'w' : '-');
		power.push_back((info.st_mode & S_IXGRP) ? 'x' : '-');
		power.push_back((info.st_mode & S_IROTH) ? 'r' : '-');
		power.push_back((info.st_mode & S_IWOTH) ? 'w' : '-');
		power.push_back((info.st_mode & S_IXOTH) ? 'x' : '-');

		struct passwd *user = getpwuid(info.st_uid);			
		struct group *grop = getgrgid(info.st_gid);

		string mtime(ctime(&info.st_mtime));
		mtime.back() = '\0';
		mtime.erase(8, 1);

		printf("%s %d %s %s %d %s %s\n", power.c_str(), static_cast<int>(info.st_nlink), user->pw_name, grop->gr_name, static_cast<int>(info.st_size), mtime.c_str(), argv[i]);
	}
	return 0; 
}
