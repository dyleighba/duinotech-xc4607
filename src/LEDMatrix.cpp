#include "LEDMatrix.h"

LEDMatrix::LEDMatrix(LEDMatrix_PinSetup pinSetup) {
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

    // frontbuffer and backbuffer setup
    buffer = (byte*) malloc(sizeof(byte) * BUFFER_SIZE * 2);

    // TODO make LEDMatrix a singleton
    if (!matrixInterruptTarget) {
        matrixInterruptTarget = this;
        Timer1.initialize(1000);
        Timer1.attachInterrupt(LEDMatrix::hardwareInterrupt);
    } else {
        delete(this);
    }
}

void LEDMatrix::setPixel(Point p, bool state) {

}

bool LEDMatrix::getPixel(Point p) {

}

bool LEDMatrix::getShownPixel(Point p) {

}

void LEDMatrix::finishFrame() {
    bufferSwapQueued = true;
}

void LEDMatrix::clearFrame() {

}

void LEDMatrix::hardwareInterrupt() {
    
}

bool LEDMatrix::inBounds(Point p) {
    return
        p.x < MATRIX_WIDTH && p.y < MATRIX_WIDTH &&
        p.x >= 0 && p.y >= 0;
}

void LEDMatrix::writeMatrixRow() {
    if (bufferSwapQueued && currentDisplayRow == 0) {
        activeBuffer = ( activeBuffer + 1 ) % 2;
    }
    // HW signalling goes here
}