# Sneed64 (outdated)
Due to this projects age and the outdated situation as of 2024, end-users are strongly adviced to go find different options/solutions playing Nintendo 64 games.

Sneed64 was a fork of loganmc10's m64p, aimed to provide a pleasant experience while otherwise being up-to-date with m64p's original codebase, with minor improvements being added as (s)needed by contributors and volunteers like you at large.

**Downloads found here: https://github.com/lordlouckster/sneed64/releases**
___

Linux Dependencies (Ubuntu 20.04)
```
sudo apt install qt5-default libqt5websockets5 libsdl2-2.0-0 libsdl2-net-2.0-0 libhidapi-hidraw0 libminizip1 p7zip-full
```
Linux Dependencies (Manjaro/Arch)
```
sudo pacman -S --needed qt5-base qt5-websockets sdl2 sdl2_net hidapi minizip p7zip zip
```
Linux Dependencies (Fedora)
```
sudo dnf install minizip-compat mesa-libGLU hidapi p7zip qt5-qtwebsockets
```
___
Building:
```
git clone https://github.com/lordlouckster/sneed64.git
cd m64p
./build.sh
```
