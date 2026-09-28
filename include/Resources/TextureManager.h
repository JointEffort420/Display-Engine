//
// Created by natha on 28/9/2026.
//

#ifndef DISPLAYENGINE_TEXTUREMANAGER_H
#define DISPLAYENGINE_TEXTUREMANAGER_H

#include <SFML/Graphics/Texture.hpp>

#include <filesystem>
#include <unordered_map>

#include "Resources/Texture.h"

namespace eng {

    class TextureManager {
    public:
        explicit TextureManager(
            std::filesystem::path engineAssetDirectory
        );

        const sf::Texture* resolve(const Texture& texture);

    private:
        const sf::Texture* getDefaultTexture();

        const sf::Texture* load(
            const std::filesystem::path& path
        );

        std::filesystem::path m_engineAssetDirectory;

        std::unordered_map<
            std::filesystem::path,
            sf::Texture
        > m_cache;
    };

}

#endif //DISPLAYENGINE_TEXTUREMANAGER_H