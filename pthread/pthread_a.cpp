#include <iostream>
#include <map>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pthread.h>

using namespace std;

void *func(void *arg)
{
	int *temp = static_cast<int*>(arg);
	cout << "child thread " << *temp << ':' << pthread_self() << endl;
	delete temp;
	return nullptr;
}

int main()
{
	map<int, pthread_t> ctps;
	for(int i = 1; i <= 5; ++i)
	{
		pthread_t temp = 0;
		pthread_create(&temp, nullptr, func, new int(i));
		ctps.insert(make_pair(i, temp));
	}
	sleep(1);
	cout << "sort:" << endl;
	for(auto val : ctps)
		cout << "child thread " << val.first << ':' << val.second << endl;
	cout << "main thread:" << pthread_self() << endl;
	return 0;
}
