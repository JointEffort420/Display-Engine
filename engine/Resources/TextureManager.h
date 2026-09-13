//
// Created by natha on 9/12/2026.
//

#ifndef GAMEOFLIFE_TEXTUREMANAGER_H
#define GAMEOFLIFE_TEXTUREMANAGER_H

#include <SFML/Graphics/Texture.hpp>
#include <string>
#include <unordered_map>
#include <iostream>

// Same contract as FontManager, for sf::Texture.
class TextureManager {
public:
    static const sf::Texture* getDefaultTexture() {
        return get("../lib/DefaultTexture.jpeg");
    }

    static const sf::Texture* get(const std::string& path) {
        auto& cache = getCache();

        if (auto it = cache.find(path); it != cache.end()) {
            return &it->second;
        }

        sf::Texture texture;
        if (!texture.loadFromFile(path)) {
            std::cerr << "TextureManager: failed to load '" << path
                      << "', substituting the default texture\n";
            if (path != "../lib/DefaultTexture.jpeg") {
                return getDefaultTexture();
            }
        }

        auto [inserted, _] = cache.emplace(path, std::move(texture));
        return &inserted->second;
    }

private:
    static std::unordered_map<std::string, sf::Texture>& getCache() {
        static std::unordered_map<std::string, sf::Texture> cache;
        return cache;
    }
};

#endif //GAMEOFLIFE_TEXTUREMANAGER_H