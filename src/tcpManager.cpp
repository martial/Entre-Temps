/*
 *  tcpManager.cpp
 *  EntreTemps
 *
 *  Created by Martial on 06/12/2011.
 *  Copyright 2011 Martial. All rights reserved.
 *
 */

#include "tcpManager.h"


void tcpManager::setup () {
    
	TCP.setup(11999);
    TCP.setMessageDelimiter("\n");
    bHasClientConnected = false;
}
 
void tcpManager::update () {
    
    
	bHasClientConnected = false;
	for(int i = 0; i < TCP.getLastID(); i++){
		
		if( !TCP.isClientConnected(i) )continue;
        
        bHasClientConnected = true;
        
        // printf("update??");
        
		string str = TCP.receive(i);
        
              
		if(str.length() > 0){
            
            ofLog(OF_LOG_NOTICE, "Received : " + str);

           			
			if ( str == "Starbuck, what do you hear?" ) {
				
				TCP.send(i, "Nothing but the rain sir." );
				
			} else {
				
				ofNotifyEvent(xmlEvt, str, this);
				
			}
			
		}
		
	}
      
}

