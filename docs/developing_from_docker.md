# Developing using Docker

Use you favourite IDE to create code and let a Docker image do the rest for you!

TL;DR: We use make rules for the common tasks, you can read the Makefile in the repo root dir or do a "make help" to see what it can do for you.

## Setup
### Dependences
You need Docker running and make to execute builds from the terminal.

### Download and code setup
 - First: clone this repo.
 - Second: download and compile libopencm3 using -> make libopencm3

## Build code
From the root dir -> make 

## Clean code
From the root dir -> make clean

## Flash binary
From the root dir -> make flash
