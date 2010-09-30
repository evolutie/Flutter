#pragma once

//#ifndef BOID_H
//#define BOID_H

#define OF_ADDON_USING_OFXOPENCV
#define OF_ADDON_USING_OFXVECTORMATH
//test
#include "ofMain.h"
#include "ofAddons.h"

class contourList{

    public:

        //---------------------------------------------
        contourList(){
            id = 0;
            colorRed = ofRandom(0,255);
            colorGreen = ofRandom(0,255);
            colorBlue = ofRandom(0,255);
            x = 0;
            y = 0;
            posx = ofGetWidth()/2;
            posy = ofGetHeight()/2;
            angle = 80;
            direction = 1;
            previousMillis = ofGetElapsedTimeMillis();
            interval = ofRandom(1000,100000);
            life = 0;
            realspeed = ofRandom(1,6);





            //FLOCKING
            loc.x = ofRandomWidth();
            loc.y = ofRandomHeight();
            vel = 0;
            acc = 0;

            cout << loc.x << ", " << loc.y << endl;
            r = 3.0;
            maxspeed = 4;
            maxforce = 0.1;
            //END FLOCKING


            contour.clear();
            trail.clear();
        }

        //---------------------------------------------
        void storeContour(vector <ofxPoint2f> contourIn, int idIn, int xIn, int yIn, int xposition, int yposition, int posix, int posiy){
            loc.x = posix;
            loc.y = posiy;
            existence = 0;
            lifeexp = ofRandom(600,9000);
            if(ofRandom(1,30) > 28){
             lifeexp = 20000;
            }


            contour.clear();
            int numPoints = contourIn.size();
            if( numPoints <= 0)return;

            contour.assign(numPoints, ofxPoint2f());

            for(int i = 0; i < numPoints; i++){
                contour[i] = contourIn[i];
            }
            x = xIn;
            y = yIn;
            id = idIn;
            posx = xposition;
            posy = yposition;

        }



        //---------------------------------------------

        void  drawContour(int anim, int newest){
            //glColorMaterial ( GL_FRONT_AND_BACK, GL_EMISSION ) ;

















            existence += 1;

            if(existence < 100){
                if(colorRed > 30 && colorRed < 200){
                colorRed += ofRandom(0,20)-9;
                }
                  if(colorBlue > 30 && colorBlue < 200){
                colorBlue += ofRandom(0,20)-9;
                  }
                  if(colorGreen > 30 && colorGreen < 200){
                colorGreen += ofRandom(0,20)-9;
                  }

            }
if(existence < lifeexp){
if((lifeexp-255) < existence){
 if(colorRed != 200){
  colorRed += 1;
 }

  if(colorBlue != 255){
  colorBlue += 1;
 }

  if(colorGreen != 255){
  colorGreen += 1;
 }
}










	float angle = (float)atan2(-vel.y, vel.x);
    float theta =  -1.0*angle;
	float heading2D = ofRadToDeg(theta)+90;



            anim = realspeed;
                glPushMatrix();
            //ofLine(handList[i].x,handList[i].y,handList[i].x+cos(handList[i].angle),handList[i].y+sin(handList[i].angle));
            glTranslatef(x, y, 0);
            ofTranslate(loc.x, loc.y);
            glRotatef(heading2D, 0, 0, 1);
            glRotatef(cos(SimplexNoise1234::noise(ofGetElapsedTimef()))*360,0,1,0);




            ofBeginShape();
            ofFill();

 if(newest == 1){
                        ofSetColor((colorRed-50)+ofRandom(1,50), (colorGreen-50)+ofRandom(1,50), (colorBlue-50)+ofRandom(1,50));

            }else{
                            ofSetColor(colorRed, colorGreen, colorBlue);

            }            for(int k = 0; k < contour.size(); k++){
                ofVertex(contour[k].x - x, contour[k].y - y);
            }

            ofEndShape(true);

            glPopMatrix();

                          glPushMatrix();
            //ofLine(handList[i].x,handList[i].y,handList[i].x+cos(handList[i].angle),handList[i].y+sin(handList[i].angle));

            glTranslatef(x, y, 0);
            ofTranslate(loc.x, loc.y);
            glRotatef(heading2D, 0, 0, 1);
            glRotatef(cos(SimplexNoise1234::noise(ofGetElapsedTimef()))*360+-((cos(SimplexNoise1234::noise(ofGetElapsedTimef()))*360)*2),0,1,0);


            ofBeginShape();
            ofFill();
           // ofSetColor(colorRed, colorGreen, colorBlue);

            for(int k = 0; k < contour.size(); k++){
                ofVertex(contour[k].x - x, contour[k].y - y);
            }

            ofEndShape(true);
            glPopMatrix();

            glPushMatrix();
            glTranslatef(x,y,0);
//            glTranslatef(posx,posy,0);

            ofEnableAlphaBlending();

            for(int p = 0; p < trail.size(); p++){

glDisable(GL_DEPTH_TEST);
            if(newest == 1){
                        ofSetColor((colorRed-50)+ofRandom(1,50), (colorGreen-50)+ofRandom(1,50), (colorBlue-50)+ofRandom(1,50), p);

            }else{
                            ofSetColor(colorRed, colorGreen, colorBlue, p);

            }
            ofCircle(trail[p].x, trail[p].y, (p-(p*2))/18);

glEnable(GL_DEPTH_TEST);

            }


            glPopMatrix();

          //   trail.push_back(100);
             //trail.push_back(posy);
            //trail.assign (1,100);


            /*
            ofSetColor(255,255,255);
            glTranslatef(x, y, 0);
            glTranslatef(posx, posy, 0);
           // ofRect(0,0,200,200);
           */
            ofDisableAlphaBlending();


}
    }


