//
// Created by natha on 9/9/2026.
//

#include "Resources/FontManager.h"

const sf::Font* FontManager::getDefaultFont() {
    return get("../assets/default_font.ttf");
}

const sf::Font* FontManager::get(const std::string& path) {
    auto& cache = getCache();

    if (auto it = cache.find(path); it != cache.end()) {
        return &it->second;
    }

    sf::Font font;
    if (!font.openFromFile(path)) {
        std::cerr << "FontManager: failed to load '" << path
                  << "', substituting the default font\n";
        if (path != "../assets/default_font.ttf") {
            return getDefaultFont();
        }
        // Failing to load the default itself is a hard startup error —
        // deliberately not silently substituted further, so it's loud.
    }

    auto [inserted, _] = cache.emplace(path, std::move(font));
    return &inserted->second;
}

std::unordered_map<std::string, sf::Font>& FontManager::getCache() {
    static std::unordered_map<std::string, sf::Font> cache;
    return cache;
}
