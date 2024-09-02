# pigpiod 
pigpio/pigpiod is is a C/C++ library for the Raspberry which allows control of the General Purpose Input Outputs (GPIO).
## Linux installtion

List of commands which must be runned in a row

```
wget https://github.com/joan2937/pigpio/archive/master.zip
unzip master.zip
cd pigpio-master
make
sudo make install
```

Insted of first line master.zip can be downloaded from "RPI gpio" folder
## Compiling programm
How should looks like folder before compling you can see in one of example folders, all following commands should be running outside of "src" folder

```
cmake
make
sudo ./programm_name
```

## CMakeLists Example
```
cmake_minimum_required(VERSION 3.18 FATAL_ERROR)

project(programm-name-example)
set(CMAKE_CXX_STANDARD 11)

add_executable(programm-name ./programm-name.cpp)
target_link_libraries(programm-name PUBLIC pigpio fmt)
```

## Links
- [Official pigpio library website](https://abyz.me.uk/rpi/pigpio/index.html)
- [Official github](https://github.com/joan2937/pigpio)
- [List of fuctions](https://abyz.me.uk/rpi/pigpio/cif.html)
- [YouTube Guide playlist](https://www.youtube.com/watch?v=R6VJE7WfXt8&list=PLf6OEfnTo5N4PXbw85heZ1q3ypCaSMOGo&pp=iAQB)
