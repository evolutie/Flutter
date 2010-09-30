#include "testApp.h"

bool debug = false;


//--------------------------------------------------------------
void testApp::setup(){
    glEnable (GL_LINE_SMOOTH);
    glEnable (GL_BLEND);
    glEnable(GL_POLYGON_SMOOTH);
    //glEnable ( GL_LIGHTING );
    //glEnable ( GL_COLOR_MATERIAL ) ;
    //GLfloat specular[] = {1.0, 1.0, 1.0, 1.0};
    //glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
ofSetFrameRate(30);
    //    glEnable(GL_LIGHT_0)

	ofBackground(255,255,255);
angle = 0;
	vid_w = 160;
	vid_h = 120;

	//change to false to use camera
	bUseVideo = true;

    handList.clear();
	//lets try and load settings from xml
	//if it doesn't find settings it uses default values
	settings.loadFile("app-settings.xml");
	diffMode	= settings.getValue("THRESH_MODE", 0);
	threshold	= settings.getValue("THRESHOLD", 30);
	smoothPct   = settings.getValue("SMOOTH_PCT", 0.13f);
	tolerance   = settings.getValue("TOLERANCE", 120);

	if(bUseVideo){
		//load our test video
		video.loadMovie("butterfly2.mov");
		video.setLoopState(true);
		video.play();

	}else{

		//setup our camera
		camera.setVerbose(true);
		camera.setDeviceID(0);
		camera.initGrabber(vid_w, vid_h);

		//check that we got the height we want
		vid_w = camera.width;
		vid_h = camera.height;
	}

	//allocate our openCV images
	cvColor.allocate(vid_w, vid_h);
	cvGray.allocate(vid_w, vid_h);
	cvBackground.allocate(vid_w, vid_h);
	cvThresh.allocate(vid_w, vid_h);
	frameCounter = 0;
	handCheck = 0;
	handRest = 0;
    handCreated = 0;
}

//--------------------------------------------------------------
void testApp::update(){

	bool bNewFrame = false;

	if(bUseVideo){

		video.idleMovie();
		if(video.isFrameNew() ){
			//put the camera pixels into openCV color image
			cvColor.setFromPixels( video.getPixels(), vid_w, vid_h);
			bNewFrame = true;
		}

	}else{


		camera.grabFrame();
		if( camera.isFrameNew() ){
			//put the camera pixels into openCV color image
			cvColor.setFromPixels( camera.getPixels(), vid_w, vid_h);
			bNewFrame = true;
		}
	}

	if( bNewFrame ){
		cvGray = cvColor;

		//we want to get a background image when we first start
		if(ofGetFrameNum() < 3 ){
			cvBackground = cvGray;
		}

		//here we compare the current frame to the background
		//there are a couple of ways to do this
		//1. absolute difference, 2. lighter than, 3.darker than

		if(diffMode == 0){
			cvThresh = cvGray;
			cvThresh.absDiff(cvBackground);
		}else if(diffMode == 1){
			cvThresh = cvGray;
			cvThresh -= cvBackground;
		}else if(diffMode == 2){
			cvThresh = cvBackground;
			cvThresh -= cvGray;
		}

		cvThresh.threshold(threshold);
		int numBlobs = contour.findContours(cvThresh, 100, 9999999, 40, false, false);

		if(numBlobs > 0){

			//lets store the bounding box and center point of our blob
			boundingBox = contour.blobs[0].boundingRect;
			centroid    = contour.blobs[0].centroid;

			//lets get out the contour data
			int length_of_contour = contour.blobs[0].pts.size();

			//clear the old contours
			contourReg.clear();
			contourReg.assign(length_of_contour, ofxPoint2f());
			contourSmooth.clear();
			contourSmooth.assign(length_of_contour, ofxPoint2f());

			//lets make a copy for ourselves
			for(int i = 0; i < length_of_contour; i++){
				contourReg[i] = contour.blobs[0].pts[i];
			}

			contourSimp.smooth(contourReg, contourSmooth, smoothPct);

			contourSimple.clear();
			contourSimp.simplify(contourSmooth, contourSimple, tolerance);
			contourSimp.convexHull(contourSimple, contourHull);
        //    handList.size()

            if(contourSmooth.size() > 200){
                if(contourSmooth.size() < 11800){
                    if(handCheck > 200){
                        if(handCheck < 11800){

                            handRest++;

                        }
                    }
                }
            }else{
                handRest = 0;
                handCreated = 0;
            }

        if(handRest > 45){
            if(handCreated == 0){


                attentionPointX = ofRandomWidth();
                attentionPointY = ofRandomHeight();

                    handList.push_back(contourList());
                    handList.back().storeContour(contourSimple, handList.size(), centroid.x, centroid.y, ofGetScreenWidth()/2, ofGetScreenHeight()/2-100, attentionPointX, attentionPointY);
                    handCreated = 1;
            }
        }


           handCheck = contourSmooth.size();


		}

       // for(int i = 0; i < handList.size(); i++){
          //  handList[i].moveContour(10,2);
        //}

        	for(int i=0; i<handList.size(); i++)
	{









		if(i<5) {
			handList[i].seek( ofPoint(mouseX, mouseY) );
		} else {
			handList[i].arrive( ofPoint(mouseX, mouseY) );
		}






		handList[i].update();
	}


	}



}

