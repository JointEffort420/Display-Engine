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

        // Should never be reached.
        throw std::runtime_error(
            "FontManager: invalid Font value"
        );
    }

    const sf::Font& FontManager::getDefaultFont() {
        const auto path =
            m_engineAssetDirectory / "custom_font.ttf";

        std::cout << "Font path: " << path.string() << '\n';

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
            const auto defaultPath =
                m_engineAssetDirectory / "custom_font.ttf";

            if (path != defaultPath) {
                std::cerr
                    << "FontManager: failed to load '"
                    << path.string()
                    << "', using default font\n";

                return getDefaultFont();
            }

            throw std::runtime_error(
                "FontManager: failed to load custom font: " +
                defaultPath.string()
            );
        }

        auto [inserted, _] =
            m_fonts.emplace(path, std::move(font));

        return inserted->second;
    }

}