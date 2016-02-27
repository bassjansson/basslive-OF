//
//  Function.hpp
//  BassLive 2.0
//
//  Created by Bass Jansson on 09/02/16.
//
//

#ifndef Function_hpp
#define Function_hpp

#include "Type.hpp"


class Function : public Type
{
public:
    //========================================================================
     Function (MainFunction* mf);
    ~Function ();
    
    //========================================================================
    virtual Character* getEndChar();
    virtual Character* draw (float& x, float& y, bool vertical);
    virtual Type* process   (sig& output, Clock& clock);
    virtual void keyPressed (int key);
    virtual void trigger();
    
protected:
    //========================================================================
    Identifier* identifier;
    Type*       close;
    
private:
    //========================================================================
    AudioModule* module;
    sig_vec      inputs;
    tick         clock;
    string       am_id;
};


#endif /* Function_hpp */
