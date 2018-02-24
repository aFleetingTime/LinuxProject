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
		index = 0;
		tarFlag = 0;
	}
	~Cmd()
	{
		for(int i = 0; i < index; ++i)
		{
			if(argv[i] != nullptr)
				delete[] argv[i];
			argv[i] = nullptr;
		}
		index = 0;
	}
	bool addArg(const string &arg)
	{
		if(index >= cmdSize)
			return false;
		argv[index] = new char[arg.length() + 1];
		strcpy(argv[index++], arg.c_str());
		return true;
	}
	void freeArg()
	{
		for(int i = 0; i < index; ++i)
		{
			if(argv[i] != nullptr)
			{
				cout << "free" << endl;
				delete[] argv[i];
			}
			argv[i] = nullptr;
		}
		index = 0;
	}
	static size_t args;
	char *argv[cmdSize];
	bool outflag;
	bool inflag;
	string target;
	char tarFlag;

private:
	size_t index;
};
size_t Cmd::args = 0;

void freeArg(Cmd *);

Cmd* getArg(string cmd)
{
	char errorChar = cmd.front();
	int findIndex = 0, index = 0;
	int pipeflag = 0;
	int dupflag = 0;
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
	while(index < cmdSize && (findIndex = cmd.find(" ")) != string::npos)
	{
		temp = cmd.substr(0, findIndex);
		if((temp.compare("|"))
		{
			cmds[index].outflag = true;
			cmds[++index].inflag = true;
			dupflag = 0
			++pipeflag;
			goto WCONTINUE;
		}
		else if(!temp.compare("<") || !temp.compare(">"))
		{
			cmds[index].tarFlag = temp.front():
			if(cmds[index].tarFlag == '<')
			{
				cmds[index].inflag = true;
				cmd.erase(0, findIndex + 1);
				findIndex = cmd.find(" ");
				cmds[index++].target = cmd.substr(0, findIndex);
			}
			else
			{
				cmds[index].outflag = true;
				cmd.erase(0, findIndex + 1);
				findIndex = cmd.find(" ");
				cmds[index++].target = cmd.substr(0, findIndex);
			}
			pipeflag = 0;
			++dupflag;
		}
		cmds[cindex].addArg(temp);
WCONTINUE:
		cmd.erase(0, findIndex + 1);
		if(pipeflag == 2 || dupflag == 2)
		{
			errorChar = temp.front();
			goto Error;
		}
	}
	if(!cmd.empty())
	{
		if(!cmd.compare("|"))
		{
			if(++pipeflag == 2)
			{
				errorChar = temp.front();
				goto Error;
			}
			cmds[cindex].outflag = true;
			cmds[++cindex].inflag = true;
		}
		else if(!cmd.compare("<") || !cmd.compare(">"))
		{
			if(++dupflag == 2)
			{
				errorChar = temp.front();
				goto Error;
			}
			cmds[index].tarFlag = cmd.front();
			if(cmds[index].tarFlag == '<')
			{

			}
			else if(cmds[index].tarFlag == '>')
			{

			}
		}
		cmds[cindex].addArg(cmd);
		Cmd::args = cindex;
	}
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
