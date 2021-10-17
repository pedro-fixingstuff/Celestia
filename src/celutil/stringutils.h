// stringutils.h
//
// Copyright (C) 2001-present, the Celestia Development Team
// Original version by Chris Laurel <claurel@shatters.net>
//
// Miscellaneous useful functions.
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.

#pragma once

#include <celcompat/charconv.h>
#include <celcompat/string_view.h>

int compareIgnoringCase(celestia::compat::string_view s1, celestia::compat::string_view s2);
int compareIgnoringCase(celestia::compat::string_view s1, celestia::compat::string_view s2, int n);

struct CompareIgnoringCasePredicate
{
    bool operator()(celestia::compat::string_view, celestia::compat::string_view) const;
};

template <typename T>
[[nodiscard]] bool to_number(celestia::compat::string_view p, T &result)
{
    auto r = celestia::compat::from_chars(p.data(), p.data() + p.size(), result);
    return r.ec == std::errc();
}

template <typename T>
[[nodiscard]] bool to_number(celestia::compat::string_view p, T &result, int base)
{
    auto r = celestia::compat::from_chars(p.data(), p.data() + p.size(), result, base);
    return r.ec == std::errc();
}
