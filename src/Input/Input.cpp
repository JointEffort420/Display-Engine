//
// Created by natha on 9/7/2026.
//

#include "Input/Input.h"

#include <algorithm>
#include <iostream>
#include <ostream>

namespace eng {
    Input* Input::singletonInstance = nullptr; //The global variable tick

    Input::Input() = default;

    Input* Input::CreateInstance() {
        if (!singletonInstance)
            singletonInstance = new Input();
        return singletonInstance;
    }


    Input* Input::GetInstance() {
        if (!singletonInstance) {
            CreateInstance();
        }
        return singletonInstance;
    }

    void Input::DestroyInstance() {
        delete singletonInstance;
        singletonInstance = nullptr;
    }

    void Input::handleEvent(const sf::Event& event) {

        if (event.is<sf::Event::MouseButtonPressed>()) {
            const auto* mouse =
                event.getIf<sf::Event::MouseButtonPressed>();

            if (!mouse) return;

            if (mouse->button == sf::Mouse::Button::Left) {
                const auto coordinates =
                    std::make_pair(
                        static_cast<unsigned int>(mouse->position.x),
                        static_cast<unsigned int>(mouse->position.y)
                    );

                notifyLeftPressed(coordinates);
            }
        }

        else if (event.is<sf::Event::MouseButtonReleased>()) {
            const auto* mouse =
                event.getIf<sf::Event::MouseButtonReleased>();

            if (!mouse) return;

            if (mouse->button == sf::Mouse::Button::Left) {
                const auto coordinates =
                    std::make_pair(
                        static_cast<unsigned int>(mouse->position.x),
                        static_cast<unsigned int>(mouse->position.y)
                    );

                notifyLeftReleased(coordinates);
            }
        }

        else if (event.is<sf::Event::MouseMoved>()) {
            const auto* mouse =
                event.getIf<sf::Event::MouseMoved>();

            if (!mouse) return;

            const auto coordinates =
                std::make_pair(
                    static_cast<unsigned int>(mouse->position.x),
                    static_cast<unsigned int>(mouse->position.y)
                );

            notifyMouseMoved(coordinates);
        }

        else if (event.is<sf::Event::Resized>()) {
            notifyResize();
        }
    }

    // Observer Pattern Management
    void Input::attach(IInputObserver* observer) {
        if (observer) {
            observers.push_back(observer);
        }
    }

    void Input::detach(IInputObserver* observer) {
        observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
    }

    void Input::notifyLeftPressed(const std::pair<unsigned int, unsigned int>& coordinates) {
        for (IInputObserver* observer : observers) {
            if (observer)
                observer->onLeftPressed(coordinates);
        }
    }

    void Input::notifyLeftReleased(const std::pair<unsigned int, unsigned int>& coordinates) {
        for (IInputObserver* observer : observers) {
            if (observer)
                observer->onLeftReleased(coordinates);
        }
    }

    void Input::notifyMouseMoved(const std::pair<unsigned int, unsigned int>& coordinates) {
        for (IInputObserver* observer : observers) {
            if (observer)
                observer->onMouseMoved(coordinates);
        }
    }

    void Input::notifyResize() {
        for (IInputObserver* observer : observers) {
            if (observer)
                observer->onResize();
        }
    }
}
