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
    
    BufferedFrame bufferedFrame;
    bool bufferSwapQueued;
    byte currentRow;

    void init(PinSetup pinSetup) {
        Timer1.initialize(1000);
        Timer1.attachInterrupt(hardwareInterrupt);
    }

    void setPixel(Point p, bool state);
    bool getPixel(Point p);
    bool getShownPixel(Point p);
    void finishFrame();
    void clearFrame();
    bool inBounds(Point p);

    void bitShiftToMatrix(byterow bytes) {
        digitalWrite(pins.enable, HIGH);
        digitalWrite(pins.a,  currentRow & 1);
        digitalWrite(pins.b, (currentRow >> 1) & 1);
        digitalWrite(pins.c, (currentRow >> 2) & 1);
        digitalWrite(pins.d, (currentRow >> 3) & 1);
        digitalWrite(pins.latch, LOW);
        shiftOut(pins.data, pins.clock, LSBFIRST, bytes[0]);
        shiftOut(pins.data, pins.clock, LSBFIRST, bytes[1]);
        digitalWrite(pins.latch, HIGH);
        digitalWrite(pins.enable, LOW);
    }

    void hardwareInterrupt() {
        if (currentRow == 0 && bufferSwapQueued) {
            bufferedFrame.swapBuffers();
        }
        byte index = currentRow*2;
        byterow row = {bufferedFrame.frontbuffer[index], bufferedFrame.frontbuffer[index+1]};
        bitShiftToMatrix(row);
        currentRow = (currentRow + 1) % LEDMATRIX_WIDTH;
    }
}

#endif