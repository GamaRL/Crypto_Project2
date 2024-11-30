# Set terminal and output
set terminal pngcairo enhanced font 'Arial,12' size 800,600
set output 'out/kem.png'

# Set labels and title
set title "ML-KEM Performance"
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

# Plot the data
plot 'out/kem.csv' using 2:xtic(1) title "Key Generation" lc rgb "blue", \
     '' using 3 title "Encapsulation" lc rgb "red", \
     '' using 4 title "Decapsulation" lc rgb "yellow"
