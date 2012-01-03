//
//  silosManager.cpp
//  networkUdpReceiverExample
//
//  Created by Martial Geoffre-Rouland on 23/08/2011.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "silosManager.h"

void silosManager::setup(){
    
    
    // setup all the silos
    totalPixels = 0;
    for ( int i=0; i<3; i++ ) {
        
        silo * siloObject = new silo();
        siloObject->setup();
        silos.push_back(siloObject);
        totalPixels += siloObject->totalPixels;
    }
    
       
    // define current to be drawn
    currentSilo = 0;
    
    // define tweens for colors
    currentColors.reserve(3);
    blurColorRate = .5;
    for ( int i=0; i<3*3 ; i++ ) {
        tweens.push_back(new ofxTween());
    }
    
    
    // setup shader for position and effects
    posShader.load("shaders/pos.vert", "shaders/pos.frag");
    effectId = 0;
    spacing = 1.0;
    setGridSpacing(spacing);
    
    
    /*
     ofFbo::Settings s;
     s.width				= (silos[0]->pManager.polyBound.getBoundingBox().width+2) * 3;
     s.height			= silos[0]->pManager.polyBound.getBoundingBox().height+2;
     s.numColorbuffers	= 4;
     s.numSamples		= 0;
     s.internalformat    = GL_RGB;
     s.useDepth          = false;
     s.useStencil        = false;
     fbo.allocate(s);
     */
	

    
}

void  silosManager::setGridSpacing(float spacing) {
    this->spacing = spacing;
    for ( int i=0; i<3; i++ ) {
        silos[i]->setGridSpacing(spacing);
    }
}

void silosManager::setEffect(int id) {
    
    effectId = id;
    
}

void silosManager::update() {
    
    for ( int i=0; i<3; i++ )  silos[i]->update();
    updateColors();
    
}

void silosManager::draw() {
    
    ofSetColor(255, 255, 255);
    
	
    posShader.begin();
    posShader.setUniform1i("effect", effectId);
    posShader.setUniform1f("mult", spacing);
    posShader.setUniform1f("timeValX", ofGetElapsedTimef() * 0.1 );
    posShader.setUniform1f("timeValY", -ofGetElapsedTimef() * 0.18 );
    
    
    float xPos = -1;
  
    for ( int i=0; i<3; i++ ) {
        ofPushMatrix();
        ofTranslate(xPos, 0);
        silos[i]->draw();
        ofPopMatrix();
        
        xPos += (silos[i]->pManager.polyBound.getBoundingBox().width-1) * spacing;
                
    }
    
    this->width = xPos - (silos[0]->pManager.polyBound.getBoundingBox().width);
    this->height = silos[0]->pManager.polyBound.getBoundingBox().height;
	
	ofSetColor(255, 255, 255);
       
    posShader.end();

}




void silosManager::drawFbo (int x, int y) {
    
    
    ofPushMatrix();
    ofTranslate(x,y);
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
    
    // find out the good silo 
        
    int siloIndex;
    int index;
    float rdm;
     for (  int i=0; i<3; i++ ) {
         char strIndex = siloNumber.at(i);
         siloIndex = atoi(&strIndex);
         
         istringstream buffer(&strIndex);
         buffer >> siloIndex;
         
         if ( silos[siloIndex]->getPctLoaded() != 1.0 ) break;
     }
    
    
    // we get the next id we want to prioritize
    // and add a pct variation of .2 ?
    
    rdm = ofRandom(0,1);
    index =  floor(ofRandom(0,3));
    
    if( rdm > .25 ) {
        
        while(silos[index]->getPctLoaded() == 1.0 )  index =  floor(ofRandom(0,3));
        
    } else {
        
        index = siloIndex;
    }
       
	silos[index]->addRandomPoint();
    
   
}

void silosManager::deleteRandomParticle(string siloNumber) {
    
  	
	// delete randomly
    
    int index =  floor(ofRandom(0,3));
	while(silos[index]->getPctLoaded() == 0.0 ) index =  floor(ofRandom(0,3));
    silos[index]->pManager.removeLastParticle();
   
}

void silosManager::setMainColor(vector<ofColor*> * colors) {
    
    currentColors.clear();
    for ( int i=0; i<3; i++ ) {
        currentColors.push_back(colors->at(i));
        
        ofColor * color = colors->at(i);
        
         for ( int j=0; j<3; j++ ) {
             
            ofxTween * tween = tweens[i * 3 + j];
            tween->setParameters(quint, ofxTween::easeOut, (float)silos[i]->pManager.mainColor.v[j], (float)color->v[j], 4000.0, 0);

         }
        
    }
   
}

void silosManager::updateColors() {
    
    if(currentColors.size() == 0 ) return;
    
    for ( int i=0; i<3; i++ ) {
        for ( int j=0; j<3; j++ ) {
            ofxTween * tween = tweens[i * 3 + j];
            silos[i]->pManager.mainColor.v[j] = tween->update();            
        }
        
    }
    
       
}

float silosManager::getPctLoaded() {
    
    float totalPct = 0.0;
    
    for ( int i=0; i<3; i++ ) 
        totalPct += silos[i]->getPctLoaded();
           
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



/*
 * For debug purposes
 */

void silosManager::drawWhiteRect (int x, int y) {
    
    
    
    int _w = ( silos[0]->pManager.polyBound.getBoundingBox().width) * 3;
    int _h = ( silos[0]->pManager.polyBound.getBoundingBox().height);
    
    ofSetColor(255, 255, 255);
    ofRect(x, y, _w, _h);
    
}
    
