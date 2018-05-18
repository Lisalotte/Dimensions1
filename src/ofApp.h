#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp {

public:

	ofCylinderPrimitive cylinder;	//Cylinder that we transform to show a dot, line and circle on screen
	ofNode myNode;
	ofCamera cam;
	ofVec3f camPosition;
	ofPolyline line;
	ofMesh mesh;
	ofVec3f look, look2, blackHolePos;

	float lineLength, angleH, angleV, distance, alpha;
	const float lineMax = 300;	// Final linelength and the diameter of the circle
	float sphericalPositions[300][3];	// Array that stores the star coordinates
	float time;
	float lookat;

	bool lineToCircle; // True when lineLength equals the diameter of the circle
	bool circleToSphere;
	bool allowCamRotate;
	bool drawSphere;
	bool blackHole;
	bool allowHorizontalOrbit;
	bool allowVerticalOrbit;
	bool firstTime;
	int counter, counter2; // A counter that makes sure that the user has some time to play with the circle, orbitting around it. When the counter has reached a maximum, the user will stop orbitting around it vertically/horizontally when it displayed flat on the screen

	void setup();
	void update();
	void draw();
	void keyPressed(int key);
	void drawStars();	// Draw background stars
	ofVec3f CalculateBezier(GLfloat t, ofVec3f p0, ofVec3f p1, ofVec3f p2, ofVec3f p3);	// Calculate point at time t, on Bezier Curve corresponding to control points (p0, p1, p2, p3)
};