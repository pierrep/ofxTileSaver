#include "ofxTileSaverImage.h"

void ofxTileSaverImage::init(unsigned int _rows, unsigned int _cols, unsigned int _colWidth, unsigned int _rowHeight)
{

    rows = _rows;
    columns = _cols;

    colWidth = _colWidth;
    rowHeight = _rowHeight;

    width = colWidth * rows;
    height = rowHeight * columns;

    bigImagePixels.allocate(width, height,3);
    allocate(width, height, OF_IMAGE_COLOR);

    bUseTexture = false;
}


void ofxTileSaverImage::addPixels(int x_, int y_, ofPixels& screenPixels)
{

    unsigned int startX = x_ * colWidth;
    unsigned int startY = y_ * rowHeight;

    for(unsigned int x=0; x<colWidth; x++){
        for(unsigned int y=0; y<rowHeight; y++){

            unsigned long srcPos = ((y * colWidth) + x) * 3;
            unsigned long dstPos = (((y + startY) * width) + x + startX) * 3;

            bigImagePixels[dstPos] = screenPixels[srcPos];
            bigImagePixels[dstPos+1] = screenPixels[srcPos+1];
            bigImagePixels[dstPos+2] = screenPixels[srcPos+2];
        }
    }
}

void ofxTileSaverImage::done(string fileName, bool _flipY)
{
    //setFromPixels(bigImagePixels, width, height, OF_IMAGE_COLOR);
    setFromPixels(bigImagePixels);
    if(_flipY)
         flipY();
    save(fileName);
    clear();
}

void ofxTileSaverImage::flipY()
{
    mirror(true, false);
}
