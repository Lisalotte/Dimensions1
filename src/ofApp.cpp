#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	//just set up the openFrameworks stuff
	ofSetFrameRate(60);
	ofSetVerticalSync(true);
	ofBackground(0);  // Clear the screen with a black color	

	cylinder.set(250, 1);
	cyline.set(0.5, 500);

	lineToCircle = false;
	circleToSphere = false;

	x_self = y_self = z_self = 0;

	lineLength = 1;
	distance = 500.f;
	roll = angleH = angleV = 0;

	// setup the camera at initial viewing angles
	cam.orbit(0, 0, distance);
	cam.orbit(0, 0, distance);

	allowCamRotate = false;

	for (int i = 0; i < 300; i++) {
		float x = ofRandomf() * 2000 - 1000;
		float y = ofRandomf() * 2000 - 1000;
		float z = ofRandomf() * 2000 - 1000;
		positions[i][0] = x;
		positions[i][1] = y;
		positions[i][2] = z;

		sphericalPositions[i][0] = ofRandomuf() * 360;
		sphericalPositions[i][1] = ofRandomuf() * 360;
		sphericalPositions[i][2] = ofRandomuf() * 1000 + 1000;
	}
	counter = 0;
}

//--------------------------------------------------------------
void ofApp::update(){
	allowCamRotate = false;
	if (angleV >= 90 || angleV <= -90) {
		lineToCircle = true;
	}

	if (angleV == 360) {
		angleV = 0;
	}
	if (angleH == 360) {
		angleH = 0;
	}
	if (angleV == -360) {
		angleV = 0;
	}
	if (angleH == -360) {
		angleH = 0;
	}
	
	// line (1D)
	if (!lineToCircle) { 
		if (ofGetKeyPressed(OF_KEY_UP) || ofGetKeyPressed(OF_KEY_DOWN)) { // only when up or down is pressed
			cam.orbit(0, angleV, distance);
			//allowCamRotate = true;
			//angleH = 0;
			if (lineLength < 500) lineLength += 1;
		}
	}
	// circle (2D)
	else if (!circleToSphere) { // keep rotating the sphere
		counter++;
		cerr << angleH << endl;
		cerr << counter << endl;
		//if (angleH <= 90 && angleH >= -90) {
		//	allowCamRotate = true;
			//cam.orbit(angleH, angleV, distance);

		if (counter <= 180 ){
			cerr << "countcountocunt" << endl;
			//angleV = 0;
			//allowCamRotate = true;
			cam.orbit(angleH, 0, distance);
		}
		else if (angleH < 90 && angleH > -90) { // als counter groter is dan 300 en de cirkel nog niet plat is
			//angleV = 0;
			//allowCamRotate = true;
			cam.orbit(angleH, 0, distance);
			cerr << angleH << endl;
		}
		else { // switch to 3D
			lineToCircle = false;
			circleToSphere = true;
		}
	}
	// Sphere (3D)
	if (circleToSphere) {
		if (ofGetKeyPressed(OF_KEY_DOWN)) { // register keypress down: move backwards into the sphere
			if (z_self < 10) z_self++; // set maximum speed to 10
		}
		else if (ofGetKeyPressed(OF_KEY_UP)) { // move forwards into the sphere 
			if (z_self > -10) z_self--; // set maximum backwards speed to -10
		}
		cerr << z_self << endl;
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	//ofEnableLighting();
	//ofEnableSmoothing();
	ofEnableDepthTest();

	//glMatrixMode(GL_PROJECTION);
	//cam.setFov(180);
	//cam.setNearClip(1);
	//cam.setFarClip(3000);
	cam.begin(); // enable camera, everything onwards will appear on the screen

	drawStars(); // draw background stars
	if (allowCamRotate) {
		cam.orbit(angleH, angleV, distance);
	}

	if (circleToSphere) {
		cam.dolly(z_self); // move along local z-axis in back of forward direction
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

	ofPushMatrix(); // object positioning

	ofNoFill(); // disable fill color
	ofSetColor(255); // set color to white

	ofPushMatrix();
	if (!lineToCircle) {
		cylinder.setRadius(lineLength);
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
		if (lineToCircle) angleH += 1; // rotate around line -> circle
		break;
	case OF_KEY_RIGHT:
		if (lineToCircle) angleH -= 1; // rotate around line -> circle
		break;
	case OF_KEY_UP:
		angleV -= 1;
		break;
	case OF_KEY_DOWN:
		angleV += 1;
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

//--------------------------------------------------------------
void ofApp::drawStars() { 

	for (int i = 0; i < 300; i++) {
		ofPushMatrix();
		// azimuth
		float rotate = sphericalPositions[i][0];
		ofRotateX(sphericalPositions[i][0]);
		// declination
		ofRotateY(sphericalPositions[i][1]);
		// radius
		ofTranslate(sphericalPositions[i][2], 0, 0);
		
		//float x = positions[i][0];
		//float y = positions[i][1];
		//float z = positions[i][2];
//		ofDrawSphere(ofPoint(x, y, z), 2);
		ofDrawSphere(ofPoint(0, 0, 0), 2);
		ofPopMatrix();
	}

}
