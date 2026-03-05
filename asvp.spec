Name:           asvp
Version:        1.0.0
Release:        1%{?dist}
Summary:        Terminal-based audio visualizer

License:        MIT
URL:            https://github.com/masterroshi06/asvp
Source0:        https://github.com/masterroshi06/asvp/archive/refs/tags/v%{version}.tar.gz

BuildRequires:  gcc-c++
BuildRequires:  cmake
BuildRequires:  pulseaudio-libs-devel
BuildRequires:  fftw-devel
BuildRequires:  ncurses-devel

%description
A lightweight, terminal-based audio frequency spectrum visualizer written in C++. ASVP captures your live system audio and displays a responsive, 32-bar frequency spectrum directly in your terminal.

%prep
%setup -q -n asvp-%{version}

%build
%cmake
%cmake_build

%install
%cmake_install

%files
%{_bindir}/asvp