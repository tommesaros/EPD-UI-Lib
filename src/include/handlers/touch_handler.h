#ifndef TOUCH_HANDLER_H
#define TOUCH_HANDLER_H

#include <touch.h>

TouchClass TouchSetup();
void AddTouchPoint(int x, int y, int width, int height, void (*function)());

#endif // TOUCH_HANDLER_H
