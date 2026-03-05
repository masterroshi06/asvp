cmake_minimum_required(VERSION 3.10)
project(ASVP)

# Find wide ncurses
find_package(PkgConfig REQUIRED)
pkg_check_modules(NCURSESW REQUIRED ncursesw)

set(CMAKE_CXX_STANDARD 17)

add_executable(asvp src/main.cpp)

# Link the libraries
target_link_libraries(asvp PRIVATE pulse pulse-simple fftw3 ncursesw)

# --- INSTALLATION RULES ---
# This tells 'make install' to put the binary in the system's PATH
install(TARGETS asvp DESTINATION bin)