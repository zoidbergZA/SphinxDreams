#include "Input.hpp"

Input::Input()
{
    //ctor
}

Input::~Input()
{
    //dtor
}

bool Input::getKeyDown(int pKeycode)
{
    return _keyDown[pKeycode];
}

bool Input::getKey(int pKeycode)
{
    return sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(pKeycode));
}

//initialize static members
bool Input::_keyDown[] = {false};
