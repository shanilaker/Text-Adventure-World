#include "Switch.h"

//Returns the shape of the switch
char Switch::getCurrentChar() const {
	if (is_on) {
		return on_char;
	}
	return off_char;
}