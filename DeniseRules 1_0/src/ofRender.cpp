
#include "ofRender.h"

//--------------------------------------------------------------
void ofRender::setup(){
    
    
    setupParameters();
    
    // Display settings -------------------------------------------
    ofSetVerticalSync(true);
	ofSetFrameRate(60);
    ofEnableAlphaBlending();
    
    ofSetBackgroundAuto(true);
    
    setWindowShape(m_slWidthDisplay, m_slHeightDisplay);
    
    // PARTICLES WORLD Setup
    m_oPartWorld.setup(m_oColorSet);
    // Ajout des forces --------------------------------------------------------
    m_aAttractors.push_back(ofxAttractor(m_oPartWorld, ofPoint(0.5*getWidth(), 0.6*getHeight())));
    
    // SPREADS Motifs --------------------------------------------------------------
    m_oSpreads.setup("XML/SpreadsSettings.xml");
    m_oSpreads.set_refColorSet(m_oColorSet);
    // Load all Drawings files -------------------------------------------------------------
    m_oSpreads.loadSVGDirectory("drawings", m_oPartWorld, m_oColorSet);
    m_oSpreads.loadDrawingDirectory("drawings", m_oPartWorld, m_oColorSet);
    m_nameSpreads = m_oSpreads.lastSpreadFamily();
    
    // MSA -----------------------
    //m_MSA.set_refColorSet(m_oColorSet);
    //m_MSA.setup();
    
    // SYPHON ------------------------
    m_oTexSyphon.allocate(m_slWidthDisplay, m_slWidthDisplay, GL_RGB);
    m_oSyphonServer.setName("Spread_Display");
    
    // ARDUINO ------------------------
    m_oArduinoServer.setup();
    
    // SPIRALO ------------------------
    m_oSpiralo.setup(m_oColorSet);
    
    m_oStrips.setup(m_oColorSet);
	
}

//--------------------------------------------------------------
void ofRender::setupParameters(){
    
    // GUI Interface -----------------------------------------
    
    string modeSeq_Lbl[4];
    modeSeq_Lbl[0] = "1 - Debut->Fin";
    modeSeq_Lbl[1] = "2 - Fin->Debut";
    modeSeq_Lbl[2] = "3 - Milieu";
    modeSeq_Lbl[3] = "4 - Random";
    
    string modeMSA[6];
    modeMSA[0] = "None";
    modeMSA[1] = "Vectors";
    modeMSA[2] = "Colors";
    modeMSA[3] = "Speed";
    modeMSA[4] = "Motion";
    modeMSA[5] = "DrawCount";
    
    m_oSpreads.setupParameters();
    m_gpTubesPatterns.setName("TubesPatterns");
    m_gpTubesPatterns.add(m_oSpreads.m_gpTubes);
    m_gpTubesPatterns.add(m_oSpreads.m_gpPatterns);
    
    
    // MSA -------------------------------------------
    /*
    m_gpMSA.setName("MSA");
    // MSA Useful ---------------------------------------------------------
    m_gpMSA_Useful.setName("MSAUseful");
    // TODO : Add Label
    m_gpMSA_Useful.add(m_slDrawMode.set("DrawMode", 0, 0, 5));
    m_gpMSA_Useful.add(m_slViscocity.set("Viscocity", 0, 0, 0.005));
    m_gpMSA_Useful.add(m_slColorDiffusion.set("ColorDiffusion", 0, 0.0, 0.0003));
    m_gpMSA_Useful.add(m_slFadeSpeed.set("FadeSpeed", 0, 0.0, 0.1));
    m_gpMSA_Useful.add(m_slDeltaT.set("DeltaT", 0, 0.1, 5));
    m_gpMSA_Useful.add(m_slColorMult.set("ColorMult", 0, 0, 100));
    m_gpMSA_Useful.add(m_slVelocityMult.set("VelocityMult", 0, 0, 100));
    m_gpMSA.add(m_gpMSA_Useful);
    
    // PAGE 3 : AUDIO + MSA parameters
    m_gpMSA_Useless.setName("MSAUseless");
    m_gpMSA_Useless.add(m_slfluidCellsX.set("FluidCellsX", 120, 20, 400));
    m_gpMSA_Useless.add(m_btResizeFluid.set("ResizeFluid", true));
    m_gpMSA_Useless.add(m_slSolverIterations.set("SolverIterations", 45, 1, 50));
    m_gpMSA_Useless.add(m_btDoRGB.set("DoRGB", true));
    m_gpMSA_Useless.add(m_btDoVorticityConfinement.set("DoVorticityConfinement", false));
    m_gpMSA_Useless.add(m_btDrawFluid.set("DrawFluid", true));
    m_gpMSA_Useless.add(m_btDrawParticles.set("DrawParticles", false));
    m_gpMSA_Useless.add(m_btWrapX.set("WrapX", true));
    m_gpMSA_Useless.add(m_btWrapY.set("WrapY", true));
    m_gpMSA.add(m_gpMSA_Useless);
    */
    
    // Display
    m_gpDisplay.setName("Display");
    m_gpDisplay.add(m_slWidthDisplay.set("WidthDisplay", 1024, 720, 2000));
    m_gpDisplay.add(m_slHeightDisplay.set("HeightDisplay", 768, 480, 2000));
    m_gpDisplay.add(m_btFullScreen.set("Fullscreen", false));
    
}

