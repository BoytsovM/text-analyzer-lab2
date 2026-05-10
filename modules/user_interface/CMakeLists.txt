add_library(user_interface STATIC src/ui.cpp)
target_include_directories(user_interface PUBLIC include)
target_link_libraries(user_interface PUBLIC data_processor logger)
