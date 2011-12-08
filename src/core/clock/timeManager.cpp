//
//  timeManager.cpp
//  networkUdpReceiverExample
//
//  Created by Martial Geoffre-Rouland on 19/08/2011.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "timeManager.h"

void timeManager::setup () {
    
    bOnline = true;
    
    hoursXml.loadFile("hours.xml");
    parseXml();
    
}

void timeManager::parseXml () {
        
    hoursXml.pushTag("root");
    
    int numOfNodes = hoursXml.getNumTags("node");
    
        
    for ( int i=0; i<numOfNodes; i++ ) {
        
        timeData * tmData = new timeData();
        
        tmData->startingDay = hoursXml.getAttribute("node", "sd", 0,i);
        tmData->endingDay = hoursXml.getAttribute("node", "ed", 31,i);
        
        tmData->month = hoursXml.getAttribute("node", "m", 0,i);
        
        hoursXml.pushTag("node", i);
        
        
        tmData->startingHour = hoursXml.getAttribute("start", "h", 0,0);
        tmData->startingMinut = hoursXml.getAttribute("start", "m", 0,0);
        
        tmData->endingHour = hoursXml.getAttribute("end", "h", 0,0);
        tmData->endingMinut = hoursXml.getAttribute("end", "m", 0,0);
        
        
        hoursXml.popTag();
        
    
        workingTimeData.push_back(tmData);
        
         
    }
    
    

}


long timeManager::update() {
    
    time_t t = time(0);
    currentUnixTime = (long)t;
    
    
    time_t rawtime;
    struct tm * timeinfo;
    char month [80];
    char day [80];
    char hour [80];
    char minut [80];
    time ( &rawtime );
    
    timeinfo = localtime ( &rawtime );
    
    strftime (month,80,"%m",timeinfo);
    strftime (day,80,"%d",timeinfo);
    strftime (hour,80,"%H",timeinfo);
    strftime (minut,80,"%M",timeinfo);
    
    currentMonth = ofToInt(month);
    currentDay = ofToInt(day);
    currentHour =  ofToInt(hour);
    currentMinut =  ofToInt(minut);
    
   // bOnline = isOnline();
    
    return currentUnixTime;
}

bool timeManager::isOnline() {
    
            
        timeData * tmData = getTimeDataOf(currentMonth, currentDay);
                
        if(currentHour >= tmData->startingHour || currentHour <= tmData->endingHour) {
                
        ofLog(OF_LOG_NOTICE, "currentHour %d - data startingHour %d - endingHour %d", currentHour, tmData->startingHour, tmData->endingHour);
                    
        // we are in the same hour period.. check minuts!
        // find if we have to be + or - 
                    
        if (currentHour == tmData->startingHour ) {
            return (currentMinut >= tmData->startingMinut);
        } 
                    
        if (currentHour == tmData->endingHour ) {
            return (currentMinut <= tmData->endingMinut);
        }
        return TRUE;
            
        }
            
          
    return FALSE;
}

timeData   * timeManager::getTimeDataOf(int month, int day) {
    
    for (int i=0; i<workingTimeData.size(); i++) {
        
        timeData * tmData = workingTimeData[i];
        if(currentMonth == tmData->month) {
            if(currentDay >= tmData->startingDay && currentDay<= tmData->endingDay ) {
                return tmData;
            }
        }
    
    }
}

long  timeManager::getSecondsElapsedBetween(long startingTime, long endingTime) {
    
    return endingTime - startingTime;
    
}


