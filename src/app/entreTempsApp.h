//
//  entreTempsApp.h
//  networkUdpReceiverExample
//
//  Created by Martial Geoffre-Rouland on 19/08/2011.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef ENTRETMPSAPP
#define ENTRETMPSAPP

#include "ofMain.h"
#include "ofxTimer.h"
#include "dataManager.h"
#include "flashUdpManager.h"
#include "timeManager.h"
#include "silosManager.h"

class entreTempsApp {
    
public:
    
    void setup();
    void update();
    void draw();
    void drawFbo();
    
    void onMainTimer(int & e);
    
    silosManager        silos;
    
    float pct;
    
    private :
    
    dataManager         data;
    flashUdpManager     flash;
    timeManager         time;
    
    ofxTimer            timer;
    
    ofFbo               fbo;
    
    
    
};



#endif
