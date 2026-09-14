//
// Created by natha on 9/12/2026.
//

#ifndef DISPLAYENGINE_TEXTUREMANAGER_H
#define DISPLAYENGINE_TEXTUREMANAGER_H

#include <SFML/Graphics/Texture.hpp>
#include <string>
#include <unordered_map>
#include <iostream>

// Same contract as FontManager, for sf::Texture.
class TextureManager {
private:
    static std::unordered_map<std::string, sf::Texture>& getCache();

public:
    static const sf::Texture* getDefaultTexture();
    static const sf::Texture* get(const std::string& path);
};

#endif //DISPLAYENGINE_TEXTUREMANAGER_H