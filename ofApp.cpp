/************************************************************
************************************************************/
#include "ofApp.h"


/************************************************************
************************************************************/

//--------------------------------------------------------------
void ofApp::setup(){
	/********************
	********************/
	ofSetWindowTitle( "TEST" );
	ofSetWindowShape( 1280, 720 );
	
	ofSetVerticalSync(true);
	ofSetFrameRate(60);
	ofSetEscapeQuitsApp(false);

	/********************
	********************/
	img.load("stage.jpg");
	
	/********************
	p1	p2
	p0	p3
	********************/
	gui.setup();
	
	/* */
	{
		GG_ImageVert.setup("Image vert");
		
		const float w_max = 1280/2;
		const float h_max = 720/2;
		const float depthSize = 100;
		
		ofVec3f point_max = ofVec3f(w_max, h_max, depthSize);
		ofVec3f point_min = ofVec3f(-w_max, -h_max, -depthSize);
		
		ofVec3f point_init = ofVec3f(-w_max, -h_max, 0);
		GG_ImageVert.add(p[0].setup("p0", point_init, point_min, point_max));
		
		point_init = ofVec3f(-w_max, h_max, 0);
		GG_ImageVert.add(p[1].setup("p1", point_init, point_min, point_max));
		
		point_init = ofVec3f(w_max, h_max, 0);
		GG_ImageVert.add(p[2].setup("p2", point_init, point_min, point_max));
		
		point_init = ofVec3f(w_max, -h_max, 0);
		GG_ImageVert.add(p[3].setup("p3", point_init, point_min, point_max));
		
		gui.add(&GG_ImageVert);
	}
	
	/* */
	{
		GG_Cam.setup("camera");
		
		{
			float _pos_max = 1000;
			
			ofVec3f PosMax = ofVec3f(_pos_max, _pos_max, _pos_max);
			ofVec3f PosMin = ofVec3f(-_pos_max, -_pos_max, -_pos_max);
			ofVec3f PosInit = ofVec3f(0, 0, 1000);
	
			GG_Cam.add(CamPosition.setup("pos", PosInit, PosMin, PosMax));
		}
		{
			float _pos_max = 1000;
			
			ofVec3f PosMax = ofVec3f(_pos_max, _pos_max, _pos_max);
			ofVec3f PosMin = ofVec3f(-_pos_max, -_pos_max, -_pos_max);
			ofVec3f PosInit = ofVec3f(0, 0, 0);

			GG_Cam.add(CamLookAt.setup("LookAt", PosInit, PosMin, PosMax));
		}
		{
			ofVec3f DirMax = ofVec3f(1, 1, 1);
			ofVec3f DirMin = ofVec3f(-1, -1, -1);
			ofVec3f DirInit = ofVec3f(0, 1, 0);
	
			GG_Cam.add(CamUpper.setup("Upper", DirInit, DirMin, DirMax));
		}
		{
			GG_Cam.add(CamAngle.setup("angle", 60, 10, 120));
		}
		
		gui.add(&GG_Cam);
	}
	
	/********************
	********************/
	for(int i = 0; i < NUM_POINTS; i++){
		Verts[i].set(p[i]);
		Color[i].set(1.0, 1.0, 1.0, 1.0);
	}
	TexCoord[0].set(0, img.getHeight());
	TexCoord[1].set(0, 0);
	TexCoord[2].set(img.getWidth(), 0);
	TexCoord[3].set(img.getWidth(), img.getHeight());
	
	Vbo.setVertexData(Verts, NUM_POINTS, GL_DYNAMIC_DRAW);
	Vbo.setColorData(Color, NUM_POINTS, GL_DYNAMIC_DRAW);
	Vbo.setTexCoordData(TexCoord, NUM_POINTS, GL_DYNAMIC_DRAW);  
}

//--------------------------------------------------------------
void ofApp::update(){
	/********************
	********************/
	glDisable(GL_CULL_FACE);
	
	for(int i = 0; i < NUM_POINTS; i++){
		Verts[i].set(p[i]);
		Color[i].set(1.0, 1.0, 1.0, 1.0);
	}
	Vbo.updateVertexData(Verts, NUM_POINTS);
	// Vbo.updateColorData(Color, NUM_POINTS);
	Vbo.updateTexCoordData(TexCoord, NUM_POINTS);
	
	/********************
	********************/
	cam.setPosition(CamPosition);
	cam.lookAt( CamLookAt, CamUpper);
	cam.setFov(CamAngle);
	
	cam.setNearClip(1);
	cam.setFarClip(2000);
}

//--------------------------------------------------------------
void ofApp::draw(){
	/********************
	********************/
	ofBackground(0);
	ofPushStyle();

	/********************
	Z-buffering and blemding mode do not work together properly in a simple way.
	(oF Essentials. p98)
	
	参考URL
		https://www.sjbaker.org/steve/omniv/alpha_sorting.html
	********************/
	// z buffering
	ofDisableAlphaBlending();
	ofEnableDepthTest();
	
	/*
	// Alpha
	ofEnableAlphaBlending();
	// ofEnableBlendMode(OF_BLENDMODE_ADD);
	ofEnableBlendMode(OF_BLENDMODE_ALPHA);
	*/
	
	/********************
	********************/
	ofSetColor(255);
	
	/********************
	in case of ofFbo
		fbo_src->getTextureReference().bind();
	********************/
	// EasyCam.begin();
	cam.begin();
	
	Vbo.bind();
	img.bind();
	Vbo.draw(GL_QUADS, 0, NUM_POINTS);
	img.unbind();
	Vbo.unbind();
	
	cam.end();
	// EasyCam.end();
	
	ofPopStyle();
	
	ofDisableDepthTest();
	
	/********************
	********************/
	gui.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	switch(key){
		case ' ':
		{
			ofImage image;
			image.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
			image.saveImage("screen.png");
			
			printf("save image\n");
		}
			break;
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
