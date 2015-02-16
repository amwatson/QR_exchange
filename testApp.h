#pragma once

#include "ofMain.h"
#include "ofxZxing.h"
#include "ofxCurl.h"

#define SCREEN_W 1280
#define SCREEN_H 960

class testApp : public ofBaseApp {
public:
	void setup();
	void update();
	void draw();
    void keyReleased(int key);
	
	ofxZxing::Result result;
	ofImage logo;
	ofVideoGrabber cam;
	float lastFound;
    
    ofDirectory *dir;
};
