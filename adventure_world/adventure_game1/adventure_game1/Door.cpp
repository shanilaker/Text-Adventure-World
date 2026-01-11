#include "Door.h"

// Attempts to open door:
void Door::openDoor()
{
	// if door isn't linked to switched - means player has a key, then lower the num of keys needed to open the door. 
	if (!linked_to_switches) {
		num_key_needed--;
		if (num_key_needed == 0) // if 0 keys are needed then open the door.
		{
			is_open = true;
		}
	}
	// If door is linked to switches - they're already correct and door sets to Open
	else
	{
		is_open = true;
	}

}

void Door::setNumKeyNeeded(int num_needed) 
{ 
	num_key_needed = num_needed; reset_num_key_needed = num_needed; 
}