#include "testApp.h"



//--------------------------------------------------------------
void testApp::setup(){
    

    
    ofSetVerticalSync(true);
    ofSetFrameRate(60);
    ofSetLogLevel(OF_LOG_NOTICE);
    
	app = new entreTempsApp();
    app->setup();
    
    ofHideCursor();
   
    
}

//--------------------------------------------------------------
void testApp::update(){
    app->update();
}

//--------------------------------------------------------------
void testApp::draw(){
	
	// do it!
	ofBackgroundHex(0x000000, 1);
    app->draw();

}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    
    
    if ( key == 'f' ) {
        ofToggleFullscreen();    
    }
    
    if ( key == 'd' ) {
        app->bDrawDebug = !app->bDrawDebug;  
    }
    
    if ( key == 'q' ) {
        app->silos.setEffect(0);
    }
    
    
    if ( key == 'w' ) {
        app->silos.setEffect(1);
    }
    
    
    
    if ( key == 'e' ) {
        app->silos.setEffect(2);
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