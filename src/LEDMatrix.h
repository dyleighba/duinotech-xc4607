#ifndef LEDMatrix_h
#define LEDMatrix_h

#include "Point.h"

#define MATRIX_LENGTH 32

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
    private:
        LEDMatrix_PinSetup pins;
        char *buffer;
        char activeBuffer;
    public:
        LEDMatrix(LEDMatrix_PinSetup pinSetup);
        void setPixel(Point p, bool state);
        bool getPixel(Point p);
        bool getShownPixel(Point p);
        void finishFrame();
};

#endif