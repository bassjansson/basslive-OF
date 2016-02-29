//
//  BufferFunction.hpp
//  BassLive 2.0
//
//  Created by Bass Jansson on 28/02/16.
//
//

#ifndef BufferFunction_hpp
#define BufferFunction_hpp

#include "Function.hpp"


class BufferFunction : public Function
{
public:
    //========================================================================
    BufferFunction (MainFunction* mf);
    
    //========================================================================
    virtual void trigger();
    
    //========================================================================
    virtual Type* process (buf& buffer, sig& output, Clock& clock);
    
private:
    //========================================================================
    bool updateAudioBuffer();
    
    //========================================================================
    AudioBuffer* buffer;
    NumberType* size;
    string buffer_id;
    
    //========================================================================
    sig_vec inputs;
    buf_vec buffers;
};


#endif /* BufferFunction_hpp */
