target extended-remote /dev/ttyACM0
monitor swdp_scan
attach 1
load src/main.elf
detach
quit