//--------------------------------------------------------------
void testApp::draw(){




    glEnable(GL_DEPTH_TEST);


//	ofRect(0, 0, vid_w, vid_h);



    glEnable(GL_DEPTH_TEST);
    ofSetColor(255, 255, 255);
    ofRect(0, 0, ofGetWidth(), ofGetHeight());

    glTranslatef(0, 0, 1);


















	for(int i = 0; i < handList.size(); i++){
if(i == handList.size()){
    handList[i].drawContour(10,1);
}
	                handList[i].drawContour(10,0);


            //handList[i].y2 = mouseX;

            //handList[i].x2 = mouseY;


	 //   handList[i].x += SimplexNoise1234::noise(ofGetElapsedTimef())*10;
	 //   handList[i].y += SimplexNoise1234::noise(ofGetElapsedTimef())*10;

/*

        float newAngle = atan2(handList[i].y - mouseY, handList[i].x - mouseX) * RAD_TO_DEG;
        newAngle += 180;

        float targetAngle = newAngle - handList[i].angle;
        handList[i].angle *= 0.95;
        handList[i].angle += 0.05 * newAngle;
*/
       // handList[i].angle = handList[i].angle + -(handList[i].angle*2);
	      //handList[i].x = handList[i].x + cos(handList[i].angle);
	      //handList[i].y = handList[i].y + sin(handList[i].angle);
	     // handList[i].angle += SimplexNoise1234::noise(0.1)-1;



	}















    glDisable(GL_DEPTH_TEST);




 if(debug){


    glDisable(GL_DEPTH_TEST);
	ofDrawBitmapString("convexHull of contour", 80,80);

	//color cv
	ofSetColor(0x000000);
	ofDrawBitmapString("color cv image", 10 + vid_w, vid_h + 15);
	ofSetColor(0xffffff);
	cvColor.draw(vid_w, 0);

	//gray cv
	ofSetColor(0x000000);
	ofDrawBitmapString("gray cv image", 10 + vid_w * 2, vid_h + 15);
	ofSetColor(0xffffff);
	cvGray.draw(vid_w * 2, 0);

	//cvBackground cv
	ofSetColor(0x000000);
	ofDrawBitmapString("background cv image", 10, 2 * vid_h + 45);
	ofSetColor(0xffffff);
	cvBackground.draw(0, vid_h + 30);

	//cvThreshold cv
	ofSetColor(0x000000);
	string threshStr = "threshold cv image - thresh is ";
	threshStr += ofToString(threshold);
	threshStr +=  "\nthresh mode is: ";

	if(diffMode == 0)threshStr += "abs diff";
	if(diffMode == 1)threshStr += "lighter than";
	if(diffMode == 2)threshStr += "darker than";

	ofDrawBitmapString(threshStr, 10 + vid_w, 2 * vid_h + 45);
	ofSetColor(0xffffff);
	cvThresh.draw(vid_w, vid_h + 30);
	contour.draw(vid_w, vid_h + 30);

	ofFill();
	ofSetColor(0x000000);
	ofRect(vid_w*2, vid_h + 30, vid_w, vid_h);
	contour.draw(vid_w*2, vid_h + 30);

	//lets draw the smoothed contour
	ofSetColor(0x000000);
	ofDrawBitmapString("smoothed contour - smoothPct: "+ofToString(smoothPct, 3), 10, 3 * vid_h + 75);
	ofSetColor(0x000000);

	glPushMatrix();
		glTranslatef(0, 2 * vid_h + 60, 0);
		ofFill();
		ofRect(0, 0, vid_w, vid_h);
		ofNoFill();
		ofSetColor(50, 0, 255);
		ofBeginShape();
		for(int i = 0; i < contourSmooth.size(); i++){
			ofVertex(contourSmooth[i].x, contourSmooth[i].y);
		}
		ofEndShape(true);
		ofFill();
	glPopMatrix();

	//lets draw the simplified contour
	ofSetColor(255,255,255);
	ofDrawBitmapString("fps/amount"+ofToString(handList.size(), 3), 20, 20);
ofDrawBitmapString(ofToString(contourSmooth.size(), 3),480, 180);
	glPushMatrix();
		glTranslatef(vid_w, 2 * vid_h + 60, 0);
		ofFill();
		ofRect(0, 0, vid_w, vid_h);
		ofNoFill();

		ofSetColor(50, 255, 0);

		ofCircle(centroid.x, centroid.y, 5);
		ofBeginShape();
		for(int i = 0; i < contourSimple.size(); i++){
			ofVertex(contourSimple[i].x, contourSimple[i].y);
		}
		ofEndShape(true);
		ofFill();
	glPopMatrix();

	//lets draw the convex hull contour
	ofSetColor(0x000000);
	ofDrawBitmapString("convexHull of contour", 2*vid_w + 10, 3 * vid_h + 75);

	glPushMatrix();
		glTranslatef(2*vid_w, 2 * vid_h + 60, 0);
		ofFill();
		ofRect(0, 0, vid_w, vid_h);
		ofNoFill();

		ofSetColor(50, 255, 0);

		ofCircle(centroid.x, centroid.y, 5);
		ofBeginShape();
		for(int i = 0; i < contourHull.size(); i++){
			ofVertex(contourHull[i].x, contourHull[i].y);
		}
		ofEndShape(true);
		for(int i = 0; i < contourHull.size(); i++){
			ofCircle(contourHull[i].x, contourHull[i].y, 2);
		}

		ofFill();
	glPopMatrix();


	//show key presses
	ofSetColor(0x000000);
	ofDrawBitmapString("'b' new background    UP/DOWN threshold    LEFT/RIGHT smooth   '-'/'=' simplfication   '1' '2' '3'  thresh mode    'c' camera settings", 10, ofGetHeight()-5);


    	// original
	ofSetColor(0x000000);

	ofDrawBitmapString("original image", 10, vid_h + 15);
	ofSetColor(0xffffff);
	if(bUseVideo)video.draw(ofGetWidth()-vid_w,ofGetHeight()-vid_h);
	else camera.draw(ofGetWidth()-vid_w,ofGetHeight()-vid_h);

	if(handCreated == 1){

	 ofRect(0+50, 0+50, vid_w-100, vid_h-100);
	}


    }



if(drawing ==1){
     	ofDrawBitmapString(ofToString(handList[0].trail.size(), 3), 20, 20);
        ofDrawBitmapString(ofToString(handList[0].trail[handList[0].trail.size()-1].x, 3), 40, 40);


}


}


