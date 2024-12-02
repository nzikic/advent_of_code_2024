add_executable(day01)
target_sources(day01 PRIVATE main.cpp)
target_link_libraries(day01 PRIVATE advent_2024_warnings)

install(TARGETS day01 DESTINATION day01)
install(FILES input.txt DESTINATION day01)
