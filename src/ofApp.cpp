#include "ofApp.h"

void ofApp::setup(){
  ofBackground(0);
  ofSetFrameRate(FRAME_RATE);
  verdana.load(font_path, 18);

  //load and play movies
  if (face_movie.load(face_movie_path)) face_movie.play();
  if (screen_movie.load(screen_movie_path)) screen_movie.play();

  //settings about ofxDatGui
  ofxDatGuiComponent* component = nullptr;

  //slider
  movie_duration = face_movie.getDuration();
  movie_slider = new ofxDatGuiSlider("", 0.0, movie_duration);
  movie_slider->onSliderEvent(this, &ofApp::onSliderEvent);
  slider_component = movie_slider;
  slider_component->setPosition(MOVIE_X_OFFSET, 340);
  slider_component->setWidth(MOVIE_WIDTH, 0);

  //AU_C matrix
  matrix = new ofxDatGuiMatrix("AU_C", AU_NUM, true);
  matrix->setPosition(0, 400);
  matrix->setWidth(200, 60);
  matrix->setRadioMode(true);

  //load json
  if (json.open(esprima_path)) {
    for (size_t i = 0; i < 3; ++i) {
      if (i == 0) {
        plotters[i] = new ofxDatGuiValuePlotter("cyclomatic", 0, 10); 
      } else if (i == 1) {
        plotters[i] = new ofxDatGuiValuePlotter("maintainability", 0, 200); 
      } else if (i == 2) {
        plotters[i] = new ofxDatGuiValuePlotter("sloc", 0, 20); 
      }

      plotters[i]->setDrawMode(ofxDatGuiGraph::LINES);
      plotters[i]->setSpeed(3.5);
      component = plotters[i];
      component -> setPosition(0, i * 80);
      component->setWidth(200, 60);
      components.push_back(component);
    }
  }

  //load csv files
  /*
  if (of_csv.load("fizzbuzz_processed.csv")) {
    for (size_t i = 0; i < PLOTTER_NUM; ++i) {
      string AU_label = of_csv[0][AU_INDEX_HEAD + i];
      plotters[i] = new ofxDatGuiValuePlotter(AU_label, 0, 5);
      plotters[i]->setDrawMode(ofxDatGuiGraph::LINES);
      plotters[i]->setSpeed(3.5);
      component = plotters[i];
      if (i < 10) {
        component -> setPosition(0, i * 80);
      } else {
        component -> setPosition(200, (i % 10) * 80);
      }
      component->setWidth(200, 60);
      components.push_back(component);
    }
  }
  */

  //mybeat
  /*
  if (mb_csv.load("fizzbuzz_scratch_mybeat.csv")) {
    for (size_t i = 0; i < MB_PLOTTER_NUM; ++i) {
      string mb_label;
      if (i < 2) {
        mb_label = mb_csv[5][i+9];
        mb_plotters[i] = new ofxDatGuiValuePlotter(mb_label, 0, 3000);
      } else {
        mb_label = "lf/hf";
        mb_plotters[i] = new ofxDatGuiValuePlotter(mb_label, 0, 5);
      }
      mb_plotters[i]->setDrawMode(ofxDatGuiGraph::LINES);
      mb_plotters[i]->setSpeed(4);
      component = mb_plotters[i];
      component->setPosition(0, i * 80);
      component->setWidth(200, 60);
      components.push_back(component);
    }
  }
  */
  //openFace
  if (of_csv.load(of_csv_path)) {
    for (size_t i = 0; i < AU_NUM; ++i) {
      string au_labels = of_csv[0][AU_C_INDEX_HEAD + i];
      string au_num = ofToString(au_labels[3]) + ofToString(au_labels[4]);
      int label = stoi(au_num);
      matrix->getButtonAtIndex(i)->setMIndex(label-1);
      matrix->getButtonAtIndex(i)->setSelected(true);
    }
  }


}

