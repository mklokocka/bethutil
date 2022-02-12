#include "../utils.hpp"
#include "btu/common/filesystem.hpp"
#include "btu/common/games.hpp"

#include <btu/hkx/functions.hpp>
#include <catch.hpp>

#include <filesystem>
#include <fstream>

const Path dir     = "convert-hkx";
const Path exe_dir = "exe";

TEST_CASE("Converting from LE to SE", "[src]")
{
    btu::hkx::Anim anim(exe_dir);
    REQUIRE_FALSE(anim.load(dir / "LE_INPUT.hkx"));
    REQUIRE_FALSE(anim.convert(btu::Game::SSE));
    fs::remove(dir / "LE_OUTPUT.hkx");
    REQUIRE_FALSE(anim.save(dir / "LE_OUTPUT.hkx"));
    CHECK(btu::common::compare_files(dir / "LE_EXPECTED.hkx", dir / "LE_OUTPUT.hkx"));
}

TEST_CASE("Converting from SE to LE", "[src]")
{
    btu::hkx::Anim anim(exe_dir);
    REQUIRE_FALSE(anim.load(dir / "SE_INPUT.hkx"));
    REQUIRE_FALSE(anim.convert(btu::Game::SLE));
    fs::remove(dir / "SE_OUTPUT.hkx");
    REQUIRE_FALSE(anim.save(dir / "SE_OUTPUT.hkx"));
    CHECK(btu::common::compare_files(dir / "SE_EXPECTED.hkx", dir / "SE_OUTPUT.hkx"));
}