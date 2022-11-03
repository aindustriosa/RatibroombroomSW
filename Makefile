# This Makefile is used when you want to compile or setup things from console.
# It uses the following Docker image in all rules.

# You can do "make help" to get a list of rules

IMAGE_NAME=pcounhago/mighty-sdk:9.2020q2
IN_IMAGE_WORKING_DIR=ratibroombroom
ENGINE = sudo docker
RUN = ${ENGINE} run -v $$(pwd):/${IN_IMAGE_WORKING_DIR}:Z -w /${IN_IMAGE_WORKING_DIR} -u $$(id -u):$$(id -g) ${IMAGE_NAME}


default: src

.PHONY: src
src:  ## (default) Compiles the micromouse code
	${RUN} make -C src/

.PHONY: flash
flash:  ## Flashes the robot using openOCD
	${RUN} make -C src/ flash

.PHONY: flash_black_magic_ttyACM0
flash_black_magic_ttyACM0:  ## Flashes the robot using GDB and the Black Magic board, the device is expected at ttyACM0
	${RUN} arm-none-eabi-gdb -x ./scripts/flash_ttyACM0.gdb

.PHONY: flash_black_magic_ttyACM3
flash_black_magic_ttyACM3:  ## Flashes the robot using GDB and the Black Magic board, the device is expected at ttyACM3
	${RUN} arm-none-eabi-gdb -x ./scripts/flash_ttyACM3.gdb

.PHONY: libopencm3
libopencm3:  ## Downloads and compiles libopencm3. Only needed once after repository clone.
	${RUN} scripts/setup_project.sh

.PHONY: clean
clean:  ## Clean micromouse build
	${RUN} make -s -C src/ clean

.PHONY: help
help: ## show this help.
	@fgrep -h "##" $(MAKEFILE_LIST) | fgrep -v fgrep | sed -e 's/\\$$//' | sed -e 's/##//'
