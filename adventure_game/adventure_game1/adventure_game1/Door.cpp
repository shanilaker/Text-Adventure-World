#include "Door.h"

void Door::openDoor()
{
	num_key_needed--;
	if (num_key_needed == 0)
	{
		is_open = true;
	}
}