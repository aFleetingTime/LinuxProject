#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <cstdio>
#include <signal.h>
#include <sstream>

using namespace std;

int main()
{
	sigset_t set{};
	sigfillset(&set);
	sigdelset(&set, SIGQUIT);

	sigprocmask(SIG_BLOCK, &set, nullptr);

	while(true)
	{
		ostringstream sigstr;
		sigset_t sigset{};
		sigpending(&sigset);
		for(int i = 1; i < 32; ++i)
			sigstr << sigismember(&sigset, i);
		cout << sigstr.str() << '\n';
		sleep(1);
	}

	return 0;
}
