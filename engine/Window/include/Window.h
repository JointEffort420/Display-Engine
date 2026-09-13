#ifndef WINDOW_H
#define WINDOW_H

#include <SFML/Graphics.hpp>
#include <string>
#include <utility>
#include <iostream>

#include "../../Utils/Input.h"
#include "../include/Camera.h"

class Window {
private:
    sf::RenderWindow window;

    unsigned int width; unsigned int height;
    std::string title;

public:
    Window() = delete;
    explicit Window(unsigned int width, unsigned int height, const std::string& title);
    ~Window();

    Window* get();
    std::pair<int,int> getDimensions();
    bool isOpen() const;

    void open();
    void close();

    void handleEvents(Input& input, Camera& camera);//Window polls out of necessity, input parses/analyses
    void clear();
    void display();

    //Print - draw - debug
    template <typename T>
    void draw(const T& drawable) {
        window.draw(drawable);
    }

};

#endif // WINDOW_H
