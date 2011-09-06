//
//  silosManager.cpp
//  networkUdpReceiverExample
//
//  Created by Martial Geoffre-Rouland on 23/08/2011.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "silosManager.h"

void silosManager::setup(){
    
   
    
    for ( int i=0; i<3; i++ ) {
        
        silo * siloObject = new silo();
        siloObject->setup();
        silos.push_back(siloObject);
        
    }
    
	ofFbo::Settings s;
	s.width				= (silos[0]->pManager.polyBound.getBoundingBox().width+2) * 3;
	s.height			= silos[0]->pManager.polyBound.getBoundingBox().height+2;
	s.numColorbuffers	= 4;
	s.numSamples		= ofFbo::maxSamples();
	fbo.allocate(s);
	
	
    //fbo.allocate((silos[0]->pManager.polyBound.getBoundingBox().width+2) * 3, silos[0]->pManager.polyBound.getBoundingBox().height+2, GL_RGBA, 1);
    
    
   }
void silosManager::update() {
    
    for ( int i=0; i<3; i++ ) {
        silos[i]->update();
    }
    
    
}

void silosManager::draw() {
    
    ofSetColor(255, 255, 255);
	fbo.begin();
    ofClear(0, 0, 0, 1); // we clear the fbo.  
	ofEnableAlphaBlending();
	
	glColor3f(1,1,1);
    float xPos = 0;
  
    for ( int i=0; i<3; i++ ) {
        ofPushMatrix();
        ofTranslate(xPos, 0);
        silos[i]->draw();
        ofPopMatrix();
        
        xPos += silos[i]->pManager.polyBound.getBoundingBox().width;
        
       // ofLog(OF_LOG_NOTICE, "xPos %f ", xPos);
        
    }
    
    this->width = xPos - (silos[0]->pManager.polyBound.getBoundingBox().width);
    this->height = silos[0]->pManager.polyBound.getBoundingBox().height;
	
	ofDisableAlphaBlending();
	ofSetColor(255, 255, 255);
	fbo.end();
    
    ofEnableAlphaBlending();
    glColor3f(1,1,1);
    fbo.draw(0, 0);
    
    ofPushMatrix();
    ofTranslate(ofGetWidth()*.5 - fbo.getWidth()*2, ofGetHeight()*.5 - fbo.getHeight()*2);
    fbo.draw(fbo.getWidth(), fbo.getHeight(),fbo.getWidth()*4, fbo.getHeight()*4 );
    ofPopMatrix();
    ofDisableAlphaBlending();
}

void silosManager::onMainTimer() {
    
    for ( int i=0; i<3; i++ ) {
        silos[i]->addRandomPoint();
    }
    
}

void silosManager::addRandomParticle () {
    
    int rdm = floor(ofRandom(3));
    silos[rdm]->addRandomPoint();
}

void silosManager::deleteRandomParticle() {
    
    int rdm = floor(ofRandom(3));
    
    silos[rdm]->pManager.removeLastParticle();
}

void silosManager::setMainColor(int color) {
    
    
    for ( int i=0; i<3; i++ ) {
        silos[i]->pManager.mainColor.setHex(color);
     }
}

float silosManager::getPctLoaded() {
    
    float totalPct = 0.0;
    for ( int i=0; i<3; i++ ) {
        totalPct += silos[i]->getPctLoaded();
    }
    
    
    return totalPct / 3.0;
}

float silosManager::getNextPct () {
    
    float totalPct = silos[0]->getNextPct();
    for ( int i=1; i<3; i++ ) {
        totalPct += silos[i]->getPctLoaded();
    }
    
    
    return totalPct / 3.0;    
}

float getBoundingBox () {
    
    return 0.0;    
}
