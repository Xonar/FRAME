/*
 * File :
 *      ./Global.h
 *
 * Author : 
 *      Xonar <Paul le Roux>
 *
 * Description :
 *      Contains all global variables
 */

#ifndef _F_H_GLOBAL_
#define _F_H_GLOBAL_

#include "Window/Window.h"
#include "Engine/FontEngine.h"
#include "Engine/ModelEngine.h"
#include "Engine/RenderEngine.h"
#include "Graphics/Graphics.h"
#include "Camera/Camera.h"
#include "Keyboard/Keyboard.h"
#include "Mouse/Mouse.h"
#include "Engine/LightEngine.h"

//FRAME
extern bool gGameOn;
extern bool gDisplayFrameStats;

extern FWindow *gWindow;

//Engines
extern FFontEngine *gFontEngine;
extern FModelEngine *gModelEngine;
extern FRenderEngine *gRenderEngine;
extern FLightEngine *gLightEngine;

//Console Font
extern FFont *gFontConsole;

//Player Camera
extern FCamera *gCamera;

//IO
extern FKeyboard *gKeyboard;
extern FMouse *gMouse;

//TERMINAL COLOUR CODES
#ifdef COLOUR_TERMINAL
  //ESC
#define TERM_ESC "\33"
  //States
#define TERM_STATE_PARSE(state) TERM_ESC "[" state "m"
#define TERM_STATE_BOLD TERM_STATE_PARSE("1")
#define TERM_STATE_NORMAL TERM_STATE_PARSE("22")
#define TERM_STATE_RESET TERM_STATE_PARSE("0")
  //Col
#define TERM_COL_PARSE(col) TERM_ESC "[" col "m"
#define TERM_COL_BLACK TERM_COL_PARSE("30")
#define TERM_COL_RED TERM_COL_PARSE("31")
#define TERM_COL_GREEN TERM_COL_PARSE("32")
#define TERM_COL_YELLOW TERM_COL_PARSE("33")
#define TERM_COL_BLUE TERM_COL_PARSE("34")
#define TERM_COL_MAGENTA TERM_COL_PARSE("35")
#define TERM_COL_CYAN TERM_COL_PARSE("36")
#define TERM_COL_WHITE TERM_COL_PARSE("37")
#define TERM_COL_DEFAULT TERM_COL_PARSE("39")
//Reset
#else
  //Define al MACRO to ""
#define TERM_ESC ""
#define TERM_STATE_PARSE(state) ""
#define TERM_STATE_BOLD ""
#define TERM_STATE_NORMAL ""
#define TERM_STATE_RESET ""
#define TERM_COL_PARSE(col) ""
#define TERM_COL_BLACK ""
#define TERM_COL_RED ""
#define TERM_COL_GREEN ""
#define TERM_COL_YELLOW ""
#define TERM_COL_BLUE ""
#define TERM_COL_MAGENTA ""
#define TERM_COL_CYAN ""
#define TERM_COL_WHITE  ""
#define TERM_COL_DEFAULT ""

#endif //COLOUR_TERMINAL

#endif // _F_H_GLOBAL_
