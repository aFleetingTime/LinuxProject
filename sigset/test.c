#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>

int main()
{
	sigset_t myset;
	sigemptyset(&myset);
	sigaddset(&myset, SIGINT);
	sigaddset(&myset, SIGQUIT);
	sigaddset(&myset, SIGKILL);

	sigprocmask(SIG_BLOCK, &myset, NULL);

	while(1)
	{
		sigset_t pendset;
		sigpending(&pendset);
		for(int i = 1; i < 32; ++i)
		{
			if(sigismember(&pendset, i))
			{
				printf("%d", 1);
			}
			else
			{
				printf("%d", 0);
			}
		}
		printf("\n");
		sleep(1);
	}
	
	return 0;
}
