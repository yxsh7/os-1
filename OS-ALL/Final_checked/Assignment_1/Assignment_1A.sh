#!/bin/bash

# ---------- Echo Command ----------
echo "Hello, World!" # Print "Hello, World!" to the terminal

# ---------- LS Command ----------
ls # List files and directories in the current folder

# ---------- Read Command ----------
read -p "Enter your name: " name
echo "Hello, $name!" # Read user input and greet

# ---------- Cat Command ----------
cat <<EOF
This is a multiline
text using the cat command.
EOF

# ---------- Touch Command ----------
touch new_file.txt # Create a new empty file called "new_file.txt"

# ---------- Test Command ----------
file="new_file.txt"
if [ -e $file ]; then
  echo "$file exists" # Check if "new_file.txt" exists and display a message
else
  echo "$file does not exist" # Display a message if the file doesn't exist
fi

# ---------- Loops ----------
# For loop
for i in {1..5}; do
  echo "Loop iteration $i" # Display loop iteration
done

# While loop
count=1
while [ $count -le 3 ]; do
  echo "While loop iteration $count" # Display while loop iteration
  ((count++))
done

# ---------- Arithmetic Comparison ----------
x=5
y=10

if [ $x -eq $y ]; then
  echo "x is equal to y" # Compare x and y and display a message if they are equal
else
  echo "x is not equal to y" # Display a message if x and y are not equal
fi

# ---------- Conditional Loops ----------
num=7
if [ $num -gt 5 ]; then
  echo "$num is greater than 5" # Check if num is greater than 5 and display a message
fi

# ---------- Grep Command ----------
grep "pattern" file.txt # Search for "pattern" in "file.txt"

# ---------- Sed Command ----------
sed 's/old_string/new_string/g' input.txt > output.txt # Replace "old_string" with "new_string" in a file and save the result in "output.txt"





