#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetFrameRate(60);
	ofBackground(255, 180, 180);
	ofEnableAlphaBlending();

	cout << "come on and slam" << endl;
	cout << "and welcome to dreamjam" << endl;

	ofSetWindowTitle("dream_launcher_app");

	background.setup();

	info.clear();
	icons.clear();
	loadXML();

	returnSound.play();

	selectionAnimationTime = 0.2f;
	selectionAnimationTimer = 0;

	curSelection = (int)ofRandom(icons.size());

	canSelectGame = true;

	//icon basic settings
	for (int i = 0; i < icons.size(); i++) {
		icons[i].animCurve = 1;
		icons[i].idTestNum = i;
	}

	//info basic settings
	for (int i = 0; i < info.size(); i++) {
		info[i].titleFont = &titleFont;
		info[i].byLineFont = &byLineFont;
		info[i].infoFont = &infoFont;
	}

	dbaaLogo.load("dba_noText-01_small_white.png");



	cycleSelection(curSelection, curSelection);

}
//--------------------------------------------------------------
void ofApp::loadXML() {
	ofXml xml;
	if (xml.load("games.xml") == false) {
		cout << "bad games xml file" << endl;
		return;
	}

	//go through the games
	xml.setTo("GAME[0]");
	do {
		GameIcon thisIcon;
		thisIcon.iconPic.load("images/"+xml.getValue<string>("ICON"));

		GameInfo thisGameInfo;
		string gameTitle = xml.getValue<string>("TITLE");
		string byLine = xml.getValue<string>("CREDITS");
		string infoText = xml.getValue<string>("INFO");
		string path = xml.getValue<string>("EXE_PATH");
		thisGameInfo.setup(gameTitle, byLine, infoText, path);
		thisGameInfo.screenshot.load("images/" + xml.getValue<string>("SCREENSHOT"));
		if (xml.exists("IS_WEB")) {
			if (xml.getValue<bool>("IS_WEB")) {
				thisGameInfo.isWeb = true;
			}
		}

		icons.push_back(thisIcon);
		info.push_back(thisGameInfo);
	} while (xml.setToSibling());

	xml.setToParent();
	

	//other settings
	if (xml.load("settings.xml") == false) {
		cout << "bad settings file" << endl;
		return;
	}
	xml.setTo("SETTINGS");
	background.bgGray = xml.getValue<int>("BG_GRAY");
	background.bgAlpha = xml.getValue<int>("BG_ALPHA");

	bottomMessageText = xml.getValue<string>("BOTTOM_MESSAGE");

	//colors
	selectTextColHex = ofHexToInt(xml.getValue<string>("SELECT_HEX_COL"));
	gameTitleColHex = ofHexToInt(xml.getValue<string>("TITLE_HEX_COL"));
	gameInfoColHex = ofHexToInt(xml.getValue<string>("INFO_HEX_COL"));
	bottomTextColHex = ofHexToInt(xml.getValue<string>("BOTTOM_MESSAGE_HEX_COL"));
	outlineColHex = ofHexToInt(xml.getValue<string>("OUTLINE_HEX_COL"));

	//fonts
	titleFont.setup("fonts/"+xml.getValue<string>("TITLE_FONT"), xml.getValue<int>("TITLE_FONT_SIZE"));
	byLineFont.setup("fonts/" + xml.getValue<string>("BY_LINE_FONT"), xml.getValue<int>("BY_LINE_FONT_SIZE"));
	infoFont.setup("fonts/" + xml.getValue<string>("INFO_FONT"), xml.getValue<int>("INFO_FONT_SIZE"));
	infoFont.waveSize = 3;

	bottomInfoFont.load("fonts/" + xml.getValue<string>("BOTTOM_FONT"), xml.getValue<int>("BOTTOM_FONT_SIZE"));

	topText.setup(xml.getValue<string>("TOP_TEXT_MESSAGE"), "fonts/"+xml.getValue<string>("TOP_TEXT_FONT"), xml.getValue<int>("TOP_TEXT_FONT_SIZE") );

	//audio
	moveSound.load("sounds/" + xml.getValue<string>("MOVE_SOUND"));
	selectSound.load("sounds/" + xml.getValue<string>("SELECT_SOUND"));
	returnSound.load("sounds/" + xml.getValue<string>("RETURN_SOUND"));

	//placement
	selectGameY = xml.getValue<float>("SELECT_GAME_Y");

	iconY = xml.getValue<float>("ICON_Y");
	iconYSpacing = xml.getValue<float>("ICON_Y_SPACING");
	iconXSpacing = xml.getValue<float>("ICON_X_SPACING");
	iconSpacingCurve = xml.getValue<float>("ICON_SPACING_CURVE");

	float gameInfoTextY = xml.getValue<float>("GAME_INFO_TEXT_Y_START");
	float gameTextX = xml.getValue<float>("GAME_TEXT_X");
	float gameTextW = xml.getValue<float>("GAME_TEXT_W");
	float gameTextByLineSpacing = xml.getValue<float>("GAME_TEXT_BY_LINE_SPACING");
	float gameTextInfoSpacing = xml.getValue<float>("GAME_TEXT_INFO_SPACING");
	float screenshotX = xml.getValue<float>("SCREEN_SHOT_X");
	float screenshotY = xml.getValue<float>("SCREEN_SHOT_Y");
	bool use_text_for_general_info = xml.getValue<string>("USE_IMAGE_FOR_DREAMHOUSE_INFO") == "TRUE";
	cout << "ima do " << use_text_for_general_info << endl;
	for (int i = 0; i < info.size(); i++) {
		info[i].textStartYPrc = gameInfoTextY;
		info[i].textXPrc = gameTextX;
		info[i].textWPrc = gameTextW;
		info[i].textByLineYSpacingPrc = gameTextByLineSpacing;
		info[i].textInfoYSpacingPrc = gameTextInfoSpacing;
		info[i].screenshotXPrc = screenshotX;
		info[i].screenshotYPrc = screenshotY;
		info[i].show_image_for_general_info = use_text_for_general_info;
	}

	logoPos.x = xml.getValue<float>("LOGO_X");
	logoPos.y = xml.getValue<float>("LOGO_Y");
	bottomTextPos.x = xml.getValue<float>("BOTTOM_TEXT_X");
	bottomTextPos.y = xml.getValue<float>("BOTTOM_TEXT_Y");

	/*if (xml.getValue<string>("HIDE_CONSOLE") == "TRUE") {
		FreeConsole();	//hides the console
	}*/

	closeAfterLaunchingGame = xml.getValue<string>("CLOSE_AFTER_GAME_LAUNCH") == "TRUE";
	cout << "close after launch " << closeAfterLaunchingGame << endl;

}