//--------------------------------------------------------------
void ofRender::update(){
    
    string WindowTitle = "";
    WindowTitle = "Spreads_Display";
    WindowTitle += " - ";
    WindowTitle += ofToString(ofGetFrameRate());
    
    setWindowTitle(WindowTitle);
    
    // 1ere Affect des tailles de fenetre
    // CALCUL DE LA TAILLE DE FENETRE ET EVENEMENT -----------------------------------
    /*
    if(m_slWidthDisplay!=getWidth() || m_slHeightDisplay!=getHeight()){
      windowResized(m_slWidthDisplay, m_slHeightDisplay);
    }
     */
    // Fullscreen ? --
    setFullscreen(m_btFullScreen);
    
    // RECUPERATION DEPUIS La GUI ET INJECTION DANS LE SYSTEME
    ofLogVerbose() << ("Trace Error : __GUI__");
    updateGUI();
    
    // MSA Modes
    // Changement de page MSA
    /*
    switch (m_slDrawMode){
        case MSAmode_Vectors:
            m_MSA.fluidDrawer.setDrawMode(msa::fluid::kDrawVectors);
            break;
        case MSAmode_Speed:
            m_MSA.fluidDrawer.setDrawMode(msa::fluid::kDrawSpeed);
            break;
        case MSAmode_Motion:
            m_MSA.fluidDrawer.setDrawMode(msa::fluid::kDrawMotion);
            break;
        case MSAmode_Colors:
            m_MSA.fluidDrawer.setDrawMode(msa::fluid::kDrawColor);
            break;
        case MSAmode_DrawCount:
            m_MSA.fluidDrawer.setDrawMode(msa::fluid::kDrawCount);
            break;
        default:
            break;
    }
    */
    // PAD -------------------------------------------------------------------------
    ofLogVerbose() << ("Trace Error : __ PADS __");
    
    // Events Particules -----------------------------------------
    // TODO : with new ofxAttractors
    /*
    if (m_oOscEvents.getConstValue("/Events/Parts/Center") > 0.5) {
        m_oPartWorld.set_partsAtPosition(POSPARTS_CENTER, m_oOscEvents.getConstValue("/Events/Parts/Center"));
    }
    if (m_oOscEvents.getConstValue("/Events/Parts/Circle") > 0.5) {
        m_oPartWorld.set_partsAtPosition(POSPARTS_CIRCLE, m_oOscEvents.getConstValue("/Events/Parts/Circle"));
    }
    if (m_oOscEvents.getConstValue("/Events/Parts/Hori") > 0.5) {
        m_oPartWorld.set_partsAtPosition(POSPARTS_HORI, m_oOscEvents.getConstValue("/Events/Parts/Hori"));
    }
    if (m_oOscEvents.getConstValue("/Events/Parts/Vert") > 0.5) {
        m_oPartWorld.set_partsAtPosition(POSPARTS_VERT, m_oOscEvents.getConstValue("/Events/Parts/Vert"));
    }
    */
    
    // --------------------------------------------------------------
    // ALL PATTERNS EVENTS -------------------------------------------
    // ON / OFF
    while (!m_oOscEventsOnOff.isEventsEmpty()){
        ofxEasyOscEventMessage eventToGo = m_oOscEventsOnOff.getFirstEvent();
        
        string  family = eventToGo.getFamily();
        string  name = eventToGo.getName();
        float   value = eventToGo.getValue();
        
        // On envoie le pattern si c'est du note off (c'est ˆ dire value = 0)
        if(value!=0){
            //m_oSpreads.eventSequence(_family, _name, m_oSpreads.m_slModeTypo2, m_oPartWorld.m_btPartsOn, false);
            //m_oSpreads.eventAll(_family, _name, m_oPartWorld.m_btPartsOn, false);
            m_oSpreads.eventOn(family, name, 255*value, m_oPartWorld.m_btPartsOn, true);
            //m_oSpreads.eventOn(family, name, 255*value, false, true);
        }else{
            m_oSpreads.eventOff(family, name);
        }
        
        if(family=="arduino"){
            m_oArduinoClient.addPwmSignal(ofToInt(name), 255*value);
        }

    };
    
    while (!m_oOscEventsFades.isEventsEmpty()){
        ofxEasyOscEventMessage eventToGo = m_oOscEventsFades.getFirstEvent();
        
        string  family = eventToGo.getFamily();
        string  name = eventToGo.getName();
        float   value = eventToGo.getValue();
        
        if(value!=0){
            // On envoie le pattern si c'est du note off (c'est ˆ dire value = 0)
            // m_oSpreads.eventAll(family, name, 255*value, m_oPartWorld.m_btPartsOn, true);
            m_oSpreads.eventSequence(family, name, 255*value, m_oPartWorld.m_btPartsOn, m_oSpreads.m_slSeqMode, true);
        }
        
        if(family=="arduino"){
            m_oArduinoClient.addPwmSignal(ofToInt(name), 255*value);
        }
        
    };
    
    // --------------------------------------------------------------
    // AUDIO REACTION ------------------------------------------------------------
    ofLogVerbose() << ("Trace Error : __ AUDIO __");
    
    /*
    if (m_oOscEvents.getConstValue("/Audio/Trigger/Bass")>0.5){
        m_oSpreads.eventSequence(ofToString(0), m_oSpreads.m_slModeTypo2, m_oPartWorld.m_btPartsOn, false);
    }
    if (m_oOscEvents.getConstValue("/Audio/Trigger/Mid")>0.5){
        m_oSpreads.eventSequence(ofToString(1), m_oSpreads.m_slModeTypo2, m_oPartWorld.m_btPartsOn, false);
    }
    if (m_oOscEvents.getConstValue("/Audio/Trigger/High")>0.5){
        m_oSpreads.eventSequence(ofToString(2), m_oSpreads.m_slModeTypo2, m_oPartWorld.m_btPartsOn, false);
    }
    */
    
    // UPDATES ----------------------------------------------------------------------
    ofLogVerbose() << ("Trace Error : __ UPDATES __");

    // COLOR SET ---------------------------------------------------------------------
    m_oColorSet.update();
    
    // PARTICULES -------------------
    m_oPartWorld.setAttractors(&m_aAttractors);
    m_oPartWorld.update();
    
    // SPREADS ----------------------
    m_oSpreads.update();
    
    // MSA no more compatible ----
    /*
    updateMSA();                    // Update des paramètres MSA
    m_MSA.update();                 // MSA Particules
    
    // RECALCULS DES TRACKERS ----------------------------------------------------------------------
    ofLogVerbose() << ("Trace Error : __ TrackersMSA __");
    // ici on gére les rendus des particules qui ne sont pas gérés dans les particules en elles-mêmes
    if(m_slDrawMode != MSAmode_None){
        
        vector<ofxParticle*>::iterator itParts;
        vector<ofxParticle*>          trackers = m_oPartWorld.m_aPartTrackers;
        
        Vec2f pos;
        Vec2f vel;
        
        for(itParts = trackers.begin(); itParts!= trackers.end(); itParts++){
            
            vel.x = (*itParts)->getVel().x / getWidth();
            vel.y = (*itParts)->getVel().y / getHeight();
            
            pos.x = (*itParts)->getPos().x / getWidth();
            pos.y = (*itParts)->getPos().y / getHeight();
            
            switch(m_slDrawMode){
                case MSAmode_Motion:
                case MSAmode_Speed:
                case MSAmode_Vectors:
                    m_MSA.addToFluid(pos,vel,true,true);
                    break;
                    
                case MSAmode_Colors:
                case MSAmode_DrawCount:
                    m_MSA.addToFluid(pos,vel,true,false);
                    break;
                    
                case MSAmode_None:
                default:
                    break;
                    
            }
        }
    }
    */
    
    // ARDUINO --------------------------------------------------------------------------
    m_oArduinoServer.update();
    // ----------------------------------------------------------------------------------
    
    //  INFOS
    m_strTrace = ofToString(ofGetElapsedTimeMillis()) + " |\t" ;
    m_strTrace += ofToString(ofGetFrameRate()) + " |\t" ;
    m_strTrace += ofToString("Parts: " + ofToString(m_oPartWorld.m_aParts.size())) + " |\t";
    m_strTrace += ofToString("Trackers: " + ofToString(m_oPartWorld.m_aPartTrackers.size())) + " |\t";
    m_strTrace += "Background : " + ofToString(m_oSpreads.m_spreadsDrawings.size()) + " x " + m_oSpreads.lastSpreadFamily() + " : " + ofToString(m_numPattern)+ " |";
    
    ofLogVerbose() << m_strTrace;
    
}

