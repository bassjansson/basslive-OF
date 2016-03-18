//
//  BasicModules.hpp
//  BassLive 2.0
//
//  Created by Bass Jansson on 16/11/15.
//
//

#ifndef BasicModules_hpp
#define BasicModules_hpp

#include "Module.hpp"


//========================================================================
// operator_Module
//========================================================================
class operator_Module : public AudioModule
{
public:
    operator_Module (const string& ID, char op);
    
private:
    virtual void process (Clock& clock);
    
    char op;
};


//========================================================================
// click_Module
//========================================================================
class click_Module : public AudioModule
{
public:
    click_Module (const string& ID);
    
private:
    virtual void process (Clock& clock);
};


//========================================================================
// loop_Module
//========================================================================
class loop_Module : public AudioModule
{
public:
    loop_Module (const string& ID);
    
private:
    virtual void process (Clock& clock);
};


#endif /* BasicModules_hpp */
