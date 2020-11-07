# Introduction

This project will contain the SW of the Ratibroombroom micromouse.

This is an open source project. That means you can build your own if you want. You can find the HW specification of this micromouse in this link (https://github.com/aindustriosa/Ratibroombroom)

# Setting up the project

Required dependencies:

* openocd (you can install it with apt install openocd in Ubuntu)

To install the dependencies and configure the project execute the following command

```
bash script/setup_project.sh
```

# Compilation

* compile from scratch

Type this command in the *src* folder

```
make
```

# Programming the micromouse

Use the following script

```
bash scripts/program_ratibroom.sh
```

# References

This project uses a fork of the mmlib library from Bulebots (Original project here: https://github.com/Bulebots/mmlib). Mmlib implements functionality for maze search and resolution, abstracting this funcitionality from the HW actually used.

This project is also inspired by the following projects:

* Bule bule micromouse: https://bulebule.readthedocs.io/en/latest/ from Bulebots and its continuation, Meiga (https://github.com/Bulebots/meiga). 

