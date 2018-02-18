#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <pthread.h>
#include <unistd.h>

using namespace std;

void *threadFunc(void *arg)
{
	int num = *static_cast<int*>(arg);
	cout << "thread" << num << "run..." << endl;
	delete static_cast<int*>(arg);
	pthread_exit(new int(num));
}

int main()
{
	pthread_t pts[5]{};
	for(int i = 0; i < 5; ++i)
		pthread_create(pts + i, nullptr, threadFunc, new int(i + 1));

	void *retval;
	int tempIndex = 0;
	while(tempIndex < 5 && !pthread_join(pts[tempIndex++], &retval))
		cout << "thread" << *static_cast<int*>(retval) << "over..." << endl;

	pthread_exit(nullptr);
}
