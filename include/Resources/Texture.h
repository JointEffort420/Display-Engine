//
// Created by natha on 28/9/2026.
//

#ifndef DISPLAYENGINE_TEXTURE_H
#define DISPLAYENGINE_TEXTURE_H

#include <filesystem>
#include <utility>

namespace eng {

    class Texture {
    public:
        static Texture defaultTexture();
        static Texture fromFile(std::filesystem::path path);
        static Texture none();

    private:
        friend class TextureManager;

        enum class Type {
            Default,
            File,
            None
        };

        explicit Texture(Type type);
        Texture(Type type, std::filesystem::path path);

        Type m_type;
        std::filesystem::path m_path;
    };

}

#endif //DISPLAYENGINE_TEXTURE_H