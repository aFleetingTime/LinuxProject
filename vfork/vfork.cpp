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

int findPipe(int args, const char * const *argv)
{
	for(int i = 0; i < args; ++i)
	{
		if(!strcmp(argv[i], "|") || !strcmp(argv[i], "<") || !strcmp(argv[i], ">"))
			return i;
	}
	return -1;
}

void exec(int args, char **argv)
{
	int index = 0, cur = findPipe(args, argv);
	char flag = '\0';
	int pfd[2]{};
	pipe(pfd);
	if(!vfork())
	{
		if(cur != -1)
		{
			delete argv[cur];
			argv[cur++] = nullptr;
			for(index = cur; index < args; ++index)
			{
				if(!strcmp(argv[index], "|") || !strcmp(argv[index], "<") || !strcmp(argv[index], ">"))
				{
					flag = *argv[index];
					delete argv[index];
					argv[index] = nullptr;
					if(argv[cur] == nullptr)
						goto CONTINUE;
					if(!vfork())
					{
						switch(flag)
						{
						case '|':
							dup2(pfd[0], STDIN_FILENO);
							break;
						case '<':
							break;
						case '>':
							break;
						}
						execvp(argv[cur], argv + cur);
						perror("shell");
						return;
					}
CONTINUE:
					cur = index + 1;
				}
			}
			if(cur < args && !vfork())
			{
				dup2(pfd[0], STDIN_FILENO);
				close(pfd[1]);
				execvp(argv[cur], argv + cur);
				perror("shell");
				return;
			}
			dup2(pfd[1], STDOUT_FILENO);
			close(pfd[0]);
			execvp(*argv, argv);
			perror("shell");
			return;
		}
		else
			execvp(*argv, argv);
		return;
	}
	close(pfd[0]);
	close(pfd[1]);
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
		memset(cmdBuf.data(), 0, bufSize);
		gethostname(hostName.data(), hostName.size());
		cout << getlogin() << '@' << hostName.data() << ':' << get_current_dir_name() << "$ ";
		size_t args = 0;
		char **argv = getArg(getCmd(cmdBuf), args);
		if(!strcmp(*argv, "cd"))
			chdir(argv[1]);
		else
			exec(args, argv);
		freeArg(argv, args);
	}
	return 0;
}
