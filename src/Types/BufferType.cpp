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
    if (getTypeString() == "")
    {
        int id = mf->getNewBufferID();
        
        mf->charSelected = this;
        new Character('b', mf);
        new Character('u', mf);
        new Character('f', mf);
        new Character((id / 10) % 10 + 48, mf);
        new Character((id / 1 ) % 10 + 48, mf);
    }
    
    if (updateFunctionPointer())
        flash(COLOR_TYPE_BUF_ID);
}
