//
//  eventData.h
//  networkUdpReceiverExample
//
//  Created by Martial Geoffre-Rouland on 19/08/2011.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef EVTDATA
#define EVTDATA

#include "ofMain.h"

class eventData {
    
public:
    
    eventData();
    ~eventData();
    
    string updateStatus(long int currentUnixTime);
   
    
    long getEndingTime () {
        return posixTime + duration;        
    }
    
    string      id;
    string      name;
    long        posixTime;
    int         duration;
    int         typeID;
    int         typeColor;
    
    bool        isRunning;
    bool        isFinished;
    
    string         siloNumber;
    
    
    
    string      status;
    
    
    
};

#endif
