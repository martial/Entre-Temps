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
    
    timer.setup(20, true);
    ofAddListener(timer.TIMER_REACHED, this, &entreTempsApp::onMainTimer);
    timer.startTimer();
    
    silos.setup();
    
    pct = 0.0;
    
    
    //fbo.allocate();
    
}
void entreTempsApp::update() {
    
    flash.update();
    silos.update();
    
}
void entreTempsApp::draw() {
    silos.draw();
    
  
}

void entreTempsApp::onMainTimer(int & e) {
        
    data.update(time.update());
    
   
    // TODO not working..
    eventData * nextEventData = data.getNextEventData();
    if(!nextEventData) return;
    
     //ofLog(OF_LOG_NOTICE, "Next event data is " + nextEventData->name);
    
    if (nextEventData->isRunning) {
        //ofLog(OF_LOG_NOTICE, "seems like one is running. Hrmpfd");
        pct = 1.0;
    } else {
		pct = time.getPctElapsedBetween(data.getFinishedEventData()->getEndingTime(), data.getNextEventData()->posixTime);
    }
    
   // printf("allo");
    
    
    silos.setMainColor(nextEventData->typeColor);
    
      
    
    if ( pct >= silos.getPctLoaded() && pct <= silos.getNextPct() ) {
        // stable
        
        //ofLog(OF_LOG_NOTICE, "Stable man! ");
        
    } else {
   
    
        if ( silos.getPctLoaded() < pct ) {
            silos.addRandomParticle();
            return;
            //ofLog(OF_LOG_NOTICE, "Add ptc! ");
        } 
        
        if (  silos.getNextPct() > pct) {
            silos.deleteRandomParticle();
            ofLog(OF_LOG_NOTICE, "Delete ptc! ");
        }
        
    }
        
    
    
   
    
   
    //ofLog(OF_LOG_NOTICE, "pct to go elapsed : %f - silos pct %f - next Pct %f", pct, silos.getPctLoaded(), silos.getNextPct() );
    
}

void entreTempsApp::drawFbo () {
    
    
    
}
