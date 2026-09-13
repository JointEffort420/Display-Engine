//
// Created by natha on 9/4/2026.
//

#ifndef GAMEOFLIFE_ITICKOBSERVER_H
#define GAMEOFLIFE_ITICKOBSERVER_H


class ITickObserver {
    public:
    ITickObserver() = default;
    virtual ~ITickObserver() = default;

    virtual void onTick() = 0;
};
#endif //GAMEOFLIFE_ITICKOBSERVER_H