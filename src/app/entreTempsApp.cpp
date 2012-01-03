//
//  entreTempsApp.cpp
//  networkUdpReceiverExample
//
//  Created by Martial Geoffre-Rouland on 19/08/2011.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "entreTempsApp.h"

void entreTempsApp::setup() {
    
    tcp.setup();
    data.setup(&tcp);
    time.setup();
    
    timer.setup(20, true);
    ofAddListener(timer.TIMER_REACHED, this, &entreTempsApp::onMainTimer);
    timer.startTimer();
    
    silos.setup();
    silos.setGridSpacing(4.0);
    
    pct = 0.0;
    
    ofLog(OF_LOG_NOTICE, "hmm");
    
    bDrawDebug = true;
    
}
void entreTempsApp::update() {
    if(!time.bOnline) return;
    tcp.update();
    silos.update();
    
}
void entreTempsApp::draw() {
    
    if(!time.bOnline) return;
    
      
    ofPushMatrix();
    
    
    // basic translation to go 1:1
    ofTranslate(-silos.spacing+1,  - 1);
    // offset
    //ofTranslate(486 - silos.spacing, 358 - 1);
    silos.draw();
  
    if(bDrawDebug ) drawDebug();
       
    ofPopMatrix();
    
    
}

void entreTempsApp::drawDebug() {
    
    
    ofSetColor(255, 255, 255);
    
    ofDrawBitmapString(ofToString(time.currentDay) + "/" + ofToString(time.currentMonth) + " " + ofToString(time.currentHour) + ":" + ofToString(time.currentMinut), 0, 70);
    ofDrawBitmapString(ofToString(pct) +"%", 0, 85);
    
    int numOfMnByPixel =  floor(time.particleStepInSec / 60.0);
    int numOfSecondsByPixel = time.particleStepInSec - ( numOfMnByPixel * 60);
    
    ofDrawBitmapString("Pixel every " + ofToString( numOfMnByPixel) +" mn " + ofToString(numOfSecondsByPixel) +" sc", 0, 100);
    
    string clientConnected = (tcp.bHasClientConnected) ? "YES" : "NO";
    ofDrawBitmapString("Has client connected : " + clientConnected, 0, 115);
    ofDrawBitmapString("Fps: " + ofToString(ofGetFrameRate()), 0, 135);
    
}

void entreTempsApp::onMainTimer(int & e) {
        
    
    data.update(time.update());
    if(!time.bOnline) return;
   
    eventData * nextEventData = data.getNextEventData();
    if(!nextEventData) return;
    
    
    if (nextEventData->isRunning) {
        pct = 1.0;
    } else {
		pct = time.getPctElapsedBetween(data.getFinishedEventData()->getEndingTime(), nextEventData->posixTime);
    }
    
    pct = ofClamp(pct, 0.0, 1.0);
    
     
    // stable
   
    silos.setMainColor(data.getColorForSilo(nextEventData->typeID));
     
    // exception if we're at 1%
    // we should fill to the top dude
    
    if(pct == 1.0 && silos.getPctLoaded() < pct ) {
        silos.addRandomParticle(nextEventData->siloNumber);
        return;
    }
      
    
    if ( pct >= silos.getPctLoaded() && pct < silos.getNextPct() ) {
        // stable             
    } else {
        
    
        if ( silos.getPctLoaded() < pct ) {
            silos.addRandomParticle(nextEventData->siloNumber);
            return;
        } 
        
        if (  silos.getNextPct() > pct) {
            
            // things are going empty.
            // we should let the program know that somehting is going on here
            
            silos.setMainColor(data.getColorForSilo(data.getFinishedEventData()->typeID));
            silos.deleteRandomParticle(nextEventData->siloNumber);
            return;
        }
        
    }
        
    
    
    
   
    
}


