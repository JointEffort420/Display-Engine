
//
// Created by natha on 9/3/2026.
//

#ifndef DISPLAYENGINE_GRIDVIEW_H
#define DISPLAYENGINE_GRIDVIEW_H

#include <SFML/Graphics.hpp>

#include "View.h"

class GridModel;

// This view will read the Grid model and draw it via the window. Never mutates the model!
class  GridView : public View {
private:
    const GridModel& grid;
    float lineWidth;
    sf::Color aliveColor = sf::Color::Red;
    sf::Color deadColor = sf::Color::Black;
    sf::Color gridLineColor = sf::Color::Red;

public:
    //----------------------------------------------------------------------------------------------------------------------
    //Constructors & Destructor
    //----------------------------------------------------------------------------------------------------------------------
    GridView() = delete;
    GridView(ViewFactory::Key key, const GridModel& grid, Window& window, Camera& camera, const GridViewConfig& config);

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

#endif //DISPLAYENGINE_GRIDVIEW_H