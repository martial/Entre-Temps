//
//  dataManager.h
//  networkUdpReceiverExample
//
//  Created by Martial Geoffre-Rouland on 19/08/2011.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef DATAMNGR
#define DATAMNGR

#include "ofMain.h"
#include "flashUdpManager.h"
#include "ofxXmlSettings.h"
#include "eventData.h"

class dataManager {
    
public:
    
    void setup(flashUdpManager * flash);
    void update(long currentUnixTime);
    void loadLocalXml ();
    void loadFromBuffer(string data);    
    void onXmlReceived(string & xml);
    
    eventData * getNextEventData();
    eventData * getFinishedEventData ();
    
private:
    
    void clean();
    void parseXml();
    void backupXml();
    
    flashUdpManager *   flash;
    ofxXmlSettings      xml;
    
    vector<eventData*>  events;
    
};


#endif
