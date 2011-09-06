//
//  silo.h
//  networkUdpReceiverExample
//
//  Created by Martial Geoffre-Rouland on 23/08/2011.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef __SILO
#define __SILO

#include "ofMain.h"
#include "particleManager.h"

class silo {
        
public:
    void setup();
    void update();
    void draw();
    
    int  getNumOfPixels();
    int  getRandomPoint();
    void addRandomPoint();
    
    
    
    float getPctLoaded();
    float getNextPct();
    
    particleManager pManager;
    
    int currentPoint, sens;
    ofPoint     xBounds;
    
    int totalPixels;
    int bounceCount;
};


#endif
