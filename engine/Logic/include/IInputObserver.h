//
// Created by natha on 9/4/2026.
//

#ifndef GAMEOFLIFE_IINPUTOBSERVER_H
#define GAMEOFLIFE_IINPUTOBSERVER_H

#include <utility>

class IInputObserver {
private:

public:
    IInputObserver() = default;
    virtual ~IInputObserver() = default;

    virtual void onLeftPressed(const std::pair<unsigned int, unsigned int>& windowCoordinates) = 0;
    virtual void onLeftReleased(const std::pair<unsigned int, unsigned int>& windowCoordinates) =0;
    virtual void onMouseMoved(const std::pair<unsigned int, unsigned int>& windowCoordinates) = 0;
};

#endif //GAMEOFLIFE_IINPUTOBSERVER_H