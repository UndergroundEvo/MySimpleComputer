#ifndef RENDER_H
#define RENDER_H

#include "include.h"
#include "myBigChars.h"
#include "myReadkey.h"
#include "mySimpleComputer.h"
#include "myTerm.h"

extern short currMemCell;
extern enum keys key;

int setCurrMemPointer_to_ICounter();
int rk_pause (int time);
int print_norm (char *str, enum colors color);
int ui_initial ();
int ui_update ();
int ui_moveCurrMemPointer (enum keys key);
int ui_setMCellValue ();
int ui_saveMemory ();
int ui_loadMemory ();
int ui_setICounter ();
int ui_setAccumulator ();
int drawingBoxes ();
int drawingTexts ();
int drawingMemory ();
int drawingAccumulator ();
int drawingOperation ();
int drawingInstructionCounter ();
int drawingFlags ();
int drawingBigChar ();
int checkCorrectInput (const char buffer[10]);
int ui_messageOutput (char *str, enum colors color);
int clearBuffIn ();
void signalHandler (int signal);

#endif