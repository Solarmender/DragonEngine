#ifndef DRAGONENGINE_INPUTSYSTEM_H
#define DRAGONENGINE_INPUTSYSTEM_H

#include <array>

class InputSystem {
public:
    bool isPressed(unsigned char keyCode);

    void keyPressed(unsigned char input);
    void keyReleased(unsigned char input);
private:
    std::array<bool, 256> keyStates{ false };
};


#endif //DRAGONENGINE_INPUTSYSTEM_H