        //---------------------------------------------


        void moveContour(int speed, int realspeed2){




            trail.push_back(ofPoint(loc.x, loc.y));
            if(trail.size() > 255){
                trail.erase(trail.begin());
            }

            life += ofRandom(-0.02,0.05);

            if (ofGetElapsedTimeMillis() - previousMillis > interval) {
                previousMillis = ofGetElapsedTimeMillis();
                int turn = ofRandom(1,2);
                if(turn == 1){
                    if(direction !=4){
                        direction++;
                    }else{
                        direction = 1;
                    }
                }else{
                    if(direction != 1){
                        direction = 4;
                    }
                }
                direction = ofRandom(1,4);
            }


           if(posx > ofGetWidth()+200){
                posx = 0-100;
            }else if(posx < 0-200){
                posx = ofGetWidth()+100;
            }else if(posy > ofGetHeight()+200){
                posy = 0-100;
            }else if(posy < 0-200){
                posy = ofGetHeight()+100;
            }

            if(direction == 1){
                posx += SimplexNoise1234::noise(ofGetElapsedTimef()-life)*speed+(sin(speed*10)*realspeed);
                posy += SimplexNoise1234::noise(ofGetElapsedTimef()-life)*speed+(cos(speed*10)*realspeed);
            }else if(direction == 2){
                posx -= SimplexNoise1234::noise(ofGetElapsedTimef()-life)*speed+(sin(speed*10)*realspeed);
                posy += SimplexNoise1234::noise(ofGetElapsedTimef()-life)*speed+(cos(speed*10)*realspeed);

            }else if(direction == 3){
                posx -= SimplexNoise1234::noise(ofGetElapsedTimef()-life)*speed+(sin(speed*10)*realspeed);
                posy -= SimplexNoise1234::noise(ofGetElapsedTimef()-life)*speed+(cos(speed*10)*realspeed);

            }else if(direction == 4){
                posx += SimplexNoise1234::noise(ofGetElapsedTimef()-life)*speed+(sin(speed*10)*realspeed);
                posy -= SimplexNoise1234::noise(ofGetElapsedTimef()-life)*speed+(cos(speed*10)*realspeed);
            }




            float newAngle = atan2(posy - lasty, posx - lastx) * RAD_TO_DEG;
            newAngle += 180;

            float targetAngle = newAngle - angle;
            angle *= 0.95;
            angle += 0.05 * newAngle;
           //angle = newAngle;    //CAUSES FLICKERING MOTION, ONLY FOR TESTING PURPOSES.

            lastx = posx;
            lasty = posy;
            glPushMatrix();

            glRotated(SimplexNoise1234::noise(ofGetElapsedTimef())*360,0,1,0);
           // ofDrawBitmapString(ofToString(SimplexNoise1234::noise(ofGetElapsedTimef())*360,x,y);

            glPopMatrix();

        }


        //---------------------------------------------









//much more flocking



// Method to update location
void update() {

    vel += acc;   // Update velocity
    vel.x = ofClamp(vel.x, -maxspeed, maxspeed);  // Limit speed
	vel.y = ofClamp(vel.y, -maxspeed, maxspeed);  // Limit speed
    loc += vel;
    acc = 0;  // Reset accelertion to 0 each cycle

	if (loc.x < -r) loc.x = ofGetWidth()+r;
    if (loc.y < -r) loc.y = ofGetHeight()+r;
    if (loc.x > ofGetWidth()+r) loc.x = -r;
    if (loc.y > ofGetHeight()+r) loc.y = -r;






    //trail

                trail.push_back(ofPoint(loc.x, loc.y));
            if(trail.size() > 255){
                trail.erase(trail.begin());
            }

            life += ofRandom(-0.02,0.05);


}

void seek(ofPoint target) {
    acc += steer(target, false);
}

void arrive(ofPoint target) {
    acc += steer(target, true);
}

// A method that calculates a steering vector towards a target
// Takes a second argument, if true, it slows down as it approaches the target
ofPoint steer(ofPoint target, bool slowdown) {
    ofPoint steer;  // The steering vector
    ofPoint desired = target - loc;  // A vector pointing from the location to the target
    float d = ofDist(target.x, target.y, loc.x, loc.y); // Distance from the target is the magnitude of the vector

	// If the distance is greater than 0, calc steering (otherwise return zero vector)
    if (d > 0) {

		desired /= d; // Normalize desired
		// Two options for desired vector magnitude (1 -- based on distance, 2 -- maxspeed)
		if ((slowdown) && (d < 100.0f)) {
			desired *= maxspeed * (d/100.0f); // This damping is somewhat arbitrary
		} else {
			desired *= maxspeed;
		}
		// Steering = Desired minus Velocity
		steer = desired - vel;
		steer.x = ofClamp(steer.x, -maxforce, maxforce); // Limit to maximum steering force
		steer.y = ofClamp(steer.y, -maxforce, maxforce);
    }
    return steer;
}










            //FLOCKING IMPLEMENTATION


           // ofPoint steer(ofPoint target, bool slowdown);

            ofPoint loc;
            ofPoint vel;
            ofPoint acc;
            float r;
            float maxforce;
            float maxspeed;

            //END FLOCKING TEST




        vector <ofxPoint2f> contour;
        vector <ofPoint> trail;
        int id;
        int colorRed;
        int colorGreen;
        int colorBlue;
        int x;
        int y;
        int posx;
        int posy;
        int lastx;
        int lasty;
        float angle;
        int direction;
        int interval;
        int previousMillis;
        float life;
        int realspeed;
        int existence;
        int lifeexp;
};




























