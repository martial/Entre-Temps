//
//  eventData.cpp
//  networkUdpReceiverExample
//
//  Created by Martial Geoffre-Rouland on 19/08/2011.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "eventData.h"

eventData::eventData () {
    
    status = "not_updated";
    isRunning = false;
    isFinished = false;
    
    posixTime = 0;
    duration = 0;
    
    
}

eventData::~eventData () {
    
    
}

string eventData::updateStatus (long currentUnixTime) {
    
    
    if ( currentUnixTime >= getEndingTime() ) {
        status = "done";
        isFinished = true;
        isRunning = false;
    }
    
    if ( currentUnixTime > posixTime && currentUnixTime < getEndingTime() ) {
        status = "running";
        isRunning = true;
    }
    
    if ( currentUnixTime < posixTime ) {
        status = "pending";
        isRunning = false;
    }
    
    
    //ofLog(OF_LOG_NOTICE, "Status : " + status);
    
    return status;
    
}