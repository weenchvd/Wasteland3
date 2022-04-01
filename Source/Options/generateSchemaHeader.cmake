
# Copyright (c) 2022 Vitaly Dikov
# 
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

set(OPTIONS_HEADER_TEXT_PREFIX
"
// Copyright (c) 2022 Vitaly Dikov
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef OPTIONS_FB_SCHEMA_HPP
#define OPTIONS_FB_SCHEMA_HPP

namespace game {
namespace global {
namespace optionsStuff {

    const char* optionsFBSchema =
"
)

set(OPTIONS_HEADER_TEXT_SUFFIX
"

} // namespace optionsStuff
} // namespace global
} // namespace game

#endif // !OPTIONS_FB_SCHEMA_HPP
"
)

file(READ "optionsFB.fbs" OPTIONS_HEADER_TEXT_BODY)
string(REGEX REPLACE "\"" "\\\\\"" OPTIONS_HEADER_TEXT_BODY "${OPTIONS_HEADER_TEXT_BODY}")
string(REGEX REPLACE "\n" "\\\\n\"\n\"" OPTIONS_HEADER_TEXT_BODY "${OPTIONS_HEADER_TEXT_BODY}")
string(PREPEND OPTIONS_HEADER_TEXT_BODY "\"")
string(APPEND OPTIONS_HEADER_TEXT_BODY "\";")
string(CONCAT OPTIONS_HEADER_TEXT "${OPTIONS_HEADER_TEXT_PREFIX}"
                                  "${OPTIONS_HEADER_TEXT_BODY}"
                                  "${OPTIONS_HEADER_TEXT_SUFFIX}"
)
file(REAL_PATH "optionsFBSchema.hpp" OPTIONS_HEADER_TEXT_FILE)
file(GENERATE OUTPUT "${OPTIONS_HEADER_TEXT_FILE}" CONTENT "${OPTIONS_HEADER_TEXT}")
