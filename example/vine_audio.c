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
#define FIXED_POINT_FRACTIONAL_BITS 5   // Fixed-point Format: 11.5 (16-bit)

static int g_agcBst = 100; // agc boost parameter
static int g_agcLmt = 100; // agc limit parameter
static int g_activeStatus = 0;

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
		g_activeStatus = 1;
	}
	else {
		ret_val = 0;
		g_activeStatus = 0;
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
	
	if (g_activeStatus == 1) {
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


/*===========================================================================
DESCRIPTION
	Processing Function for floating point data type (float)

	Return values
	fail: 0
	success: 1
===========================================================================*/
int VineProcessAGCF (float* pcmInput, float* pcmOutput)
{
	int i;
	int retval = 0;
	vagc_ProcessResult agcResult;
	short bufIn[FRAMESIZE_WB];
	short bufOut[FRAMESIZE_WB];
	
	// 1. Calculate x = floating_input * 2^(fractional_bits)
  	// 2. Round x to the nearest whole number (e.g. round(x))
  	// 3. Store the rounded x in an integer container
	for(i=0; i < FRAMESIZE_WB; i++) {
		bufIn[i] = (short)(round(pcmInput[i] * (1 << FIXED_POINT_FRACTIONAL_BITS)));	
	}
	

	if(g_activeStatus == 1) {
		agcResult = vagcProcess(bufIn, bufOut, g_agcBst, g_agcBst);

		if (agcResult == vagc_Success) {
			retval = 1;
		}
		else {
			retval = 0;
		}
		
		// Convert fixedSample (11.5) to doubleSample
		for(i=0; i < FRAMESIZE_WB; i++) {
			pcmOutput[i] = ((double)bufOut[i] / (double)(1 << FIXED_POINT_FRACTIONAL_BITS));
		}
	}
	else {
		for(i=0;i<FRAMESIZE_NB;i++) { pcmOutput[i] = pcmInput[i]; }
		retval = 1;
	}
			
	return retval;
}

/*===========================================================================
DESCRIPTION
	Processing Function for floating point data type (double)

	Return values
	fail: 0
	success: 1
===========================================================================*/
int VineProcessAGCD (double* pcmInput, double* pcmOutput)
{
	int i;
	int retval = 0;
	vagc_ProcessResult agcResult;
	short bufIn[FRAMESIZE_WB];
	short bufOut[FRAMESIZE_WB];
	
	// 1. Calculate x = floating_input * 2^(fractional_bits)
  	// 2. Round x to the nearest whole number (e.g. round(x))
  	// 3. Store the rounded x in an integer container
	for(i=0; i < FRAMESIZE_WB; i++) {
		bufIn[i] = (short)(round(pcmInput[i] * (1 << FIXED_POINT_FRACTIONAL_BITS)));	
	}
	

	if(g_activeStatus == 1) {
		agcResult = vagcProcess(bufIn, bufOut, g_agcBst, g_agcBst);

		if (agcResult == vagc_Success) {
			retval = 1;
		}
		else {
			retval = 0;
		}
		
		// Convert fixedSample (11.5) to doubleSample
		for(i=0; i < FRAMESIZE_WB; i++) {
			pcmOutput[i] = ((double)bufOut[i] / (double)(1 << FIXED_POINT_FRACTIONAL_BITS));
		}
	}
	else {
		for(i=0;i<FRAMESIZE_NB;i++) { pcmOutput[i] = pcmInput[i]; }
		retval = 1;
	}
			
	return retval;
}

#endif //__VINE_AUDIO_MAIN__
