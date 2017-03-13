#pragma once

#include "ofMain.h"
#include "ofxTileSaverImage.h"


struct ofxFrustumData{
	void set(float _left, float _right, float _bottom, float _top, float _near, float _far){
		left = _left;
		right = _right;
		bottom = _bottom;
		top = _top;
		near = _near;
		far = _far;
	}
	float left, right, bottom, top, near, far;
};

class ofxTileSaver {

public:

	ofxTileSaver(){}
	~ofxTileSaver(){
		cleanUp();
	}
	
	void init(int _steps, int _border, bool _bBigImage);	
	void begin();
	void end();
	void finish(string _fileName, bool _bFlipY);
	void setPerspectiveData(float _fov, float _aspect, float _nearZ, float _farZ);
	void setCameraData(ofVec3f _pos, ofVec3f _eye, ofVec3f _up);
	void setPerspective();
	void positionCamera();
	void setFrustum(int _row, int _col);	

	ofxFrustumData getCurFrustum(){
		return curFrustum;
	}

	int getCurCol(){
		return currentCol;
	}

	int getCurRow(){
		return currentRow;
	}

	void cleanUp(){
		final.clear();
		current.clear();
	}

	float aspect, fov, nearZ, farZ, imageWidth, imageHeight, tileHeight, tileWidth, tileWidthNoBorder, tileHeightNoBorder;
	int steps, currentRow, currentCol, border, currentTile;

	ofxTileSaverImage final;
	ofImage current;

	ofxFrustumData curFrustum;

	string fileName;

	bool bGoTiling, bFlipY, bBigImage;
	ofVec3f pos, eye, up;
};
