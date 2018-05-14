#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofBackground(0);  // Clear the screen with a black color

	cylinder.set(250, 1);
	cyline.set(0.5, 500);

	myRotation = 0;
	lineToCyl = false;
}

//--------------------------------------------------------------
void ofApp::update(){
	if (myRotation >= 90 || myRotation <= -90) {
		lineToCyl = true;
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofEnableDepthTest();

	ofNoFill();
	ofSetColor(255);
	ofPushMatrix();
	ofPoint p1(ofGetWidth()*0.5 - x_self, ofGetHeight()*0.5 + y_self, 0 + z_self);
	ofTranslate(p1);

	ofSetColor(255, 0, 0);
	ofLine(-1000, 0, 0, 1000, 0, 0);
	ofSetColor(0, 255, 0);
	ofLine(0, -1000, 0, 0, 1000, 0);
	ofSetColor(0, 0, 255);
	ofLine(0, 0, 1000, 0, 0, -1000);
	ofSetColor(255);
	ofPushMatrix();

	// Adjust to user input
	ofRotateX(myRotation);

	if (!lineToCyl) {
		/*
		// Draw a line
		ofLine(0, 0, 250, 0, 0, -250);
		ofSetLineWidth(1);
		// Draw the begin and end caps
		ofPushMatrix();
		ofTranslate(0, 0, 250);
		ofDrawEllipse(ofPoint(0, 0, 0), 1, 1);
		ofTranslate(0, 0, -500);
		ofDrawEllipse(ofPoint(0, 0, 0), 1, 1);
		ofPopMatrix();
		*/
		ofPushMatrix();
		ofRotateX(90);
		cyline.setResolution(50, 50, 50);
		cyline.draw();
		ofPopMatrix();
		
		cerr << "LINE" << endl;
	} else {
		ofPushMatrix();
		ofRotateZ(90);
		cylinder.setResolution(50, 50, 50);
		cylinder.setCapped(false);
		cylinder.draw();
		ofPopMatrix();
		cerr << "NOT LINE" << endl;
		ofPushMatrix();
		ofRotateX(90);
		cyline.setResolution(50, 50, 50);
		cyline.draw();
		ofPopMatrix();
	}
	
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
