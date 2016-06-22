//
//  Modules.h
//  BassLive 2.0
//
//  Created by Bass Jansson on 16/11/15.
//
//

#ifndef Modules_h
#define Modules_h

#include "Module.hpp"
#include "BasicModules.hpp"

#define SAMPLERATE 48000
#define BUFFERSIZE 128

#define MAX_NUM_INPUTS 20

#define FADE_SIZE (SAMPLERATE / 200.0f) // 5 milliseconds

#define LATENCY_COMPENSATION (BUFFERSIZE * 2)

#define REAL 0
#define IMAG 1

#endif /* Modules_h */
