//
//  flashUdpManager.h
//  networkUdpReceiverExample
//
//  Created by Martial Geoffre-Rouland on 19/08/2011.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef FLASHUDPMNGR
#define FLASHUDPMNGR

#include "ofMain.h"
#include "ofxFlashCommunication.h"

class flashUdpManager {
    
    public:
    
    void setup();
    void update();
    
    ofxFlashCommunication   flash;
    
    ofEvent<string>         messageEvt;
    ofEvent<string>         xmlEvt;
    
    
};




#endif
