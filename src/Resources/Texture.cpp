//
// Created by natha on 9/28/2026.
//

#include "Resources/Texture.h"

#include "Resources/Font.h"

namespace eng {
    Texture Texture::defaultTexture() {
        return Texture(Type::Default);
    }

    Texture Texture::fromFile(std::filesystem::path path) {
        return Texture(Type::File, std::move(path));
    }

    Texture Texture::none() {
        return Texture(Type::None);
    }

    Texture::Texture(Type type)
        : m_type(type) {}

    Texture::Texture(Type type, std::filesystem::path path)
        : m_type(type),
          m_path(std::move(path)) {}

}
