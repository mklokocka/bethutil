#pragma once

#include "btu/tex/error_code.hpp"

#include <tl/expected.hpp>

namespace btu::tex {
class Texture;

using Result      = tl::expected<Texture, Error>;
using ResultError = tl::expected<void, Error>;
} // namespace btu::tex
