#include "testApp.h"



//--------------------------------------------------------------
void testApp::setup(){
    

    
    ofSetVerticalSync(true);
    ofSetFrameRate(60);
    ofSetLogLevel(OF_LOG_NOTICE);
    
    
    ofLog(OF_LOG_NOTICE, "setup...");
	app = new entreTempsApp();
    app->setup();
    
    
   
    
}

//--------------------------------------------------------------
void testApp::update(){
    app->update();
}

//--------------------------------------------------------------
void testApp::draw(){
	
	
	ofBackgroundHex(0x000000, 1);
    app->draw();

}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    
    
    if ( key == 'f' ) {
            
        ofToggleFullscreen();
    
    }
    
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