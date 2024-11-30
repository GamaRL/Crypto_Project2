# Define the filename and output file
algorithm = system("echo $ALGORITHM")
escaped_algorithm = system("echo $ALGORITHM | sed 's/_/\\\\_/g'")
filename = algorithm . ".csv"
outputfile = algorithm . ".png"

set datafile separator ","
set xlabel "Message Size [bytes]"
set ylabel "Time [s]"

set title sprintf("Data from %s", escaped_algorithm)

set terminal png
set output "out/".outputfile

plot "out/".filename using 1:2 with lines lw 5 title "Signing time", \
     "out/".filename using 1:3 with lines lw 5 title "Verifying time"
