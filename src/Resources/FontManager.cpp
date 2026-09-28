//
// Created by natha on 28/9/2026.
//

#include "Resources/FontManager.h"

#include <stdexcept>
#include <utility>

namespace eng {

    FontManager::FontManager(
        std::filesystem::path engineAssetDirectory
    )
        : m_engineAssetDirectory(std::move(engineAssetDirectory)) {
    }

    const sf::Font& FontManager::resolve(const Font& font) {
        switch (font.m_type) {
            case Font::Type::Default:
                return getDefaultFont();

            case Font::Type::File:
                return load(font.m_path);
        }

        throw std::runtime_error("FontManager: invalid Font value");
    }

    const sf::Font& FontManager::getDefaultFont() {
        const auto path =
            m_engineAssetDirectory / "default_font.otf";

        return load(path);
    }

    const sf::Font& FontManager::load(
        const std::filesystem::path& path
    ) {
        if (auto it = m_fonts.find(path); it != m_fonts.end()) {
            return it->second;
        }

        sf::Font font;

        if (!font.openFromFile(path)) {
            throw std::runtime_error(
                "FontManager: failed to load font: " +
                std::filesystem::absolute(path).string()
            );
        }

        auto [it, inserted] =
            m_fonts.emplace(path, std::move(font));

        return it->second;
    }

}