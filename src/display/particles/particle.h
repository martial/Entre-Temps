//
//  particle.h
//  networkUdpReceiverExample
//
//  Created by Martial Geoffre-Rouland on 23/08/2011.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef __PTCLET
#define __PTCLET

#include "ofMain.h"
#include "ofxVec2f.h"

class particleManager;

class particle {
        
public:
    
    particle();
    ~particle();
    void setup(particleManager * mom, float x, float y);
    void update();
       
    void checkCollision();
    void checkCollision (ofVec2f pnt);
    void resetForce();
    void addDampingForce();
    void addForce(float x, float y);
    
    ofxVec2f frc; 
    ofxVec2f pos;
    ofxVec2f vel;
    
    float damping;
    
    ofColor  color;
    
    bool    isFixed;
    int     id;
    
    // 
    float   underShockTime;
    int   underShockCount;
    bool    bIsUnderShock;
    
    bool    bTestPoly;
    
    particleManager  * mom;
    
    float highestPos;
    
    int numOfTrails;
    float currentNumOfTrails;
    
};



#endif
