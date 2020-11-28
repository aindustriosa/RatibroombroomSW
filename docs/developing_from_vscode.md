# Developing using Docker and VSCode

Use VSCode to create code, compile and flash it.

This repo contains VSCode configurations for:
 - linking to libopencm3 code references from the robot source code.
 - run development tasks

## Setup
### Dependences
You need Docker running and make to execute builds from the terminal.

### Download and code setup
 - First: clone this repo.
 - Second: download and compile libopencm3 using -> "Terminal"->"Run Task..."->"Build libopencm3"

## Build code
From the root dir -> "Terminal"->"Run Task..."->"Build Ratibroom firmware" 

## Clean code
From the root dir -> "Terminal"->"Run Task..."->"Clean"

## Flash binary
From the root dir -> TBD