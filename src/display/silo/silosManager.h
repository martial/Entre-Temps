//
//  silosManager.h
//  networkUdpReceiverExample
//
//  Created by Martial Geoffre-Rouland on 23/08/2011.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef SILOMNGR
#define SILOMNGR

#include "ofMain.h"
#include "silo.h"

class silosManager {
        
public:
    
    void setup();
    void update();
    void draw();
    
    void onMainTimer();
    void addRandomParticle();
    void deleteRandomParticle();
    void setMainColor(int color);
        
    
    
    float getPctLoaded();
    float getNextPct();
    
    float getBoundingBox();
    
    vector<silo*>   silos;
    ofFbo           fbo;
    ofPoint         xBounds;
    int             currentPoint;
    int             sens;
    
    float           width, height;
};


#endif