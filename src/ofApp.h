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

    void onSliderEvent(ofxDatGuiSliderEvent e);

    ofVideoPlayer faceMovie;
    ofVideoPlayer screenMovie;
    ofxCsv of_csv;
    //ofxCsv mb_csv;

    static const int AU_NUM = 18;
    static const int PLOTTER_NUM = 17;
    static const int AU_INDEX_HEAD = 679;
    static const int AU_C_INDEX_HEAD = 696;
    static const int AU_C_INDEX_END = 713;
    float gaze_0_x, gaze_0_y;
    float gaze_1_x, gaze_1_y;
    float elapsed_movie_time = 0.0;
    float movie_duration = 0.0;
    bool is_mouse_pressed = false;

    ofTrueTypeFont verdana;
    ofxDatGuiValuePlotter* plotters[PLOTTER_NUM];
    ofxDatGuiSlider* movie_slider;
    ofxDatGuiComponent* slider_component;
    ofxDatGuiMatrix* matrix;
    //ofxDatGuiComponent* matrix_component;
    vector<ofxDatGuiComponent*> components;

};

