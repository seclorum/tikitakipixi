cmake_minimum_required(VERSION 3.15)

project(titapiJUCE VERSION 1.0)

# JUCE Setup
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

include(FetchContent)
FetchContent_Declare(
  juce
  GIT_REPOSITORY https://github.com/juce-framework/JUCE.git
  GIT_TAG        master
)
FetchContent_MakeAvailable(juce)

# Add executable target
juce_add_gui_app(
  titapiJUCE
  PRODUCT_NAME "titapiJUCE"
)

# Add source files
target_sources(titapiJUCE
  PRIVATE
	src/LoupeComponent.cpp
	src/LoupeComponent.h
	src/Main.cpp
	src/MainComponent.cpp
	src/MainComponent.h
)

# Link JUCE module
target_link_libraries(titapiJUCE
  PRIVATE
    juce::juce_gui_extra
)
