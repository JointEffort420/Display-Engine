#ifndef DISPLAYENGINE_TICK_H
#define DISPLAYENGINE_TICK_H

#include <chrono>
#include <vector>
#include <iostream>
#include <ostream>
#include <algorithm>

#include "Logic/ITickObserver.h"

class Tick {
private:
    Tick();

    static Tick* CreateInstance();
    static Tick *singletonInstance;

    using ClockType = std::chrono::steady_clock;
    ClockType::time_point startTime;
    ClockType::time_point lastUpdateTime;
    double deltaTime = 0; //in seconds
    double deltaThreshold = 0.20;//in seconds
    double elapsedTime = 0.0;//in seconds
    unsigned int tick = 0;

    std::vector<ITickObserver*> observers;

public:
    //Prevent any move or copies!
    Tick (const Tick& copy) = delete;
    Tick& operator= (const Tick& copy) = delete;
    Tick (Tick&& move) = delete;
    Tick& operator= (Tick&& move) = delete;

    static Tick* GetInstance();
    static void DestroyInstance();

    //Functionality
    void start();
    void update();
    void reset();
    void incr();

    //Getters
    [[nodiscard]] unsigned int getTick() const;
    [[nodiscard]] double getElapsed() const; // in seconds
    [[nodiscard]] double getDelta() const; //in seconds

    // Observer Pattern Management
    void attach(ITickObserver* observer);
    void detach(ITickObserver* observer);
    void notifyObservers();
};

#endif //DISPLAYENGINE_TICK_H