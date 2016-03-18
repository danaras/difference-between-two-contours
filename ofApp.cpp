#include "ofApp.h"

using namespace ofxCv;
using namespace cv;
//--------------------------------------------------------------
void ofApp::setup(){
    contourFinderAverage.setMinAreaRadius(50);
    contourFinderAverage.setMaxAreaRadius(200);
    contourFinderCapture.setMinAreaRadius(50);
    contourFinderCapture.setMaxAreaRadius(200);
    eyeDrawing.load("images/eye2.jpg");
    eyeDrawing.resize(500,250);
    eye.load("images/eye.jpg");
    eye.resize(500,250);
    
    
    cout << eyeDrawing.getWidth()<<" "<< eyeDrawing.getHeight() << endl;

}

//--------------------------------------------------------------
void ofApp::update(){
    contourFinderAverage.setThreshold(8);
    
    
    contourFinderCapture.setThreshold(8);
    convertColor(eye, grayEye, CV_RGB2GRAY);
    convertColor(eyeDrawing, grayDraw, CV_RGB2GRAY);
    
    Sobel(grayEye, sobelEye);
    Sobel(grayDraw, sobelDraw);
   
    
    grayEye.update();
    sobelEye.update();
    grayDraw.update();
    sobelDraw.update();
  
    
    int wDraw = sobelDraw.getWidth();
    int hDraw = sobelDraw.getHeight();
    int iDraw = 0;
    
    int wCapture = sobelEye.getWidth();
    int hCapture = sobelEye.getHeight();
    int iCapture = 0;
    
    

    auto& averagePixels = sobelDraw.getPixels();
    auto& capturePixels = sobelEye.getPixels();
//    ofLog() << sobelDraw.getPixels().getNumChannels() << endl;
//    ofLog() << sobelDraw.getWidth() << ',' << sobelDraw.getHeight() << endl;
    

    for(int y = 0; y < hDraw; y++){
        for(int x = 0; x < wDraw; x++){
            unsigned char brightness = averagePixels[iDraw];
            if(brightness > 10){
                averagePixels[iDraw] = brightness + 70;
            }
            iDraw += 1;
          //ofLog() << "here1" << endl;
        }
    }
    
    for(int y = 0; y < hCapture; y++){
        for(int x = 0; x < wCapture; x++){
            unsigned char brightness = capturePixels[iCapture];
            if(brightness > 10){
                capturePixels[iCapture] = brightness + 70;
            }
            iCapture += 1;
            //ofLog() << "here2" << endl;
            
        }
    }
    //ofLog() << "here3" << endl;
    sobelDraw.update();
    sobelEye.update();
    blur(sobelDraw, blurDraw, 10);
    blur(sobelEye, blurEye, 10);
    blurDraw.update();
    blurEye.update();
    
    vector<int> vAverage;
    
//    for (int i = 0; i <20; i++){
//        contourFinderAverage.setThreshold(i);
//        vAverage[i] = contourFinderAverage.;
//        
//        
//    }
    
    contourFinderAverage.findContours(blurDraw);
    contourFinderCapture.findContours(blurEye);
//ofLog() << "here4" << endl;
    
    
    
   ofLog() << "Center: " << contourFinderAverage.getCenter(0) << " Width: " << contourFinderAverage.getBoundingRect(0).width << endl;
   blurDraw.crop(contourFinderAverage.getBoundingRect(0).x, contourFinderAverage.getBoundingRect(0).y, contourFinderAverage.getBoundingRect(0).width, contourFinderAverage.getBoundingRect(0).height);
   blurEye.crop(contourFinderCapture.getBoundingRect(0).x, contourFinderCapture.getBoundingRect(0).y, contourFinderCapture.getBoundingRect(0).width, contourFinderCapture.getBoundingRect(0).height);
    blurDraw.resize(500, 250);
    blurEye.resize(500, 250);
    


    

}

//--------------------------------------------------------------
void ofApp::draw(){
    blurDraw.draw(5, 5);
    blurEye.draw(5, blurDraw.getHeight()+10);
    
    //contourFinderAverage.draw();

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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
