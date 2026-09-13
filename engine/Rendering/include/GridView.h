
//
// Created by natha on 9/3/2026.
//

#ifndef GAMEOFLIFE_GRIDVIEW_H
#define GAMEOFLIFE_GRIDVIEW_H

#include <SFML/Graphics.hpp>

#include "Camera.h"
#include "Window.h"
#include "View.h"

class VirtualGridModel;

// This view will read the Grid model and draw it via the window. Never mutates the model!
class  GridView : public View {
private:
    const VirtualGridModel& grid;
    float lineWidth;
    sf::Color aliveColor = sf::Color::Red;
    sf::Color deadColor = sf::Color::Black;
    sf::Color gridLineColor = sf::Color::Red;

public:
    //----------------------------------------------------------------------------------------------------------------------
    //Constructors & Destructor
    //----------------------------------------------------------------------------------------------------------------------
    GridView() = delete;
    GridView(Factory::Key key, const VirtualGridModel& grid, Window& window, Camera& camera, const GridViewConfig& config);

    //----------------------------------------------------------------------------------------------------------------------
    //Setters
    //----------------------------------------------------------------------------------------------------------------------
    void setColors(const sf::Color& aliveColor, const sf::Color& deadColor, const sf::Color& gridLineColor);

    //----------------------------------------------------------------------------------------------------------------------
    //Getters
    //----------------------------------------------------------------------------------------------------------------------

    //----------------------------------------------------------------------------------------------------------------------
    //Subscribtions
    //----------------------------------------------------------------------------------------------------------------------

    //----------------------------------------------------------------------------------------------------------------------
    //View, Draw, Print & Debug
    //----------------------------------------------------------------------------------------------------------------------
    void draw() override;
};

#endif //GAMEOFLIFE_GRIDVIEW_H