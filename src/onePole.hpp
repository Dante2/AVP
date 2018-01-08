//
//  onePole.hpp
//  CP2
//
//  Created by dante on 11/05/2017.
//
//

#ifndef onePole_hpp
#define onePole_hpp

#include "ofMain.h"

class OnePole{
    
public:
    OnePole();
    void SetCoefficients(float time, int sampleRate);
    float Process(float sig);
    float z;
    float a;
    float b;
    
private:
};

#endif /* onePole_hpp */

