#include "ofApp.h"

/*
This program shows you a dot (1D) that transforms into a line, which transforms into a circle (2D).
(In the code, the dot and the line are oddly shaped ellipses.) The circle, in turn, transforms
into a sphere (3D) once you enter it. Then, when you are inside the sphere, a black hole is created.
The black hole is a tunnel that will compress you back to 1D, into a dot.
*/

void ofApp::setup() {
	ofSetFrameRate(60);
	ofSetVerticalSync(true);
	ofBackground(0);

	cylinder.set(1, 1);		// Create a dot

	lineToCircle = false;
	circleToSphere = false;
	blackHole = false;
	drawSphere = false;
	allowHorizontalOrbit = true;
	allowVerticalOrbit = true;

	lineLength = 1;
	distance = 500.f;
	angleH = angleV = 0;
	alpha = 0;
	counter = 0;
	counter2 = 0;
	lookat = 0;

	blackHolePos = ofVec3f(0, 0, -50000);

	// Setup the camera's initial viewing angles
	cam.orbit(0, 0, distance);
	cam.orbit(0, 0, distance);

	// Setup the coordinates for 300 stars
	for (int i = 0; i < 300; i++) {
		sphericalPositions[i][0] = ofRandomuf() * 360;
		sphericalPositions[i][1] = ofRandomuf() * 360;
		sphericalPositions[i][2] = ofRandomuf() * 1000 + 1000;
	}
}

