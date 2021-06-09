#pragma once

#include "ofMain.h"
#include "ofxDatGui.h"
#include "ofxCsv.h"

class ofApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

    ofVideoPlayer faceMovie;
    ofVideoPlayer screenMovie;
    ofxCsv of_csv;
    ofxCsv mb_csv;

    static const int AU_NUM = 18;
    static const int PLOTTER_NUM = 20;
    static const int AU_INDEX_HEAD = 696;
    float gaze_0_x, gaze_0_y;
    float gaze_1_x, gaze_1_y;

    ofxDatGuiValuePlotter* plotters[PLOTTER_NUM];
    vector<ofxDatGuiComponent*> components;

};

