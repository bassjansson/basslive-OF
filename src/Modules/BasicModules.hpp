//
//  BasicModules.h
//  BassLive
//
//  Created by Bass Jansson on 16/11/15.
//
//

#ifndef __BassLive__BasicModules__
#define __BassLive__BasicModules__

#include "Module.hpp"


//========================================================================
// loop_Module
//========================================================================
class loop_Module : public AudioModule
{
public:
    virtual void process (sig_vec& inputs, buf_vec& buffers, sig output, Clock clock);
};


//========================================================================
// add_Module
// sub_Module
// mul_Module
// div_Module
//========================================================================
class add_Module : public AudioModule
{
public:
    virtual void process (sig_vec& inputs, buf_vec& buffers, sig output, Clock clock);
};

class sub_Module : public AudioModule
{
public:
    virtual void process (sig_vec& inputs, buf_vec& buffers, sig output, Clock clock);
};

class mul_Module : public AudioModule
{
public:
    virtual void process (sig_vec& inputs, buf_vec& buffers, sig output, Clock clock);
};

class div_Module : public AudioModule
{
public:
    virtual void process (sig_vec& inputs, buf_vec& buffers, sig output, Clock clock);
};


#endif /* defined(__BassLive__BasicModules__) */
