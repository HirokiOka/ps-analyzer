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

    ofxCsv csv;
    //float AU_values[18];
    float gaze_0_x, gaze_0_y;
    float gaze_1_x, gaze_1_y;
    
    ofxDatGuiValuePlotter* AU01_c;
    ofxDatGuiValuePlotter* AU02_c;
    ofxDatGuiValuePlotter* AU04_c;
    ofxDatGuiValuePlotter* AU05_c;
    ofxDatGuiValuePlotter* AU06_c;
    ofxDatGuiValuePlotter* AU07_c;
    ofxDatGuiValuePlotter* AU09_c;
    ofxDatGuiValuePlotter* AU10_c;
    ofxDatGuiValuePlotter* AU12_c;
    ofxDatGuiValuePlotter* AU14_c;
    ofxDatGuiValuePlotter* AU15_c;
    ofxDatGuiValuePlotter* AU17_c;
    ofxDatGuiValuePlotter* AU20_c;
    ofxDatGuiValuePlotter* AU23_c;
    ofxDatGuiValuePlotter* AU25_c;
    ofxDatGuiValuePlotter* AU26_c;
    ofxDatGuiValuePlotter* AU28_c;
    ofxDatGuiValuePlotter* AU45_c;

    ofxDatGui* gui;
};

