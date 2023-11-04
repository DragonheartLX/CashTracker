file(GLOB_RECURSE Drmix_Src LIST_DIRECTORIES false 
    *.cpp
    **/*.cpp)

add_executable(CashTracker ${Drmix_Src})

target_include_directories(CashTracker PRIVATE .)

find_package(spdlog CONFIG REQUIRED)
    target_link_libraries(CashTracker PRIVATE spdlog::spdlog_header_only)
find_package(jsoncpp CONFIG REQUIRED)
    target_link_libraries(CashTracker PRIVATE JsonCpp::JsonCpp)

install(TARGETS CashTracker DESTINATION bin)