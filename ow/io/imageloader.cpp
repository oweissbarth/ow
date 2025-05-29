#include "imageloader.h"

#include <stb_image.h>

namespace ow::io::ImageLoader {
    cg::Image load(const std::string& path) {

        int width;
        int height;
        int channels;

        float* data = stbi_loadf(path.c_str(), &width, &height, &channels, 0);

        return {width, height, std::span<float>(data, width*height*channels)};

        stbi_image_free(data);
    }
}