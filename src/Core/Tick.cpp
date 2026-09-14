//
// Created by natha on 9/1/2026.
//

#include "Core/Tick.h"

Tick* Tick::singletonInstance = nullptr; //The global variable tick

Tick::Tick() = default;

Tick* Tick::CreateInstance() {
    if (!singletonInstance)
        singletonInstance = new Tick();
    return singletonInstance;
}


Tick* Tick::GetInstance() {
    if (!singletonInstance) {
        CreateInstance();
    }
    return singletonInstance;
}

void Tick::DestroyInstance() {
    delete singletonInstance;
    singletonInstance = nullptr;
}


//Functionality
void Tick::start() {
    startTime = ClockType::now();
    lastUpdateTime = startTime;
    reset();
}

void Tick::update() {
    auto now = ClockType::now();

    // deltaTime in seconds (double)
    deltaTime += std::chrono::duration<double>(now - lastUpdateTime).count();
    elapsedTime = std::chrono::duration<double>(now - startTime).count();
    lastUpdateTime = now;

    if (deltaTime > deltaThreshold) {
        incr();
        deltaTime -= deltaThreshold;
    }
}

void Tick::reset() {
    tick = 0;
}

void Tick::incr() {
    tick++;
    notifyObservers();
}

// Getters
double Tick::getDelta() const { return deltaTime; }
double Tick::getElapsed() const { return elapsedTime; }
unsigned int Tick::getTick() const { return tick; }

// Observer Pattern Management
void Tick::attach(ITickObserver* observer) {
    if (observer) {
        observers.push_back(observer);
    }
}

void Tick::detach(ITickObserver* observer) {
    observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
}
void Tick::notifyObservers() {
    for (ITickObserver* observer : observers) {
        observer->onTick();
    }
}