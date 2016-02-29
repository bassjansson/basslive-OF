//
//  Types.h
//  BassLive 2.0
//
//  Created by Bass Jansson on 28/02/16.
//
//

#ifndef Types_h
#define Types_h

#include "Character.hpp"
#include "Type.hpp"
#include "Function.hpp"

#include "NumberType.hpp"
#include "InputType.hpp"
#include "ModuleType.hpp"
#include "BufferType.hpp"

#include "ModuleFunction.hpp"
#include "BufferFunction.hpp"
#include "MainFunction.hpp"

#define HORIZONTAL 0
#define VERTICAL   1

#define LEFT  0
#define RIGHT 1
#define UP    0
#define DOWN  1

#define FRAME_RATE 30
#define FONT_SIZE  15

#define CHAR_TYPE_NUMBER '$'
#define CHAR_TYPE_INPUT  '>'
#define CHAR_TYPE_MOD_ID ':'
#define CHAR_TYPE_BUF_ID '@'

#define CHAR_FUNC_MOD_OPEN  '('
#define CHAR_FUNC_MOD_CLOSE ')'
#define CHAR_FUNC_BUF_OPEN  '['
#define CHAR_FUNC_BUF_CLOSE ']'

#define COLOR_DEFAULT     ofColor(255)
#define COLOR_ERROR       ofColor(219, 44,  56 )
#define COLOR_SELECTION   ofColor(101, 101, 77 , 127)
#define COLOR_TYPE_NUMBER ofColor(120, 109, 196)
#define COLOR_TYPE_INPUT  ofColor(0  , 160, 190)
#define COLOR_TYPE_MOD_ID ofColor(131, 192, 87 )
#define COLOR_TYPE_BUF_ID ofColor(131, 192, 87 )
#define COLOR_FUNC_MODULE ofColor(0  , 160, 190)
#define COLOR_FUNC_BUFFER ofColor(178, 24 , 137)

#endif /* Types_h */
