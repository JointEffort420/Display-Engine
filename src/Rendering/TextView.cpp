//
// Created by natha on 9/9/2026.
//

#include "Rendering/TextView.h"
#include "Logic/Model.h"

#include <algorithm>

namespace eng {
    //----------------------------------------------------------------------------------------------------------------------
    // Constructors & Destructor
    //----------------------------------------------------------------------------------------------------------------------
    TextView::TextView(ViewFactory::Key key, const Model& model, Window& window, Camera& camera,
                       const TextViewConfig& config)
        : View(key, model, window, camera),
        string(config.string),
        requestedCharacterSize(config.characterSize),
        fillColor(config.fillColor),
        edgeColor(config.edgeColor),
        edgeThickness(config.edgeThickness),
        fill(config.fill),
        edge(config.edge)
    {
        if (config.font) {
            text.emplace(*config.font, string, requestedCharacterSize);
            text->setFillColor(fillColor);
            if (edge) {
                text->setOutlineColor(edgeColor);
                text->setOutlineThickness(edgeThickness);
            }
        }

        calibrate();
    }

    //----------------------------------------------------------------------------------------------------------------------
    // Setters
    //----------------------------------------------------------------------------------------------------------------------

    void TextView::setFont(const sf::Font* font) {
        if (!font) {
            text.reset();          // explicitly going text-less
            return;
        }
        // Rebuild in place — sf::Text has no setFont taking a bare pointer in SFML 3
        // constructor-injected font model, so re-emplace with the new font + current state.
        text.emplace(*font, string, requestedCharacterSize);
        text->setFillColor(fillColor);
        if (edge) {
            text->setOutlineColor(edgeColor);
            text->setOutlineThickness(edgeThickness);
        }
    }

    void TextView::setString(const std::string& string) {
        this->string = string;
        text->setString(string);
    }

    void TextView::setCharacterSize(unsigned int size) {
        requestedCharacterSize = size;
        calibrate();
    }

    void TextView::setFill(bool fill) {
        this->fill = fill;
        if (text) text->setFillColor(fill? fillColor : sf::Color::Transparent);
    }

    void TextView::setEdge(bool edge) {
        this->edge = edge;
        if (text) text->setOutlineColor(edge? edgeColor : sf::Color::Transparent);
    }

    void TextView::setEdgeThickness(float et) {
        edgeThickness = et;
        if (text) text->setOutlineThickness(edgeThickness);
    }

    void TextView::setFillColor(const sf::Color& color) {
        fillColor = color;
        if (text) text->setFillColor(color);
    }

    void TextView::setEdgeColor(const sf::Color& color) {
        edgeColor = color;
        if (text) text->setOutlineColor(color);
    }

    void TextView::setColors(const sf::Color& fillColor, const sf::Color& edgeColor) {
        this->fillColor = fillColor;
        this->edgeColor = edgeColor;
        if (text) text->setFillColor(fillColor);
        if (text) text->setOutlineColor(edgeColor);
    }

    //----------------------------------------------------------------------------------------------------------------------
    // Getters
    //----------------------------------------------------------------------------------------------------------------------

    std::string TextView::getString() const {return string;}
    unsigned int TextView::getCharacterSize() const {return text->getCharacterSize();}
    unsigned int TextView::getRequestedCharacterSize() const {return requestedCharacterSize;}
    bool TextView::getFill() const {return fill;}
    bool TextView::getEdge() const {return edge;}
    float TextView::getEdgeThickness() const {return edgeThickness;}
    sf::Color TextView::getFillColor() const {return fillColor;}
    sf::Color TextView::getEdgeColor() const {return edgeColor;}

    //----------------------------------------------------------------------------------------------------------------------
    // Logic
    //----------------------------------------------------------------------------------------------------------------------

    void TextView::calibrate() {
        // 1. Guard against empty text
        if (text->getString().isEmpty()) {
            return;
        }

        // 2. Fetch world metrics safely
        const auto [x, y] = getCamera().worldToWindowPosition(getModel().getPosition());
        const auto [width, height] = getCamera().worldToWindowSize(getModel().getSize());

        // Guard against zero-sized bounds
        if (width <= 0.0f || height <= 0.0f) {
            return;
        }

        unsigned int characterSize = requestedCharacterSize;

        // 3. Binary search or safe decrement loop
        while (characterSize > 1) {
            text->setCharacterSize(characterSize);

            const sf::FloatRect bounds = text->getLocalBounds();

            if (bounds.size.x <= width && bounds.size.y <= height) {
                break;
            }

            --characterSize;
        }

        const sf::FloatRect bounds = text->getLocalBounds();

        // Guard against zero bounds before calculating origin
        if (bounds.size.x > 0.0f && bounds.size.y > 0.0f) {
            text->setOrigin(
                sf::Vector2f(
                    bounds.position.x + bounds.size.x / 2.0f,
                    bounds.position.y + bounds.size.y / 2.0f
                )
            );
        }

        text->setPosition(
            sf::Vector2f(
                x + width / 2.0f,
                y + height / 2.0f
            )
        );
    }

    //----------------------------------------------------------------------------------------------------------------------
    // View, Draw, Print & Debug
    //----------------------------------------------------------------------------------------------------------------------

    void TextView::draw() {
        if (!isVisible() or text->getString().isEmpty()) {
            return;
        }

        getWindow().draw(*text);
    }
}