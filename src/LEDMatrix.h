#ifndef LEDMatrix_h
#define LEDMatrix_h

#define LEDMATRIX_WIDTH 16

#include "BufferedFrame.h"
#include "PinSetup.h"
#include "Point.h"

#include <TimerOne.h>

namespace LEDMatrix {
    typedef byte byterow[2];

    const PinSetup pins;
    const BufferedFrame bufferedFrame;
    
    bool bufferSwapQueued;

    void init(PinSetup pinSetup);
    void setPixel(Point p, bool state);
    bool getPixel(Point p);
    bool getShownPixel(Point p);
    void finishFrame();
    void clearFrame();
    bool inBounds(Point p);
    void bitShiftToMatrix(byterow bytes);
    void hardwareInterrupt();
}

#endif