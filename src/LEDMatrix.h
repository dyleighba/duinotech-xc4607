#ifndef LEDMatrix_h
#define LEDMatrix_h

#define LEDMATRIX_WIDTH 16

#include "BufferedFrame.h"
#include "PinSetup.h"
#include "Point.h"

#include <TimerOne.h>

namespace LEDMatrix {
    typedef byte byterow[2];

    static PinSetup pins;
    static BufferedFrame bufferedFrame;
    
    bool bufferSwapQueued;
    byte currentRow;

    void init(PinSetup pinSetup) {
        pins = pinSetup;
        pinMode(pins.latch, OUTPUT);
        pinMode(pins.clock, OUTPUT);
        pinMode(pins.data, OUTPUT);
        pinMode(pins.enable, OUTPUT);
        pinMode(pins.a, OUTPUT);
        pinMode(pins.b, OUTPUT);
        pinMode(pins.c, OUTPUT);
        pinMode(pins.d, OUTPUT);
        digitalWrite(pins.latch, HIGH);
        Timer1.initialize(1000);
        Timer1.attachInterrupt(hardwareInterrupt);
    }

    void setPixel(Point p, bool state) {
        bufferedFrame.setPixel(p, state);
    }

    bool getPixel(Point p) {
        return bufferedFrame.getPixel(p);
        
    }

    bool getShownPixel(Point p) {
        return bufferedFrame.getFrontPixel(p);
    }

    void finishFrame() {
        bufferSwapQueued = true;
        while (bufferSwapQueued);
    }
    
    void clearFrame() {
        for (byte i=0; i<LEDMATRIX_BUFFER_SIZE; i++) {
            bufferedFrame.backbuffer[i] = 0x0;
        }
    }

    bool inBounds(Point p) {
        return
            p.x < LEDMATRIX_WIDTH && p.y < LEDMATRIX_WIDTH &&
            p.x >= 0 && p.y >= 0;
    }

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