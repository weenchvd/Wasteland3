
# Copyright (c) 2021 Vitaly Dikov
# 
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)

cmake_minimum_required(VERSION 3.14)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)



set(EXEC_NAME "wl3")
set(SOURCE_CXX_LIST "graphicUI.cpp"
                    "initializationAux.cpp"
                    "main.cpp"
                    "textUI.cpp"
)

# Add source to this project's executable.
add_executable(${EXEC_NAME} ${SOURCE_CXX_LIST})

target_link_libraries(${EXEC_NAME}
                      PRIVATE initialization
                      PRIVATE imgui
                      PRIVATE inventory
                      PRIVATE locator
                      PRIVATE menu
                      PRIVATE squad
                      PRIVATE unit
)

# Add tests and install targets if needed.
install(TARGETS ${EXEC_NAME} DESTINATION "${W3EXEC__INSTALL_DIR}")