//--------------------------------------------------------------
void testApp::keyPressed  (int key){
	if(key == 'c'){
		camera.videoSettings();
	}

	if(key == 'a'){
handList.clear();
	}



	if(key == 'd')debug = !debug;

	if(key == 'b'){
		cvBackground = cvGray;
	}

	if(key == 'p'){
		float speed = video.getSpeed();

		if(speed == 0)video.setSpeed(1.0);
		else video.setSpeed(0);
	}

	if(key =='1'){
		diffMode = 0;
	}else if(key =='2'){
		diffMode = 1;
	}else if(key == '3'){
		diffMode = 2;
	}

	if(key == OF_KEY_RIGHT){
		smoothPct += 0.01;
	}else if(key == OF_KEY_LEFT){
		smoothPct -= 0.01;
		if(smoothPct < 0)smoothPct = 0;
	}

	if(key == '='){
		angle += 1;
	}else if(key == '-'){
		angle -= 1;
		if(angle < 0)angle = 0;
	}

	if(key == OF_KEY_UP){
		threshold += 2;
	}else if(key == OF_KEY_DOWN){
		threshold -= 2;
		if(threshold < 0)threshold = 0;
	}

	if(key == OF_KEY_INSERT){

drawing = 1;
	}

	if(key == OF_KEY_END){

	}
}

//--------------------------------------------------------------
void testApp::keyReleased  (int key){
	settings.setValue("THRESHOLD", threshold);
	settings.setValue("THRESH_MODE", diffMode);
	settings.setValue("SMOOTH_PCT", smoothPct);
	settings.setValue("TOLERANCE", tolerance);

	settings.saveFile("app-settings.xml");
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){


}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(){

}
