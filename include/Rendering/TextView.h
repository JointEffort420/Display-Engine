//
// Created by natha on 9/9/2026.
//

#ifndef DISPLAYENGINE_TEXTVIEW_H
#define DISPLAYENGINE_TEXTVIEW_H

#include <SFML/Graphics.hpp>
#include <string>

#include "View.h"

namespace eng {
    class TextView : public View {
    private:
        std::optional<sf::Text> text;

        //Text is optional
        //Therefore a shadowstate is necessary keeping the text's data
        std::string string;
        bool fill;
        bool edge;
        float edgeThickness;
        sf::Color fillColor;
        sf::Color edgeColor;
        unsigned int requestedCharacterSize;

    public:
        //----------------------------------------------------------------------------------------------------------------------
        //Constructors & Destructor
        //----------------------------------------------------------------------------------------------------------------------
        TextView() = delete;
        TextView(ViewFactory::Key key, const Model& model, Window& window, Camera& camera, const TextViewConfig& config);

        //----------------------------------------------------------------------------------------------------------------------
        //Setters
        //----------------------------------------------------------------------------------------------------------------------
        void setFont(const sf::Font* font);
        void setString(const std::string& string);
        void setCharacterSize(unsigned int size);
        void setFill(bool fill);
        void setEdge(bool edge);
        void setEdgeThickness(float edgeThickness);
        void setFillColor(const sf::Color& color);
        void setEdgeColor(const sf::Color& color);
        void setColors(const sf::Color& fillColor, const sf::Color& edgeColor);

        //----------------------------------------------------------------------------------------------------------------------
        //Getters
        //----------------------------------------------------------------------------------------------------------------------
        [[nodiscard]] std::string getString() const;
        [[nodiscard]] unsigned int getCharacterSize() const;
        [[nodiscard]] unsigned int getRequestedCharacterSize() const;
        [[nodiscard]] bool getFill() const;
        [[nodiscard]] bool getEdge() const;
        [[nodiscard]] float getEdgeThickness() const;
        [[nodiscard]] sf::Color getFillColor() const;
        [[nodiscard]] sf::Color getEdgeColor() const;

        //----------------------------------------------------------------------------------------------------------------------
        //Logic
        //----------------------------------------------------------------------------------------------------------------------
        void calibrate();

        //----------------------------------------------------------------------------------------------------------------------
        //View, Draw, Print & Debug
        //----------------------------------------------------------------------------------------------------------------------
        void draw() override;
    };
}

#endif //DISPLAYENGINE_TEXTVIEW_H