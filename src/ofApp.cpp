#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofBackground(0);  // Clear the screen with a black color

	cylinder.set(1, 500);

	myRotation = 0;
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	ofEnableDepthTest();

	//ofNoFill();
	ofSetColor(255);
	ofPushMatrix();
	ofPoint p1(ofGetWidth()*0.5 - x_self, ofGetHeight()*0.5 + y_self, 0 + z_self);
	ofTranslate(p1);

	ofPushMatrix();
	//ofRotateX(90);
	ofRotateX(myRotation);
	ofLine(0, 0, 250, 0, 0, -250);
	ofSetLineWidth(5);
	ofPushMatrix();
	ofTranslate(0, 0, 250);
	ofDrawSphere(2.5);
	ofTranslate(0, 0, -500);
	ofDrawSphere(2.5);
	ofPopMatrix();
	//cylinder.draw();
	ofPopMatrix();

	
//	myNode.tilt(20);
	//cerr << z << endl;

	/*
	cylinder.setCapped(false);
	cylinder.setResolution(20,20,20);
	cylinder.drawWireframe();
	*/
	ofPopMatrix();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

	switch (key) {
	case OF_KEY_LEFT:
		x_self = x_self - 5;
		break;
	case OF_KEY_RIGHT:
		x_self = x_self + 5;
		break;
	case OF_KEY_UP:
		//y_self = y_self + 1;
		//z_self = z_self + 5;
		myRotation = myRotation + 1;
		break;
	case OF_KEY_DOWN:
		//y_self = y_self - 1;
		//z_self = z_self - 5;
		myRotation = myRotation - 1;
		break;
	}

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
