#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	//just set up the openFrameworks stuff
	ofSetFrameRate(60);
	ofSetVerticalSync(true);
	ofBackground(0);  // Clear the screen with a black color	

	cylinder.set(250, 1);
	cyline.set(0.5, 500);

	lineToCyl = false;
	lineLength = 1;
	distance = 500.f;
	roll = angleH = angleV = 0;

	for (int i = 0; i < 300; i++) {
		float x = ofRandomf() * 2000 - 1000;
		float y = ofRandomf() * 2000 - 1000;
		float z = ofRandomf() * 2000 - 1000;
		cerr << x << y << z << endl;
		positions[i][0] = x;
		positions[i][1] = y;
		positions[i][2] = z;
	}
}

//--------------------------------------------------------------
void ofApp::update(){
	if (angleV >= 90 || angleV <= -90) {
		lineToCyl = true;
	}
	if (!lineToCyl) {
		cam.orbit(0, angleV, distance);
	}
	else {
		cam.orbit(angleH, 0, distance);
	}
	cam.roll(roll);
}

//--------------------------------------------------------------
void ofApp::draw(){
	//ofEnableLighting();
	//ofEnableSmoothing();
	ofEnableDepthTest();

	//glMatrixMode(GL_PROJECTION);
	//cam.setFov(180);
	//cam.setNearClip(1);
	cam.setFarClip(2000);
	cam.begin();

	for (int i = 0; i < 300; i++) {
		float x = positions[i][0];
		float y = positions[i][1];
		float z = positions[i][2];
		ofDrawSphere(ofPoint(x, y, z), 2);
	}

	ofPushMatrix(); // global positioning
	/*
	ofPoint p1(ofGetWidth()*0.5 - x_self, ofGetHeight()*0.5 + y_self, 0 + z_self);
	ofTranslate(p1);
	*//*
	// Adjust to user input
	ofRotateX(x_rot);
	ofRotateY(y_rot);
	ofRotateZ(z_rot);
	*/

	ofVec3f center = ofVec3f(0, 0, 0);
	//cam.lookAt(center);

	ofPushMatrix(); // object positioning

	ofNoFill();
	ofSetColor(255);

	/*
	// x,y,z-axes
	ofSetColor(255, 0, 0);
	ofLine(-1000, 0, 0, 1000, 0, 0);
	ofSetColor(0, 255, 0);
	ofLine(0, -1000, 0, 0, 1000, 0);
	ofSetColor(0, 0, 255);
	ofLine(0, 0, 1000, 0, 0, -1000);
	ofSetColor(255);
	*/
	ofPushMatrix();
	if (!lineToCyl) {
		cylinder.setRadius(lineLength);
		cerr << "LINE" << endl;
	} else {
		cerr << "NOT LINE" << endl;
	}
	ofRotateZ(90);
	cylinder.setResolution(50, 50, 50);
	cylinder.setCapped(false);
	cylinder.draw();
	ofPopMatrix();

	ofPopMatrix(); // objects

	ofPopMatrix(); // global

	cam.end();

	//ofDisableLighting();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	switch (key) {
	case OF_KEY_LEFT:
		angleH -= 1;
		break;
	case OF_KEY_RIGHT:
		angleH += 1;
		break;
	case OF_KEY_UP:
		angleV += 1;
		break;
	case OF_KEY_DOWN:
		angleV -= 1;
		break;
	case 'r':
		roll++;
		break;
	}
	if (angleV < 90 && angleV > -90) {
		lineLength += 2;
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
