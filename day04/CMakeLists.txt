add_executable(day04)
target_sources(day04 PRIVATE main.cpp)
target_link_libraries(day04 PRIVATE advent_2024_warnings)

install(TARGETS day04 DESTINATION day04)
install(FILES input.txt DESTINATION day04)
