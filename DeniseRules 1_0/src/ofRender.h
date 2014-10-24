#pragma once

#include "ofMain.h"
// My addons ---------------
#include "ofxParticleWorld.h"
#include "ofxSpreads.h"
//#include "ofdSpreadGuiWindowWithOsc.h"  // Fenetre d'interface
#include "ofxColorSet.h"
#include "ofxEasyOsc.h"
#include "ofxSpiralo.h"
#include "ofxFullOfStrips.h"

// Ext addons
//#include "msaFluidParticlesApp.h"
//#include "ofxSimpleGuiToo.h"
#include "ofxFensterManager.h"
#include "ofxSyphon.h"


// Obsoletes
/*
#include "ofdGrid.h"
#include "ofxThreadedImageSaver.h"
#include "ofdWordSet.h"
#include "ofdScreenRecord.h"
#include "ofdAudioReact_2.h"
#include "ofdFX.h"
#include "ofdMovements.h"
*/

// Constantes ---------------------------------
#define     TYPO_ALL        0
#define     TYPO_FROMBEG    1
#define     TYPO_FROMEND    2
#define     TYPO_FROMRND    3
#define     TYPO_OUTLBEG    4
#define     TYPO_OUTLEND    5

#define     SPTYPO_SPREADS  "Spreads"

class ofRender : public ofBaseApp{

	public:
        ofRender();
        ~ofRender(){}
    
		void setup();
		void setupParameters();
		void update();
		void draw();

		void keyPressed  (int key);
		void keyReleased(int key);
		void windowResized(int w, int h);


    // PARTICULES
public:
    ofxParticleWorld m_oPartWorld;
    vector<ofxAttractor>        m_aAttractors;
    
private:
    // SPREADS
    ofdSpreads m_oSpreads;

    // MSA : MegaAwesomeVisuals, that's right
    /* Not OF recent compatible
        msaFluidParticlesApp m_MSA;
        void updateMSA();
    */
    
public:
    ofxColorSet m_oColorSet;

    // Discours Président
    private:
        string m_nameSpreads;
        string m_lastSpreads;
        unsigned int    m_numPattern;


    public:
    // Define GUI --------------------------------------------------
        void updateGUI();

        //ofdSpreadGuiToApp mIn_vars;
        string m_strTrace;

    // SYPHON -------------------------------------------------------
    ofxSyphonServer m_oSyphonServer;
    ofTexture       m_oTexSyphon;
    
    // PARAMETERS -----------------------------------------------------
    ofParameterGroup m_gpTubesPatterns;
    //ofParameterGroup m_gpMSA;
    
    // MSA ------------------
    /*
    ofParameterGroup     m_gpMSA_Useful;
    ofParameter<int>    m_slDrawMode;
    ofParameter<float>  m_slViscocity;
    ofParameter<float>  m_slColorDiffusion;
    ofParameter<float>  m_slFadeSpeed;
    ofParameter<float>  m_slDeltaT;
    ofParameter<float>  m_slColorMult;
    ofParameter<float>  m_slVelocityMult;
    
    ofParameterGroup        m_gpMSA_Useless;
    ofParameter<int>        m_slfluidCellsX;
    ofParameter<bool>       m_btResizeFluid;
    ofParameter<int>        m_slSolverIterations;
    ofParameter<bool>       m_btDoRGB;
    ofParameter<bool>       m_btDoVorticityConfinement;
    ofParameter<bool>       m_btDrawFluid;
    ofParameter<bool>       m_btDrawParticles;
    ofParameter<bool>       m_btWrapX;
    ofParameter<bool>       m_btWrapY;
    */
    
    // Display ---------------
    ofParameterGroup    m_gpDisplay;
    ofParameter<int>    m_slWidthDisplay;
    ofParameter<int>    m_slHeightDisplay;
    ofParameter<bool>   m_btFullScreen;
    
    // OSC Event
    ofxEasyOsc  m_oOscEventsOnOff;
    ofxEasyOsc  m_oOscEventsFades;
    
    // ARDUINO -----------------------------------------------------------------------------------------
public:
    ofxMyArduinoServer    m_oArduinoServer;
    ofxMyArduinoClient    m_oArduinoClient;
    
    // SPIRALO -----------------------------------------------------------------------------------------
public:
    ofxSpiralo  m_oSpiralo;
    
    // Strips ------------------------------------------------------------------------------------
public:
    ofxFullOfStrips m_oStrips;

    
};
