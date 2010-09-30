#ifndef _TEST_APP
#define _TEST_APP

//#define OF_ADDON_USING_OFXOBJLOADER
//#define OF_ADDON_USING_OFXDIRLIST
//#define OF_ADDON_USING_OFXNETWORK
//#define OF_ADDON_USING_OFXVECTORGRAPHICS
//#define OF_ADDON_USING_OFXOSC
//#define OF_ADDON_USING_OFXTHREAD

#define OF_ADDON_USING_OFXOPENCV
#define OF_ADDON_USING_OFXVECTORMATH
#define OF_ADDON_USING_OFXXMLSETTINGS

#include "ofMain.h"
#include "ofAddons.h"

#include "simplexnoise1234.h"

#include "contourSimplify.h"

#include "contourList.h"

class testApp : public ofSimpleApp{

	public:

		void setup();
		void update();
		void draw();

		void keyPressed  (int key);
		void keyReleased (int key);

		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased();

		ofVideoGrabber camera;
		ofVideoPlayer video;

		ofxCvGrayscaleImage cvBackground;
		ofxCvGrayscaleImage cvGray;
		ofxCvGrayscaleImage cvThresh;
		ofxCvColorImage cvColor;
		ofxCvContourFinder contour;

		contourSimplify contourSimp;

		ofxXmlSettings settings;

		vector <ofxPoint2f> contourReg;
		vector <ofxPoint2f> contourSmooth;
		vector <ofxPoint2f> contourSimple;
		vector <ofxPoint2f> contourHull;

		vector <contourList> handList;



        float handCheck;
        int frameCounter;
        int handRest;
        int handCreated;
        int drawing;
        int attentionPointX;
        int attentionPointY;



		ofPoint centroid;
		ofRectangle boundingBox;

		float smoothPct;
		float tolerance;
		int threshold;
		int diffMode;
		int vid_w, vid_h;
		bool bUseVideo;

		int angle;
		int x2;
		int y2;

};

#endif