//--------------------------------------------------------------
void ofRender::draw(){
    
    ofLogVerbose() << ("DRAW BEGIN");
    ofEnableSmoothing();

    // Clear with alpha, so we can capture via syphon and composite elsewhere should we want.
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    
    // MSA ------------------------
    //if(m_slDrawMode != MSAmode_None){
    //    m_MSA.draw();
    //}
    
    m_oPartWorld.draw();    // PARTICULES --------------
    m_oSpreads.draw();    // SPREADS : Neons ------------------
    m_oSpiralo.draw();  // SPIRALO ---------------------------
    m_oStrips.draw();   // STRIPS ------------------------
    
    // OUT TO SYPHON : Syphon server -------------------
    m_oTexSyphon.loadScreenData(0, 0, getWidth(), getHeight());
    m_oTexSyphon.draw(0,0);
    
    m_oSyphonServer.publishScreen();

    
}

//--------------------------------------------------------------
void ofRender::keyPressed(int key){
    // MSA --------------------------------------------------------------------
    //m_MSA.keyPressed(key);
}

//--------------------------------------------------------------
void ofRender::keyReleased(int key){
    
    //    switch(key){
    switch(key){
            // TOUCHES F1, etc.... = SELECTEUR On/Off
        case 257:   break;      // F1 : PARTICULES OK S1
        case 258:   break;      // F2 : LETTRE OK S2
        case 259:   break;      // F3 : RAYURES OK S3
        case 260:   break;      // F4 : MSA Colors OK S4
        case 261:   break;      // F5 : MSA Motion OK S5
        case 262:   break;      // F6 : MSA Vectors OK S6
        case 263:   break;      // F7 : MSA Vectors OK S6
        case 264:   break;      // F8 : FORCES
        case 265:   break;      // F9
        case 266:   break;      // F10
        case 267:   break;      // F11
        case 268:   ofToggleFullscreen();   break;      // F12
            ////  -------------------------------------------------------
            
        case 356:   // Fleche Gauche
            m_oColorSet.prevSet();
            //           m_colorSet_2.prevSet();
            break;
        case 357:
            m_oSpreads.nextSpreadFamily();
            break;                          // Fleche Haut
        case 358:   // Fleche Droite
            m_oColorSet.nextSet();
            //           m_colorSet_2.nextSet();
            break;
        case 359:
            m_oSpreads.prevSpreadFamily();
            break;                          // Fleche Bas
            // ----------------------------------------------------------------
        default:    break;
    }
}

