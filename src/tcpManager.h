/*
 *  tcpManager.h
 *  EntreTemps
 *
 *  Created by Martial on 06/12/2011.
 *  Copyright 2011 Martial. All rights reserved.
 *
 */

#ifndef TCPMNGR
#define TCPMNGR

#include "ofMain.h"
#include "ofxNetwork.h"

class tcpManager {
    
public:
    
    void setup();
    void update();
   
    
	ofxTCPServer			TCP;
    
    //ofEvent<string>         messageEvt;
    ofEvent<string>         xmlEvt;
    
    bool bHasClientConnected;
    
};




#endif
