//
//  ofxTimeUtils.h
//  networkUdpReceiverExample
//
//  Created by Martial Geoffre-Rouland on 22/09/2011.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef OFXTMUTLS
#define OFXTMUTLS

#include "ofMain.h"

class ofxTimeUtils {
    
public:
    
    ofxTimeUtils();
    int getCurrentDate();
    int getCurrentDate(long posixTime);
    
    int getCurrentMonth();
    int getCurrentDay();
    int getCurrentHour();
    int getCurrentMinut();
    int getCurrentSecond();
    
    
    int convertHoursToSeconds(int hour, int minuts);
    int convertHoursToSeconds(int hour);
    int convertMinutsToSeconds(int minuts);
    
};


#endif
