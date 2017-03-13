/*
 OpenGL TileSaving C++ Library for OpenFrameworks
 http://www.openframeworks.cc

 Copyright (c) 2009 by Matthias Dörfelt & Jeremy Rotsztain

 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation; either version 2 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */
#ifndef _OFX_TILE_SAVER_IMAGE_
#define _OFX_TILE_SAVER_IMAGE_


#include "ofMain.h"
#include "ofImage.h"


class ofxTileSaverImage : public ofImage {

public:

    virtual ~ofxTileSaverImage(){}
    ofxTileSaverImage(){}
    void init(unsigned int _rows, unsigned int _cols, unsigned int _colWidth, unsigned int _rowHeight);
    void addPixels(int x_, int y_, ofPixels& screenPixels);
    void done(string fileName, bool _flipY);
    void flipY();

    unsigned int rows, columns;
    unsigned int colWidth, rowHeight;
    unsigned int width, height;

    ofPixels bigImagePixels;

};

#endif

