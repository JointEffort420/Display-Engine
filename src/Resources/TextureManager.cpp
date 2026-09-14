//
// Created by natha on 9/12/2026.
//

#include "Resources/TextureManager.h"

const sf::Texture* TextureManager::getDefaultTexture() {
    return get("../assets/default_texture.jpeg");
}

const sf::Texture* TextureManager::get(const std::string& path) {
    auto& cache = getCache();

    if (auto it = cache.find(path); it != cache.end()) {
        return &it->second;
    }

    sf::Texture texture;
    if (!texture.loadFromFile(path)) {
        std::cerr << "TextureManager: failed to load '" << path
                  << "', substituting the default texture\n";
        if (path != "../assets/default_texture.jpeg") {
            return getDefaultTexture();
        }
    }

    auto [inserted, _] = cache.emplace(path, std::move(texture));
    return &inserted->second;
}

std::unordered_map<std::string, sf::Texture>& TextureManager::getCache() {
    static std::unordered_map<std::string, sf::Texture> cache;
    return cache;
}
