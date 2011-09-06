//
//  timeManager.cpp
//  networkUdpReceiverExample
//
//  Created by Martial Geoffre-Rouland on 19/08/2011.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "timeManager.h"

void timeManager::setup () {
    
    
}

long timeManager::update() {
    
    time_t t = time(0);
    currentUnixTime = (long)t;
    
    
    time_t rawtime;
    struct tm * timeinfo;
    char month [80];
    time ( &rawtime );
    timeinfo = localtime ( &rawtime );
    strftime (month,80,"%m",timeinfo);
    currentMonth = ofToInt(month);
    
    
    struct tm * ptm;
    ptm = gmtime ( &rawtime );
    currentHour = (ptm->tm_hour+1) % 2;
    
    ofLog(OF_LOG_NOTICE, "current unix time : %d", currentHour);
    
    return currentUnixTime;
}

long  timeManager::getSecondsElapsedBetween(long startingTime, long endingTime) {
    
    return endingTime - startingTime;
    
}


float timeManager::getPctElapsedBetween(long startingTime, long endingTime) {
    
    int remainingSeconds = getSecondsElapsedBetween(startingTime, endingTime);
    int elapsedSeconds = remainingSeconds - getSecondsElapsedBetween(currentUnixTime, endingTime);
    
    
    //ofLog(OF_LOG_NOTICE, "endingTime : %d", endingTime);
    //ofLog(OF_LOG_NOTICE, "remainingSeconds : %d", remainingSeconds);
    //ofLog(OF_LOG_NOTICE, "elapsedSeconds : %d", elapsedSeconds);
    
    return (float)((float)elapsedSeconds / (float)remainingSeconds);
}

/*

 if(eventDataArr.length < 2) return 0.0;
 if(!finishedEvent) return 0.0;
 
 var nextEvent:EventData = eventDataArr[1] as EventData;
 
 if ( nextEvent.isRunning ) return 1.0;
 
 var currentDate:Date = new Date();
 var realStartingDate:Date = new Date(finishedEvent.posixTime*1000 + finishedEvent.duration);
 var nextEventDate:Date = new Date(nextEvent.posixTime*1000);
 
 var totalSecondsRemaining:Number = nextEventDate.time - realStartingDate.time;
 var totalSecondsElapsed:Number = totalSecondsRemaining - (nextEventDate.time - (currentDate.time));
 
 
 return totalSecondsElapsed / totalSecondsRemaining;

*/