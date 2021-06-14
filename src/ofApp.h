#pragma once

#include "ofMain.h"
#include "ofxDatGui.h"
#include "ofxCsv.h"

class ofApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();
		
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);

    void onSliderEvent(ofxDatGuiSliderEvent e);
    void onMatrixEvent(ofxDatGuiMatrixEvent e);

    ofVideoPlayer face_movie;
    ofVideoPlayer screen_movie;
    ofxCsv of_csv;
    ofxCsv mb_csv;

    string face_movie_path = "movies/reflection_cam.mp4";
    string screen_movie_path = "movies/reflect_screen_trimed.mov";
    string of_csv_path = "reflection_cam.csv";
    string font_path = "ofxbraitsch/fonts/Verdana.ttf";

    static const int AU_NUM = 18;
    static const int PLOTTER_NUM = 17;
    static const int MB_PLOTTER_NUM = 3;
    static const int AU_INDEX_HEAD = 679;
    static const int AU_C_INDEX_HEAD = 696;
    static const int AU_C_INDEX_END = 713;
    static const int MOVIE_WIDTH = 640;
    static const int MOVIE_HEIGHT = 400;
    static const int MOVIE_X_OFFSET = 400;
    static const int FRAME_RATE = 30;

    float gaze_0_x = 0.0, gaze_0_y = 0.0;
    float gaze_1_x = 0.0, gaze_1_y = 0.0;
    float movie_duration = 0.0;
    bool is_mouse_pressed = false;

    ofTrueTypeFont verdana;
    ofxDatGuiValuePlotter* plotters[PLOTTER_NUM];
    ofxDatGuiValuePlotter* mb_plotters[MB_PLOTTER_NUM];
    ofxDatGuiSlider* movie_slider;
    ofxDatGuiComponent* slider_component;
    ofxDatGuiMatrix* matrix;
    vector<ofxDatGuiComponent*> components;

};

