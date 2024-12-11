add_executable(day03)
target_sources(day03 PRIVATE main.cpp)
target_link_libraries(day03 PRIVATE advent_2024_warnings)

install(TARGETS day03 DESTINATION day03)
install(FILES input.txt DESTINATION day03)
