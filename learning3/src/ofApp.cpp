#include "ofApp.h"

//--------------------------------------------------------------
ofApp::ofApp() {
}
ofApp::~ofApp() {
}

void ofApp::setup() {


	displayGui = true;

	// ##### Load External Elements

	font.load("OpenSans-Light.ttf", 10);

	// ##### Main GUI - Setup

	//overlay.setup(); 
	//mainGroup.add(overlay.params);
	//mainMenu.setup(mainGroup);

	// ##### Info Display

	infoText.push_back("1,2,3 to select active layer");
	infoText.push_back("z,x,c,v,.. to start simulations");
	//infoText.push_back("take you somewhere nice");
	//infoText.push_back("Kaspar Ravel");

	// ##### Layer System - Setup

	for (size_t i = 0; i < NUMLAYERS; ++i)
	{
		layers[i] = new Layer(i + 1, Scene_Default);
		layers[i]->setup();
		layers[i]->inTransition = false;
	}

	// ##### Post Processing Initiating

	//post.init(ofGetWidth(), ofGetHeight());
	//post.createPass<BloomPass>();
}

//--------------------------------------------------------------
void ofApp::update() {



	// # Fullscreen toggle doesn't work with keyboard f for fullscreen
	// if (fullScreenToggle) ofSetFullscreen(true); else ofSetFullscreen(false);

	// # Play Drag & Dropped Video
	//for (int v = 0; v < dropImage.size(); v++) dropVideo[v].update();

	// ##### Layer System - Update

	for (size_t i = 0; i < NUMLAYERS; i++)
	{
		layers[i]->update();

	}

	for (auto& ts : transitions) {
		if (!ts.finished && !ts.changed) {
			if (layers[ts.layer]->opacity > 0) {
				layers[ts.layer]->opacity -= 4;
			}
			else if (layers[ts.layer]->opacity <= 0) {
				delete layers[ts.layer];
				layers[ts.layer] = new Layer(ts.layer + 1, ts.type);
				layers[ts.layer]->setup();
				layers[ts.layer]->opacity = 0;
				ts.changed = true;
			}
		}

		if (ts.changed && !ts.finished) {
			if (layers[ts.layer]->opacity < 255) {
				layers[ts.layer]->opacity += 4;
			}
			else if (layers[ts.layer]->opacity >= 255) {
				ts.finished = true;
				layers[ts.layer]->inTransition = false;
				layers[ts.layer]->opacity = 255;
			}
		}
	}
	//deleting all finished transition; it checks if the element is finished, then deletes it and goes to the next, or just goes to the next
	for (vector<LayerTransHelper>::iterator it = transitions.begin(); it != transitions.end();) {
		if (it->finished) {
			it = transitions.erase(it);
		}
		else {
			++it;
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	// # Default Colors
	ofSetBackgroundColor(0);															// put the background color ehre or keep it in overlay ? or put both in overlay
	//ofSetColor(255);                                                              // MAKE THIS COLOR BE THE CONTRARY OF THE BACKGROUND MENU, or always +100 - 100 somth, like relative

		// ##### Main GUI - Draw

	//overlay.draw();
	mainMenu.draw();																// MAKE ANOTHER FUNCTION FOR THe SCENE MENU DRAW SO THAT I CAN CALL IT BEFORE THE CAMERA

	if (displayGui)
	{

		// ##### Info Display															// the INFO DISPLAY CAN GO IN THE OVERLAY ASWELL

		ofSetColor(255);
		infoText.push_back("Current FPS : " + to_string(ofGetFrameRate()));
		for (size_t i = 0; i < infoText.size(); i++)
		{
			float w = ofGetWidth() - font.stringWidth(infoText[i]) - 10;
			float h = 20 + i * (font.stringHeight(infoText[i]) + 5);
			font.drawString(infoText[i], w, h);
		}
		infoText.pop_back();

		// ##### Display Layer Info

		for (size_t i = 0; i < NUMLAYERS; i++)
		{
			string active = layers[i]->isActiveLayer() ? ">" : "-";
			string text = active + " Layer " + std::to_string(i + 1);
			float w = ofGetWidth() - 55;
			float h = 20 + i * ((font.stringHeight(text)) + 5);
			h += (font.stringHeight(infoText[0])) * infoText.size() + 20;
			font.drawString(text, w, h);
		}
	}

	// ##### Layer System - Draw

	for (size_t i = 0; i < NUMLAYERS; i++) // draw every layer
	{
		layers[i]->draw();
	}

	// ##### GUI - Draw

	if (displayGui)
	{
		for (size_t i = 0; i < NUMLAYERS; i++) // draw every layer
		{
			if ((i + 1) == layers[i]->getActiveLayer())
			{
				layers[i]->sceneMenu.draw();
			}
		}
	}

	// Webcam 
	//webcam.draw((ofGetWidth() / 2) - 360, (ofGetHeight() / 2) - 240, 360, 240);               // PUT THIS INTO ITS OWN SCENE


	// Drag and Drop Image && Video                                                                                                      // PUT THIS INTO ITS OWN SCENE
	//for (int i = 0; i < dropImage.size(); i++) dropImage[i].draw(0 - dropImage[i].getWidth() / 2, 0 - dropImage[i].getHeight() / 2);
	//for (int v = 0; v < dropImage.size(); v++) dropVideo[v].draw(0 - dropVideo[v].getWidth() / 2, 0 - dropVideo[v].getHeight() / 2);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	switch (key)
	{
	case ' ':
		// used for testing things
		break;
	case 'p':
	{																								// HAVE LITTLE POPUP TEXT SAY IT TOOK SCREENSHOT
		imgScreenshot.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
		string filename = "screenshot_" + ofToString(screenshotCount, 5, '0') + ".png";
		imgScreenshot.save(filename);
		screenshotCount++;
		break;
	}
	case 'o':
		displayGui = displayGui ? false : true;
		break;
	case 'f':
		//ofToggleFullscreen();
		//fbo.allocate(ofGetWidth(), ofGetHeight());
		//fbo.begin();
		//ofClear(255);
		//fbo.end();
		break;

	case 'z': initSceneChange(Scene_DiffLine); break;
	case 'x': initSceneChange(Scene_DLA); break;
	case 'c': initSceneChange(Scene_SpaceColonization); break;
	case 'v': initSceneChange(Scene_Boids); break;
	case 'b': initSceneChange(Scene_Julia2D); break;
	case 'n': initSceneChange(Scene_SimplexTerrain); break;
	case 'm': initSceneChange(Scene_DomainWarping); break;
	case ',': initSceneChange(Scene_Default); break;
	case '.': initSceneChange(Scene_ShaderTest); break;
	case '1':	layers[0]->setActiveLayer(); break;
	case '2':	layers[1]->setActiveLayer(); break;
	case '3':	layers[2]->setActiveLayer(); break;
		//case '4':	activeLayer = 4; break;
		//case '5':	activeLayer = 5; break;
		//case '6':	activeLayer = 6; break;
		//case '7':	activeLayer = 7; break;
		//case '8':	activeLayer = 8; break;
		//case '9':	activeLayer = 9; break;
	default: break;
	}
}

// ###### Start Scene and Delete Old one Before

void ofApp::startScene(SceneType Type) {                                  // THINK OF SOMEWHERE ELSE TO PUT THIS FUNCTION
	for (size_t i = 0; i < NUMLAYERS; i++)
	{
		if (layers[i]->isActiveLayer())
		{
			delete layers[i];
			layers[i] = new Layer(i + 1, Type);
			layers[i]->setup();

			break;
		}
	}
}

void ofApp::initSceneChange(SceneType Type) {
	for (size_t i = 0; i < NUMLAYERS; i++)
	{
		if (layers[i]->isActiveLayer() && !layers[i]->inTransition)
		{
			LayerTransHelper temp;
			temp.layer = i;
			temp.finished = false;
			temp.changed = false;
			temp.type = Type;

			transitions.push_back(temp);
			layers[i]->inTransition = true;
		}
	}
}
//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {
	//// # Drag and Drop Sound // Images // Videos
	//if (dragInfo.files.size() > 0)
	//{
	//	dropSound.assign(dragInfo.files.size(), ofSoundPlayer());
	//	for (int s = 0; s < dragInfo.files.size(); s++)
	//	{
	//		dropSound[s].load(dragInfo.files[s]);
	//		dropSound[s].play();
	//		dropSound[s].setVolume(0.6);
	//		dropSound[s].setLoop(true);
	//	}
	//}

	//if (dragInfo.files.size() > 0)
	//{
	//	dropImage.assign(dragInfo.files.size(), ofImage());
	//	for (int i = 0; i < dragInfo.files.size(); i++)
	//	{
	//		dropImage[i].load(dragInfo.files[i]);
	//	}
	//}

	//if (dragInfo.files.size() > 0)
	//{
	//	dropVideo.assign(dragInfo.files.size(), ofVideoPlayer());
	//	for (int v = 0; v < dragInfo.files.size(); v++)
	//	{
	//		dropVideo[v].load(dragInfo.files[v]);
	//		dropVideo[v].play();
	//	}
	//}
}