#include "InputSystem.h"
#include "../logger/Logger.h"

bool InputSystem::isPressed(unsigned char keyCode)
{
    return keyStates[keyCode];
}

void InputSystem::keyPressed(unsigned char input)
{
    keyStates[input] = true;
}

void InputSystem::keyReleased(unsigned char input)
{
    keyStates[input] = false;
}
