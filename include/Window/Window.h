#ifndef DISPLAYENGINE_WINDOW_H
#define DISPLAYENGINE_WINDOW_H

#include <SFML/Graphics.hpp>
#include <string>
#include <utility>
#include <iostream>

#include "Input/Input.h"
#include "Window/Camera.h"

class Window {
private:
    sf::RenderWindow window;
    sf::View pixelView;

    std::string title;

    void updatePixelView();
public:
    Window() = delete;
    explicit Window(unsigned int width, unsigned int height, const std::string& title);
    ~Window();

    Window* get();
    std::pair<int,int> getDimensions();
    bool isOpen() const;

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

#endif // DISPLAYENGINE_WINDOW_H
