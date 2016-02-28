//
//  BufferType.cpp
//  BassLive 2.0
//
//  Created by Bass Jansson on 28/02/16.
//
//

#include "Types.h"


//========================================================================
BufferType::BufferType (MainFunction* mf)
: Type(CHAR_TYPE_BUF_ID, mf)
{
    typeType = BUFFER;
}

//========================================================================
void BufferType::trigger()
{
    funcPointer = mf->getBufferFunction(getTypeString());
    
    if (funcPointer) flash(ofColor(121, 182, 77));
}
