#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
  ofBackground(0);
  ofSetFrameRate(60);
  
  //ofSetLogLevel("ofxCsv", OF_LOG_VERBOSE);

  if (csv.load("fizzbuzz_processed.csv")) {
    cout << "csv loaded";
  }

  gui = new ofxDatGui( ofxDatGuiAnchor::TOP_LEFT );
  AU01_c = gui->addValuePlotter("AU01_c", 0, 1);
  AU02_c = gui->addValuePlotter("AU02_c", 0, 1);
  AU04_c = gui->addValuePlotter("AU04_c", 0, 1);
  AU05_c = gui->addValuePlotter("AU05_c", 0, 1);
  AU06_c = gui->addValuePlotter("AU06_c", 0, 1);
  AU07_c = gui->addValuePlotter("AU07_c", 0, 1);
  AU09_c = gui->addValuePlotter("AU09_c", 0, 1);
  AU10_c = gui->addValuePlotter("AU10_c", 0, 1);
  AU12_c = gui->addValuePlotter("AU12_c", 0, 1);
  AU14_c = gui->addValuePlotter("AU14_c", 0, 1);
  AU15_c = gui->addValuePlotter("AU15_c", 0, 1);
  AU17_c = gui->addValuePlotter("AU17_c", 0, 1);
  AU20_c = gui->addValuePlotter("AU20_c", 0, 1);
  AU23_c = gui->addValuePlotter("AU23_c", 0, 1);
  AU25_c = gui->addValuePlotter("AU25_c", 0, 1);
  AU26_c = gui->addValuePlotter("AU26_c", 0, 1);
  AU28_c = gui->addValuePlotter("AU28_c", 0, 1);
  AU45_c = gui->addValuePlotter("AU45_c", 0, 1);

  faceMovie.load("movies/fizzbuzz_processed.mp4");
  faceMovie.play();
  screenMovie.load("movies/fizzbuzz_scratch.mp4");
  screenMovie.play();
}
  

//--------------------------------------------------------------
void ofApp::update(){
  faceMovie.update();
  screenMovie.update();

  int current_frame = faceMovie.getCurrentFrame();
  if (current_frame > 0) {
    gaze_0_x = stof(csv[current_frame][5]);
    gaze_0_y = stof(csv[current_frame][6]);
    gaze_1_x = stof(csv[current_frame][8]);
    gaze_1_y = stof(csv[current_frame][9]);

    float current_au01_c = stof(csv[current_frame][679]);
    float current_au02_c = stof(csv[current_frame][680]);
    float current_au04_c = stof(csv[current_frame][681]);
    float current_au05_c = stof(csv[current_frame][682]);
    float current_au06_c = stof(csv[current_frame][683]);
    float current_au07_c = stof(csv[current_frame][684]);
    float current_au09_c = stof(csv[current_frame][685]);
    float current_au10_c = stof(csv[current_frame][686]);
    float current_au12_c = stof(csv[current_frame][687]);
    float current_au14_c = stof(csv[current_frame][688]);
    float current_au15_c = stof(csv[current_frame][689]);
    float current_au17_c = stof(csv[current_frame][690]);
    float current_au20_c = stof(csv[current_frame][691]);
    float current_au23_c = stof(csv[current_frame][692]);
    float current_au25_c = stof(csv[current_frame][693]);
    float current_au26_c = stof(csv[current_frame][694]);
    float current_au28_c = stof(csv[current_frame][695]);
    float current_au45_c = stof(csv[current_frame][696]);

    AU01_c->setValue(current_au01_c);
    AU02_c->setValue(current_au02_c);
    AU04_c->setValue(current_au04_c);
    AU05_c->setValue(current_au05_c);
    AU06_c->setValue(current_au06_c);
    AU07_c->setValue(current_au07_c);
    AU09_c->setValue(current_au09_c);
    AU10_c->setValue(current_au10_c);
    AU12_c->setValue(current_au12_c);
    AU14_c->setValue(current_au14_c);
    AU15_c->setValue(current_au15_c);
    AU17_c->setValue(current_au17_c);
    AU20_c->setValue(current_au20_c);
    AU23_c->setValue(current_au23_c);
    AU25_c->setValue(current_au25_c);
    AU26_c->setValue(current_au26_c);
    AU28_c->setValue(current_au28_c);
    AU45_c->setValue(current_au45_c);
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
  faceMovie.setPosition((float)x / (float)ofGetWidth());
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
  faceMovie.setPaused(true);
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
