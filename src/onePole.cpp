//
//  onePole.cpp
//  mySketch
//
//  Created by Jools on 08/01/2018.
//

#include "onePole.hpp"

// One Pole constructor ----------------------------------
// Initialise its variables

OnePole::OnePole(){
    z = 0;
    b = 0.99;
    a = 1 - b;
}

// -----------------------------------------------------------

// One Pole Process function ---------------------------------
// This takes all the coefficients and applies the folloeing mathematical operation to them. 1 is the normalised maximum value of the process. 1 minus b gives us a very small
// number which is then multiplied by our incoming signal (the 2d vector array) and then added to b to calculate the difference between
// the vector's initial state and its changed one. It is all then multiplied by z to modify our original z signal by the newly updated z signal.

float OnePole::Process(float sig){
    z = a * sig + b * z;
    return z;
}

// One Pole setCoefficients function ---------------------------------
// Calculates the coefficients of a and b relative to the time domain and sample rate

// I have tried messing around with the exponent in variable b a little to see what sort of data smoothing effects I get

void OnePole::SetCoefficients(float time, int sampleRate){
    b = exp(-0.5/(time * sampleRate));
    a = 1.0 - b;
    
}