//--------------------------------------------------------------
void ofRender::windowResized(int w, int h){
    
    setWindowShape(w, h);
    
    m_oTexSyphon.allocate(getWidth(), getHeight(), GL_RGB);
    
}

//--------------------------------------------------------------
/*
void ofRender::updateMSA(){
    
    m_MSA.fluidCellsX                       = m_slfluidCellsX;
	m_MSA.resizeFluid                       = m_btResizeFluid;
	m_MSA.fluidSolver.viscocity             = m_slViscocity;
	m_MSA.fluidSolver.colorDiffusion        = m_slColorDiffusion;
	m_MSA.fluidSolver.fadeSpeed             = m_slFadeSpeed;
	m_MSA.fluidSolver.solverIterations      = m_slSolverIterations;
	m_MSA.fluidSolver.deltaT                = m_slDeltaT;
	m_MSA.fluidSolver.doRGB                 = m_btDoRGB;
	m_MSA.fluidSolver.doVorticityConfinement= m_btDoVorticityConfinement;
	m_MSA.drawFluid                         = m_btDrawFluid;
	m_MSA.drawParticles                     = m_btDrawParticles;
	m_MSA.fluidSolver.wrap_x                = m_btWrapX;
	m_MSA.fluidSolver.wrap_y                = m_btWrapY;
	m_MSA.colorMult                         = m_slColorMult;
	m_MSA.velocityMult                      = m_slVelocityMult;
    
}
*/

void ofRender::updateGUI(){
    // Pattern Family  + Pattern number -----------------------
    m_numPattern = m_oSpreads.m_slNumPattern;
    m_oSpreads.putOneSpreadFamilyByNum(m_oSpreads.m_slPatternFamily);

}

