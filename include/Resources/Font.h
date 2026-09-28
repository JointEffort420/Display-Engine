//
// Created by natha on 9/28/2026.
//

#ifndef DISPLAYENGINE_FONT_H
#define DISPLAYENGINE_FONT_H

#include <filesystem>
#include <string>
#include <utility>

namespace eng {
    class Font {
    public:
        static Font defaultFont();
        static Font fromFile(std::filesystem::path path);

    private:
        friend class FontManager;

        enum class Type {
            Default,
            File
        };

        explicit Font(Type type);
        Font(Type type, std::filesystem::path path);

        Type m_type;
        std::filesystem::path m_path;
    };
}

#endif //DISPLAYENGINE_FONT_H