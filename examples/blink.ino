#include <duinotech-xc4607.h>

LEDMatrix::PinSetup pinSetup = {
    9, 8, 7, 6, 5, 4, 3, 2
};

void setup() {
    pinMode(LED_BUILTIN, OUTPUT);
    
    Serial.begin(9600);
    LEDMatrix::init(pinSetup);
    
    LEDMatrix::setPixel(LEDMatrix::Point{2, 2}, false);
    
    LEDMatrix::setPixel(LEDMatrix::Point{5, 7}, false);
    
    Serial.write("Begin test");
    Serial.write(LEDMatrix::getPixel(LEDMatrix::Point{1, 1}));
    Serial.write(LEDMatrix::getPixel(LEDMatrix::Point{2, 2}));
    Serial.write(LEDMatrix::getPixel(LEDMatrix::Point{5, 7}));
    Serial.write("End test"); 
    
    LEDMatrix::finishFrame();
    digitalWrite(LED_BUILTIN, HIGH);
   
}

void loop() {
    
}