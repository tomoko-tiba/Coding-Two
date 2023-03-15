#pragma once
#include "boid.h"
#include <vector>
#include "ofMain.h"
#include <stdio.h>

class childBoid : public Boid {
    public:
        childBoid();
        childBoid(ofVec3f& pos, ofVec3f& vel);

        ~childBoid();

        void draw();

};
