#include "ofApp.h"
#include <stdlib.h>
#include <math.h>

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(10);
    ofSetBackgroundColor(0,0,0);
    ofSetWindowShape(800, 800);
    
    
    wbs.set(10000,10000);
    bs.set(0, 0);
    
    //initialize starting positions, velocity and evaluation value of particles randomly
    for (int i = 0; i < theNumberOfParticles; i++) {
        pos[i].set(ofRandom(-1000,1000), ofRandom(-1000,1000));
        vel[i].set(ofRandom(-1,1), ofRandom(-1,1));
        pbs[i].set(ofRandom(-10000,10000), ofRandom(-10000,10000));
        
    }
   
 
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    if (t < theNumberOfMaxTrial){
    
    double w = 0.8;
    double c1 = 1;
    double c2 = 1;
    double r1 = ofRandom(0,1);
    double r2 = ofRandom(0,1);
    double candis; //candidate distance
    double pbsdis; //personel best distanse
    double wbsdis; // whole best distance
    
    
    for (int i = 0; i < theNumberOfParticles; i++) {
        
        //x(t+1)の位置をx(t)+v(i)で更新、x(t+1)とbest solutionの距離を取得
        pos[i].set(pos[i]+vel[i]);
        candis = evaluation(bs,pos[i]); 
        pbsdis = evaluation(bs,pbs[i]);
        wbsdis = evaluation(bs, wbs);
        
        
        //personel best solutionの更新
        //x(t+1)とbest solutionの距離　< personel best solutionとbest soultionの距離
        //つまり、x(t+1)の方がそれまでのpersonel best solutionよりbsに近い（＝評価値が高い時）
        // personel best solutionをx(t+1)で更新
        if (candis < pbsdis) {
            pbs[i].set(pos[i]);
        } 
        
        //whole best solutionの更新
        //x(t+1)とbest solutionの距離　< whole best solutionとbest soultionの距離
        //つまり、x(t+1)の方がそれまでのwhole best solutionよりbsに近い（＝評価値が高い時）
        // whole best solutionをx(t+1)で更新
        else if (candis < wbsdis){
            wbs.set(pos[i]);
        }
    
        
       
        newvel = (w * vel[i]) + (r1 * c1 * (pbs[i] - pos[i])) + (r2 * c2 * (wbs - pos[i])); 
        vel[i].set(newvel);
    }
    
    t++;
    }

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofTranslate(400, 400);
    ofScale(1, -1);

        
    ofSetColor(255, 255, 255);
    ofDrawCircle(bs, 10); //bestsolution white
    ofSetColor(255, 0, 0);
    ofDrawCircle(wbs, 10); //global best solution red
    ofDrawLine(bs,wbs);
    
    for (int i = 0; i < theNumberOfParticles; i++) {
        ofSetColor(0, 255, 0);
        ofDrawCircle(pos[i], 10); //searching green
        ofDrawLine(bs, pos[i]);
        ofSetColor(0, 0, 255);
        ofDrawCircle(pbs[i], 10); //local best solution blue
        ofDrawLine(bs,pbs[i]);
        ofSetColor(0, 0, 255);
        ofDrawBitmapString("pbs" + ofToString(i) + ": " + ofToString(pbs[i]), -360, 360 + (-i*10));
       
        //wbs==pbsの時、pbsを赤色で表示
        for (int i = 0; i < theNumberOfParticles; i++){
            if(evaluation(bs,pbs[i]) == evaluation(bs, wbs)){
                ofSetColor(255, 0, 0);
                ofDrawBitmapString("pbs" + ofToString(i) + ": " + ofToString(pbs[i]), -360, 360 + (-i*10));
                
            }
        }
    
    }
    ofSetColor(255, 255, 255);
    ofDrawBitmapString("trial: " + ofToString(t), -380, 380);
    ofSetColor(255, 0, 0);
    ofDrawBitmapString("wbs: " + ofToString(wbs), -370, 370);
    
    
}

//--------------------------------------------------------------
//ピタゴラスの定理で距離を算出する評価関数
double ofApp::evaluation(ofVec2f &bestsolution, ofVec2f &candidate){
    double x;
    double y;
    double distance;
    x = abs(bestsolution.x - candidate.x);
    y = abs(bestsolution.y - candidate.y);
    distance = sqrt(x*x + y*y);
    return distance;
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 
    
}

