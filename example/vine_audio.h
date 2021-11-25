/*===========================================================================
File name: vine_audio.h

Copyright 2021 The Vine Corporation All Rights Reserved.
===========================================================================*/

#ifndef __VINE_AUDIO__
#define __VINE_AUDIO__


typedef unsigned char  BOOLEAN;
typedef short          INT16;
typedef int            INT32;
typedef unsigned short UINT16;
typedef unsigned int   UINT32;


/*===========================================================================
Function VineInitAGC

DESCRIPTION
	This function initializes VINE. (AGC)
	
ARGUMENTS	
	None 

RETURN VALUE
	1: succeed
	0: not succeed
===========================================================================*/
int VineInitAGC (void);


/*===========================================================================
Function VineProcessAGC

DESCRIPTION
	This function processes AGC.
	
ARGUMENTS	
	pcmInput: A pointer to Tx PCM buffer from Vocoder, which is used as the input PCM signal.
			[PCM format : signed, 15 bits]
			[Frame size : 320 bytes]
			(16K samples/second * 16bits/sample * 20msec)
	pcmOutput :A pointer to Tx PCM buffer will be filled with processed data. 

RETURN VALUE
	1: succeed
	0: not succeed
===========================================================================*/
int VineProcessAGC (short* pcmInput, short* pcmOutput);


/*===========================================================================
Function VineProcessAGCF

DESCRIPTION
	This function processes AGC. (float input)
	
ARGUMENTS	
	pcmInput: A pointer to Tx PCM buffer from Vocoder, which is used as the input PCM signal.
			[PCM format : signed double, 32 bits]
			[Frame size : 640 bytes]
			(16K samples/second * 32bits/sample * 20msec)
	pcmOutput :A pointer to Tx PCM buffer will be filled with processed data. 
===========================================================================*/
int VineProcessAGCF (float* pcmInput, float* pcmOutput);


/*===========================================================================
Function VineProcessAGCD

DESCRIPTION
	This function processes AGC. (double input)
	
ARGUMENTS	
	pcmInput: A pointer to Tx PCM buffer from Vocoder, which is used as the input PCM signal.
			[PCM format : signed double, 32 bits]
			[Frame size : 640 bytes]
			(16K samples/second * 32bits/sample * 20msec)
	pcmOutput :A pointer to Tx PCM buffer will be filled with processed data. 
===========================================================================*/
int VineProcessAGCD (double* pcmInput, double* pcmOutput);

#endif //____VINE_AUDIO____
