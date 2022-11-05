target extended-remote /dev/ttyACM3
monitor swdp_scan
attach 1
load src/main.elf
detach
quit