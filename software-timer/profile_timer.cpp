#include "profile_timer.h"

typedef struct {
	uint36 time;
	uint32 tag;
} timeStamp;

volatile timeStamp times[65536];
uint16 count = 0;


void profile_timer(uint32 *commandIn, uint32 *tagIn, uint36 *timeIn, uint32 *tagOut, uint32 *timeOutHigh, uint32 *timeOutLow, uint32 *countOut) {
#pragma HLS INTERFACE s_axilite port=commandIn bundle=BUS_A
#pragma HLS INTERFACE s_axilite port=tagIn bundle=BUS_A
#pragma HLS INTERFACE s_axilite port=tagOut bundle=BUS_A
#pragma HLS INTERFACE s_axilite port=timeOutHigh bundle=BUS_A
#pragma HLS INTERFACE s_axilite port=timeOutLow bundle=BUS_A
#pragma HLS INTERFACE s_axilite port=countOut bundle=BUS_A
#pragma HLS INTERFACE s_axilite port=return bundle=BUS_A

	if (*commandIn == 0 && *tagIn != 0) {
		times[count].time = *timeIn;
		times[count].tag = *tagIn;
		count++;
	}
	else if (*commandIn <= 65536) {
		uint16 item = *commandIn - 1;
		*tagOut = times[item].tag;
		uint36 time = times[item].time;
		*timeOutHigh = time >> 32;
		*timeOutLow = time & 0xFFFFFFFF;
	}
	else if (*commandIn == 0xFFFFFFFF) {
		count = 0;
		for (uint17 i = 0; i < 65536; i++) {
			times[i].time = 0;
			times[i].tag = 0;
		}
	}

	*countOut = count;
}
