# Set terminal and output
set terminal pngcairo enhanced font 'Arial,12' size 800,600
set output 'out/key_generation_times.png'

# Set labels and title
set title "Signing Key Generation Times"
set xlabel "Algorithm"
set ylabel "Metrics [s]"
set ytics format "%.6f"

# Customize grid and style
set style data histogram
set style histogram cluster gap 1
set style fill solid border -1
set boxwidth 0.75
set grid ytics

# Datafile settings
set datafile separator ","

# Adjust x-tic labels to avoid overlap
set xtics rotate by -45

# Plot the data
plot 'out/key_generation_times.csv' using 2:xtic(1) title "Key Generation" lc rgb "green"
