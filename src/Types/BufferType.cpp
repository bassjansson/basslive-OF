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
        int  id  = mf->getNewBufferID();
        char id1 = (id / 10) % 10 + 48;
        char id2 = (id / 1 ) % 10 + 48;
        
        mf->charSelected = this;
        new Character('b', mf);
        new Character('u', mf);
        new Character('f', mf);
        new Character(id1, mf);
        new Character(id2, mf);
        
        string str = "buf";
        str += id1;
        str += id2;
        setTypeString(str);
    }
    
    if (updateFunctionPointer())
        flash(COLOR_TYPE_BUF_ID);
}
