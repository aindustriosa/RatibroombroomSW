
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
make clean
make
```

# Programming the micromouse

Use the following script that uses *openocd*

```
bash scripts/program_ratibroom.sh
```