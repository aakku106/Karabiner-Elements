set(CMAKE_OSX_DEPLOYMENT_TARGET "13.0" CACHE STRING "Minimum OS X deployment version")

set(CMAKE_CXX_STANDARD 20)

include_directories(SYSTEM ${CMAKE_CURRENT_LIST_DIR}/../vendor/Karabiner-DriverKit-VirtualHIDDevice/include)
include_directories(SYSTEM ${CMAKE_CURRENT_LIST_DIR}/../vendor/vendor/include)
include_directories(${CMAKE_CURRENT_LIST_DIR}/../src/share)

add_compile_options(-Wall)
add_compile_options(-Werror)
add_compile_options(-O2)
