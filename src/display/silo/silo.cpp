//
//  silo.cpp
//  networkUdpReceiverExample
//
//  Created by Martial Geoffre-Rouland on 23/08/2011.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "silo.h"

void silo::setup() {
    
    pManager.setup();
    
    xBounds.set(pManager.polyBound.getBoundingBox().x, pManager.polyBound.getBoundingBox().width - pManager.polyBound.getBoundingBox().x-1);
    currentPoint = xBounds.x+1;
    
    sens = 1;
    bounceCount = 0;
    
    
    totalPixels = pManager.getNumOfPixelsInBounds();
        
    
}

void silo::setGridSpacing(float spacing) {
    pManager.setGridSpacing(spacing);
}

void silo::update(){
    pManager.update();        
}
void silo::draw() {
    pManager.draw();
}



void silo::addRandomPoint() {
    
    if(getPctLoaded() == 1.0)  return;
     
    
    int randomPoint = getRandomPoint();    
    
    bool isFull =  pManager.isColumnFull(randomPoint);
    while ( isFull ) {
        randomPoint = getRandomPoint();
        isFull =  pManager.isColumnFull(randomPoint);
    }
    
    pManager.addParticle(randomPoint, 0);
    
}



int silo::getRandomPoint() {
    
    
    
    float rdm = ofRandom(1.0);
    if ( rdm > .95 + ofRandom(0.05) ) {
        sens *= -1;
    }
    
    if( currentPoint>=xBounds.y) {
        bounceCount++;
        sens = 0;
        if ( bounceCount >= 2 ) {
            sens = -1;
            bounceCount = 0;
        }
    } 
    if ( currentPoint<= 1) {
        bounceCount++;
        sens = 0;
        if ( bounceCount >= 2 ) {
            sens = 1;
            bounceCount = 0;
        }
    }
    
    currentPoint +=sens;
    
    
    return currentPoint;
}

float silo::getPctLoaded () {
        
    if(pManager.particles.size() == 0 ) return 0.0;
    if(pManager.particles.size() >= 786 ) return 1.0;
    return  pManager.particles.size() / 786.0;
}



float silo::getNextPct() {
    return  (pManager.particles.size() +1 ) / 786.0;
}


