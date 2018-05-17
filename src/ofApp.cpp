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
	blackHole = false;

	x_self = y_self = z_self = 0;

	lineLength = 1;
	distance = 500.f;
	roll = angleH = angleV = 0;
	alpha = 0;
	firstAngle = 0;

	// setup the camera at initial viewing angles
	cam.orbit(0, 0, distance);
	cam.orbit(0, 0, distance);

	allowCamRotate = false;
	drawSphere = false;

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
	if (lineLength >= lineMax) {
		lineToCircle = true;
	}

	if (angleV >= 360) {
		angleV = 0;
	}
	if (angleH >= 360) {
		angleH = 0;
	}
	if (angleV <= -360) {
		angleV = 0;
	}
	if (angleH <= -360) {
		angleH = 0;
	}
	
	// line (1D)
	if (!lineToCircle) { 
		if (ofGetKeyPressed(OF_KEY_UP) || ofGetKeyPressed(OF_KEY_DOWN)) { // only when up or down is pressed
			if (angleV <= 180) cam.orbit(0, angleV, distance);
			//allowCamRotate = true;
			//angleH = 0;
			if (lineLength < lineMax && (angleV > 10 || angleV < -10)) lineLength += 1;
		}
	}
	// circle (2D)
	else if (!circleToSphere) { // keep rotating the sphere
		counter++;
		//if (angleH <= 90 && angleH >= -90) {
		//	allowCamRotate = true;
			//cam.orbit(angleH, angleV, distance);

		if (counter <= 180 ){
			//angleV = 0;
			//allowCamRotate = true;
			cam.orbit(angleH, angleV, distance);
		}
		else if (angleH < 90 && angleH > -90) { // als counter groter is dan 300 en de cirkel nog niet plat is
			//angleV = 0;
			//allowCamRotate = true;
			cam.orbit(angleH, angleV, distance);
		}
		else { // switch to 3D
			lineToCircle = false;
			circleToSphere = true;
		}
	}
	// Sphere (3D)
	if (circleToSphere) {

		// Calculate radial distance to center of the sphere
		camPosition = cam.getGlobalPosition();
		float distance = sqrtf(camPosition[0] * camPosition[0] + camPosition[1] * camPosition[1] + camPosition[2] * camPosition[2]);

		if (distance <= lineLength*0.4) {
			//cerr << z << endl;
			if (alpha < 255) alpha++;
			drawSphere = true;
		}
		if (!drawSphere) {
			if (ofGetKeyPressed(OF_KEY_UP)) { // move forwards into the sphere 
				//if (z_self > -10) z_self -= 0.5; // set maximum backwards speed to -10
				cam.dolly(-2);
			}
			else if (ofGetKeyPressed(OF_KEY_DOWN)) { // register keypress down: move backwards into the sphere
			 //if (z_self < 10) z_self += 0.5; // set maximum speed to 10
				cam.dolly(2);
			}
		}
		else if (ofGetKeyPressed(OF_KEY_UP)) { // move forwards into the sphere 
			if (distance >= lineLength*0.4) {
				cam.tilt(2);
				cam.dolly(-0.5);
			}
			else {
				cam.dolly(-2);
			}
		}
		else if (ofGetKeyPressed(OF_KEY_DOWN)) {
			if (distance >= lineLength*0.4) {
				cam.tilt(-2);
				cam.dolly(0.5);
			}
			else {
				cam.dolly(2);
			}
		}
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

	//if (circleToSphere) {
	//	cam.dolly(z_self); // move along local z-axis in back of forward direction
	//}

	ofPushMatrix(); // global positioning

	ofPushMatrix(); // object positioning

	ofNoFill(); // disable fill color
	ofSetColor(255); // set color to white

	// BLACK HOLE IN YOUR FACE
	if (blackHole) {
		// at random orientation

		float t, p;
		ofVec3f goTo;
		mesh.setMode(OF_PRIMITIVE_LINES);
		for (int j = 0; j <= 360; j += 10) {
			for (int i = 0; i < 140; i++) {
				float R = lineMax*0.5;
				t = float(i* 0.0174533); //radians
				p = float(j* 0.0174533);
				goTo[0] = R * sin(t) * cos(p);
				goTo[1] = R * sin(t) * sin(p);
				goTo[2] = R * cos(t);
				mesh.addVertex(goTo);
			}

			cerr << j << " ";

			//float rad = lineMax*0.5;
			float rad = 1;
			for (int i = 0; i < 200; i++) {
				glPushMatrix();
				ofTranslate(goTo);
				ofRotateZ(float(j));

				ofVec3f first = goTo;

				t = 140 * 0.0174533;
				p = 0;
				first.operator*(rad);
				//ofVec3f second(sin(t) * cos(p), sin(t) * sin(p), cos(t));
				ofVec3f second(goTo[0] - 30 * rad * cos(p), goTo[1] + 0, goTo[2] - 30 * rad);

				//second.operator*(rad);
				t = 160 * 0.0174533;
				ofVec3f third(goTo[0] - 15 * rad  * cos(p), goTo[1], goTo[2] - 500 * rad);

				//ofVec3f third(1.5 * sin(t) * cos(p), -2 * sin(t) * sin(p), cos(t));
				//third.operator*(rad);
				t = 180 * 0.0174533;
				ofVec3f fourth(goTo[0] - 30 * rad * cos(p), goTo[1], goTo[2] - 10000 * rad);
				//ofVec3f fourth(1.5 * sin(t) * cos(p), -5 * sin(t) * sin(p), cos(t));

				//fourth.operator*(rad);
				float time = float(i) / 200.0;
				mesh.addVertex(CalculateBezier(time, first, second, third, fourth));
				glPopMatrix();
			}
		}
		mesh.draw();
		/*
		ofVec3f top(100.0, 50.0, 0.0);
		ofVec3f left(50.0, 150.0, 0.0);
		ofVec3f right(150.0, 150.0, 0.0);

		mesh.addVertex(top);
		mesh.addVertex(left);
		mesh.addVertex(right);
		mesh.draw();
		*/
		// deform circle into tunnel
		ofSetLineWidth(5);
		float R = lineMax*0.5;
		t = 0;
		p = 0;
		ofPushMatrix();
		ofTranslate(0, R, 0);
		goTo[0] = R * sin(t) * cos(p);
		goTo[0] = R;
		goTo[1] = R * sin(t) * sin(p);
		goTo[1] = 0;
		goTo[2] = R * cos(t);
		goTo[2] = 0;
		cerr << goTo[0] << goTo[1] << goTo[2] << endl;
		line.curveTo(goTo, 30);
		line.draw();
		ofSetLineWidth(1);
		ofPopMatrix();

	}

	ofPushMatrix();
	if (!lineToCircle) {
		cylinder.setRadius(lineLength/2);
	}
	ofRotateZ(90);
	cylinder.setResolution(50, 50, 50);
	cylinder.setCapped(false);
	cylinder.draw();

	if (drawSphere) {
		ofSetColor(255, 255, 255, alpha);
		ofDrawSphere(lineLength*0.5);
	}
	ofSetColor(255);
	
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
	case 'b':
		blackHole = true;
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

// Calculate point at time t, on Bezier Curve corresponding to control points (p0, p1, p2, p3)
ofVec3f ofApp::CalculateBezier(GLfloat t, ofVec3f p0, ofVec3f p1, ofVec3f p2, ofVec3f p3)
{
	GLfloat u = 1 - t;
	GLfloat uu = u * u;
	GLfloat uuu = uu * u;
	GLfloat tt = t * t;
	GLfloat ttt = tt * t;
	
	ofVec3f bezier = (p0.operator*(uuu)) + p1.operator*(3 * uu * t) + p2.operator*(3 * u * tt) + p3.operator*(ttt);
	return bezier;
}

