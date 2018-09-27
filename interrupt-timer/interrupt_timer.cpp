#include "interrupt_timer.h"

volatile uint36 times[65536];
uint16 count = 0;

uint1 intrLast = 0;
uint1 intr = 0;
uint32 command = 0;


void interrupt_timer(volatile uint32 *commandIn, volatile uint1 *intrIn, volatile uint36 *timeIn, uint32 *timeOutHigh, uint32 *timeOutLow, uint32 *countOut) {
#pragma HLS INTERFACE s_axilite port=commandIn bundle=BUS_A
#pragma HLS INTERFACE s_axilite port=timeOutHigh bundle=BUS_A
#pragma HLS INTERFACE s_axilite port=timeOutLow bundle=BUS_A
#pragma HLS INTERFACE s_axilite port=countOut bundle=BUS_A
#pragma HLS INTERFACE ap_ctrl_none port=return

	intr = *intrIn;
	command = *commandIn;

	if (command == 0 && intrLast == 0 && intr == 1) {
		times[count] = *timeIn;
		count++;
	}
	else if (command <= 65536) {
		uint16 item = command - 1;
		uint36 time = times[item];
		*timeOutHigh = time >> 32;
		*timeOutLow = time & 0xFFFFFFFF;
	}
	else if (command == 0xFFFFFFFF) {
		count = 0;
		for (uint17 i = 0; i < 65536; i++) {
			times[i] = 0;
		}
	}

	intrLast = intr;
	*countOut = count;
}
