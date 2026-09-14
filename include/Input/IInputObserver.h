//
// Created by natha on 9/4/2026.
//

#ifndef DISPLAYENGINE_IINPUTOBSERVER_H
#define DISPLAYENGINE_IINPUTOBSERVER_H

#include <utility>

class IInputObserver {
private:

public:
    IInputObserver() = default;
    virtual ~IInputObserver() = default;

    virtual bool onLeftPressed(const std::pair<unsigned int, unsigned int>& windowCoordinates) = 0;
    virtual bool onLeftReleased(const std::pair<unsigned int, unsigned int>& windowCoordinates) =0;
    virtual bool onMouseMoved(const std::pair<unsigned int, unsigned int>& windowCoordinates) = 0;
    virtual void onResize() = 0;
};

#endif //DISPLAYENGINE_IINPUTOBSERVER_H