//
//  silosManager.cpp
//  networkUdpReceiverExample
//
//  Created by Martial Geoffre-Rouland on 23/08/2011.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "silosManager.h"

void silosManager::setup(){
    
   
    totalPixels = 0;
    for ( int i=0; i<3; i++ ) {
        
        silo * siloObject = new silo();
        siloObject->setup();
        silos.push_back(siloObject);
        totalPixels += siloObject->totalPixels;
    }
    
	ofFbo::Settings s;
	s.width				= (silos[0]->pManager.polyBound.getBoundingBox().width+2) * 3;
	s.height			= silos[0]->pManager.polyBound.getBoundingBox().height+2;
	s.numColorbuffers	= 4;
	s.numSamples		= 0;
    s.internalformat    = GL_RGB;
    s.useDepth          = false;
    s.useStencil        = false;
	fbo.allocate(s);
	
    currentSilo = 0;
    
   }

void silosManager::update() {
    
    for ( int i=0; i<3; i++ ) {
        silos[i]->update();
    }
    
    
}

void silosManager::draw() {
    
    ofSetColor(255, 255, 255);
	fbo.begin();
    
    ofClear(1, 1, 1, 1); // we clear the fbo. 
    
	//ofEnableAlphaBlending();
	
	
    float xPos = -1;
  
    for ( int i=0; i<3; i++ ) {
        ofPushMatrix();
        ofTranslate(xPos, 0);
        silos[i]->draw();
        ofPopMatrix();
        
        xPos += silos[i]->pManager.polyBound.getBoundingBox().width-1;
        
       // ofLog(OF_LOG_NOTICE, "xPos %f ", xPos);
        
    }
    
    this->width = xPos - (silos[0]->pManager.polyBound.getBoundingBox().width);
    this->height = silos[0]->pManager.polyBound.getBoundingBox().height;
	
	//ofDisableAlphaBlending();
	ofSetColor(255, 255, 255);
	fbo.end();
    
    ofEnableAlphaBlending();
   
   
    fbo.draw(0, 0);
    
    return;
    
    ofPushMatrix();
    ofTranslate(ofGetWidth()*.5 - fbo.getWidth()*4/2, ofGetHeight()*.5 - fbo.getHeight()*4/2);
    fbo.draw(fbo.getWidth(), fbo.getHeight(),fbo.getWidth()*4, fbo.getHeight()*4 );
    ofPopMatrix();
    ofDisableAlphaBlending();
    
    
    
    
}

void silosManager::onMainTimer() {
    
    for ( int i=0; i<3; i++ ) {
        silos[i]->addRandomPoint();
    }
    
}

void silosManager::addRandomParticle (string siloNumber) {
    
    int index;
    int i = 0;
    
    for (  i=0; i<3; i++ ) {
       
       char strIndex = siloNumber.at(i);
       index = atoi(&strIndex);
       if ( silos[index]->getPctLoaded() != 1.0 ) break;
        
    }
       
    silos[index]->addRandomPoint();
   
}

void silosManager::deleteRandomParticle(string siloNumber) {
    
    
    int index;
    int i = 0;
    
    for (  i=0; i<3; i++ ) {
        
        char strIndex = siloNumber.at(i);
        index = atoi(&strIndex);
        if ( silos[index]->getPctLoaded() != 0.0 ) break;
        
    }
    
    silos[index]->pManager.removeLastParticle();
    
   
}

void silosManager::setMainColor(vector<ofColor*> * colors) {
    
    
    for ( int i=0; i<3; i++ ) {
        silos[i]->pManager.mainColor.r = colors->at(i)->r;
        silos[i]->pManager.mainColor.g = colors->at(i)->g;
        silos[i]->pManager.mainColor.b = colors->at(i)->b;
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
    
    float totalPct = 0.0;
    for ( int i=0; i<3; i++ ) {
        
        // check if ok to go on
        
        float nextSiloPct = silos[i]->getNextPct();
        float pct = ( i < 2 ) ? ( nextSiloPct > 1.0 ) ? 1.0 : nextSiloPct : nextSiloPct;
        
        totalPct += pct;

    }
    
    
    return totalPct / 3.0;    
}

float getBoundingBox () {
    
    return 0.0;    
}
