//
//  particleManager.h
//  networkUdpReceiverExample
//
//  Created by Martial Geoffre-Rouland on 23/08/2011.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef PTCLMNGR
#define PTCLMNGR

#include "ofMain.h"
#include "particle.h"



class particleManager {
        
    
public:
    
    void setup();
    void update();
    void draw();
    
    void    checkForCollisions (particle * p);    
    void    addParticle(int x, int y);
    void    removeParticle(particle * p);
    void    removeLastParticle();
    void    addBounds();
    
    float   getNextHighestYPos(float x,particle * p = NULL);
    bool    isFull();
    bool    isColumnFull(int x);
    int     getNumOfPixelsInBounds();
    
    void    clearFixed(bool bClearFixed);
    void    clear();
    
    int     findPosYInLine(ofVec2f pntA, ofVec2f pntB, int x);
    
    void    setGridSpacing(float spacing);
    
    vector<particle*>   particles;
    ofPolyline          polyBound;
    vector<ofxVec2f>    boundVertices;
    
    int pnpoly(int nvert, float *vertx, float *verty, float testx, float testy);
    
    bool bClearFixed;
    
    ofColor mainColor;
    ofPolyline poly;
    
    ofShader posShader;
    
    
    private :
    
    
    float spacing;

    
};


#endif
