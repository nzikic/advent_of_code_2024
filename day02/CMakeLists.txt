add_executable(day02)
target_sources(day02 PRIVATE main.cpp)
target_link_libraries(day02 PRIVATE advent_2024_warnings)

install(TARGETS day02 DESTINATION day02)
install(FILES input.txt DESTINATION day02)
