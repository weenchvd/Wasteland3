
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
"\n"
"// Copyright (c) 2022 Vitaly Dikov\n"
"// \n"
"// Distributed under the Boost Software License, Version 1.0.\n"
"// (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)\n"
"\n"
"namespace fbOptions;\n"
"\n"
"file_identifier \"OPTS\";\n"
"\n"
"enum FB_Options_Language:int8 {\n"
"  INVALID = 0,\n"
"\n"
"  EN,\n"
"  RU\n"
"}\n"
"\n"
"table FB_Options {\n"
"  language:FB_Options_Language = INVALID;\n"
"}\n"
"\n"
"root_type FB_Options;\n"
"";

} // namespace optionsStuff
} // namespace global
} // namespace game

#endif // !OPTIONS_FB_SCHEMA_HPP
