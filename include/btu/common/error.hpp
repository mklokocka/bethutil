/* Copyright (C) 2021 Edgar B
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#pragma once

#include <iostream>
#include <source_location>
#include <system_error>

namespace btu::common {
#ifdef __clang__
struct SourceLocation
{
};

#define BETHUTIL_CURRENT_SOURCE_LOC \
    ::btu::common::SourceLocation {}

#else
struct SourceLocation : public std::source_location
{
};

#define BETHUTIL_CURRENT_SOURCE_LOC \
    static_cast<::btu::common::SourceLocation>(std::source_location::current())
#endif

inline auto operator<<(std::ostream &os, [[maybe_unused]] SourceLocation loc) -> std::ostream &
{
#ifdef __clang__
    return os << std::string_view("source location unsupported with clang");
#else
    return os << "file: " << loc.file_name() << "(" << loc.line() << ":" << loc.column() << ") `"
              << loc.function_name() << "`";
#endif
}

struct Error : public std::error_code
{
    explicit Error(std::error_code ec, SourceLocation l = BETHUTIL_CURRENT_SOURCE_LOC)
        : std::error_code(ec)
        , loc(l)
    {
    }

    static auto success(SourceLocation l = BETHUTIL_CURRENT_SOURCE_LOC)
    {
        return Error(std::error_code(0, std::generic_category()), l);
    }

    SourceLocation loc;
};

inline auto operator<<(std::ostream &os, const Error &err) -> std::ostream &
{
    return os << err.value() << ":" << err.category().name() << ":" << err.message() << "; " << err.loc;
}
} // namespace btu::common
