//
//  ModuleFunction.cpp
//  BassLive 2.0
//
//  Created by Bass Jansson on 28/02/16.
//
//

#include "Syntax.h"


//========================================================================
ModuleFunction::ModuleFunction() : Function(CHAR_FUNC_MOD_OPEN,
                                            CHAR_FUNC_MOD_CLOSE)
{
    typeType = MODULE;
    
    identifier = new ModuleType();
    identifier->charType = IDEN;
    add(identifier);
    
    module = NULL;
}

//========================================================================
void ModuleFunction::drawTypeAnimation()
{
    // Draw function beat flash
    if (module && module->getBeatTime() >= 0.0f)
    {
        ofSetColor(typeColor.r, typeColor.g, typeColor.b,
                   (1.0f - module->getBeatTime()) * 191);
        
        ofDrawRectRounded(xAnim + charWidth, yAnim,
                          identifier->xAnim - xAnim - charWidth,
                          identifier->yAnim - yAnim + charHeight,
                          charWidth * 0.25f);
    }
    
    
    // Draw function line
//    sample RMS = 0.0f;
//    if (module) RMS = module->getRMS();
//    if (RMS.L > 1.0f) RMS.L = 1.0f;
//    if (RMS.R > 1.0f) RMS.R = 1.0f;
//    
//    float alpha  = powf(1.0f - (RMS.L + RMS.R), 2.0f);
//    float width  = identifier->end()->x - x + 1.5f * charWidth;
//    float height = end()->y - y;
    
    ofSetColor(typeColor.r, typeColor.g, typeColor.b, 150); //alpha * 255);
    //ofSetLineWidth(2.0f);
    ofDrawLine(xAnim + 0.5f * charWidth,        yAnim + charHeight,
               xAnim + 0.5f * charWidth, end()->yAnim + charHeight);
    //ofDrawRectangle(x + 0.5f * charWidth, y + charHeight,
    //                width * (RMS.L + RMS.R) + 1.0f, height);
}

//========================================================================
sig* ModuleFunction::compile (Memory* memory, bool record)
{
    // Fill strings if empty
    if (typeString == "")
    {
        add(new Character('*'));
        typeString = "*";
    }
    
    if (identifier->typeString == "")
    {
        string str = "m" + ofToString(memory->getNewModuleID());
        
        charSelected = identifier;
        
        for (int i = 0; i < strlen(str.c_str()); i++)
            charSelected->add(new Character(str.c_str()[i]));
        
        identifier->typeString = str;
    }
    
    
    // Get or add module
    module = memory->getModule(identifier->typeString);
    
    if (module == NULL)
        module = memory->addModule(typeString, identifier->typeString);
    
    
    // Set inputs of module
    if (module)
    {
        sig_vec inputs;
        
        for (Character* c = identifier->getType(RIGHT);
             c != end();
             c = c->end()->right)
        {
            Type* t = (Type*)c;
            
            inputs.push_back(t->compile(memory, record));
        }
        
        module->setInputs(inputs);
        inputs.clear();
        
        flash(COLOR_FUNC_MODULE);
        return identifier->compile(memory, record);
    }
    else
    {
        flash(COLOR_ERROR);
        return NULL;
    }
}
