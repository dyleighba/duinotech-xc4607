#ifndef LEDMatrix_h
#define LEDMatrix_h

#include <TimerOne.h>

#include "Point.h"

#define MATRIX_WIDTH 16
#define BUFFER_SIZE MATRIX_WIDTH*2

struct LEDMatrix_PinSetup {
    char latch;  // LAT
    char clock;  // CLK
    char data;   // DI
    char enable; // G
    char a;      // A
    char b;      // B
    char c;      // C
    char d;      // D
};

class LEDMatrix {
    public:
        LEDMatrix(LEDMatrix_PinSetup pinSetup);
        void setPixel(Point p, bool state);
        bool getPixel(Point p);
        bool getShownPixel(Point p);
        void finishFrame();
    private:
        LEDMatrix_PinSetup pins;
        char *buffer;
        char activeBuffer;
        bool bufferSwapQueued;
        char currentDisplayRow;
        bool inBounds(Point p);
        void writeDisplayRow(char row);
        void writeDisplayInterrupt();
};

#endif