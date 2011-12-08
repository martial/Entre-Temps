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
    
    this->mom = mom;
    
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
    
    numOfTrails = 10.0;
    currentNumOfTrails = 10.0;
   
   }

void particle::resetForce(){
    frc.set(0,0);	
}

void particle::addForce(float x, float y){
   
    frc.x = frc.x + x;
    frc.y = frc.y + y;

}

void particle::addRepulsionForce(ofVec2f pnt, float radius, float scale){
	
	// ----------- (1) make a vector of where this particle p is: 
	ofVec2f posOfForce;
	posOfForce.set(pnt.x,pnt.y);
	
	// ----------- (2) calculate the difference & length 
	
	ofVec2f diff	= pos - posOfForce;
	float length	= diff.length();
	
    
	// ----------- (3) check close enough
	
	bool bAmCloseEnough = true;
    if (radius > 0){
        if (length > radius){
            bAmCloseEnough = false;
        }
    }
	
	// ----------- (4) if so, update force
    
	if (bAmCloseEnough == true){
		float pct = 1 - (length / radius);  // stronger on the inside
		diff.normalize();
		frc.x = frc.x + diff.x * scale * pct;
        frc.y = frc.y + diff.y * scale * pct;
		
		//p->frc.x = p->frc.x - diff.x * scale * pct;
       // p->frc.y = p->frc.y - diff.y * scale * pct;
		
    }
}

void particle::addDampingForce(){
	
	// the usual way to write this is  vel *= 0.99
	// basically, subtract some part of the velocity 
	// damping is a force operating in the oposite direction of the 
	// velocity vector
	
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

void particle::checkCollision (float x, float y) {
    
    
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
    
    float yPosPct = .5 + (pos.y / 52 / 2);
    
    color.r =  mom->mainColor.r * yPosPct;
    color.g = mom->mainColor.g * yPosPct;
    color.b =  mom->mainColor.b * yPosPct;

    
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
    
 
    
    if(isFixed) {
        if(currentNumOfTrails > 0) currentNumOfTrails -= .5; 
        return;
        
    }
            
    vel = vel + frc;
    pos = pos + vel;
    
           
}



