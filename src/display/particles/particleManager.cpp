//
//  particleManager.cpp
//  networkUdpReceiverExample
//
//  Created by Martial Geoffre-Rouland on 23/08/2011.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "particleManager.h"

void particleManager::setup() {
    
    addBounds();
    getNumOfPixelsInBounds();
    
    bClearFixed = false;
    mainColor = 0xffffff;
    
    //ofLog(OF_LOG_NOTICE, "num of pixels in bouns size ? %d", getNumOfPixelsInBounds());
    
}
void particleManager::update() {
    
   
    
    for ( int i=0; i<particles.size(); i++ ) {
        particles[i]->resetForce();
        particles[i]->addForce(0, 0.008);
        
        if(!bClearFixed) {
            checkForCollisions(particles[i]);   
        } else {
            particles[i]->addDampingForce();
        }
        
        particles[i]->update();
        
        if(particles[i]->pos.y > polyBound.getBoundingBox().height+1 ) removeParticle(particles[i]);
        
    }
    
    if(isFull()) {
        ofLog(OF_LOG_NOTICE, "test size ? %d", particles.size());
    }
    
    
    /*
     
     */
     
    
}
void particleManager::draw() {
    
    ofSetColor(0,255,0);
    //polyBound.draw();
    
    
    ofSetColor(0, 255, 255);
    
    for ( int i=0; i<boundVertices.size()-1; i++ ) {
        
        // calculate length of every segment and interpolate coords.
        
        ofVec2f diff = boundVertices[i] - boundVertices[i+1];
        int _max = max(abs(diff.x), abs(diff.y));
        float cnt = 0.0;
        for ( int j=0; j<_max; j++ ) {
            ofxVec2f interpolatedP =  boundVertices[i].getInterpolated( boundVertices[i+1], (float)j/(float)(_max));
            ofRect(interpolatedP.x, interpolatedP.y, 1, 1);
        }
        
    }

    
    
    int numOfParticles = particles.size();
    int numOfVertices = numOfParticles * 2;
    GLfloat vertices[numOfVertices];
    GLfloat colors[numOfParticles*4];
    
    int vCnt = 0;
    int cCnt = 0;
    for ( int i=0; i<numOfParticles; i++ ) {
        
        vertices[vCnt++] = particles[i]->pos.x;
        vertices[vCnt++] = particles[i]->pos.y;
        
        colors[cCnt++] = particles[i]->color.r / 255.0;
        colors[cCnt++] = particles[i]->color.g / 255.0; 
        colors[cCnt++] = particles[i]->color.b / 255.0; 
        colors[cCnt++] = particles[i]->color.a / 255.0; 
        
    }
        
    ofSetColor(255, 255, 255);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glColorPointer(4, GL_FLOAT, 0, colors);
    glVertexPointer(2, GL_FLOAT, 0, vertices);        
    glDrawArrays(GL_POINTS, 0, numOfParticles);
    glDisableClientState(GL_VERTEX_ARRAY);  
    glDisableClientState(GL_COLOR_ARRAY);
    
    
    
}

void particleManager::addParticle(int x, int y) {
    
    particle * ptcl = new particle();
    ptcl->setup(this,x,y);
    ptcl->id = particles.size();
    particles.push_back(ptcl);
    
}

void particleManager::removeParticle(particle *p) {
  
    
    for ( vector<particle*>::iterator it = particles.begin(); it != particles.end(); ++it ) {
        if( (*it)->pos == p->pos  ) {
            delete * it;  
            particles.erase(it);
        } else {
        
        }
    }
    
}

void particleManager::removeLastParticle() {
    
    if(particles.size() < 1 ) return;
       
        delete particles[particles.size()-1]; 
        particles.pop_back();
       
    
    
}

