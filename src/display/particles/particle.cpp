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
    
    color.r = 255;
    color.g = 255;
    color.b = 255;
    color.a = 255;
    
    isFixed = false;
    
    damping = .5;
    
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
    
    float highestPos = mom->getNextHighestYPos(pos.x, this) -1.0;
        
    if(pos.y >= highestPos  ) {
                
        pos.y =   highestPos;
        isFixed = true;
        color.r = 0;
        color.g = 255;
        color.b = 0;
        //ofLog(OF_LOG_NOTICE, "bingo! %d", highestPos);
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
            color.r = 255;
            color.g = 0;
            color.b = 0;
            
            
        }       
        
        
    }
    
       
    
    
}

void particle::update() {
    
    //color.r = pos.y * 255 / mom->polyBound.getBoundingBox().height;
   // color.r = pos.y * mom->mainColor.r / mom->polyBound.getBoundingBox().height;;
   // color.g = pos.y * mom->mainColor.g / mom->polyBound.getBoundingBox().height;;;
    //color.b = pos.y * mom->mainColor.b / mom->polyBound.getBoundingBox().height;;;
   
    
    if(isFixed) return;
    
    color.r = mom->mainColor.r;
    color.g = mom->mainColor.g ;
    color.b = mom->mainColor.b ;
        
        vel = vel + frc;
        pos = pos + vel;
    
       // pos.x = (int)pos.x;
       // pos.y = (int)pos.y;
    
}

void particle::draw() {
    
    ofPushMatrix();
    ofSetColor(color.r, color.g, color.b);
    ofTranslate(pos.x, pos.y);
    ofRect(0, 0, 1, 1);
    ofPopMatrix();
    
}


