#pragma once

#define NikkingsFolder  "Nikkings/"

// Ext addons
//#include "ofxSimpleGuiToo.h"
#include "ofxGui.h"
//#include "ofxFensterManager.h"
// My addons
#include "ofRender.h"

#include "ofxColorSet.h"
#include "ofxLiveGrabber.h"

//#include "msaFluidParticlesApp.h"
//#include "ofdFx.h" // Removed fx because of syphon + Resolume
//#include "ofdTools.h"

#define WindowWidth     1024
#define WindowHeight    768


typedef struct {
    string  name;
    bool    action;
}nikking;

class ofGui: public ofBaseApp{
    
public:
    
    void setup(ofRender &_render);
    void draw();
    
    //void createDisplay();
    void setupGUI();
    void setupOSC();
    
    void update();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void windowResized(int _width, int _height);
    
protected:
private:
    ofxParticle partToSetup;
    
public:
    //ofdSpreadGuiToApp mOut_vars;
    string m_strTrace;
    
private:
    vector<nikking>  m_nikkings;
    
    nikking     m_currentNikking;
    void    loadPresetsFromFolder(string _folder);
    
private:
    // OSC ----------------------------------------------
    ofxOscLiveGrabberParameterSync m_oLiveGrabberColors;
    ofxOscLiveGrabberParameterSync m_oLiveGrabberParts;
    ofxOscLiveGrabberParameterSync m_oLiveGrabberTubesPatterns;
    //ofxOscLiveGrabberParameterSync m_oLiveGrabberMSA;
    ofxOscLiveGrabberParameterSync m_oLiveGrabberStrips;
    ofxOscLiveGrabberParameterSync m_oLiveGrabberSpiralo;
    
    void updateOSC();
    
private:
    // New display system
    ofRender *m_oRender;
    
    // GUI -------------------------------------------------
    ofxPanel m_uiColors;
    ofxPanel m_uiParts;
    ofxPanel m_uiTubesPatterns;
    ofxPanel m_uiArduino;
    //ofxPanel m_uiMSA;
    ofxPanel m_uiEasyOscOnOff;
    ofxPanel m_uiEasyOscFades;
    ofxPanel m_uiDisplay;
    ofxPanel m_uiSpiralo;
    ofxPanel m_uiStrips;
    
    ofxPanel m_uiOthers;
    ofxIntSlider m_slSetLogLevel;
    ofxLabel     m_lbGetLogLevel;
    
    // OSC
    ofParameterGroup     m_gpEasyOsc;
    
    
};
