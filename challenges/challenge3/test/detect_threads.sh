#!/bin/bash
# Script to detect the number of threads per core

# Detect the total number of threads
total_threads=$(grep -c ^processor /proc/cpuinfo)

# Detect the total number of cores (physical cores)
total_cores=$(grep "cpu cores" /proc/cpuinfo | uniq | awk '{print $4}')

# Detect the number of sockets
total_sockets=$(grep "physical id" /proc/cpuinfo | sort -u | wc -l)

# Calculate threads per core
threads_per_core=$((total_threads / (total_cores * total_sockets)))

echo $threads_per_core