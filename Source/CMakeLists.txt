
# Copyright (c) 2021 Vitaly Dikov
# 
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
add_compile_definitions(_UNICODE UNICODE)

add_subdirectory("Common")
add_subdirectory("Factory")
add_subdirectory("Initialization")
add_subdirectory("Locator")
add_subdirectory("Main")
add_subdirectory("Menu")
add_subdirectory("Object")
add_subdirectory("Options")
add_subdirectory("PlainText")
