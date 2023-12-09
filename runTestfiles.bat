#!/bin/bash

input_dir="TestInput"
output_dir="TestOutput"
compiler_path="Debug/MIECCompiler.exe"

for input_file in "$input_dir"/*; do
    # Extracting the file name without extension
    filename=$(basename -- "$input_file")
    filename_noext="${filename%.*}"
    output_name = $filename_noext"_output"
    # Constructing the output file path
    output_file="$output_dir/$filename_noext+_output.iex"
    echo "Output File name: " $output_file

    # Running the compiler command
    "$compiler_path" -in "$input_file" -out "$output_file"

    # Print a message indicating the completion of the compilation
    echo "Compiled $input_file to $output_file"
done
