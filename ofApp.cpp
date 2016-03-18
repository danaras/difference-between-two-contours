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
    eye.load("images/eye.jpg");
    
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
    
    //adjust the brightness for each image
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
        }
    }
    
    //apply sobel and blur
    sobelDraw.update();
    sobelEye.update();
    blur(sobelDraw, blurDraw, 10);
    blur(sobelEye, blurEye, 10);
    blurDraw.update();
    blurEye.update();
    

    //find contours of the images and crop the images to the bounding boxes of the contours
    contourFinderAverage.findContours(blurDraw);
    contourFinderCapture.findContours(blurEye);

    blurDraw.crop(contourFinderAverage.getBoundingRect(0).x, contourFinderAverage.getBoundingRect(0).y, contourFinderAverage.getBoundingRect(0).width, contourFinderAverage.getBoundingRect(0).height);
    blurEye.crop(contourFinderCapture.getBoundingRect(0).x, contourFinderCapture.getBoundingRect(0).y, contourFinderCapture.getBoundingRect(0).width, contourFinderCapture.getBoundingRect(0).height);
    blurDraw.resize(500, 250);
    blurEye.resize(500, 250);
    
    //compare two images by calculating an euclidian distance among pixels of the two images
    auto& compareAveragePixels =blurDraw.getPixels();
    auto& compareCapturePixels =blurEye.getPixels();
    int pixelNumber =0;
    vector<int> squaredDifference;
    for(int y = 0; y < 250; y++){
        for(int x = 0; x < 500; x++){
            signed char difference = compareAveragePixels[pixelNumber] - compareCapturePixels[pixelNumber];
            squaredDifference.push_back(difference * difference);
            pixelNumber += 1;
        }
    }
    eucldist = 0;
    for(int i = 0; i<squaredDifference.size(); i++){
        eucldist += squaredDifference[i];
        
    }
    eucldist = sqrt(eucldist);
    
}

//--------------------------------------------------------------
void ofApp::draw(){
     ofBackground(255, 255, 255);
    eyeDrawing.resize(500,250);
    eye.resize(500,250);
    eyeDrawing.draw(5, 5);
    eye.draw(5, 10 + eye.getHeight());
    blurDraw.draw(10 + eye.getWidth(), 5);
    blurEye.draw(10 + eye.getWidth(), 10 + eye.getHeight());
    ofSetColor(0, 0, 0);
    ofDrawRectangle(5, 5, 140, 22);
    ofSetColor(255, 255, 255);
    ofDrawBitmapString("Difference: " + ofToString(eucldist), 10, 20);//easiest way to put text on the screen
  

}