float timeManager::getPctElapsedBetween(long startingTime, long endingTime) {
    
    remainingSeconds = getSecondsElapsedBetween(startingTime, endingTime);
    
    // to remaining seconds, we should take off the non working hours
    // how to do that ?
    // maybe first of all, check how many days are between each event.
    
   // ofLog(OF_LOG_NOTICE, "Days between two events ? %d", getNumOfDays(remainingSeconds));
    
    // bon ca. Ca marche.
    
    // then, check how many days left are in the month with current work time, and go on.
    // I guess we can do it in a loop using unixtime?
    
    // like back to the future right?
    
    // we know that one day is 60 * 60 * 24 = 86400 seconds
    
    
    // ok so now we get how many seconds REALLY are elapsed since then
    // then the number of days BUT
    // we may be in the case where there's 0 days between, but still a gap has to be filled
    // how do we do that.. check if we're before or after the online mode
    
    int numOfDays = getNumOfDays(remainingSeconds);
    
    
    int numOfDaysSecondsNow = currentUnixTime - startingTime;
    // how many days since now ?
    int numOfDaysElapsedSinceNow = getNumOfDays(numOfDaysElapsedSinceNow);
    
    // hey if we are before the gap, we should add one day right?
    /*
    if(numOfDays==0) {
        timeData * tmData = getTimeDataOf(currentMonth, currentDay);
        if ( currentHour < tmData->endingHour ) {
            numOfDaysElapsedSinceNow++; 
            ofLog(OF_LOG_NOTICE, "add one");
        }
        
    }
     
     */
    
    
    long futurePosixTime = startingTime;
    for(int i=0; i<numOfDaysElapsedSinceNow; i++) {
        
        futurePosixTime += 86400;
        
        time_t rawtime = futurePosixTime;
        
        struct tm * timeinfo;
        char month [80];
        char day [80];

        timeinfo =  gmtime(&rawtime);
        
        strftime (month,80,"%m",timeinfo);
        strftime (day,80,"%d",timeinfo);
 
        
        
        remainingSeconds -= getNumOfNonWorkingsSecondsFor(ofToInt(month), ofToInt(day));
    }
    
    
    particleStepInSec = (float) remainingSeconds /  (786 * 3.0 ) ;
    

        
    //ofLog(OF_LOG_NOTICE, "particleStepInSec %f", particleStepInSec );
    
    
    // now we want to know - how many seconds are elapsed without the gaps since the beginning
    
    // how many seconds between starting event and now ?
  
    futurePosixTime = startingTime;
    int unixTimeWithoutGaps = currentUnixTime;
    
  
    
    
    for ( int i=0; i<numOfDaysElapsedSinceNow; i++) {
            
        futurePosixTime += 86400;
        time_t rawtime = futurePosixTime;
        
        struct tm * timeinfo;
        char month [80];
        char day [80];
        
        timeinfo = gmtime(&rawtime);
        
        strftime (month,80,"%m",timeinfo);
        strftime (day,80,"%d",timeinfo);
        
        
        
        unixTimeWithoutGaps -= getNumOfNonWorkingsSecondsFor(ofToInt(month), ofToInt(day));
        
    }
    
    
    
    long elapsedSeconds = remainingSeconds - getSecondsElapsedBetween(unixTimeWithoutGaps, endingTime);
    
   
    return (float)((float)elapsedSeconds / (float)remainingSeconds);
}

int timeManager::getNumOfNonWorkingsSecondsFor(int month, int day) {
    
    for (int i=0; i<workingTimeData.size(); i++) {
        
        timeData * tmData = workingTimeData[i];
        
        if(month == tmData->month) {
            
            if(day >= tmData->startingDay && day <= tmData->endingDay ) {
                // GO GO GO
               // ofLog(OF_LOG_NOTICE, "ok %d", timeUtils.convertHoursToSeconds(tmData->endingHour, tmData->endingMinut));
                
                return timeUtils.convertHoursToSeconds(tmData->endingHour, tmData->endingMinut) - timeUtils.convertHoursToSeconds(tmData->startingHour, tmData->startingMinut);
                
            }
            
        }
        
        
    }
    
    
}

int timeManager::getNumOfDays(long numOfSeconds) {
    return floor((float)numOfSeconds / 60.0 / 60.0 / 24.0);
    
}