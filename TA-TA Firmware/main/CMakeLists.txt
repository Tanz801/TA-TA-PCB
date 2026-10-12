idf_component_register(SRCS
                        "main.c"
                        "power_handle.c"
                        "tmp_handle.c"
                        "buzzer_handle.c"
                        "i2c_components/screen_handle.c"
                        "i2c_components/i2c_handle.c"
                        "i2c_components/face_elements.c"
                        "i2c_components/imu_handle.c"
                    INCLUDE_DIRS
                        "."
                        "i2c_components")

target_compile_options(${COMPONENT_LIB} PRIVATE 
    "-Wno-error=unused-function"
    "-Wno-error=unused-variable"
    "-Wno-error=unused-but-set-variable"
)