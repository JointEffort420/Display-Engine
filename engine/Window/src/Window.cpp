//
// Created by natha on 9/1/2026.
//

#include "../include/Window.h"

Window::Window(unsigned int width, unsigned int height, const std::string& title){
    window.create(sf::VideoMode({width, height}), title);
    this->width = width;
    this->height = height;
}

Window::~Window() = default;

//Getters
Window* Window::get() {
    return this;
}
std::pair<int,int> Window::getDimensions() {
    return std::make_pair(this->width,this->height);
}

bool Window::isOpen() const {
    return window.isOpen();
}

void Window::open() {
    if (!window.isOpen()) {
        window.create(
            sf::VideoMode({width, height}),
            title
        );
    }
}

void Window::close() {
    this->window.close();
}

// Window.cpp
void Window::handleEvents(Input& input, Camera& camera) {
    while (auto event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            close();
        }
        else if (auto* resized = event->getIf<sf::Event::Resized>()) {
            width  = resized->size.x;
            height = resized->size.y;

            // Keep SFML's own pixel mapping 1:1 with the new window size,
            // otherwise SFML stretches on top of whatever Camera does.
            window.setView(sf::View(sf::FloatRect({0.f, 0.f},
                {static_cast<float>(width), static_cast<float>(height)})));

            camera.setWindowDimensions({width, height});
        }

        input.handleEvent(*event);
    }
}

void Window::clear() {
    window.clear(sf::Color::Black);
}

void Window::display() {
    window.display();
}
