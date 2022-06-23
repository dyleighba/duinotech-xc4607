#ifndef BufferedFrame_h
#define BufferedFrame_h

#define LEDMATRIX_BUFFER_SIZE LEDMATRIX_WIDTH * 2

#include "LEDMatrix.h"
#include "Point.h"



namespace LEDMatrix {
    typedef byte buffer[LEDMATRIX_BUFFER_SIZE];

    struct PixelIndex {
        byte byteIndex;
        byte bitIndex;
    };

    class BufferedFrame {
        public:
            BufferedFrame();
            void setPixel(Point p, bool state);
            bool getPixel(Point p);
            bool getFrontPixel(Point p);
            void swapBuffers();
            void clearBackbuffer();
            void pointToPixelIndex(Point p);
            buffer &backbuffer;
            buffer &frontbuffer;
        private:
            byte buffer[LEDMATRIX_BUFFER_SIZE*2];
            byte bufferInUse;
    };
};

#endif