void ofApp::update(){
  //time and frame
  int current_frame = face_movie.getCurrentFrame();
  int elapsed_movie_sec = current_frame / FRAME_RATE;

  //movies
  face_movie.update();
  screen_movie.update();

  if (current_frame > 0 && elapsed_movie_sec > 0) {
    gaze_0_x = stof(of_csv[current_frame][5]);
    gaze_0_y = stof(of_csv[current_frame][6]);
    gaze_1_x = stof(of_csv[current_frame][8]);
    gaze_1_y = stof(of_csv[current_frame][9]);

    //mybeat plotter
    /*
    float lf = stof(mb_csv[5+elapsed_movie_sec][9]);
    float hf = stof(mb_csv[5+elapsed_movie_sec][10]);
    float lf_hf = lf / hf;
    for (size_t i = 0; i < MB_PLOTTER_NUM; ++i) {
      if (i == 0) {
        mb_plotters[i]->setValue(lf);
      } else if(i == 1) {
        mb_plotters[i]->setValue(hf);
      } else {
        mb_plotters[i]->setValue(lf_hf);
      }
      components[i]->update();
    }
    */

    for (size_t i = 0; i < 3; ++i) {
      float current_value = 0.0;
      string time = ofToString(elapsed_movie_sec);
      if (i == 0) {
        current_value = json[time]["cyclomatic"].asFloat();
      } else if (i == 1) {
        current_value = json[time]["maintainability"].asFloat();
      } else if (i == 2) {
        current_value = json[time]["sloc"].asFloat();
      }
      plotters[i]->setValue(current_value);
      components[i]->update();
    }
  }

  
  //slider
  if (!is_mouse_pressed) movie_slider->setValue(elapsed_movie_sec);
  slider_component->update();
  
  //AU_C matrix
  if (current_frame > 0) {
    for (int i = AU_C_INDEX_HEAD; i < AU_C_INDEX_END + 1; ++i) {
      //int au_c_value = stoi(of_csv[current_frame][i]);
      int matrix_index = i - AU_C_INDEX_HEAD; 
      if(stoi(of_csv[current_frame][i])) {
        matrix->getButtonAtIndex(matrix_index-1)->setSelected(false);
      } else {
        matrix->getButtonAtIndex(matrix_index-1)->setSelected(true);
      }
    }
  }
  matrix->update();

}

void ofApp::draw(){
  ofSetColor(255);

  face_movie.draw(MOVIE_X_OFFSET+MOVIE_WIDTH, 0, -MOVIE_WIDTH, MOVIE_HEIGHT);
  screen_movie.draw(MOVIE_X_OFFSET, 360, MOVIE_WIDTH, MOVIE_HEIGHT);

  ofSetColor(0, 255, 0);
  float gaze_x = ofMap(gaze_0_x, -1, 1,  MOVIE_WIDTH + 800, -800); 
  float gaze_y = ofMap(gaze_0_y, -1, 1, 0, MOVIE_HEIGHT); 
  ofDrawCircle(MOVIE_X_OFFSET + gaze_x, 300 + gaze_y, 5);

  for (size_t i = 0; i < components.size(); ++i) components[i]->draw();
  slider_component->draw();
  matrix->draw();
}

//--------------------------------------------------------------
//
void ofApp::onSliderEvent(ofxDatGuiSliderEvent e) {
  if (is_mouse_pressed) {
    face_movie.setPosition(e.value / movie_duration);
    screen_movie.setPosition(e.value / movie_duration);
  }
}

void ofApp::onMatrixEvent(ofxDatGuiMatrixEvent e) {

}

void ofApp::mousePressed(int x, int y, int button){
  is_mouse_pressed = true;
  face_movie.setPaused(true);
  screen_movie.setPaused(true);
}

void ofApp::mouseReleased(int x, int y, int button){
  is_mouse_pressed = false;
  face_movie.setPaused(false);
  screen_movie.setPaused(false);
}

