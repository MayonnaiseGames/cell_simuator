#pragma once

//External
#include <vector>
#include <iostream>
#include <inttypes.h>

//Internal

class Simulation{
    public:
        Simulation();
        ~Simulation();
        void update();
        std::vector<uint16_t> data;
        
    private:
};
