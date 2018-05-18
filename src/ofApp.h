#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{

	public:

		ofCylinderPrimitive cylinder, cyline;
		ofNode myNode;
		ofCamera cam;
		ofVec3f camPosition;
		ofPolyline line;
		ofMesh mesh;
		ofVec3f look, look2, blackHolePos;
		
		float x_rot, y_rot, z_rot;
		float x_self, y_self, z_self;
		float lineLength, angleH, angleV, distance, roll;
		float alpha;
		float firstAngle;
		float lookat;
		const float lineMax = 300;
		const int delayMax = 1000;

		float positions[300][3];
		float sphericalPositions[300][3];

		bool lineToCircle;
		bool circleToSphere;
		bool allowCamRotate;
		bool drawSphere;
		bool blackHole;
		int counter, counter2;
		int sphereanglecounter;

		bool firstTime;
		float time;

		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		void drawStars();
		ofVec3f CalculateBezier(GLfloat t, ofVec3f p0, ofVec3f p1, ofVec3f p2, ofVec3f p3);
};