//--------------------------------------------------------------
void ofApp::update(){
	for (int i = 0; i < icons.size(); i++) {
		icons[i].update();
	}

	selectionAnimationTimer += ofGetLastFrameTime();

	background.update();
}

//--------------------------------------------------------------
void ofApp::draw(){

	//background
	background.draw();
	
	

	float selectionAnimPrc = selectionAnimationTimer / selectionAnimationTime;
	selectionAnimPrc = MIN(selectionAnimPrc, 1);
	//draw the info for this game, crossfading when the seleciton changes
	info[curSelection].draw(255 * selectionAnimPrc, gameTitleColHex, gameInfoColHex, outlineColHex);
	
	if (selectionAnimPrc < 1.0) {
		info[oldSelection].draw(255 * (1.0 - selectionAnimPrc), gameTitleColHex, gameInfoColHex, outlineColHex);
	}


	//top text
	ofSetHexColor(selectTextColHex);
	topText.draw(ofGetWidth() / 2, ofGetHeight() * selectGameY);

	//icons
	for (int i = 0; i < icons.size(); i++) {
		icons[i].draw(outlineColHex);
	}

	//bottom stuff
	ofColor bottomTextCol;
	bottomTextCol.setHex(bottomTextColHex);
	float zeno = 0.1;
	if (info[curSelection].is_general_info) {
		bottomTextAlpha *= (1.0-zeno);
	}
	else {
		bottomTextAlpha = (1.0-zeno) * bottomTextAlpha +  (zeno)*255.0;
	}
	if (info[curSelection].show_image_for_general_info == false) {
		bottomTextAlpha = 255;
	}
	bottomTextCol.a = bottomTextAlpha;

	//logo
	ofSetColor(bottomTextCol);
	float logoScale = 0.35;
	ofPushMatrix();
	ofTranslate(ofGetWidth() * logoPos.x, ofGetHeight() * logoPos.y);
	ofScale(logoScale, logoScale);
	ofRotate( ofMap( sin(ofGetElapsedTimef()), -1, 1, -10, -25) );
	dbaaLogo.draw(-dbaaLogo.getWidth() / 2, -dbaaLogo.getHeight() / 2);
	ofPopMatrix();

	//info
	//ofSetHexColor(bottomTextColHex);
	bottomInfoFont.drawString(bottomMessageText, ofGetWidth() * bottomTextPos.x, ofGetHeight() * bottomTextPos.y);
}

