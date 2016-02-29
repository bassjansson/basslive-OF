//
//  BufferFunction.cpp
//  BassLive 2.0
//
//  Created by Bass Jansson on 28/02/16.
//
//

#include "Types.h"


//========================================================================
bool BufferFunction::updateAudioBuffer()
{
    if (buffer) delete buffer;
    
    if (buffer_id == "buf") return buffer = new AudioBuffer();
    
    return buffer;
}

//========================================================================
BufferFunction::BufferFunction (MainFunction* mf)
: Function(CHAR_FUNC_BUF_OPEN,
           CHAR_TYPE_BUF_ID,
           CHAR_FUNC_BUF_CLOSE, mf)
{
    typeType = BUFFER;
    
    buffer    =  NULL;
    size      =  NULL;
    buffer_id = "NULL";
}

//========================================================================
void BufferFunction::trigger()
{
    // Update buffer and id
    if (buffer_id != getTypeString())
    {
        if (getTypeString() == "")
        {
            mf->charSelected = this;
            new Character('b', mf);
            new Character('u', mf);
            new Character('f', mf);
        }
        
        buffer_id = getTypeString();

        if (updateAudioBuffer())
            flash(COLOR_FUNC_BUFFER);
    }
    
    
    // Trigger children and get size
    Type* t = identifier;
    size = NULL;
    
    while (true)
    {
        if (t == NULL)
            break;
        
        t->trigger();
        
        if (t == close)
            break;
        
        if (size == NULL && t->typeType == NUMBER)
            size = (NumberType*)t;
        
        t = t->getType(RIGHT);
    }
    
    
    // Record buffer
    if (buffer)
    {
        float beats = 8.0f;
        if (size) beats = size->getValue();
        buffer->record(tick(beats * mf->getBeatLength()));
    }
}

//========================================================================
Type* BufferFunction::process (buf& buffer, sig& output, Clock& clock)
{
    buffer = this->buffer;
    output = NULL;
    
    
    if (typeClock != clock.clock)
    {
        typeClock = clock.clock;
        
        if (buffer)
        {
            inputs.clear();
            buffers.clear();
            
            Type* t = identifier->getType(RIGHT);
            
            while (true)
            {
                if (t == NULL || t == close)
                    break;
                
                sig s;
                buf b;
                
                t = t->process(b, s, clock);
                
                if (s && t != size)
                    inputs.push_back(s);
                if (b)
                    buffers.push_back(b);
            }
            
            buffer->process(inputs, buffers, output, clock);
        }
    }
    
    
    return close->getType(RIGHT);
}
