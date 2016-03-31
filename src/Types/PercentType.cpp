//
//  PercentType.cpp
//  BassLive 2.0
//
//  Created by Bass Jansson on 31/03/16.
//
//

#include "Syntax.h"


//========================================================================
PercentType::PercentType() : Type(CHAR_TYPE_PERCENT), value(1.0f)
{
    typeType = PERCENT;
    
    percent = new Character('1');
    typeString = '1';
    add(percent);
    
    flash(COLOR_TYPE_PERCENT);
}

//========================================================================
void PercentType::keyPressed (int key)
{
    if (key != OF_KEY_BACKSPACE)
    {
        // Make sure there is only one character
        Character* c = end();
        
        if (c != percent)
        {
            while (c != begin)
            {
                c = c->left;
                c->right->remove();
            }
            
            value[0] = 1.0f;
            
            percent = new Character('1');
            typeString = '1';
            add(percent);
            
            flash(COLOR_TYPE_PERCENT);
        }
    
    
        // Set value by key
        if (key > 47 && key < 58)
        {
            value[0] = key - 48;
            
            percent->charString = key;
            typeString = key;
            
            flash(COLOR_TYPE_PERCENT);
        }
        else if ((key > 64 && key < 91) ||
                 (key > 96 && key < 123))
        {
            switch (key)
            {
                default: value[0] = 0.0f; break;
                    
                case 'a': value[0] = powf(2.0f, -12.0f / 12.0f); break;
                case 'w': value[0] = powf(2.0f, -11.0f / 12.0f); break;
                case 's': value[0] = powf(2.0f, -10.0f / 12.0f); break;
                case 'e': value[0] = powf(2.0f,  -9.0f / 12.0f); break;
                case 'd': value[0] = powf(2.0f,  -8.0f / 12.0f); break;
                case 'f': value[0] = powf(2.0f,  -7.0f / 12.0f); break;
                case 't': value[0] = powf(2.0f,  -6.0f / 12.0f); break;
                case 'g': value[0] = powf(2.0f,  -5.0f / 12.0f); break;
                case 'y': value[0] = powf(2.0f,  -4.0f / 12.0f); break;
                case 'h': value[0] = powf(2.0f,  -3.0f / 12.0f); break;
                case 'u': value[0] = powf(2.0f,  -2.0f / 12.0f); break;
                case 'j': value[0] = powf(2.0f,  -1.0f / 12.0f); break;
                case 'k': value[0] = powf(2.0f,  -0.0f / 12.0f); break;
                    
                case 'A': value[0] = powf(2.0f,   0.0f / 12.0f); break;
                case 'W': value[0] = powf(2.0f,   1.0f / 12.0f); break;
                case 'S': value[0] = powf(2.0f,   2.0f / 12.0f); break;
                case 'E': value[0] = powf(2.0f,   3.0f / 12.0f); break;
                case 'D': value[0] = powf(2.0f,   4.0f / 12.0f); break;
                case 'F': value[0] = powf(2.0f,   5.0f / 12.0f); break;
                case 'T': value[0] = powf(2.0f,   6.0f / 12.0f); break;
                case 'G': value[0] = powf(2.0f,   7.0f / 12.0f); break;
                case 'Y': value[0] = powf(2.0f,   8.0f / 12.0f); break;
                case 'H': value[0] = powf(2.0f,   9.0f / 12.0f); break;
                case 'U': value[0] = powf(2.0f,  10.0f / 12.0f); break;
                case 'J': value[0] = powf(2.0f,  11.0f / 12.0f); break;
                case 'K': value[0] = powf(2.0f,  12.0f / 12.0f); break;
                    
                case 'z': value[0] = powf(2.0f, -6.0f); break;
                case 'x': value[0] = powf(2.0f, -5.0f); break;
                case 'c': value[0] = powf(2.0f, -4.0f); break;
                case 'v': value[0] = powf(2.0f, -3.0f); break;
                case 'b': value[0] = powf(2.0f, -2.0f); break;
                case 'n': value[0] = powf(2.0f, -1.0f); break;
                case 'm': value[0] = powf(2.0f, -0.0f); break;
                    
                case 'Z': value[0] = powf(2.0f, 0.0f); break;
                case 'X': value[0] = powf(2.0f, 1.0f); break;
                case 'C': value[0] = powf(2.0f, 2.0f); break;
                case 'V': value[0] = powf(2.0f, 3.0f); break;
                case 'B': value[0] = powf(2.0f, 4.0f); break;
                case 'N': value[0] = powf(2.0f, 5.0f); break;
                case 'M': value[0] = powf(2.0f, 6.0f); break;
            }
            
            if (value[0].L > 0.0f)
            {
                percent->charString = key;
                typeString = key;
            }
            else
            {
                value[0] = 1.0f;
                
                percent->charString = '1';
                typeString = '1';
            }
            
            flash(COLOR_TYPE_PERCENT);
        }
    }
}

sig* PercentType::compile (Memory* memory, bool record)
{
    Character* c = end();
    
    if (c != percent)
    {
        while (c != begin)
        {
            c = c->left;
            c->right->remove();
        }
        
        value[0] = 1.0f;
        
        percent = new Character('1');
        typeString = '1';
        add(percent);
    }
    
    flash(COLOR_TYPE_PERCENT);
    
    return &value;
}

//========================================================================
float PercentType::getValue()
{
    return value[0].L;
}
