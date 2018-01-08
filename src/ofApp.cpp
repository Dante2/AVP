/* a big fat mega synth */

/* WARNING dont turn up to loud as there is a little bit of speaker popping happening upon intiation */

#include "ofApp.h"

// ofxCvFlow ----------------------------------------------------------------------

// ofxCvFlow ----------------------------------------------------------------------

//using namespace ofxCv;
//using namespace cv;

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetFrameRate(60);
    
    // So far I have found that a time of 1 and sample rate of 10 tends to give me the best results in terms of smoothing the signal.
    mOnePole.SetCoefficients(1, 10);
    
    // maxiClock
    myClock.setTicksPerBeat(2);
    myClock.setTempo(60);
    
    // set sampling Rate
    sampleRate = 44100;
    
    // set buffer Size. you have to fill this buffer with sound using the for loop in the audioOut method
    bufferSize = 512;
    
    // calling the calling the setup method in maximilian settings containing samplerate and buffer size
    ofxMaxiSettings::setup(sampleRate, 2, bufferSize);
    
    for (int i = 0; i < 6; i++) {
    
    // apply ADSR values accordingly
    ADSR[i].setAttack(20);
    ADSR[i].setDecay(100);
    ADSR[i].setSustain(0.25);
    ADSR[i].setRelease(1000);
    }
    
    ofBackground(0,0,0);
    
    ofSoundStreamSetup(2,2,this, sampleRate, bufferSize, 4);
    ampOut = 0.5;
}

//--------------------------------------------------------------
void ofApp::draw(){
 
   /* LFO1out = mOnePole.z; // this needs work
    
    // z is the finished onePole signal
    cout << "z signal = " << LFO1out << endl; */
    
    // draw the interactive line. Push and Pop matrix to hold together the draw parameters of the line
    
    ofPushMatrix();
    ofSetColor(255);
    ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
    
    /* We use ofRotate with the onePole process function. angle is fed into the sig variable in the process function
     and therefore multiplied by the coefficients. Rotate is therefore working off the process function calculating the coeeficients
     with the angle data being fed from our 2d vector variable named "direction" */
    
    // ofRotate(mOnePole.Process(angle));
    ofDrawLine(0, 0, 0, 300);
    ofPopMatrix();
    
}

//--------------------------------------------------------------
void ofApp::audioOut(float * output, int bufferSize, int nChannels) {
    
    for (int i = 0; i < bufferSize; i++){
        
        mix = 0;
        
        myClock.ticker();
        if (myClock.tick) {
            if (voice == 6) {
                voice = 0;
            }
            
            ADSR[voice].trigger = 1;
            pitch[voice] = voice + 1;
            voice ++;
        }
        
        for (int i = 0; i < 6; i++) {
        
        ADSRout[i] = ADSR[i].adsr(1., ADSR[i].trigger);
        LFO1out = LFO1.sinewave(5) * 2;
        LFO2out = LFO2.sinewave(0.1) * 1500;
        LFO3out[i] = LFO3[i].sinebuf(0.2);
        VCO4out[i] = VCO4[i].pulse((110 * pitch[i]) + LFO3out[i], 0.2);
        VCO5out[i] = VCO5[i].pulse(55 * pitch[i], 0.6);
        VCF5out[i] = VCF5[i].lores((VCO5out[i] + VCO4out[i]) * 0.5, 250 + ((pitch[i] + LFO3out[i]) * 1000), 10);
        }
        
        // sequencing with phasor and an array of freq values
        
        int myArray[10] = {100, 200, 300, 400, 500, 600, 500, 400, 300, 200};
        currentCount = myCounter.phasor(1, 1, 9);
        
        //--- oscillators ---//
        
        // worth playing around with high pass / band pass / band reject
        VCO1out = VCO1.square(2000) * currentCount;
        
        // LFO controlled oscillator --> vibrato
        VCO2out = VCO2.sawn(200 + LFO1out);
        
        // using env to control pitch of oscillator --> good for drums with currentCount phasor as clock
        VCO3out = VCO3.sawn(currentCount * 100 * ADSRout[i] * 10);
        
        // filters
        // low pass - portamento
        VCF1out = VCO1.square(VCF1.lopass(myArray[currentCount], 0.005));
        
        // low res - vibrato
        VCF2out = VCF2.lores(VCO2out, 2000 + LFO2out, 20);
            
        // VCF3out = VCF3.lores((VCO3out + VCO4out[i]) * 0.5, 250 + ((pitch[i] + LFO3out[6]) * 1000), 10);
        
        // apply envs
        double VCF2env = VCF2out * ADSRout[i];
        double VCO3env = VCO3out * ADSRout[i];
        
        // amplitude control on raw oscillator and filter
        double VCO1amp = VCO1out * 0.0;
        double VCF1amp = VCF1out * 0.05;
        double VCF2amp = VCF2env * 0.5;
        double VCO2amp = VCO2out * 0.15;
        double VCO3amp = VCO3env * 0.5;
        
        double otherAmp = VCF5out[i] * ADSRout[i] / 6;

        // mixer
        mix += VCO1amp + VCF1amp + VCF2amp + VCO2amp + VCO3amp + otherAmp;
        
        ADSR[i].trigger = 0;
        output[i * nChannels] = mix;
        output[i * nChannels + 1] = mix;
        
    }
}

