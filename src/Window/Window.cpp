//
// Created by natha on 9/1/2026.
//

#include "Window/Window.h"

Window::Window(unsigned int width, unsigned int height, const std::string& title){
    window.create(sf::VideoMode({width, height}), title);
    updatePixelView();
}

Window::~Window() = default;

//Getters
Window* Window::get() {
    return this;
}
std::pair<int,int> Window::getDimensions() {
    return std::make_pair(window.getSize().x,window.getSize().y);
}

bool Window::isOpen() const {
    return window.isOpen();
}

void Window::close() {
    this->window.close();
}

void Window::handleEvents(Input& input, Camera& camera) {
    while (auto event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            close();
        }
        else if (auto* resized = event->getIf<sf::Event::Resized>()) {
            updatePixelView();
            camera.setWindowDimensions({resized->size.x, resized->size.y});   //recalculates uniformScale/offset
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

void Window::updatePixelView()
{
    pixelView.setSize({
        static_cast<float>(window.getSize().x),
        static_cast<float>(window.getSize().y)
    });

    pixelView.setCenter({
        static_cast<float>(window.getSize().x) / 2.0f,
        static_cast<float>(window.getSize().y) / 2.0f
    });

    window.setView(pixelView);
}