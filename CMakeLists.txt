cmake_minimum_required(VERSION 3.12)

# Set the SDK path explicitly
set(PICO_SDK_PATH "D:/pico-sdk")

# Include build functions from the PICO SDK
include(${PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(main C CXX ASM)
set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD 20)

# Initialize the SDK
pico_sdk_init()

# Add executable with all source files
add_executable(${PROJECT_NAME}
    main.cpp
    ir-sensor.cpp
)

# Include directory for the header file
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# Link to standard Pico libraries
target_link_libraries(${PROJECT_NAME} pico_stdlib hardware_gpio)

# Enable USB output, disable UART output
pico_enable_stdio_usb(${PROJECT_NAME} 1)
pico_enable_stdio_uart(${PROJECT_NAME} 0)

# Create map/bin/hex files
pico_add_extra_outputs(${PROJECT_NAME})
