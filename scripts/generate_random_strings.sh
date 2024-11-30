#!/bin/bash

# File to store the random strings
OUTPUT_FILE="random_strings.txt"

# Number of random strings to generate
NUM_STRINGS=20

# Create or empty the output file
> "$OUTPUT_FILE"

echo "Generating $NUM_STRINGS random strings..."

for ((i = 1; i <= NUM_STRINGS; i++)); do
  # Generate the random string and append it to the file
  tr -dc 'A-Za-z0-9!"#$%&'\''()*+,-./:;<=>?@[\]^_`{|}~' </dev/urandom | head  -c $(($i * 20000)) >> "$OUTPUT_FILE"

  # Add a newline to separate strings
  echo >> "$OUTPUT_FILE"
done

echo "Random strings saved to $OUTPUT_FILE."
