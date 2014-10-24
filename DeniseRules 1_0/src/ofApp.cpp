#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0,0,0);

    //ofVbo::disableVAOs();

    glfw = (ofxMultiGLFWWindow*)ofGetWindowPtr();

    // vector of windows, count set in main
    windows = &glfw->windows;
    
    // configure first window : GUI
    glfw->setWindow(windows->at(0));    // set window pointer
    glfw->initializeWindow();       // initialize events (mouse, keyboard, etc) on window (optional)
    ofSetWindowPosition(0, 100);    // business as usual...
    ofSetWindowShape(600, 800);
    ofSetWindowTitle("DR GUI");
    //ofSetFullscreen(true);        // order important with fullscreen

    
    // configure second window : Display
    glfw->setWindow(windows->at(1));
    glfw->initializeWindow();
    ofSetWindowPosition(500, 100);
    ofSetWindowShape(1024, 768);
    ofSetWindowTitle("DR Display");
    
    glfw->setWindow(windows->at(0));
    
    render.setup();
    gui.setup(render);
    
}

//--------------------------------------------------------------
void ofApp::update(){
    // update is still called once per frame
    switch (updateIndex) { // switch on window index
        case 0:
            gui.update();
            updateIndex=1;
            break;
        case 1:
            render.update();
            updateIndex=0;
            break;
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    // draw is called once on each window every frame
    
    // the window index will increment
    wIndex = glfw->getWindowIndex();

    switch (wIndex) { // switch on window index
        case 0:
            gui.draw();
            break;
        case 1:
            render.draw();
            break;
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
    // get event window to identify window source
    if (glfw->getEventWindow() == windows->at(0))
        cout << "window 1: key pressed" << endl;
    else if (glfw->getEventWindow() == windows->at(1))
        cout << "window 2: key pressed" << endl;
    
    // hide current window
    if (key == 'h')
        glfw->hideWindow(glfw->getEventWindow());
    
    // show current window
    else if (key == '1')
        glfw->showWindow(windows->at(0));
    else if (key == '2')
        glfw->showWindow(windows->at(1));
    else if (key == 'n') {
        glfw->setWindow(glfw->getEventWindow());
        ofHideCursor();
    }
    else if (key == 'm') {
        glfw->setWindow(glfw->getEventWindow());
        ofShowCursor();
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    cout << "key released" << endl;
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    // get event window to identify window source
    if (glfw->getEventWindow() == windows->at(0))
        cout << "window 1: mouse moved" << endl;
    else if (glfw->getEventWindow() == windows->at(1))
        cout << "window 2: mouse moved" << endl;
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    cout << "mouse dragged" << endl;
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    // get event window to identify window source
    if (glfw->getEventWindow() == windows->at(0))
        cout << "window 1: mouse pressed" << endl;
    else if (glfw->getEventWindow() == windows->at(1))
        cout << "window 2: mouse pressed" << endl;
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    cout << "mouse released" << endl;
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
