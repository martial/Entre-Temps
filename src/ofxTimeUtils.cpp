//
//  ofxTimeUtils.cpp
//  networkUdpReceiverExample
//
//  Created by Martial Geoffre-Rouland on 22/09/2011.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include "ofxTimeUtils.h"


ofxTimeUtils::ofxTimeUtils () {
    

}

int ofxTimeUtils::getCurrentDate(long posixTime) {
    
}

int ofxTimeUtils::getCurrentDate() {
    
}
int ofxTimeUtils::getCurrentMonth() {
    
}
int ofxTimeUtils::getCurrentDay() {
    
}

int ofxTimeUtils::getCurrentHour() {
    
}

int ofxTimeUtils::getCurrentMinut() {
    
}

int ofxTimeUtils::getCurrentSecond() {
    
}

int ofxTimeUtils::convertHoursToSeconds(int hour, int minuts) {
    return convertHoursToSeconds (hour * 60) + convertMinutsToSeconds(minuts);
}

int ofxTimeUtils::convertHoursToSeconds(int hour) {
    return convertMinutsToSeconds (hour * 60);
}

int ofxTimeUtils::convertMinutsToSeconds(int minuts) {
    return  minuts * 60;
}
