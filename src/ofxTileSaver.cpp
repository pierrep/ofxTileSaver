#include "ofxTileSaver.h"

void ofxTileSaver::init(int _steps, int _border, bool _bBigImage)
{
	steps = _steps;
	currentRow = 0;
	currentCol = 0;
	border = _border;
	float width = ofGetWidth();
	float height = ofGetHeight();

	tileWidth = width;
	tileHeight = height;

	tileWidthNoBorder = width-border*2;
	tileHeightNoBorder = height-border*2;

	imageWidth = tileWidthNoBorder*steps;
	imageHeight = tileHeightNoBorder*steps;

	bGoTiling = false;
	bFlipY = false;
	bBigImage = _bBigImage;

	currentTile = 0;

	float halfFov, theTan, screenFov, aspect;
	screenFov 		= 60.0f;

	float eyeX 		= (float)width / 2.0;
	float eyeY 		= (float)height / 2.0;
	halfFov 		= PI * screenFov / 360.0;
	theTan 			= tanf(halfFov);
	float dist 		= eyeY / theTan;
	float nearDist 	= dist / 10.0;	// near / far clip plane
	float farDist 	= dist * 10.0;
	aspect 			= (float)width/(float)height;

	ofVec3f eyeHolder, posHolder, upHolder;
	posHolder.set(eyeX, eyeY, dist);
	eyeHolder.set(eyeX, eyeY, 0.0);
	upHolder.set(0,1,0);
	setPerspectiveData(screenFov, aspect, nearDist, farDist);
	setCameraData( posHolder, eyeHolder, upHolder);
}

//setup perspective and Camera, if done, safe Image
void ofxTileSaver::begin()
{
	if(!bGoTiling)
		return;
	if(currentRow == steps){

		if(bBigImage)
			final.done(fileName, bFlipY);

		setPerspective();
		positionCamera();
		ofSetOrientation(ofGetOrientation(), true);
		bGoTiling = false;
		currentTile = 0;
		return;
	}


	ofSetOrientation(ofGetOrientation(), false);
	setFrustum(currentCol, currentRow);
	positionCamera();
}

//grab FrameBuffer and ddd it to the Image or save the tile right away
void ofxTileSaver::end()
{
	if(!bGoTiling)
		return;

	current.grabScreen(border, border, tileWidthNoBorder, tileHeightNoBorder);
	if(!bBigImage){
		current.save(ofToString(currentTile)+".png");
	} else {
		final.addPixels(currentRow, currentCol, current.getPixels());
	}
	if(currentCol==steps-1){
		currentCol = 0;
		currentRow++;
	} else {
		currentCol++;
	}
	currentTile++;
}

//this starts the saving Process
void ofxTileSaver::finish(string _fileName, bool _bFlipY)
{
	if(bBigImage)
		final.init(steps, steps, tileWidthNoBorder, tileHeightNoBorder);
	bGoTiling = true;
	currentCol = 0;
	currentRow = 0;
	fileName = _fileName;
	bFlipY = _bFlipY;
}

//Camera Stuff
void ofxTileSaver::setPerspectiveData(float _fov, float _aspect, float _nearZ, float _farZ)
{
	fov = _fov;
	aspect = _aspect;
	nearZ = _nearZ;
	farZ = _farZ;
	float Top = nearZ * tan(fov * PI / 360.0);
	float Bottom = -Top;

	float Left = Bottom * aspect;
	float Right = Top * aspect;
	float Near = nearZ;
	float Far = farZ;

	curFrustum.set(Left, Right, Bottom, Top, Near, Far);
}

void ofxTileSaver::setCameraData(ofVec3f _pos, ofVec3f _eye, ofVec3f _up)
{
	pos = _pos;
	eye = _eye;
	up = _up;
}

void ofxTileSaver::setPerspective()
{
	ofSetupScreenPerspective(ofGetWidth(), ofGetHeight(), fov, nearZ, farZ);
}

void ofxTileSaver::positionCamera()
{
	ofSetMatrixMode(OF_MATRIX_MODELVIEW);
	ofLoadIdentityMatrix();
	ofMatrix4x4 m;
	m.makeLookAtViewMatrix(pos, eye, up);
	ofLoadMatrix(m);
}

//this is the important part, the Frustum gets setup correctly so we can tile perfectly
void ofxTileSaver::setFrustum(int _row, int _col)
{
	float Top = nearZ * tan(fov * PI / 360.0);
	float Bottom = -Top;

	float Left = Bottom * aspect;
	float Right = Top * aspect;
	float Near = nearZ;
	float Far = farZ;

	float left   = Left + (((Right - Left) * (_col * tileWidthNoBorder-border)) / imageWidth);
	float right  = left + (((Right - Left) * tileWidth) / imageWidth);
	float bottom = Bottom + (Top - Bottom) * ((steps-1-_row)* tileHeightNoBorder-border) / imageHeight;
	float top    = bottom + (((Top - Bottom) * tileHeight) / imageHeight);

	ofViewport(0, 0, tileWidth, tileHeight);

	ofSetMatrixMode(OF_MATRIX_PROJECTION);
	ofLoadIdentityMatrix();

	// this is strange but we need it
	float diff = 0;

	curFrustum.set(left, right, bottom+diff, top+diff, Near, Far);

	ofMatrix4x4 m;
	m.makeFrustumMatrix(left, right, bottom+diff, top+diff, Near, Far);
	ofLoadMatrix(m);
}
	
	
