#ifndef BufferedFrame_h
#define BufferedFrame_h

#include "Constants.h"
#include "Point.h"



namespace LEDMatrix {

    struct PixelIndex {
        byte byteIndex;
        byte bitIndex;
    };

    class BufferedFrame {
        public:
            byte *backbuffer;
            byte *frontbuffer;

            BufferedFrame() {
                swapBuffers();
            };

            void setPixel(Point p, bool state) {
                PixelIndex index = pointToPixelIndex(p);
                byte pixelMask = 1 << index.bitIndex;
                backbuffer[index.byteIndex] = backbuffer[index.byteIndex] & ~pixelMask;
                if (state) {
                    backbuffer[index.byteIndex] = backbuffer[index.byteIndex] | pixelMask;
                }
            }

            bool getPixel(Point p) {
                PixelIndex index = pointToPixelIndex(p);
                return (bool)((backbuffer[index.byteIndex] >> index.bitIndex) & 1);
            }

            bool getFrontPixel(Point p) {
                PixelIndex index = pointToPixelIndex(p);
                return (bool)((frontbuffer[index.byteIndex] >> index.bitIndex) & 1);
            }

            void swapBuffers() {
                byte frontBufferIndex = bufferInUse;
                bufferInUse = (bufferInUse + 1) % 2;
                backbuffer = bufferBytes+(LEDMATRIX_BUFFER_SIZE * bufferInUse);
                frontbuffer = bufferBytes+(LEDMATRIX_BUFFER_SIZE * frontBufferIndex);
            }

            void clearBackbuffer() {
                for (byte i=0; i<LEDMATRIX_BUFFER_SIZE; i++) {
                    backbuffer[i] = 0x0;
                }
            }

            PixelIndex pointToPixelIndex(Point p) {
                PixelIndex pi;
                pi.bitIndex = p.x % 8;
                pi.byteIndex = ( p.y*2 ) + ( pi.bitIndex > 0.5 );
                return pi;
            };

        private:
            byte bufferBytes[LEDMATRIX_BUFFER_SIZE*2];
            byte bufferInUse;
    };
};

#endif