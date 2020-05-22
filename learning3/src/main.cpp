

#include "ofMain.h"
#include "ofApp.h"

using namespace std;

//========================================================================
int main( ){
	// 4K:4096x2160
	// 2K:2048x1080
	// FullHD:1920x1080
	// HD:1440x1080
	// HD720p:1280x720
	// DVD:720x480

	//ofSetupOpenGL(1024,768,OF_WINDOW);			// <-------- setup the GL context
	//ofSetupOpenGL(1280, 720, OF_FULLSCREEN);

	ofGLFWWindowSettings settings;
	settings.setGLVersion(4, 1); //we define the OpenGL version we want to use
	settings.setSize(1280, 720);
	ofCreateWindow(settings);

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new ofApp());

}
