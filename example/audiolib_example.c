/**
 * @file audiolib_example.c
 * @author thevine-admin
 * @brief Executable library example
 * @result Output file name: [Input file name]_out.pcm   
 * @version 0.8
 * @date 2021-10-27
 * 
 * @copyright Copyright THE VINE CORPORATION (c) 2021
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "vine_audio.h"

#ifndef FRAME_SIZE
#define FRAME_SIZE  160
#endif


/** 
 * File path splitting function
 */
void splitpath(const char *path, char *drv, char *dir, char *name, char *ext) {
    const char *end;
    const char *p;
    const char *s;
    if (path[0] && path[1] == ':') {
        if (drv) {
            *drv++ = *path++;
            *drv++ = *path++;
            *drv = '\0';
        }
    } else if (drv)
        *drv = '\0';
    for (end = path; *end && *end != ':';)
        end++;
    for (p = end; p > path && *--p != '\\' && *p != '/';)
        if (*p == '.') {
            end = p;
            break;
        }
    if (ext)
        for (s = end; (*ext = *s++);)
            ext++;
    for (p = end; p > path;)
        if (*--p == '\\' || *p == '/') {
            p++;
            break;
        }
    if (name) {
        for (s = p; s < end;)
            *name++ = *s++;
        *name = '\0';
    }
    if (dir) {
        for (s = path; s < p;)
            *dir++ = *s++;
        *dir = '\0';
    }
}


int main(int argc, char *argv[]) {
    printf("VINE audiolib Tx Test\n");

    if (argc < 2) {
        printf("Usage: (Windows shell) > audiolib_test [input pcm file]\n");
        printf("   or  (bash)          $ ./audiolib_test [input pcm file]\n");
        return -1;
    }
    char *strInFile = argv[1];
    char drive[3];
    char dir[256];
    char fname[256];
    char ext[256];
    char strOutFile[1024];
    splitpath(strInFile, drive, dir, fname, ext);
    sprintf(strOutFile, "%s%s%s_out%s", drive, dir, fname, ext);
    
    short       inputBuffer[FRAME_SIZE];
   	short       outputBuffer[FRAME_SIZE];
   	int         isEnd = 0;
    int         szRead = 0;
	int         initResult = 0;
    int         i;
    FILE        *fidIn;
    FILE        *fidOut;
    
    // Init function
    initResult = VineInitAGC();

    if (initResult != 1) {
        printf("\nInitialization Error - exit(1)");
        exit(1);
    }
	fidIn = fopen(strInFile, "rb");
	if(fidIn==NULL){
	    printf("\nError in opening Tx input file - exit(1)");
	    exit(1);
	}
	
    fidOut = fopen(strOutFile, "wb"); 
    printf("Input file: %s\n", strInFile);
    printf("Output file: %s\n", strOutFile);

	// Processing block
	while(!isEnd) {
		szRead = fread(inputBuffer, sizeof(short), FRAME_SIZE, fidIn);
		
		if(szRead < FRAME_SIZE) {
			for(i = szRead; i < FRAME_SIZE; i++) {
				inputBuffer[i] = 0;
			}
			isEnd = 1;
		} 
		else {
            VineProcessAGC(inputBuffer, outputBuffer);
		}

		fwrite(outputBuffer, sizeof(short), FRAME_SIZE, fidOut);
	}	

	// End
    fclose(fidOut);
    fclose(fidIn);

    return 0;
}
