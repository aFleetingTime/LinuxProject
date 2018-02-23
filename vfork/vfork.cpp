#include <iostream>
#include <array>
#include <vector>
#include <string>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>

using namespace std;

constexpr size_t bufSize = 1024;
constexpr size_t cmdSize = 16;
constexpr size_t argSize = 32;

struct Cmd
{
public:
	Cmd() : argv{}
	{
		outflag = false;
		inflag = false;
	}
	static size_t args;
	char *argv[cmdSize];
	bool outflag;
	bool inflag;
	string target;
};
size_t Cmd::args = 0;

void freeArg(Cmd *);

Cmd* getArg(string cmd)
{
	char errorChar = cmd.front();
	int count = 0;
	int findIndex = 0, aindex = 0, cindex = 0;
	Cmd *cmds = new Cmd[cmdSize];
	if(errorChar == '|' || errorChar == '<' || errorChar == '>')
	{
Error:
		cout << "-bash: 未预期的符号" << '\'' << errorChar << '\'' << "附近有语法错误" << endl;
		Cmd::args = cindex + 1;
		freeArg(cmds);
		Cmd::args = 0;
		return nullptr;
	}
	string temp;
	while(cindex < cmdSize && (findIndex = cmd.find(" ")) != string::npos)
	{
		temp = cmd.substr(0, findIndex);
		int flag = 0;
		if((!temp.compare("|") ? flag = 1 : 0) || (!temp.compare("<") ? flag = 2 : 0) || (!temp.compare(">") ? flag = 3 : 0))
		{
			switch(flag)
			{
			case 1:
				cmds[cindex].outflag = true;
				cmds[++cindex].inflag = true;
				break;
			case 2:

				break;
			case 3:
				cmds[cindex].outflag = true;
				cmd.erase(0, findIndex + 1);
				findIndex = cmd.find(" ");
				cmds[cindex].target = cmd.substr(0, findIndex);
				break;
			}
			aindex = 0;
			//++count;
			goto WCONTINUE;
		}
		else if(count != 0)
			--count;
		cmds[cindex].argv[aindex] = new char[temp.length() + 1];
		strcpy(cmds[cindex].argv[aindex++], temp.c_str());
WCONTINUE:
		cmd.erase(0, findIndex + 1);
		aindex %= cmdSize;
		if(count == 2)
		{
			errorChar = temp.front();
			goto Error;
		}
	}
	if(!temp.compare("|") || !temp.compare("<") || !temp.compare(">"))
	{
		if(++count == 2)
		{
			errorChar = temp.front();
			goto Error;
		}
		cmds[cindex].outflag = true;
		cmds[++cindex].inflag = true;
	}
	cmds[cindex].argv[aindex] = new char[cmd.length() + 1];
	strcpy(cmds[cindex++].argv[aindex], cmd.c_str());
	Cmd::args = cindex;
	return cmds;
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

void creatExec(Cmd *arg, int index, bool flag)
{
	if(index == Cmd::args - 1)
	{
		execvp(arg[index].argv[0], arg[index].argv);
		perror("bash");
		return;
	}
	int pfd[2]{};
	pipe(pfd);
	if(!fork())
	{
		if(arg[index].target.empty())
			dup2(pfd[1], STDOUT_FILENO);
		else
		{
			int fd = open(arg[index].target.c_str(), O_WRONLY | O_CREAT, 0664);
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		close(pfd[0]);
		close(pfd[1]);
		execvp(arg[index].argv[0], arg[index].argv);
		perror("bash");
		return;
	}
	dup2(pfd[0], STDIN_FILENO);
	close(pfd[0]);
	close(pfd[1]);
	creatExec(arg, index + 1, flag);
}

void exec(Cmd *argv)
{
	if(Cmd::args == 0)
		return;
	if(!vfork())
		creatExec(argv, 0, argv[Cmd::args].inflag);
	else
		wait(nullptr);
}

void freeArg(Cmd *argv)
{
	if(argv == nullptr)
		return;
	for(int i = 0; i < Cmd::args; ++i)
	{
		for(int j = 0; i < cmdSize; ++i)
		{
			if(argv[i].argv[j])
				delete[] argv[i].argv[j];
		}
	}
	delete[] argv;
	Cmd::args = 0;
}

void runCmd(Cmd *argv)
{
	if(!strcmp(argv[0].argv[0], "cd"))
		chdir(argv[0].argv[1]);
	else
		exec(argv);
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
		Cmd *argv = getArg(getCmd(cmdBuf));
		if(argv == nullptr)
			continue;
		runCmd(argv);
		freeArg(argv);
	}
	return 0;
}
