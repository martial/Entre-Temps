#include "testApp.h"



//--------------------------------------------------------------
void testApp::setup(){
    
    //ofSetBackgroundAuto(true);
    //ofBackgroundHex(0x000000);
    //ofSetVerticalSync(true);
    ofSetFrameRate(60);
    ofLogLevel(OF_LOG_NOTICE);
     ofLog(OF_LOG_NOTICE, "setup...");
	app = new entreTempsApp();
    app->setup();
    
    
   
    
}

//--------------------------------------------------------------
void testApp::update(){
    app->update();
    ofLog(OF_LOG_NOTICE, "updateing...");
}

//--------------------------------------------------------------
void testApp::draw(){
	
	
	ofBackgroundHex(0x000000, 1);
	
     ofLog(OF_LOG_NOTICE, "draw...");
    app->draw();
    
    ofSetColor(255,0,0);
   // ofRect(c++,0,10,10);
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 
    
}