//--------------------------------------------------------------
void ofApp::update() {
	if (lineLength >= lineMax) {
		lineToCircle = true;
	}

	// Reset angles when they reach 360
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

	// Line (1D)
	if (!lineToCircle) { // Orbit vertically around the line
		allowHorizontalOrbit = false;
		cam.orbit(angleH, angleV, distance);
		lineLength = abs(angleV) * (299 / 90) + 1; // Make the line look longer when you orbit vertically around it
	}

	// Circle (2D)
	else if (lineToCircle) { // Orbit around the circle
		counter++;
		if (counter <= 900) {
			allowHorizontalOrbit = true;
			cam.orbit(angleH, angleV, distance);
		}
		else if (angleV < 180 && angleV > -180) {
			allowHorizontalOrbit = true;
			cam.orbit(angleH, angleV, distance);
		}
		else if (counter <= 1200) {
			allowHorizontalOrbit = true;
			allowVerticalOrbit = false;
			cam.orbit(angleH, angleV, distance);
		}
		else if (angleH < 90 && angleH > -90) {
			allowHorizontalOrbit = true;
			allowVerticalOrbit = false;
			cam.orbit(angleH, angleV, distance);
		}
		else { // Switch to 3D
			lineToCircle = false;
			circleToSphere = true;
		}
	}
	// Sphere (3D)
	if (circleToSphere) {

		// Calculate radial distance to center of the sphere
		camPosition = cam.getGlobalPosition();
		float distance = sqrtf(camPosition[0] * camPosition[0] + camPosition[1] * camPosition[1] + camPosition[2] * camPosition[2]);

		if (!drawSphere) {
			if (ofGetKeyPressed(OF_KEY_UP)) { // Move forwards into the sphere 
				cam.dolly(-2);
			}
			else if (ofGetKeyPressed(OF_KEY_DOWN)) { // Register keypress down: move backwards into the sphere
				cam.dolly(2);
			}
		}
		if (!blackHole && distance <= 50) {
			while (distance > 5) {
				cam.setPosition(camPosition - camPosition.operator*(0.1));
				camPosition = cam.getGlobalPosition();
				distance = sqrtf(camPosition[0] * camPosition[0] + camPosition[1] * camPosition[1] + camPosition[2] * camPosition[2]);
			}
			cam.setPosition(ofPoint(0, 0, 0));
			// rotate enabled
			if (alpha < 255) {
				alpha++;
			}
			drawSphere = true;

		}

		if (drawSphere) {
			allowHorizontalOrbit = false;
			allowVerticalOrbit = false;
			if (ofGetKeyPressed(OF_KEY_UP)) {
				cam.tilt(1);
			}
			if (ofGetKeyPressed(OF_KEY_DOWN)) {
				cam.tilt(-1);
			}
			if (ofGetKeyPressed(OF_KEY_LEFT)) {
				cam.pan(1);
			}
			if (ofGetKeyPressed(OF_KEY_RIGHT)) {
				cam.pan(-1);
			}
			counter2++;

			if (counter2 > 420) {
				blackHole = true;
				if (alpha > 0) alpha--;
				else {
					drawSphere = false;
				}
			}
		}
		if (blackHole) {
			allowHorizontalOrbit = false;
			allowVerticalOrbit = false;
			camPosition = cam.getGlobalPosition();
			float bhDistance = camPosition.distance(blackHolePos);

			ofPoint dir = cam.getLookAtDir();
			dir = dir.normalize();
			float xdir = -1 * dir[0];
			float ydir = -1 * dir[1];
			float zdir = -1 * (dir[2]);

			if (firstTime) {
				for (int j = 0; j < 500; j++) {
					camPosition = cam.getGlobalPosition();
					cam.lookAt(dir + (ofPoint(xdir, ydir, zdir - camPosition[2] - 1).operator/(500.0)));
				}
				cam.lookAt(ofPoint(0, 0, -50000));
				firstTime = false;
				time = 0;
			}

			if (camPosition[2] > blackHolePos[2]) {
				camPosition = cam.getGlobalPosition();
				//bhDistance = camPosition.distance(blackHolePos);
				cam.setPosition(camPosition + ofPoint(0, 0, -5 - 0.01*time*time));
				time = time + 1;
			}
			else {
				ofBackground(0);

				cylinder.set(1, 1);		// Create a dot

				lineToCircle = false;
				circleToSphere = false;
				blackHole = false;
				drawSphere = false;
				allowHorizontalOrbit = true;
				allowVerticalOrbit = true;

				lineLength = 1;
				distance = 500.f;
				angleH = angleV = 0;
				alpha = 0;
				counter = 0;
				counter2 = 0;
				lookat = 0;

				blackHolePos = ofVec3f(0, 0, -50000);

				// Setup the camera's initial viewing angles
				cam.orbit(0, 0, distance);
				cam.orbit(0, 0, distance);

				// Setup the coordinates for 300 stars
				for (int i = 0; i < 300; i++) {
					sphericalPositions[i][0] = ofRandomuf() * 360;
					sphericalPositions[i][1] = ofRandomuf() * 360;
					sphericalPositions[i][2] = ofRandomuf() * 1000 + 1000;
				}
			}
			if (ofGetKeyPressed(OF_KEY_UP)) {
				cam.tilt(1);
			}
			if (ofGetKeyPressed(OF_KEY_DOWN)) {
				cam.tilt(-1);
			}
			if (ofGetKeyPressed(OF_KEY_LEFT)) {
				cam.pan(1);
			}
			if (ofGetKeyPressed(OF_KEY_RIGHT)) {
				cam.pan(-1);
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofEnableDepthTest();

	cam.begin(); // Enable camera, everything onwards will appear on the screen

	drawStars();

	ofPushMatrix(); // Global positioning

	ofPushMatrix(); // Object positioning

	ofNoFill(); // Disable fill color
	ofSetColor(255); // Set color to white

	// Black Hole in your face
	if (blackHole) {
		// at random orientation
		float t, p;
		ofVec3f goTo;
		mesh.setMode(OF_PRIMITIVE_POINTS);
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

			//float rad = lineMax*0.5;
			float rad = 1;
			for (int i = 0; i < 1000; i++) {
				glPushMatrix();
				ofTranslate(goTo);
				ofRotateZ(float(j));

				ofVec3f first = goTo;

				t = 140 * 0.0174533;
				p = float(j* 0.0174533);
				first.operator*(rad);
				//ofVec3f second(sin(t) * cos(p), sin(t) * sin(p), cos(t));
				ofVec3f second(goTo[0] - 50 * rad * sin(t) * cos(p), goTo[1] + 0, goTo[2] - 30 * rad);

				//second.operator*(rad);
				t = 160 * 0.0174533;
				ofVec3f third(goTo[0] - 50 * rad * sin(t) * cos(p), goTo[1], goTo[2] - 50 * rad);

				//ofVec3f third(1.5 * sin(t) * cos(p), -2 * sin(t) * sin(p), cos(t));
				//third.operator*(rad);
				t = 180 * 0.0174533;
				ofVec3f fourth(goTo[0] - 0 * rad * sin(t) * cos(p), goTo[1], goTo[2] - 50000 * rad);
				//ofVec3f fourth(1.5 * sin(t) * cos(p), -5 * sin(t) * sin(p), cos(t));

				//fourth.operator*(rad);
				float time = float(i) / 1000.0;
				mesh.addVertex(CalculateBezier(time, first, second, third, fourth));
				glPopMatrix();
			}
		}
		mesh.draw();
	}

	ofPushMatrix();
	if (!lineToCircle) { // If the line still looks like a line
						 // Set settings for the circle
		cylinder.setRadius(lineLength / 2);
		cylinder.setResolution(50, 50, 50);
		cylinder.setCapped(false);
	}
	// Draw a circle and make sure that it is rotated 90 degrees over the Z axis, so at first sight it appears to be a line
	ofRotateZ(90); //
	if (!drawSphere) cylinder.draw();

	if (drawSphere) {
		ofSetColor(255, 255, 255, alpha);
		ofDrawSphere(lineLength*0.5);
	}
	ofSetColor(255);

	ofPopMatrix();

	ofPopMatrix(); // Objects

	ofPopMatrix(); // Global

	cam.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	switch (key) {
	case OF_KEY_LEFT:
		if (allowHorizontalOrbit) angleH += 1;
		break;
	case OF_KEY_RIGHT:
		if (allowHorizontalOrbit) angleH -= 1;
		break;
	case OF_KEY_UP:
		if (allowVerticalOrbit) angleV -= 1;
		break;
	case OF_KEY_DOWN:
		if (allowVerticalOrbit) angleV += 1;
		break;
	}
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

		ofDrawSphere(ofPoint(0, 0, 0), 2);
		ofPopMatrix();
	}
}

ofVec3f ofApp::CalculateBezier(GLfloat t, ofVec3f p0, ofVec3f p1, ofVec3f p2, ofVec3f p3) {
	GLfloat u = 1 - t;
	GLfloat uu = u * u;
	GLfloat uuu = uu * u;
	GLfloat tt = t * t;
	GLfloat ttt = tt * t;

	ofVec3f bezier = (p0.operator*(uuu)) + p1.operator*(3 * uu * t) + p2.operator*(3 * u * tt) + p3.operator*(ttt);
	return bezier;
}