#pragma once

#include "ofMain.h"
#include "BounceText.h"
#include "GameIcon.h"
#include "GameInfo.h"
#include "TopText.h"
#include "Background.hpp"
//#include <windows.h>

class ofApp : public ofBaseApp{

	public:
		void setup();
		void loadXML();
		void update();
		void draw();

		void cycleSelection(int _oldSelection, int newSelection);
		int getRelativeIconOrder(int iconID);
		ofVec2f getIconPos(int slotNum);


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

		void launchGame(string path);
		void launchWeb(string url);

		bool isFullScreened();


		BounceText titleFont, byLineFont, infoFont;

		vector<GameIcon> icons;
		vector<GameInfo> info;
		int curSelection, oldSelection;

		float selectionAnimationTime;
		float selectionAnimationTimer;

		TopText topText;

		ofImage dbaaLogo;
		ofTrueTypeFont bottomInfoFont;

		Background background;

		//some settings from XML
		string bottomMessageText;
		int selectTextColHex;
		int gameTitleColHex;
		int gameInfoColHex;
		int bottomTextColHex;
		float bottomTextAlpha;
		int outlineColHex;

		float selectGameY;

		float iconY;
		float iconYSpacing;
		float iconXSpacing;
		float iconSpacingCurve;

		ofVec2f logoPos;
		ofVec2f bottomTextPos;

		bool canSelectGame;

		ofSoundPlayer moveSound, selectSound, returnSound;
		bool closeAfterLaunchingGame;
		
};
