<h1 align="center">Audio Spectrum Visualizer Program (ASVP) </h1>

<p align="center">
  <b>A lightweight, terminal-based audio visualizer for Linux.</b><br>
  Hooks directly into PulseAudio/PipeWire and uses FFT to draw a 32-bar frequency spectrum using <code>ncurses</code>.
</p>


<p align="center">
  <img src="asvp-teaser.gif" width="100%" alt="ASVP Visualizer Demo">
</p>

<p align="center">
  <a href="asvp-final.mp4"><b>🎬 Watch Full Installation & Demo Video</b></a>
</p>



<p align="center">
  <img src="https://img.shields.io/badge/C++-17-blue.svg" alt="C++17">
  <img src="https://img.shields.io/badge/Platform-Linux-lightgrey.svg" alt="Linux">
  <a href="https://copr.fedorainfracloud.org/coprs/masterroshi06/asvp/"><img src="https://img.shields.io/badge/Fedora-COPR-blue?style=flat&logo=fedora" alt="Fedora COPR"></a>
  <a href="https://launchpad.net/~masterroshi06/+archive/ubuntu/asvp"><img src="https://img.shields.io/badge/Ubuntu-PPA-orange?style=flat&logo=ubuntu" alt="Ubuntu PPA"></a>
</p>

---

## 📦 Dependencies

You need the development headers for PulseAudio, FFTW3, and ncurses (wide-character support), plus standard build tools.

**Arch Linux:**
```bash
sudo pacman -S base-devel pulseaudio fftw ncurses cmake
```

**Fedora/RHEL:**
```bash
sudo dnf install pulseaudio-libs-devel fftw-devel ncurses-devel cmake gcc-c++
```


**Ubuntu/Debian:**
```bash
sudo apt install libpulse-dev libfftw3-dev libncursesw5-dev cmake g++
```

## 🚀 Build & Install

### Ubuntu / Debian (Recommended)
You can install `asvp` directly from the official PPA:
```bash
sudo add-apt-repository ppa:masterroshi06/asvp && sudo apt update
sudo apt install asvp
```

### Fedora / RHEL (Recommended)
You can install `asvp` directly via COPR:
```bash
sudo dnf copr enable masterroshi06/asvp && sudo dnf install asvp
```

### For Other distros
Clone the repo and build using CMake:

```bash
git clone https://github.com/masterroshi06/asvp.git
cd asvp
mkdir build && cd build
cmake ..
make
sudo make install
```

## 💻 Usage

If installed globally, just run:

```bash
asvp
```

* Play any system audio to see the visualizer react.
* Press `q` to quit.
* Terminal resizing is handled automatically.