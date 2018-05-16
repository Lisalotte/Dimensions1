#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{

	public:

		ofCylinderPrimitive cylinder, cyline;
		ofNode myNode;
		ofCamera cam;
		
		float x_rot, y_rot, z_rot;
		float x_self, y_self, z_self;
		float lineLength, angleH, angleV, distance, roll;

		float positions[300][3];
		float sphericalPositions[300][3];

		bool lineToCircle;
		bool circleToSphere;
		bool allowCamRotate;

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
		
};
