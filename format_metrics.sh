#!/bin/bash

# File to store key generation times
output_file="out/key_generation_times.csv"

# Clear the output file
rm "$output_file"

# Loop through all the files in the current directory
for file in out/*.csv; do
  # Check if the file is a regular file
  if [[ -f "$file" ]]; then
    # Extract the filename without "out/" and ".csv"
    filename=$(basename "$file" .csv)

    # Escape underscores in the filename
    filename_escaped=$(echo "$filename" | sed 's/_/\\\\_/g')

    # Extract the first line (key generation time)
    gen_time=$(head -n 1 "$file")

    # Append the escaped filename and key generation time to the output file
    echo "$filename_escaped,$gen_time" >> "$output_file"

    # Remove the first line from the file
    tail -n +2 "$file" > "$file.tmp" && mv "$file.tmp" "$file"
  fi
done

echo "Processing complete. Key generation times saved in $output_file."
