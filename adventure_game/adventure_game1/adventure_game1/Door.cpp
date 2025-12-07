#include "Door.h"

void Door::openDoor()
{
	if (!linked_to_switches) {
		num_key_needed--;
		if (num_key_needed == 0)
		{
			is_open = true;
		}
	}
	else 
	{
		is_open = true;
	}
	
}