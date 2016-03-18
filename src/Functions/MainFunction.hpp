//
//  MainFunction.hpp
//  BassLive 2.0
//
//  Created by Bass Jansson on 18/02/16.
//
//

#ifndef MainFunction_hpp
#define MainFunction_hpp

#include "Function.hpp"


class MainFunction : public Function
{
public:
    //========================================================================
    MainFunction (Memory* memory);
    
    //========================================================================
    sig* compile (Memory* memory, bool record);
    
    //========================================================================
    void draw();
    
    //========================================================================
    void keyPressed (int key);
    
private:
    //========================================================================
    Memory* memory;
    int cursorTime;
};


#endif /* MainFunction_hpp */
