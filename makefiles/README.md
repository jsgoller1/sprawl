# makefiles

The makefile system for sprawl is adapted from https://stackoverflow.com/a/28663974/1320882, and "Recursive Make Considered Harmful" by Peter Miller.
All the makefiles live in this folder, and shouldn't live anywhere else at present. 

## Overview
At a high level, here's how building works in Sprawl:
1. Commands are invoked from the top-level directory.
1. The command triggers a single recursive make for the desired project to select the desired makefile.
1. The desired makefile is loaded.
1. On load, a `.<project-name>-depend` target is automatically invoked. This creates a `.<project-name>-depend` file using the clang preprocessor to calculate the exact dependencies of each `.o` file. 
1. The project target is then built; this will independently compile each target required, then link them into a single object.
1. If applicable, the object is executed. 

