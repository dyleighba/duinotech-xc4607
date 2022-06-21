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
}

void LEDMatrix::setPixel(Point p, bool state) {

}

bool LEDMatrix::getPixel(Point p) {

}

bool LEDMatrix::getShownPixel(Point p) {

}

void LEDMatrix::finishFrame() {

}
