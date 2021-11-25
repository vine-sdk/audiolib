/*===========================================================================
File name: VineAGC.h

	AGC for speech signal.

Copyright 2021 AKOUOLAB & THE VINE CORP. All Rights Reserved.
===========================================================================*/

#ifndef __VINESDK_AGC__
#define __VINESDK_AGC__

/*===========================================================================
DESCRIPTION
	Processing result can be found as below. 
	
	vagc_Error: "0" Out of supporting target gain or setting values.
	vagc_Success: "1" When supporting values are set.
===========================================================================*/
typedef enum {
	vagc_Error,
	vagc_Success	
}vagc_ProcessResult;


/*===========================================================================
Function vagcInitialize

DESCRIPTION
	Initialize VineAGC.
	
ARGUMENTS
	AGCBoost : Tunable target gain. [1 ~ 32767]
	AGCLimit : Limiter level setting value. [1 ~ 32767]
===========================================================================*/
vagc_ProcessResult vagcInitialize(int AGCBoost, int AGCLimit);


/*===========================================================================
Function vagcProcess

DESCRIPTION
	Process VineAGC.
	
ARGUMENTS
	txInput: A pointer to Tx PCM buffer from Vocoder, which is used as the input PCM signal.
			[PCM format : signed, 15 bits]
			[Frame size : 160 bytes]
			(8K samples/second * 16bits/sample * 10msec)
	txOutput :A pointer to Tx PCM buffer will be filled with processed data. 
			     This buffer is filled at speech mode, the rest cases are bypassed
	AGCBoost : Tunable target gain. [1 ~ 32767]
	AGCLimit : Limiter level setting value. [1 ~ 32767]
===========================================================================*/
vagc_ProcessResult vagcProcess(short* txInput, short* txOutput, int AGCBoost, int AGCLimit);


#endif //__VINESDK_AGC__
