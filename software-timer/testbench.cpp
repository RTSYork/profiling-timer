#include "profile_timer.h"

typedef struct {
	unsigned int time;
	unsigned int tag;
} timeStamp;

static timeStamp times[256];

int main() {

	uint32 commandIn = 0;
	uint32 tagIn = 0;
	uint32 timeIn = 0;
	uint32 tagOut = 0;
	uint32 timeOut = 0;

	// Clear timer
	commandIn = 0xFFFFFFFF;
	profile_timer(&commandIn, &tagIn, &timeIn, &tagOut, &timeOut);

	// Tag 0x001 at time 0x00000123 three times
	timeIn = 0x00000123;
	tagIn = 0x001;
	commandIn = 0;
	profile_timer(&commandIn, &tagIn, &timeIn, &tagOut, &timeOut);
	profile_timer(&commandIn, &tagIn, &timeIn, &tagOut, &timeOut);
	profile_timer(&commandIn, &tagIn, &timeIn, &tagOut, &timeOut);

	for (int i = 0; i < 256; i++) {
		commandIn = i + 1;
		profile_timer(&commandIn, &tagIn, &timeIn, &tagOut, &timeOut);
		times[i].time = timeOut;
		times[i].tag = tagOut;
	}

	// Print out the times...
	for (int i = 0; i < 256; i++) {
		printf("%3d: 0x%03x = 0x%08x\n", i+1, times[i].tag, times[i].time);
		// if (times[i].tag == 0 && times[i].time == 0)
		// 	break;
	}

	return 0;
}
