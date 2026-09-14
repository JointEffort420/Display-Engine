//
// Created by natha on 9/9/2026.
//

#ifndef DISPLAYENGINE_FONTMANAGER_H
#define DISPLAYENGINE_FONTMANAGER_H

#include <SFML/Graphics/Font.hpp>
#include <string>
#include <unordered_map>
#include <iostream>

// Sole responsibility: own every sf::Font for the life of the program and
// hand out stable, non-owning pointers to them. Nothing else may construct
// or own an sf::Font that a View could end up pointing at.

class FontManager {
private:
    static std::unordered_map<std::string, sf::Font>& getCache();

public:
    static const sf::Font* getDefaultFont();
    static const sf::Font* get(const std::string& path);
};

#endif //DISPLAYENGINE_FONTMANAGER_H