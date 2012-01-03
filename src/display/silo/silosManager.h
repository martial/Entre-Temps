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
#include "ofxTween.h"

class silosManager {
        
public:
    
    void setup();
    void update();
    void draw();
    void drawFbo(int x, int y);
    
    void  setGridSpacing(float spacing);
    void setEffect(int id);
    
    void onMainTimer();
    void addRandomParticle(string siloNumber);
    void deleteRandomParticle(string siloNumber);
    
    void setMainColor(vector<ofColor*> * colors);
    void updateColors();
    
    void drawWhiteRect(int x, int y);
    
    float getPctLoaded();
    float getNextPct();
    
    
    vector<silo*>   silos;
    ofFbo           fbo;
    ofPoint         xBounds;
    int             currentPoint;
    int             sens;
    
    float           width, height;
    
    int             totalPixels;
    int             currentSilo;
    
    vector<ofColor*> currentColors;
    
    float           spacing;
    
    float           blurColorRate;
    
    ofxEasingQuint      quint;
    vector<ofxTween*>    tweens;
    
    ofShader posShader;
    int     effectId;
    
};


#endif
