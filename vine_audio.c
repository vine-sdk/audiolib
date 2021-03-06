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
#define MAX_FRAMESIZE FRAMESIZE_WB
#define DEFAULT_SAMPLE_RATE 8000
#define DEFAULT_FRAMESIZE_IN_MS	20
#define AGC_PARAM_MIN_VAL 1
#define AGC_PARAM_MAX_VAL 32767
#define FIXED_POINT_FRACTIONAL_BITS 5   // Fixed-point Format: 11.5 (16-bit)

static int g_agcBst = AGC_PARAM_MIN_VAL; // agc boost parameter
static int g_agcLmt = AGC_PARAM_MIN_VAL; // agc limit parameter
static int g_activeStatus = 0;
static int g_frameSize = FRAMESIZE_WB;

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
	int sampleRate = DEFAULT_SAMPLE_RATE;
	int frameSizeInMs = DEFAULT_FRAMESIZE_IN_MS;
	

	agcResult = vagcInitialize(g_agcBst, g_agcLmt, sampleRate, frameSizeInMs);

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

	if(g_activeStatus == 1) {
		agcResult = vagcProcess(pcmInput, pcmOutput, g_agcBst, g_agcBst);

		if (agcResult == vagc_Success) {
			retval = 1;
		}
		else {
			for(i=0;i<g_frameSize;i++) { pcmOutput[i] = pcmInput[i]; }
			retval = 0;
		}
	}
	else {
		for(i=0;i<g_frameSize;i++) { pcmOutput[i] = pcmInput[i]; }
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
	short bufIn[MAX_FRAMESIZE];
	short bufOut[MAX_FRAMESIZE];
	
	// 1. Calculate x = floating_input * 2^(fractional_bits)
  	// 2. Round x to the nearest whole number (e.g. round(x))
  	// 3. Store the rounded x in an integer container
	for(i=0; i < g_frameSize; i++) {
		bufIn[i] = (short)(round(pcmInput[i] * (1 << FIXED_POINT_FRACTIONAL_BITS)));	
	}
	

	if(g_activeStatus == 1) {
		agcResult = vagcProcess(bufIn, bufOut, g_agcBst, g_agcBst);

		if (agcResult == vagc_Success) {
			retval = 1;
		}
		else {
			for(i=0;i<g_frameSize;i++) { pcmOutput[i] = pcmInput[i]; }
			retval = 0;
		}
		
		// Convert fixedSample (11.5) to doubleSample
		for(i=0; i < g_frameSize; i++) {
			pcmOutput[i] = ((double)bufOut[i] / (double)(1 << FIXED_POINT_FRACTIONAL_BITS));
		}
	}
	else {
		for(i=0;i<g_frameSize;i++) { pcmOutput[i] = pcmInput[i]; }
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
	short bufIn[MAX_FRAMESIZE];
	short bufOut[MAX_FRAMESIZE];
	
	// 1. Calculate x = floating_input * 2^(fractional_bits)
  	// 2. Round x to the nearest whole number (e.g. round(x))
  	// 3. Store the rounded x in an integer container
	for(i=0; i < g_frameSize; i++) {
		bufIn[i] = (short)(round(pcmInput[i] * (1 << FIXED_POINT_FRACTIONAL_BITS)));	
	}
	

	if(g_activeStatus == 1) {
		agcResult = vagcProcess(bufIn, bufOut, g_agcBst, g_agcBst);

		if (agcResult == vagc_Success) {
			retval = 1;
		}
		else {
			for(i=0;i<g_frameSize;i++) { pcmOutput[i] = pcmInput[i]; }
			retval = 0;
		}
		
		// Convert fixedSample (11.5) to doubleSample
		for(i=0; i < g_frameSize; i++) {
			pcmOutput[i] = ((double)bufOut[i] / (double)(1 << FIXED_POINT_FRACTIONAL_BITS));
		}
	}
	else {
		for(i=0;i<g_frameSize;i++) { pcmOutput[i] = pcmInput[i]; }
		retval = 1;
	}
			
	return retval;
}

#endif //__VINE_AUDIO_MAIN__
