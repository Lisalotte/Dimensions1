#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofBackground(0);  // Clear the screen with a black color

	cylinder.set(100, 1);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	ofEnableDepthTest();

	ofNoFill();
	ofSetColor(255);
	ofPushMatrix();
	ofPoint p1(500, 500, 0);
	ofTranslate(p1);
	//ofRotateX(90);
	//ofDrawCylinder(0, 0, 0, 100, 1);
	cylinder.setCapped(false);
	cylinder.setResolution(20,20,20);
	cylinder.drawWireframe();
	ofPopMatrix();
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
