cmake_minimum_required(VERSION 3.16)
project(ShieldSimulation)

find_package(Geant4 REQUIRED ui_all vis_all)
include(${Geant4_USE_FILE})

include_directories(${PROJECT_SOURCE_DIR}/src)
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)

add_executable(ShieldSim main.cc ${sources})
target_link_libraries(ShieldSim ${Geant4_LIBRARIES})

