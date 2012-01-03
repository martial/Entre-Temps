//
//  particle.cpp
//  networkUdpReceiverExample
//
//  Created by Martial Geoffre-Rouland on 23/08/2011.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "particle.h"
#include "particleManager.h"

particle::particle () {
    
}

particle::~particle () {
    
}



void particle::setup (particleManager * mom, float x, float y) {
    
    // hello to your mother
    this->mom = mom;
    
    // basic props
    pos.set((float)x, (float)y);
    vel.set(0,0);
    frc.set(0,0);
    
    color.r = 255;
    color.g = 255;
    color.b = 255;
    color.a = 255;
    
    isFixed = false;
    
    damping = 0.3;
    
    underShockTime = 30;
    underShockCount = 0;
    bIsUnderShock = false;
    
    highestPos = mom->getNextHighestYPos(pos.x, this)-1;
    
    bTestPoly = false;
    
    numOfTrails = int(3 + ofRandom(20));
    currentNumOfTrails = numOfTrails;
   
    
   }

void particle::resetForce(){
    frc.set(0,0);	
}

void particle::addForce(float x, float y){
   
    frc.x = frc.x + x;
    frc.y = frc.y + y;

}



void particle::addDampingForce(){
	
    frc.x = frc.x - vel.x * damping;
    frc.y = frc.y - vel.y * damping;
}



void particle::checkCollision () {
   
    if(isFixed) return;
    
    
    
    if(pos.y >= highestPos  ) {
                
        pos.y =   highestPos;
        isFixed = true;
       
        
        underShockCount = 0;
        bIsUnderShock = true;
        color.setSaturation(500);
        
    }
        
}



void particle::checkCollision (ofVec2f pnt) {
    
    if(isFixed) return;
    
        
    if ( !isFixed && pos.x == pnt.x  ) {
        
        // we're on same x
                
        if ( pos.y >= pnt.y ) {
            pos.y = pnt.y;
            isFixed = true;
           
            
            underShockCount = 0;
            bIsUnderShock = true;
            color.setSaturation(500);
        }       
        
        
    }
    
       
    
    
}

void particle::update() {
    
    
    // updating color to to a subtle gradient
    
    float yPosPct = .5 + (pos.y / 52 * .5);
    
    color.r = mom->mainColor.r * yPosPct;
    color.g = mom->mainColor.g * yPosPct;
    color.b = mom->mainColor.b * yPosPct;

    
    // flickering
    if(bIsUnderShock) {
        
        
        
        underShockCount++;
        if( underShockCount % 4 < 2 ) {
            
            float divr = 255 - color.r;
            float divg = 255 - color.g;
            float divb = 255 - color.b;
                        
            float pct =  (float)underShockCount / (float) underShockTime;
            
            color.r = 255 - divr * pct;
            color.g = 255 - divg * pct;
            color.b = 255 - divb * pct;
            
            color.set(255,255,255);
            
            
        } else {
            
            color.set(0,0,0);
            
        }
        
        
        
        if(underShockCount > underShockTime ) {
            color.set(0,0,0);
            bIsUnderShock = false;
        }
        
        
    }
    
 
    // if we're fixed, reduce the trail size
    if(isFixed) {
        if(currentNumOfTrails > 0) currentNumOfTrails -= .5; 
        return;
        
    }
     
    
    // update pos
    vel = vel + frc;
    pos = pos + vel;
    
           
}



