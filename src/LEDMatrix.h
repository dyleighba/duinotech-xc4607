#ifndef LEDMatrix_h
#define LEDMatrix_h

#include <TimerOne.h>

#include "Point.h"

#define MATRIX_WIDTH 16
#define BUFFER_SIZE MATRIX_WIDTH*2

struct LEDMatrix_PinSetup {
    byte latch;  // LAT
    byte clock;  // CLK
    byte data;   // DI
    byte enable; // G
    byte a;      // A
    byte b;      // B
    byte c;      // C
    byte d;      // D
};


LEDMatrix matrixInterruptTarget;

class LEDMatrix {
    public:
        LEDMatrix(LEDMatrix_PinSetup pinSetup);
        void setPixel(Point p, bool state);
        bool getPixel(Point p);
        bool getShownPixel(Point p);
        void finishFrame();
        void clearFrame();
        static void hardwareInterrupt();
    private:
        LEDMatrix_PinSetup pins;
        byte *buffer;
        byte activeBuffer;
        bool bufferSwapQueued;
        byte currentDisplayRow;
        bool inBounds(Point p);
        void writeMatrixRow();
};

#endif