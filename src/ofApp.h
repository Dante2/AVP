#pragma once

#include "ofMain.h"
#include "ofxMaxim.h"
#include "onePole.hpp"

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void draw();
    void audioOut(float * output, int bufferSize, int nChannels);
    
    // buffer size
    int bufferSize;
    
    // sample rate
    int sampleRate;
    
    // maxiClock object wasn't working but I solved it
    maxiClock myClock;
    
    // set up oscillators. Hardcoding number at VCO3 --> bad?
    maxiOsc VCO1, VCO2, VCO3, VCO4[6], VCO5[6], myCounter, LFO1, LFO2, LFO3[6], myPhasor, myOtherPhasor;
    
    // for use with myCounter
    int currentCount, voice;
    
    // for use with ADSR trigger if statement in clock
    double pitch[6];
    
    // control sound output from oscillators. Hardcoding number at VCO3out --> bad?
    double VCO1out, VCO2out, VCO3out, VCO4out[6], VCO5out[6], LFO1out, LFO2out, LFO3out[6], myOtherPhasorOut;
    
    // envs
    maxiEnv ADSR[6];
    
    // env output
    double ADSRout[6];
    
    // filter
    maxiFilter VCF1, VCF2, VCF3, VCF5[6];
    
    // control out put from filter
    double VCF1out, VCF2out, VCF3out, VCF5out[6];
    
    // oscillator 3 mixed with env
    double VCO3env[6];
    
    // amplitude control oscillator 3
    double VCO3amp[6];
    
    // volume control
    double ampOut;
    
    // mix it all together
    double mix;
    
    double wave;
    
    maxiSample beats, beats2;
    
    double sample1, sample2;

    OnePole mOnePole;
    
    ofVideoGrabber camera;
    
    
};
