//
// Created by natha on 9/4/2026.
//

#ifndef DISPLAYENGINE_ITICKOBSERVER_H
#define DISPLAYENGINE_ITICKOBSERVER_H

class ITickObserver {
public:
    ITickObserver() = default;
    virtual ~ITickObserver() = default;

    virtual void onTick() = 0;
};

#endif //DISPLAYENGINE_ITICKOBSERVER_H