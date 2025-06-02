#!/bin/bash
python3 "plaintext_hex_generator.py"
gcc "expectedOutput.c" -o "expectedOutput"
./expectedOutput