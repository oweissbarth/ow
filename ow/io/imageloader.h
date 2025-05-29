#pragma once

#include "ow/cg/image.h"

namespace ow::io::ImageLoader{
    cg::Image load(const std::string& path);
}