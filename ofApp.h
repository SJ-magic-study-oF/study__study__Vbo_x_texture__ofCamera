/************************************************************
************************************************************/
#pragma once

/************************************************************
************************************************************/
#include "ofMain.h"
#include "ofxGui.h"

/************************************************************
************************************************************/

/**************************************************
**************************************************/
class ofApp : public ofBaseApp{
private:
	/****************************************
	****************************************/
	enum{
		NUM_POINTS = 4,
	};
	
	/****************************************
	****************************************/
	ofVbo Vbo;
	ofVec3f Verts[NUM_POINTS];
	ofVec2f TexCoord[NUM_POINTS];
	ofFloatColor Color[NUM_POINTS];
	
	ofEasyCam EasyCam;
	ofCamera cam;
	
	ofImage img;
	
	/********************
	********************/
	ofxPanel gui;
	
	ofxGuiGroup GG_ImageVert;
	ofxVec3Slider p[NUM_POINTS];
	
	ofxGuiGroup GG_Cam;
	ofxVec3Slider CamPosition;
	ofxVec3Slider CamLookAt;
	ofxVec3Slider CamUpper;
	ofxFloatSlider CamAngle;
	
	
	
public:
	/****************************************
	****************************************/
	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);
	
};
