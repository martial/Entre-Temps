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
#include "ofxXmlSettings.h"
#include "timeData.h"
#include "ofxTimeUtils.h"

class timeManager {
    
public:
    
    void        setup();
    void        parseXml();
    
    
    long        update();
    
    long        getSecondsElapsedBetween(long startingTime, long endingTime);
    float       getPctElapsedBetween(long startingTime, long endingTime);
    
    int         getDaysBetween(long startingTime, long EndingTime);
    int         getNumOfDays(long numOfSeconds);
    
    int         getNumOfNonWorkingsSecondsFor(int month, int day);
    
    timeData   *getTimeDataOf(int month, int day);
    
    long        currentUnixTime;
    int         currentMonth, currentDay, currentHour, currentMinut;
    
    bool        isOnline();
    
    bool        bOnline;
    
    long        remainingSeconds;
    
    float       particleStepInSec;
    
private:
    
    
    
    ofxXmlSettings      hoursXml;
    vector<timeData*>   workingTimeData;
    ofxTimeUtils        timeUtils;
    
};


#endif
