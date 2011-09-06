//
//  dataManager.cpp
//  networkUdpReceiverExample
//
//  Created by Martial Geoffre-Rouland on 19/08/2011.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "dataManager.h"

void dataManager::setup(flashUdpManager * flash){
    this->flash = flash;
    ofAddListener(flash->xmlEvt, this, &dataManager::onXmlReceived);
        
    loadLocalXml();
    
}

void dataManager::update(long currentUnixTime) {
    
    for (int i=0; i<events.size(); i++) {
        events[i]->updateStatus(currentUnixTime);
    }
    
}


void dataManager::loadLocalXml () {
    
    clean();
    
    if(!xml.loadFile("data.xml")) {
        ofLog(OF_LOG_NOTICE, "- hey. No xml here. First time uh ?" );
    } else {
        parseXml();
    }
    
}

void dataManager::loadFromBuffer (string data) {
    
    clean();
    xml.loadFromBuffer(data);
}


void dataManager::backupXml() {
    
    xml.saveFile("data.xml");
    
}

void dataManager::onXmlReceived(string & xml){
    
    loadFromBuffer(xml);
    parseXml();
    backupXml();
    
}


void dataManager::clean() {
    
    xml.clear();    
    for ( vector<eventData*>::iterator it = events.begin(); it != events.end(); ++it ) delete * it;
    events.clear();
    
}
void dataManager::parseXml() {
    
    ofLog(OF_LOG_NOTICE, "[Parsing XML]");
    
    xml.pushTag("root");
    xml.pushTag("events");
    
    int numOfEvents = xml.getNumTags("event");
    
    for( int i=0; i<numOfEvents; i++ ) {
        
        xml.pushTag("event",i);
        
        eventData * evtData = new eventData();
        
        evtData->id = xml.getValue("id", "null");
        evtData->name = xml.getValue("title", "null");
        evtData->posixTime = xml.getValue("posixTime", 0);
        evtData->duration = xml.getValue("duration", 0);
        evtData->typeID = xml.getValue("typeID", 0);
        evtData->typeColor = xml.getValue("typeColor", 0);
        events.push_back(evtData);
        
        xml.popTag();
        
      
        
    }
    
    xml.popTag();
    xml.popTag();
    
    ofLog(OF_LOG_NOTICE, "there are %d events", events.size());
    
    
}

eventData * dataManager::getNextEventData () {
    
    // check for most recent - should not be essential but who knows?
    
    
    
    long  lowestPosixTime = LONG_MAX;
    int index = 0;
    for (int i=0; i<events.size(); i++) {
        if(!events[i]->isFinished) {
            if ( lowestPosixTime > events[i]->posixTime ) {
                lowestPosixTime = events[i]->posixTime;
                index = i;
            }
        }
    }
    return events[index];
}

eventData * dataManager::getFinishedEventData () {
    
    for (int i=0; i<events.size(); i++) {
        if(events[i]->isFinished) return events[i];
    }
    return NULL;
}

