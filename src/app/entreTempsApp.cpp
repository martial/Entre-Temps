//
//  entreTempsApp.cpp
//  networkUdpReceiverExample
//
//  Created by Martial Geoffre-Rouland on 19/08/2011.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "entreTempsApp.h"

void entreTempsApp::setup() {
    
    flash.setup();
    data.setup(&flash);
    time.setup();
    
    timer.setup(20, true);
    ofAddListener(timer.TIMER_REACHED, this, &entreTempsApp::onMainTimer);
    timer.startTimer();
    
    silos.setup();
    
    pct = 0.0;
    
    
    //fbo.allocate();
    
}
void entreTempsApp::update() {
    if(!time.bOnline) return;
    flash.update();
    silos.update();
    
}
void entreTempsApp::draw() {
    if(!time.bOnline) return;
    
    ofPushMatrix();
    ofTranslate(294, 214 - 1);
    silos.draw();
    
   // drawDebug();
    ofPopMatrix();
    
}

void entreTempsApp::drawDebug() {
    
    
    ofSetColor(255, 255, 255);
    
    ofDrawBitmapString(ofToString(time.currentDay) + "/" + ofToString(time.currentMonth) + " " + ofToString(time.currentHour) + ":" + ofToString(time.currentMinut), 0, 70);
    ofDrawBitmapString(ofToString(pct) +"%", 0, 85);
    
    int numOfMnByPixel =  floor(time.particleStepInSec / 60.0);
    int numOfSecondsByPixel = time.particleStepInSec - ( numOfMnByPixel * 60);
    
    ofDrawBitmapString("Pixel every " + ofToString( numOfMnByPixel) +" mn " + ofToString(numOfSecondsByPixel) +" sc", 0, 100);
    
    
    
}

void entreTempsApp::onMainTimer(int & e) {
        
    data.update(time.update());
    if(!time.bOnline) return;
   
    eventData * nextEventData = data.getNextEventData();
    if(!nextEventData) return;
    
    
    if (nextEventData->isRunning) {
        pct = 1.0;
    } else {
		pct = time.getPctElapsedBetween(data.getFinishedEventData()->getEndingTime(), data.getNextEventData()->posixTime);
    }
    
    
    
    
    // stable
    
    
    
     silos.setMainColor(data.getColorForSilo(nextEventData->typeID));
   
      
    
    if ( pct >= silos.getPctLoaded() && pct < silos.getNextPct() ) {
        // stable
        
        
    } else {
   
    
        if ( silos.getPctLoaded() < pct ) {
            silos.addRandomParticle(nextEventData->siloNumber);
            return;
            //ofLog(OF_LOG_NOTICE, "Add ptc! ");
        } 
        
        if (  silos.getNextPct() > pct) {
            
            silos.setMainColor(data.getColorForSilo(data.getFinishedEventData()->typeID));
            silos.deleteRandomParticle(nextEventData->siloNumber);
            return;
        }
        
    }
        
    
    
    
   
    
}

void entreTempsApp::drawFbo () {
    
    
    
}
