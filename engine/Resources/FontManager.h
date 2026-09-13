//
// Created by natha on 9/9/2026.
//

#ifndef GAMEOFLIFE_FONTMANAGER_H
#define GAMEOFLIFE_FONTMANAGER_H

#include <SFML/Graphics/Font.hpp>
#include <string>
#include <unordered_map>
#include <iostream>

// Sole responsibility: own every sf::Font for the life of the program and
// hand out stable, non-owning pointers to them. Nothing else may construct
// or own an sf::Font that a View could end up pointing at.
class FontManager {
public:
    static const sf::Font* getDefaultFont() {
        return get("../lib/FreedomFont.ttf");
    }

    // Cache by path. unordered_map guarantees references/pointers to existing
    // elements stay valid across further inserts (only iterators are
    // invalidated), so handing out &it->second is safe forever after.
    static const sf::Font* get(const std::string& path) {
        auto& cache = getCache();

        if (auto it = cache.find(path); it != cache.end()) {
            return &it->second;
        }

        sf::Font font;
        if (!font.openFromFile(path)) {
            std::cerr << "FontManager: failed to load '" << path
                      << "', substituting the default font\n";
            if (path != "../lib/FreedomFont.ttf") {
                return getDefaultFont();
            }
            // Failing to load the default itself is a hard startup error —
            // deliberately not silently substituted further, so it's loud.
        }

        auto [inserted, _] = cache.emplace(path, std::move(font));
        return &inserted->second;
    }

private:
    static std::unordered_map<std::string, sf::Font>& getCache() {
        static std::unordered_map<std::string, sf::Font> cache;
        return cache;
    }
};

#endif //GAMEOFLIFE_FONTMANAGER_H