//
// Created by natha on 28/9/2026.
//

#include "Resources/TextureManager.h"

#include <iostream>
#include <stdexcept>
#include <utility>

namespace eng {

    TextureManager::TextureManager(
        std::filesystem::path engineAssetDirectory
    )
        : m_engineAssetDirectory(std::move(engineAssetDirectory)) {
    }

    const sf::Texture* TextureManager::resolve(
        const Texture& texture
    ) {
        switch (texture.m_type) {
            case Texture::Type::None:
                return nullptr;

            case Texture::Type::Default:
                return getDefaultTexture();

            case Texture::Type::File:
                return load(texture.m_path);
        }

        // Should never be reached.
        throw std::runtime_error(
            "TextureManager: invalid Texture value"
        );
    }

    const sf::Texture* TextureManager::getDefaultTexture() {
        const auto path =
            m_engineAssetDirectory / "default_texture.jpeg";

        std::cout << "Texture path: " << path.string() << '\n';

        return load(path);
    }

    const sf::Texture* TextureManager::load(
        const std::filesystem::path& path
    ) {
        if (auto it = m_cache.find(path); it != m_cache.end()) {
            return &it->second;
        }

        sf::Texture texture;

        if (!texture.loadFromFile(path)) {
            const auto defaultPath =
                m_engineAssetDirectory / "default_texture.jpeg";

            if (path != defaultPath) {
                std::cerr
                    << "TextureManager: failed to load '"
                    << path.string()
                    << "', using default texture\n";

                return getDefaultTexture();
            }

            throw std::runtime_error(
                "TextureManager: failed to load default texture: " +
                defaultPath.string()
            );
        }

        auto [inserted, _] =
            m_cache.emplace(path, std::move(texture));

        return &inserted->second;
    }

}