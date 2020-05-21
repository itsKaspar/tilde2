#pragma once

#include "ofMain.h"
#include "ofxGui.h" // maybe we can take this one out now that my voerlay is a class ?
#include "Overlay.h"
#include "Layer.h"
#include "ofxPostProcessing.h"

#define NUMLAYERS 3

class ofApp : public ofBaseApp{

	public:
		ofApp();
		~ofApp();

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

		// ##### Custom Functions

		void startScene(SceneType Type);

		// ##### Load External Elements

		ofTrueTypeFont font; // Default Font
		
		// ##### GUI

		ofxPanel mainMenu;
		ofParameterGroup mainGroup;
		Overlay overlay;

		// ##### Info Display

		vector<string> infoText;

		// ##### Layer System

		Layer *layers[NUMLAYERS];

		// ##### Screenshot System

		ofImage imgScreenshot;
		int screenshotCount;

		//   PUT THIS INSIDE A SCENE INSTEAD

		// ###### 3 - Webcam
		//bool toggleWebcam = false;
		//ofVideoGrabber webcam;

		//Drag n Drop
		//vector<ofSoundPlayer> dropSound;
		//vector<ofVideoPlayer> dropVideo;
		//vector<ofImage> dropImage;

		//ofFBO
		//ofFbo fbo;
		//ofImage image;

		// Post Processing
		//ofxPostProcessing post;

};


