#include "ofApp.h"

//--------------------------------------------------------------

void ofApp::setup(){
  //ofSetLogLevel("ofxCsv", OF_LOG_VERBOSE);
  ofBackground(0);
  ofSetFrameRate(30);
  verdana.load("ofxbraitsch/fonts/Verdana.ttf", 18);

  if (faceMovie.load("movies/fizzbuzz_processed.mp4")) faceMovie.play();
  if (screenMovie.load("movies/fizzbuzz_scratch.mp4")) screenMovie.play();

  ofxDatGuiComponent* component = nullptr;

  movie_duration = faceMovie.getDuration();
  movie_slider = new ofxDatGuiSlider("", 0.0, movie_duration);
  movie_slider->onSliderEvent(this, &ofApp::onSliderEvent);
  slider_component = movie_slider;
  slider_component->setPosition(400, 340);
  slider_component->setWidth(640, 0);

  matrix = new ofxDatGuiMatrix("MATRIX", AU_NUM, true);
  matrix->setPosition(200, 600);


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

}

//--------------------------------------------------------------
void ofApp::update(){
  faceMovie.update();
  screenMovie.update();

  int current_frame = faceMovie.getCurrentFrame();
  elapsed_movie_time = current_frame / 30;

  if (current_frame > 0 && elapsed_movie_time > 0) {

    gaze_0_x = stof(of_csv[current_frame][5]);
    gaze_0_y = stof(of_csv[current_frame][6]);
    gaze_1_x = stof(of_csv[current_frame][8]);
    gaze_1_y = stof(of_csv[current_frame][9]);

    for (size_t i = 0; i < components.size(); ++i) {
      float current_value = 0.0;
      current_value = stof(of_csv[current_frame][AU_INDEX_HEAD + i]);
      plotters[i]->setValue(current_value);
      components[i]->update();
    }
  }
  if (!is_mouse_pressed) movie_slider->setValue(elapsed_movie_time);
  slider_component->update();

  matrix->update();

}

//--------------------------------------------------------------
void ofApp::draw(){
  ofSetColor(255);
  
  //verdana.drawString("Blink: ", 200, 600);

  faceMovie.draw(400+640, 0, -640, 360);
  screenMovie.draw(400, 360, 640, 360);

  ofSetColor(0, 255, 0);
  float gaze_x = ofMap(gaze_0_x, -1, 1,  screenMovie.getWidth(), -50); 
  float gaze_y = ofMap(gaze_0_y, -1, 1, 0, screenMovie.getHeight()); 
  ofDrawCircle(gaze_x, gaze_y+200, 5);

  for (size_t i = 0; i < components.size(); ++i) {
    components[i]->draw();
  }
  slider_component->draw();

  matrix->draw();
}

//--------------------------------------------------------------
//
void ofApp::onSliderEvent(ofxDatGuiSliderEvent e) {
  if (is_mouse_pressed) {
    //movie_slider->setValue(e.value);
    faceMovie.setPosition(e.value / movie_duration);
    screenMovie.setPosition(e.value / movie_duration);
  }
}

void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
  //faceMovie.setPosition((float)x / (float)ofGetWidth());
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
  is_mouse_pressed = true;
  faceMovie.setPaused(true);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
  is_mouse_pressed = false;
  faceMovie.setPaused(false);
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

