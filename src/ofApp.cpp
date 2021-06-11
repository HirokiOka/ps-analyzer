#include "ofApp.h"

//--------------------------------------------------------------

void ofApp::setup(){
  ofBackground(0);
  ofSetFrameRate(30);
  verdana.load("ofxbraitsch/fonts/Verdana.ttf", 18);

  //load and play movies
  if (faceMovie.load("movies/fizzbuzz_processed.mp4")) faceMovie.play();
  if (screenMovie.load("movies/fizzbuzz_scratch.mp4")) screenMovie.play();

  //settings about ofxDatGui
  ofxDatGuiComponent* component = nullptr;

  movie_duration = faceMovie.getDuration();
  movie_slider = new ofxDatGuiSlider("", 0.0, movie_duration);
  movie_slider->onSliderEvent(this, &ofApp::onSliderEvent);
  slider_component = movie_slider;
  slider_component->setPosition(400, 340);
  slider_component->setWidth(640, 0);

  matrix = new ofxDatGuiMatrix("AU_C", AU_NUM, true);
  matrix->setPosition(200, 560);
  matrix->setWidth(200, 60);
  matrix->setRadioMode(true);

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

  for (size_t i = 0; i < AU_NUM; ++i) {
    string AU_labels = of_csv[0][AU_C_INDEX_HEAD + i];
    string num = ofToString(AU_labels[3]) + ofToString(AU_labels[4]);
    int label = stoi(num);
    matrix->getButtonAtIndex(i)->setMIndex(label-1);
    matrix->getButtonAtIndex(i)->setSelected(true);
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
  
  if (current_frame > 0) {
    for (int i = AU_C_INDEX_HEAD; i < AU_C_INDEX_END + 1; ++i) {
      int au_c_value = stoi(of_csv[current_frame][i]);
      int matrix_index = i - AU_C_INDEX_HEAD; 

      if(stoi(of_csv[current_frame][i])) {
        //cout << "matrix index: " << matrix_index << "\n";
        matrix->getButtonAtIndex(matrix_index-1)->setSelected(false);
      } else {
        matrix->getButtonAtIndex(matrix_index-1)->setSelected(true);
      }
    }
  }

  matrix->update();
}

//--------------------------------------------------------------
void ofApp::draw(){
  ofSetColor(255);

  faceMovie.draw(400+640, 0, -640, 360);
  screenMovie.draw(400, 360, 640, 360);

  ofSetColor(0, 255, 0);
  float gaze_x = ofMap(gaze_0_x, -1, 1,  screenMovie.getWidth(), -50); 
  float gaze_y = ofMap(gaze_0_y, -1, 1, 0, screenMovie.getHeight()); 
  ofDrawCircle(gaze_x, gaze_y+200, 5);

  for (size_t i = 0; i < components.size(); ++i) components[i]->draw();
  slider_component->draw();
  matrix->draw();
}

//--------------------------------------------------------------
//
void ofApp::onSliderEvent(ofxDatGuiSliderEvent e) {
  if (is_mouse_pressed) {
    faceMovie.setPosition(e.value / movie_duration);
    screenMovie.setPosition(e.value / movie_duration);
  }
}

void ofApp::onMatrixEvent(ofxDatGuiMatrixEvent e) {

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
  screenMovie.setPaused(true);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
  is_mouse_pressed = false;
  faceMovie.setPaused(false);
  screenMovie.setPaused(false);
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

