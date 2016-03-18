#pragma once

#include "ofMain.h"
#include "ofxCv.h"



class ofApp : public ofBaseApp{

	public:
    
        ofImage eyeDrawing;
        ofImage eye;
        ofImage grayEye, edgeEye, sobelEye, blurEye;
        ofImage grayDraw, edgeDraw, sobelDraw, blurDraw;
        ofImage cutDraw;
        int eucldist;
        
    
        ofxCv::ContourFinder contourFinderAverage, contourFinderCapture;
    
		void setup();
		void update();
		void draw();

};
