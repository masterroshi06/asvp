# ASVP(Audio Spectrum Visualizer Program)

A terminal-based audio spectrum visualizer for Linux. It hooks directly into PulseAudio/PipeWire and uses FFT to draw a 32-bar frequency spectrum using `ncurses`.

## Dependencies

You need the development headers for PulseAudio, FFTW3, and ncurses (wide-character support), plus standard build tools (CMake, GCC/Clang).

**Fedora/RHEL:**
sudo dnf install pulseaudio-libs-devel fftw-devel ncurses-devel cmake gcc-c++

**Ubuntu/Debian:**
sudo apt install libpulse-dev libfftw3-dev libncursesw5-dev cmake g++

## Build & Install

Clone the repo and build using CMake:

git clone https://github.com/masterroshi06/asvp.git
cd asvp
mkdir build && cd build
cmake ..
make
sudo make install

## Usage

If installed globally, just run:
asvp

- Play any system audio to see the visualizer react.
- Press `q` to quit.
- Terminal resizing is handled automatically.