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
#include "fftw3.h"


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
// operator_Module
//========================================================================
class operator_Module : public AudioModule
{
public:
    operator_Module (const string& ID, char op);
    
    virtual void setInputs (sig_vec& newInputs);
    
private:
    virtual void process (Clock& clock);
    
    char op;
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


//========================================================================
// crush_Module
//========================================================================
class crush_Module : public AudioModule
{
public:
    crush_Module (const string& ID);
    
private:
    virtual void process (Clock& clock);
};


//========================================================================
// comp_Module
//========================================================================
class comp_Module : public AudioModule
{
public:
    comp_Module (const string& ID);
    
private:
    virtual void process (Clock& clock);
    
    sample targetRMS;
    sample currentRMS;
};


//========================================================================
// pitch_Module
//========================================================================
class pitch_Module : public AudioModule
{
public:
     pitch_Module (const string& ID);
    ~pitch_Module ();
    
private:
    virtual void process (Clock& clock);
    
    sig    buffer;
    tick   pointer;
    sample phasor;
};


//========================================================================
// delay_Module
//========================================================================
class delay_Module : public AudioModule
{
public:
     delay_Module (const string& ID);
    ~delay_Module ();
    
private:
    virtual void process (Clock& clock);
    
    sig  buffer;
    tick pointer;
};


//========================================================================
// pan_Module
//========================================================================
class pan_Module : public AudioModule
{
public:
    pan_Module (const string& ID);
    
private:
    virtual void process (Clock& clock);
};


////========================================================================
//// vocod_Module
////========================================================================
//class vocod_Module : public AudioModule
//{
//public:
//     vocod_Module (const string& ID);
//    ~vocod_Module ();
//    
//private:
//    virtual void process (Clock& clock);
//    
//    int pointer;
//    int p_size;
//    int b_size;
//    
//    float* carIn;
//    float* modIn;
//    float* vocOut;
//    
//    fftwf_complex* carOut;
//    fftwf_complex* modOut;
//    fftwf_complex* vocIn;
//    
//    fftwf_plan carPlan;
//    fftwf_plan modPlan;
//    fftwf_plan vocPlan;
//};


//========================================================================
// switch_Buffer
//========================================================================
class switch_Buffer : public AudioBuffer
{
public:
    switch_Buffer (const string& ID);
    
    virtual void record (tick size);
    
private:
    virtual void process (Clock& clock);
    
    int selectedBufferNumber;
};


#endif /* BasicModules_hpp */
