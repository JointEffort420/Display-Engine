//
// Created by natha on 9/28/2026.
//
#include "Resources/Font.h"

namespace eng {

    Font Font::defaultFont() {
        return Font(Type::Default);
    }

    Font Font::fromFile(std::filesystem::path path) {
        return Font(Type::File, std::move(path));
    }

    Font::Font(Type type)
        : m_type(type) {
    }

    Font::Font(Type type, std::filesystem::path path)
        : m_type(type),
          m_path(std::move(path)) {
    }

}