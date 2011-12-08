//
//  flashUdpManager.cpp
//  networkUdpReceiverExample
//
//  Created by Martial Geoffre-Rouland on 19/08/2011.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "flashUdpManager.h"

void flashUdpManager::setup () {
    
	flash.setup("192.168.1.9", 1234);
	flash.addPolicy("*","*"); 
	flash.start();
    
}

void flashUdpManager::update () {
    
    while(flash.hasMessage()) {
        
		string message = flash.getNextMessage();
        
        if( message == "Starbuck, what do you hear?" ) {
            flash.send("Nothing but the rain sir.");
        } else {
            
            flash.send("xml received correctly");
            ofNotifyEvent(xmlEvt, message, this);
            
        }
        
		cout << "received: '" << message << "'" << endl;
	}
    
}