//--------------------------------------------------------------
void ofApp::cycleSelection(int _oldSelection, int newSelection) {
	
	curSelection = newSelection;
	oldSelection = _oldSelection;

	selectionAnimationTimer = 0;

	//cout << "going from "<<oldSelection << " to " << curSelection << endl;

	bool goingUp = (oldSelection + 1) % icons.size() == curSelection;
	
	//set the positions
	for (int i = 0; i < icons.size(); i++) {
		int endOrder = getRelativeIconOrder(i);
		int startOrder = getRelativeIconOrder(i - 1);
		if (goingUp) {
			startOrder = getRelativeIconOrder(i + 1);
		}
		icons[i].startPos = getIconPos( startOrder );
		icons[i].endPos = getIconPos(endOrder);

		//dumb error checking
		if ((icons[i].startPos.x < 0 && icons[i].endPos.x > ofGetWidth()) || (icons[i].startPos.x > ofGetWidth() && icons[i].endPos.x < 0)) {
			icons[i].startPos = icons[i].endPos;
		}

		//kick it off
		icons[i].startAnimation(selectionAnimationTime);
	}


}

//--------------------------------------------------------------
int ofApp::getRelativeIconOrder(int iconID) {
	int relativePos = iconID - curSelection;
	if (relativePos < -4) {
		relativePos += icons.size();
	}
	if (relativePos > 4) {
		relativePos -= icons.size();
	}
	return relativePos;
}

//--------------------------------------------------------------
//0 is center
ofVec2f ofApp::getIconPos(int slotNum) {
	ofVec2f pos;
	pos.y = ofGetHeight() * iconY - abs(slotNum) * ofGetHeight() * iconYSpacing;
	
	float distPrc = (float)slotNum / 3.0;
	float curvePrc = powf(abs(distPrc), iconSpacingCurve);
	float spacing = ofGetWidth() * iconXSpacing;
	if (slotNum < 0)	spacing *= -1;
	pos.x = ofGetWidth() / 2 + curvePrc * spacing;

	return pos;
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	//this command is used by the autohotkey script and is called whenever the app is given focus
	if (key == 'R') {
		cout << "better resize" << endl;
		returnSound.play();
		if (isFullScreened() == false) {
			ofToggleFullscreen();
		}
		canSelectGame = true;
	}

	//trying out just killing all input if the autohotkey script hasn't told us it's OK
	if (!canSelectGame) {
		return;
	}
	//cout << "ya pressed " << key << endl;
	
	//left and right
	if (key == 'a' || key == 'A' || key == OF_KEY_LEFT) {
		cycleSelection(curSelection, (curSelection + icons.size() - 1) % icons.size());
		background.offsetInt--;
		moveSound.play();
	}
	if (key == 'd' || key == 'D' || key == OF_KEY_RIGHT) {
		cycleSelection(curSelection, (curSelection + 1) % icons.size());
		background.offsetInt++;
		moveSound.play();
	}

	//all player buttons act as selecitons
	if (key == 'C' || key == 'c' || key == 'V' || key == 'v' || key == 'N' || key == 'n' || key == 'M' || key == 'm' || key == ' ') {
		if (canSelectGame) {
			if (info[curSelection].is_general_info == false) {
				cout << "launch " << info[curSelection].titleText << endl;
				selectSound.play();
				if (info[curSelection].isWeb) {
					//ofToggleFullscreen();
					launchWeb(info[curSelection].executablePath);
				}
				else {
					launchGame(info[curSelection].executablePath);
				}
			}
		}
		else {
			cout << "Can't select games right now" << endl;
		}
	}

	//testing. should this be removed?
	if (key == 'f') {
		ofToggleFullscreen();
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
void ofApp::launchGame(string path) {
	if (isFullScreened()) {
		ofToggleFullscreen();
	}

	system(path.c_str());
	
	canSelectGame = false;

	if (closeAfterLaunchingGame) {
		ofExit();
	}
}


//--------------------------------------------------------------
void ofApp::launchWeb(string url) {
	/*if (isFullScreened()) {
		ofToggleFullscreen();
	}

	std::wstring pathTemp = std::wstring(url.begin(), url.end());
	LPCWSTR pathLPC = pathTemp.c_str();

	ShellExecute(0, 0, pathLPC, 0, 0, SW_MAXIMIZE);

	canSelectGame = false;
	if (closeAfterLaunchingGame) {
		ofExit();
	}*/
}

//--------------------------------------------------------------
bool ofApp::isFullScreened() {
	return ofGetHeight() == ofGetScreenHeight();
}
