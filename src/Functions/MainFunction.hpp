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
    ~MainFunction ();
    
    //========================================================================
    void draw();
    
    //========================================================================
    void keyPressed (int key);
    sig* compile (Memory* memory, bool record);
    
    //========================================================================
    void mousePressed  (float x, float y, int button);
    void mouseReleased (float x, float y, int button);
    
private:
    //========================================================================
    Memory* memory;
    int cursorTime;
};


#endif /* MainFunction_hpp */
