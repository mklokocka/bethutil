#pragma once

#include "btu/common/error.hpp"
#include "btu/common/path.hpp"
#include "btu/nif/common.hpp"

#include <nifly/NifFile.hpp>
#include <tl/expected.hpp>

namespace btu::nif {
class Mesh
{
    nifly::NifFile file_;
    Path load_path_;

public:
    [[nodiscard]] auto load(Path path) -> ResultError;
    [[nodiscard]] auto save(const Path &path) -> ResultError;

    auto get() noexcept -> nifly::NifFile &;
    auto get() const noexcept -> const nifly::NifFile &;

    auto get_load_path() const noexcept -> const Path &;
    void set_load_path(Path path) noexcept;
};

auto canonize_path(Path path) noexcept -> std::u8string;

} // namespace btu::nif
