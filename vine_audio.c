#ifndef __VINE_AUDIO_MAIN__
#define __VINE_AUDIO_MAIN__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vine_audio.h"
#include "./agc/VineAGC.h"

// common default constatns
#define FRAMESIZE_NB 160
#define FRAMESIZE_WB 320
#define AGC_PARAM_MIN_VAL 1
#define AGC_PARAM_MAX_VAL 32767


static int g_agcBst = PARAM_MIN_VAL; // agc boost parameter
static int g_agcLmt = PARAM_MIN_VAL; // agc limit parameter


/*===========================================================================
DESCRIPTION
	Result can be found as below.
	
	fail: "0" Out of supporting setting values.
	success: "1" When supporting values are set.
===========================================================================*/
int VineInitAGC ()
{
	vagc_ProcessResult agcResult;
	int ret_val = 0;
 
	agcResult = vagcInitialize(g_agcBst, g_agcLmt);

	if (agcResult == vagc_Success) {
		ret_val = 1;
	}
	else {
		ret_val = 0;
	}
	
	return ret_val;
}


/*===========================================================================
DESCRIPTION
	Processing Function

	Return values
	fail: 0
	success: 1
===========================================================================*/
int VineProcessAGC (short* pcmInput, short* pcmOutput)
{
	int i;
	int retval = 0;
	vagc_ProcessResult agcResult;

	if(is_valid == 1) {
		agcResult = vagcProcess(pcmInput, pcmOutput, g_agcBst, g_agcBst);

		if (agcResult == vagc_Success) {
			retval = 1;
		}
		else {
			retval = 0;
		}
	}
	else {
		for(i=0;i<FRAMESIZE_NB;i++) { pcmOutput[i] = pcmInput[i]; }
		retval = 1;
	}
			
	return retval;
}

#endif //__VINE_AUDIO_MAIN__
