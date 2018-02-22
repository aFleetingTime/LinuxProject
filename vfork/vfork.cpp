#include <iostream>
#include <array>
#include <vector>
#include <string>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

using namespace std;

constexpr size_t bufSize = 1024;
constexpr size_t cmdSize = 16;
constexpr size_t argSize = 32;

char **getArg(string cmd, size_t &args)
{
	static int i = 0;
	int findIndex = 0, aindex = 0;
	char **argv = new char*[cmdSize]();
	string temp;
	while((findIndex = cmd.find(" ")) != string::npos)
	{
		temp = cmd.substr(0, findIndex);
		argv[aindex] = new char[temp.length() + 1];
		strcpy(argv[aindex++], temp.c_str());
		cmd.erase(0, findIndex + 1);
	}
	argv[aindex] = new char[cmd.length() + 1];
	strcpy(argv[aindex++], cmd.c_str());
	args = aindex;
	return argv;
}

void eraseSpace(string &str)
{
	if(!str.empty())
	{
		str.erase(0, str.find_first_not_of(' '));
		str.erase(str.find_last_not_of(' ') + 1);
	}
}

string getCmd(array<char, bufSize> &cmdBuf)
{
	cin.getline(cmdBuf.data(), bufSize);
	string tempCmd(cmdBuf.data());
	eraseSpace(tempCmd);
	return tempCmd;
}

void exec(int args, char **argv)
{
	if(!vfork())
	{
		execvp(*argv, argv);
		perror("shell");
	}
	while(wait(nullptr) != -1);
}

void freeArg(char **argv, size_t args)
{
	for(int i = 0; i < args; ++i)
	{
		if(argv[i])
			delete[] argv[i];
	}
	delete[] argv;
}

int main()
{
	array<char, bufSize> cmdBuf{};
	array<char, cmdSize> hostName{};
	while(true)
	{
		gethostname(hostName.data(), hostName.size());
		cout << getlogin() << '@' << hostName.data() << ':' << get_current_dir_name() << "$ ";
		memset(cmdBuf.data(), 0, bufSize);
		size_t args = 0;
		char **argv = getArg(getCmd(cmdBuf), args);
		exec(args, argv);
		freeArg(argv, args);
	}
	return 0;
}