void particleManager::checkForCollisions(particle * p) {
        
       // first check polygon boundaries
    //if ( !p->isFixed ) p->checkCollision();
    for ( int i=0; i<boundVertices.size()-1; i++ ) {
        
        ofVec2f diff = boundVertices[i] - boundVertices[i+1];
        int _max = max(abs(diff.x), abs(diff.y));
        for ( int j=0; j<_max; j++ ) {
            ofxVec2f interpolatedP =  boundVertices[i].getInterpolated( boundVertices[i+1], (float)j/(float)(_max));
            p->checkCollision(interpolatedP);
            if(p->isFixed) return;
        }
             
    }
    
   if(!p->isFixed) p->checkCollision();
   
    
}

float particleManager::getNextHighestYPos(float x, particle * p) {
    
    float highest = 9999.0;
    int index = 0;
    for ( int i=0; i<particles.size(); i++ ) {
        
        // avoid same particle.
        if( p != 0 && particles[i]->id == p->id ) continue;
        
        // avoid non fixed particles.
        if(!particles[i]->isFixed) continue;
                
        // avoid particles on other xcoord.
        
        if (particles[i]->pos.x != x ) continue;
               
        if(particles[i]->pos.y <= highest) {
            highest  = particles[i]->pos.y;
            
        }
        
    }
    
    
    
    return highest;
}

bool particleManager::isFull() {
    
  
    int cnt = 0;
    for ( int i=1; i<polyBound.getBoundingBox().width; i++ ) {
        
        if ( getNextHighestYPos(i) <= 0 ) {
            cnt++;
        }
        
    }
    
    return ( cnt >= polyBound.getBoundingBox().width-1 );
    
}

bool particleManager::isColumnFull(int x) {
    
    return  (getNextHighestYPos(x) <= 0 ); 
    
}

void particleManager::clear () {
    
    
    for ( vector<particle*>::iterator it = particles.begin(); it != particles.end(); ++it ) delete * it;
    particles.clear();
    
}

void particleManager::clearFixed (bool bClearFixed) {
     
     this->bClearFixed = bClearFixed;
     for ( int i=0; i<particles.size(); i++ ) {
         particles[i]->isFixed = false;
         particles[i]->damping =  (particles[i]->pos.y * .001 / polyBound.getBoundingBox().height) + ofRandom(0.001);
     }
    
}

int particleManager::pnpoly(int nvert, float *vertx, float *verty, float testx, float testy)
{
    int i, j, c = 0;
    for (i = 0, j = nvert-1; i < nvert; j = i++) {
        if ( ((verty[i]>testy) != (verty[j]>testy)) &&
            (testx < (vertx[j]-vertx[i]) * (testy-verty[i]) / (verty[j]-verty[i]) + vertx[i]) )
            c = !c;
    }
    return c;
}

void particleManager::addBounds() {
    
    vector<int> pts;
    
    
    pts.push_back(0);
    pts.push_back(0);
         
    pts.push_back(0);
    pts.push_back(42);
    
    
    pts.push_back(9);
    pts.push_back(51);
    
    pts.push_back(18);
    pts.push_back(42);
        
    pts.push_back(18);
    pts.push_back(0);
    

   
    
    
    for (int j=0; j<pts.size(); j+=2) {
        
        
        float x = pts[j];
        float y = pts[j+1];
        polyBound.addVertex(x, y);
        
        ofxVec2f vertice;
        vertice.set(x, y);
        boundVertices.push_back(vertice);
        
    }

    
}


int particleManager::getNumOfPixelsInBounds() {
    
    
    ofRectangle box = polyBound.getBoundingBox();
    
    float  vertx[polyBound.getVertices().size()];
    float  verty[polyBound.getVertices().size()];
    
    for ( int i=0; i<boundVertices.size(); i++ ) {
        
        vertx[i] = boundVertices[i].x;
        verty[i] = boundVertices[i].y;
        
    }
    
    int cnt = 0;
    for ( int i=0; i<box.width; i++ ) {
        
        for ( int j=0; j<box.height; j++ ) {
            
            if ( pnpoly(boundVertices.size(), vertx, verty, i,j) == 1 ) {
                cnt++; 
            }
        }
        
        
    }
    ofLog(OF_LOG_NOTICE, "Result ? %d", cnt);

}
