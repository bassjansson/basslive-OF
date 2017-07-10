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

#define NEWTON_SIZE 4 // Maybe should not be here


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
    
    //========================================================================
    float a[2]; // TODO: code should be more clear, maybe not public
    float coefs[NEWTON_SIZE][2];
    
private:
    //========================================================================
    Memory* memory;
    int   cursorTime;
    float cursorAnim;
};


#endif /* MainFunction_hpp */
