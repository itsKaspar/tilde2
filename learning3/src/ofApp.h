#pragma once

#include "ofMain.h"
#include "ofxGui.h" // maybe we can take this one out now that my voerlay is a class ?
#include "Overlay.h"
#include "Layer.h"

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

		void startScene(SceneType Type);

		// ##### 0 - Defaults
		ofTrueTypeFont font; // Default Font
		
		// ##### 1 - GUI
		ofxPanel gui;
		ofParameterGroup mainGroup;

		Overlay overlay;

		// ##### X - Info Text

		vector<string> infoText;

		// ###### 2 - Peasy Cam
		bool togglePeasyCam = false;
		ofEasyCam cam;

		// ###### 3 - Webcam
		bool toggleWebcam = false;
		ofVideoGrabber webcam;

		// GUI tutorial
		//ofxFloatSlider floatSlider;
		//ofxButton button;
		//ofxLabel label;
		//ofxIntField intField;
		//ofxFloatField floatField;
		//ofxTextField textField;
		//ofxVec2Slider vec2Slider;
		//ofxVec3Slider vec3Slider;
		//ofxVec4Slider vec4Slider;

		// IMG settings
		ofImage imgScreenshot;
		int screenshotCount;

		// temp little things
		int size;
		float rotate;

		//Drag n Drop
		vector<ofSoundPlayer> dropSound;
		vector<ofVideoPlayer> dropVideo;
		vector<ofImage> dropImage;

		//ofFBO
		ofFbo fbo;
		ofImage image;

		// draw line 2
		ofPolyline polyline;

		// Scenes
		vector<Layer> layers;

		// Scene Settings
		int activeLayer;

};
