![C/C++ CI](https://github.com/aindustriosa/RatibroombroomSW/workflows/C/C++%20CI/badge.svg?branch=master)

# Introduction

This project will contain the SW of the Ratibroombroom micromouse. The micromouse is based in the *STM32F405RGT6* microcontroller.

This is an open source project. That means you can build your own if you want. You can find the HW specification of this micromouse in this link (https://github.com/aindustriosa/Ratibroombroom)

# Developing
Please read [development](docs/developing.md)

# Programming

0) Flash the program

Type make in the root of the project

```
make
```

## Black Magic

### Quickstep

#### Using the pre-built gdb scripts

Execute the command:

```
make flash_black_magic_ttyACM0
```

If the blackmagic is in the tty/ACM0 device or 

```
make flash_black_magic_ttyACM3
```

If the blackmagic is in the tty/ACM3 device


### Step-by-step

#### Using the official docker image of the project

1) Run the following command

```
sudo docker run  --privileged -v $(pwd):/ratibroombroom:Z -w /ratibroombroom -u $(id -u):$(id -g) -ti pcounhago/mighty-sdk:9.2020q2 bash

```

_NOTE: In some cases you must specify the user as root if the following steps throw privilege issues_


2) Plug the blackmagic

TODO: Add images with the connections

https://black-magic.org/usage/gdb-commands.html

3) Search for the devices:

```
ls /dev/ttyACM*

```

4) Run the following command

```
arm-none-eabi-gdb
```

5) Insert the following command in gdb

Supposing the black magic is in /dev/ttyACM0

```
target extended-remote /dev/ttyACM0
monitor swdp_scan
```

The STM32F4 should appear in the output

```
Available Targets:
No. Att Driver
 1      STM32F40x M4

```

6) Attach to the device

```
attach 1
```

 
 
7) Finally flash the main.elf


```
(gdb) load src/main.elf
Loading section .text, size 0x6c4c lma 0x8000000
Loading section .ARM.exidx, size 0x8 lma 0x8006c4c
Loading section .data, size 0x690 lma 0x8006c54
Start address 0x8004a24, load size 29412
Transfer rate: 32 KB/sec, 919 bytes/write. 
```

8) Optional: Detach to the device and quit

```
detach
quit
```

# References

This project uses a fork of the mmlib library from Bulebots (Original project here: https://github.com/Bulebots/mmlib). Mmlib implements functionality for maze search and resolution, abstracting this funcitionality from the HW actually used.

This project is also inspired by the following projects:

* Bule bule micromouse: https://bulebule.readthedocs.io/en/latest/ from Bulebots and its continuation, Meiga (https://github.com/Bulebots/meiga). 

