//
//  BufferType.cpp
//  BassLive 2.0
//
//  Created by Bass Jansson on 28/02/16.
//
//

#include "Syntax.h"


//========================================================================
BufferType::BufferType() : Type(CHAR_TYPE_BUF_ID)
{
    typeType = BUFFER;
}

//========================================================================
sig* BufferType::compile (Memory* memory, bool record)
{
    AudioBuffer* buffer = memory->getBuffer(getTypeString());
    
    if (buffer)
    {
        flash(COLOR_TYPE_BUF_ID);
        return buffer->getOutput();
    }
    else
    {
        flash(COLOR_ERROR);
        return NULL;
    }
}
