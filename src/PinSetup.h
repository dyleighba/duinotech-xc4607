#ifndef PinSetup_h
#define PinSetup_h

namespace LEDMatrix {
    struct PinSetup {
        byte latch;  // LAT
        byte clock;  // CLK
        byte data;   // DI
        byte enable; // G
        byte a;      // A
        byte b;      // B
        byte c;      // C
        byte d;      // D
    };
}

#endif