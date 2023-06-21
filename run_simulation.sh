#!/bin/bash

# Run gamma_simulation in the background
./gamma_simulation &

# Store the PID of gamma_simulation process
gamma_pid=$!

# Wait for some time (adjust as needed)
sleep 1

# Run plotter.py in the foreground
python3 plotter.py

# Wait for gamma_simulation process to finish
wait $gamma_pid
ython3 plotter.py
