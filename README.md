# audiolib
VINE Audio Processing Library Standard Edition
<br/>
<br/>

# Features
Standard 버전에서는 AGC (Automaic Gain Control)기능을 제공합니다.
Audio PCM buffer interface가 제공되는 환경이면 본 프로젝트를 통해 AGC를 Intel x86/x64, ARM64, ARM32기반 등 다양한 플랫폼에 적용 가능합니다.

AGC는 Mic와 화자 간 거리에 따라 자동으로 송신음량을 최적화하는 기능입니다.

![AGC_IN_OUT](https://user-images.githubusercontent.com/75764437/142515569-30c9f4c5-b1ca-4668-93c7-e43e07bab56c.png)

마이크와 화자간의 거리가 멀어지면 음성신호의 크기가 줄어들어서 상대편에 작게 전달될 수가 있습니다.
AGC 기술을 통해 자동으로 적절한 음량으로 gain을 증가또는 감소시켜 전달 가능합니다. 이는 반대의 상황(마이크와 화자의 거리가 가까워져서 소리가 커지는 경우)에도 마찬가지로 적용됩니다.
<br/>
<br/>

# Library 적용 가이드

<br/>
AGC
AGC 는 초기화, 프로세싱 함수(8K, 16K)로 구성되어 있으며 별도의 종료함수가 없습니다.
프로세싱 함수는 매 프레임마다 호출되어야 하며, 압축이 해제된 PCM raw data를 프레임(20ms) 단위로 입력받습니다.
적용대상(오디오시스템 또는 앱)의 PCM buffer를 얻어오는 callback함수단에서 호출합니다.
   
1. 헤더파일과 바이너리 파일을 컴파일 환경에 추가
  (예: make, Android.bp 등)
	vine_audio.h, VineAGC.a

2. 소스코드에서 헤더파일 인클루드
	#include “vine_audio.h”

3. 라이브러리 제공기능 (Standard Edition v0.8)
	- AGC (Auto Gain Control): 통화중 송신음 음량 최적화

<br/>   
<br/>
<br/>

## API 호출 예제

1. 오디오시스템의 PCM Interface 초기화 부분에서 AGC 초기화 함수 호출
시스템의 초기화 함수 호출부에서 호출하여 주십시오.

```c
    vine_result vineResult;
    
    // agcBst: gain 상승 커브 파라미터 1~32767
    // agcLmt: gain 억제 파라미터 1~32767
    vineResult = VineInitAGC(agcBst, agcLmt);
    
    if(vineResult == vine_fail) {
    	PRINT_LOG("[VINE] Initialization failed");
    	return FALSE;
    } else {
    	PRINT_LOG("[VINE] Initialization success");
    }
```    
       
<br/>
<br/>

2. 오디오시스템 콜백함수에서 AGC 프로세싱 함수 호출 예제
   - 입력 pcm 프레임: txin
   - 출력 pcm 프레임: txout
   
```c
  boolean audiosys_postprocess(uint16* txin, uint16* txout)
  {
	  vine_result vineResult;

	  vineResult = VineProcessAGC(txin, txout);
	  if(vcresult == vine_fail) {
  		return FALSE;
  	}
  	// Print tuning Message for AGC
  	PRINT_LOG("[VINE AGC] %d, vineResult);

  	return TRUE;    
  }
```
<br/>
<br/>

# License

[![License: LGPL v2.1](https://img.shields.io/badge/License-LGPL_v2.1-blue.svg)](https://www.gnu.org/licenses/lgpl-2.1)

<br/>
<br/>

# Copyright
Copyright (c) 2021, THE VINE CORPORATION All right reserved.
