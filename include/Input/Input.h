//
// Created by natha on 9/7/2026.
//

#ifndef DISPLAYENGINE_INPUT_H
#define DISPLAYENGINE_INPUT_H

#include <vector>
#include <SFML/Window/Event.hpp>

#include "Logic/IInputObserver.h"

class Input {
private:
    Input();

    static Input* CreateInstance();
    static Input *singletonInstance;

    bool clicked;

    std::vector<IInputObserver*> observers;

public:
    //Prevent any move or copies!
    Input (const Input& copy) = delete;
    Input& operator= (const Input& copy) = delete;
    Input (Input&& move) = delete;
    Input& operator= (Input&& move) = delete;

    static Input* GetInstance();
    static void DestroyInstance();
    void handleEvent(const sf::Event& event);

    // Observer Pattern Management
    void attach(IInputObserver* observer);
    void detach(IInputObserver* observer);
    void notifyLeftPressed(const std::pair<unsigned int, unsigned int>& coordinates);
    void notifyLeftReleased(const std::pair<unsigned int, unsigned int>& coordinates);
    void notifyMouseMoved(const std::pair<unsigned int, unsigned int>& coordinates);
};


#endif //DISPLAYENGINE_INPUT_H