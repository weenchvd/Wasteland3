
# Copyright (c) 2022 Vitaly Dikov
# 
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

set(OPTIONS_FBS_HEADER__TEXT_PREFIX
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

set(OPTIONS_FBS_HEADER__TEXT_SUFFIX
"

} // namespace optionsStuff
} // namespace global
} // namespace game

#endif // !OPTIONS_FB_SCHEMA_HPP
"
)

file(READ "${OPTIONS_FB_SCHEMA_FILE_NAME}" OPTIONS_FBS_HEADER__TEXT_BODY)
string(REGEX REPLACE "\"" "\\\\\"" OPTIONS_FBS_HEADER__TEXT_BODY "${OPTIONS_FBS_HEADER__TEXT_BODY}")
string(REGEX REPLACE "\n" "\\\\n\"\n\"" OPTIONS_FBS_HEADER__TEXT_BODY "${OPTIONS_FBS_HEADER__TEXT_BODY}")
string(PREPEND OPTIONS_FBS_HEADER__TEXT_BODY "\"")
string(APPEND OPTIONS_FBS_HEADER__TEXT_BODY "\";")
string(CONCAT OPTIONS_FBS_HEADER__TEXT "${OPTIONS_FBS_HEADER__TEXT_PREFIX}"
                                  "${OPTIONS_FBS_HEADER__TEXT_BODY}"
                                  "${OPTIONS_FBS_HEADER__TEXT_SUFFIX}"
)
file(REAL_PATH "optionsFBSchema.hpp" OPTIONS_FBS_HEADER__TEXT_FILE)
file(GENERATE OUTPUT "${OPTIONS_FBS_HEADER__TEXT_FILE}" CONTENT "${OPTIONS_FBS_HEADER__TEXT}")
