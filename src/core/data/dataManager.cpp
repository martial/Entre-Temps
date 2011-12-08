//
//  dataManager.cpp
//  networkUdpReceiverExample
//
//  Created by Martial Geoffre-Rouland on 19/08/2011.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "dataManager.h"

void dataManager::setup(tcpManager * tcp){
    this->tcp = tcp;
    ofAddListener(tcp->xmlEvt, this, &dataManager::onXmlReceived);
    
    createColors();
    loadLocalXml();
    
    
}

void dataManager::createColors () {
    
    
    vector<ofColor*> colors0;
    vector<ofColor*> colors1;
    vector<ofColor*> colors2;
    vector<ofColor*> colors3;
    vector<ofColor*> colors4;
    
    colors0.push_back(new ofColor(0,67,255));
    colors0.push_back(new ofColor(255,238,0));
    colors0.push_back(new ofColor(255,70, 67));
    
    colors1.push_back(new ofColor(255,78,0));
    colors1.push_back(new ofColor(249,121,0));
    colors1.push_back(new ofColor(255,182,0));
    
    colors2.push_back(new ofColor(255,255,255));
    colors2.push_back(new ofColor(255,248,47));
    colors2.push_back(new ofColor(194,255,0));
    
    colors3.push_back(new ofColor(247,105,1));
    colors3.push_back(new ofColor(255,0,0));
    colors3.push_back(new ofColor(255,51,68));
    
    colors4.push_back(new ofColor(0, 115, 199));
    colors4.push_back(new ofColor(0,241,255));
    colors4.push_back(new ofColor(0,0,243));
    

    colors.push_back(colors0);
    colors.push_back(colors1);
    colors.push_back(colors2);
    colors.push_back(colors3);
    colors.push_back(colors4);
    
    
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
        
        evtData->siloNumber = xml.getValue("siloIndex", "012");
        
        events.push_back(evtData);
        
        xml.popTag();
        
      
        
    }
    
    xml.popTag();
    xml.popTag();
    
    
    
}

eventData * dataManager::getNextEventData () {
    
    // check for most recent - should not be essential but who knows?
    
    //ofLog(OF_LOG_NOTICE, "events.size() %d", events.size());
    if(events.size() < 2 ) return NULL;
    
    
    
    long  lowestPosixTime = LONG_MAX;
    int index = -1;
    for (int i=0; i<events.size(); i++) {
        if(!events[i]->isFinished) {
            if ( lowestPosixTime > events[i]->posixTime ) {
                lowestPosixTime = events[i]->posixTime;
                index = i;
            }
        }
    }
    
    // this means that we have actually only finished events in the xml..
    if(index == -1 ) return NULL;
    
    // we're ok - go !
    return events[index];
}

eventData * dataManager::getFinishedEventData () {
    
    for (int i=0; i<events.size(); i++) {
        if(events[i]->isFinished) return events[i];
    }
    return NULL;
}


ofColor * dataManager::getColorForSilo(int typeID, int siloIndex) {
        
    return colors[typeID][siloIndex];
       
}

vector<ofColor*> * dataManager::getColorForSilo(int typeID) {
        
    return &colors[typeID];

}

