cmake_minimum_required(VERSION 3.24)
project("Farming Sim")

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

Include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.8.1
)

FetchContent_MakeAvailable(Catch2)

#game
add_executable(farm_game
    main.cpp
    src/farm.cpp
    src/farm_printer.cpp
)

target_include_directories(farm_game PRIVATE ${CMAKE_SOURCE_DIR}/src)

#tests
add_executable(farm_test
    tests/farm_test.cpp
    tests/player_test.cpp
    tests/farm_printer_test.cpp
    tests/veg_carrot_test.cpp
    tests/veg_lettuce_test.cpp
    tests/veg_spinach_test.cpp
    tests/veg_beet_test.cpp
    tests/veg_brussel_sprouts_test.cpp
    tests/farm_watering_test.cpp
    tests/bunny_test.cpp

    src/farm.cpp
    src/farm_printer.cpp
)

target_include_directories(farm_test PRIVATE ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(farm_test PRIVATE Catch2::Catch2WithMain)
