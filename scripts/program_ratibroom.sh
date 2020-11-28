#!/bin/bash

root=$(dirname $0)/../

pushd $root

openocd -f interface/stlink-v2.cfg -f target/stm32f4x.cfg -c "program src/main.elf verify reset" -c exit

popd
