# CMakeLists.txt
# ESP-IDF Build Configuration for Indicator System Project
# This file tells the build system which source files and include paths to use.

idf_component_register(
    SRCS
        "app_main.c"
        "indicator_app.c"
        "gpio_driver.c"
        "pwm_driver.c"
        "hw_timer_driver.c"
    INCLUDE_DIRS "."
)

