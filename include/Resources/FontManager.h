//
// Created by natha on 9/9/2026.
//

#ifndef DISPLAYENGINE_FONTMANAGER_H
#define DISPLAYENGINE_FONTMANAGER_H

#include <SFML/Graphics/Font.hpp>
#include <string>
#include <unordered_map>
#include <iostream>

#include "Font.h"

namespace eng {
    class FontManager {
    public:
        explicit FontManager(std::filesystem::path engineAssetDirectory);

        const sf::Font& resolve(const Font& font);

    private:
        const sf::Font& load(
            const std::filesystem::path& path
        );

        const sf::Font& getDefaultFont();

        std::filesystem::path m_engineAssetDirectory;

        std::unordered_map<
            std::filesystem::path,
            sf::Font
        > m_fonts;
    };
}

#endif //DISPLAYENGINE_FONTMANAGER_H