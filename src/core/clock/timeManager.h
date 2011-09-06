//
//  timeManager.h
//  networkUdpReceiverExample
//
//  Created by Martial Geoffre-Rouland on 19/08/2011.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef TIMEMNGER
#define TIMEMNGER

#include "ofMain.h"
#include "ofxTimer.h"

class timeManager {
    
public:
    
    void    setup();
    long     update();
    
    long     getSecondsElapsedBetween(long startingTime, long endingTime);
    float   getPctElapsedBetween(long startingTime, long endingTime);
    
    long      currentUnixTime;
    int       currentMonth, currentHour;
    
private:
    
    
};


#endif
