#!/bin/bash

# Parameters
TOLERANCE=1e-6
MAX_ITER=100000
PRINT_INFO=false
DIMENSION_VTK=3

# Function to calculate pi
pi=$(awk 'BEGIN {printf "%.16e", 4 * atan2(1, 1)}')

# Function to calculate sin(x) in radians
sin() {
    awk -v x="$1" 'BEGIN {printf "%.16e", sin(x)}'
}

make clean
make
mkdir ./plot

# Loop over the values of NUM_PROCS
NUM_PROCS_LIST=(1 2 4)

for NUM_PROCS in "${NUM_PROCS_LIST[@]}"; do

    # Output file for Gnuplot
    output_file="plot/errors_${NUM_PROCS}procs.dat"
    echo "# n error" > $output_file

    # Loop over the values of k
    for k in {4..8}; do
        n=$((2**k))
        echo "Running simulation for n=$n, NUM_PROCS=$NUM_PROCS"

        # Run the program
        make run N=$n TOLERANCE=$TOLERANCE MAX_ITER=$MAX_ITER NUM_PROCS=$NUM_PROCS PRINT_INFO=$PRINT_INFO DIMENSION_VTK=$DIMENSION_VTK

        # Generated VTK file
        vtk_file="data/solution.vtk"

        # Read the VTK file and calculate the error
        sum_error=0.0

        while read line; do
            # Read x, y, z
            x=$(echo $line | awk '{print $1}')
            y=$(echo $line | awk '{print $2}')
            z=$(echo $line | awk '{print $3}')

            # Calculate sin(2*pi*x) * sin(2*pi*y)
            exact=$(awk -v x="$x" -v y="$y" -v pi="$pi" 'BEGIN {printf "%.16e", sin(2*pi*x) * sin(2*pi*y)}')

            # Calculate (exact - z)^2 and add to the sum
            diff=$(awk -v exact="$exact" -v z="$z" 'BEGIN {printf "%.16e", exact - z}')
            diff_squared=$(awk -v diff="$diff" 'BEGIN {printf "%.16e", diff * diff}')
            sum_error=$(awk -v sum_error="$sum_error" -v diff_squared="$diff_squared" 'BEGIN {printf "%.16e", sum_error + diff_squared}')
        done < <(tail -n +7 $vtk_file)

        # Calculate the final error
        error=$(awk -v sum_error="$sum_error" -v n="$n" 'BEGIN {printf "%.16e", sqrt(sum_error / (n-1))}')

        # Add the result to the output file
        echo "$n $error" >> $output_file
    done
done

# Build plot command for Gnuplot
plot_command="plot"
for file in ./plot/errors_*.dat; do
    NUM_PROCS=$(echo $file | awk -F'_' '{print $2}' | awk -F'procs' '{print $1}')
    plot_command="$plot_command \"$file\" using 1:2 with linespoints title \"$NUM_PROCS processes\","
done
# Remove the extra comma at the end
plot_command=${plot_command%,}

# Plot with Gnuplot and save as PNG
gnuplot <<-EOFMarker
    set terminal pngcairo enhanced font "arial,10"
    set output './plot/error_plot.png'
    set title "Error vs n for different number of processes"
    set xlabel "n"
    set ylabel "Error"
    $plot_command
EOFMarker

echo "./plot/error_plot.png generated"