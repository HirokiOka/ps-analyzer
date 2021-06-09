#include "ofApp.h"

//--------------------------------------------------------------

void ofApp::setup(){
  ofBackground(0);
  ofSetFrameRate(30);
  //ofSetLogLevel("ofxCsv", OF_LOG_VERBOSE);
  ofxDatGuiComponent* component = nullptr;

  if (of_csv.load("fizzbuzz_processed.csv") && mb_csv.load("fizzbuzz_scratch_mybeat.csv")) {
    for (size_t i = 0; i < PLOTTER_NUM; ++i) {

      if (i < AU_NUM) {
        string name = of_csv[0][AU_INDEX_HEAD + i];
        plotters[i] = new ofxDatGuiValuePlotter(name, 0, 1);
        plotters[i]->setDrawMode(ofxDatGuiGraph::LINES);
        component = plotters[i];
        i > 9 ? component-> setPosition(140, (i % 8) * 80) : component -> setPosition(0, i * 80);
      } else {
        string name = mb_csv[6][i-9];
        plotters[i] = new ofxDatGuiValuePlotter(name, 0, 100);
        plotters[i]->setDrawMode(ofxDatGuiGraph::LINES);
        component = plotters[i];
        component->setPosition(140, (i % 8) * 80);
      }

      component->setWidth(200, 60);
      components.push_back(component);
    }
  }

  if (faceMovie.load("movies/fizzbuzz_processed.mp4")) faceMovie.play();
  if (screenMovie.load("movies/fizzbuzz_scratch.mp4")) screenMovie.play();
}
  

//--------------------------------------------------------------
void ofApp::update(){
  faceMovie.update();
  screenMovie.update();

  int current_frame = faceMovie.getCurrentFrame();

  if (current_frame > 0) {
    gaze_0_x = stof(of_csv[current_frame][5]);
    gaze_0_y = stof(of_csv[current_frame][6]);
    gaze_1_x = stof(of_csv[current_frame][8]);
    gaze_1_y = stof(of_csv[current_frame][9]);

    for (size_t i = 0; i < components.size(); ++i) {
      float current_value;
      if (i < AU_NUM ) {
        current_value = stof(of_csv[current_frame][AU_INDEX_HEAD + i]);
      } else {
        /*
        current_value = stof(mb_csv[current_frame][i - 9]);
        */
      }
      plotters[i]->setValue(current_value);
      components[i]->update();
    }
  }
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

  for (size_t i = 0; i < components.size(); ++i) {
    components[i]->draw();
  }
}

//--------------------------------------------------------------
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
  //faceMovie.setPaused(true);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
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
