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
#include "tcpManager.h"
#include "ofxXmlSettings.h"
#include "eventData.h"

class dataManager {
    
public:
    
    void setup(tcpManager * tcp);
    void update(long currentUnixTime);
    void loadLocalXml ();
    void loadFromBuffer(string data);    
    void onXmlReceived(string & xml);
    
    void createColors();
    vector<ofColor*> * getColorForSilo(int typeID);
    ofColor * getColorForSilo(int typeID, int siloIndex);
    
    eventData * getNextEventData();
    eventData * getFinishedEventData ();
    
private:
    
    void clean();
    void parseXml();
    void backupXml();
    
    tcpManager *   tcp;
    ofxXmlSettings      xml;
    
    vector<eventData*>  events;
    
    
    vector<vector<ofColor*> > colors;
};


#endif
