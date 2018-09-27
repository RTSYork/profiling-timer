#ifndef __PROFILE_TIMER_H_
#define __PROFILE_TIMER_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ap_int.h>

typedef ap_uint<1> uint1;
typedef ap_uint<16> uint16;
typedef ap_uint<17> uint17;
typedef ap_uint<32> uint32;
typedef ap_uint<36> uint36;

void profile_timer(uint32 *commandIn, uint32 *tagIn, uint36 *timeIn, uint32 *tagOut, uint32 *timeOutHigh, uint32 *timeOutLow, uint32 *countOut);

#endif
