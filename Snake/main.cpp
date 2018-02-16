#include "Map.h"
#include <unistd.h>

Point MapSize(10, 20);

int main()
{
	Map map(MapSize);
	while(true)
	{
		map.flush();
		usleep(500);
	}
	return 0;
}
