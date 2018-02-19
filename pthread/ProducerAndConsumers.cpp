#include <iostream>
#include <thread>
#include <string>
#include <queue>
#include <mutex>
#include <condition_variable>

using namespace std;

queue<string> food;
string foodname(".");
mutex mlock;
condition_variable cond;
chrono::microseconds pSleepTime(1);
chrono::microseconds cSleepTime(1);

void producerRun()
{
	while(true)
	{
		unique_lock<mutex> ulock(mlock);
		food.push(foodname);
		cout << "生产者生产" << foodname << " 物品还剩:" << food.size() << endl;
		cond.notify_one();
		ulock.unlock();
		this_thread::sleep_for(pSleepTime);
	}
}
void consumersRun()
{
	while(true)
	{
		unique_lock<mutex> ulock(mlock);
		if(!food.size())
			cond.wait(ulock);
		string fname = food.front();
		food.pop();
		cout << "消费者购买" << fname << " 物品还剩:" << food.size() << endl;
		ulock.unlock();
		this_thread::sleep_for(cSleepTime);
	}
}

int main()
{
	thread producer(producerRun);
	thread consumers(consumersRun);

	producer.join();
	consumers.join();
	
	return 0;
}
