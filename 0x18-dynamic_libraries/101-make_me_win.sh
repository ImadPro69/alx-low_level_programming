#!/bin/bash

# Set the LD_PRELOAD environment variable to the path of the shared library
export LD_PRELOAD=./override.so

# Run the Giga Millions program with your chosen numbers
./gm 9 8 10 24 75 9


