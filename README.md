# FileParser

## Command Line Parsing using Clara Library

- After compiling the file *CommandLineArguments.cpp*, run it using (ex: ./app) and add the path to the input files then path of output file (ex: ./app   pathOfTheFile/Input1.txt  pathOfTheFile/Input1.txt   pathOfTheFile/Output.txt).

- Note: Don't switch the order of the arguments as they are stored in variables in this order.

## Using FileParser

- Arguments required are:

  - Directory of the first text file (ex: /home/user/directory/txtfile.txt)
  - One of the following operations ("plus" - "minus" - "multiply" - "divide")
  - Directory of the second text file
  - Delimiter if any exists (use [-q] followed by first delimiter and [-w] followed by second delimiter)
  - Output Directory (Leave blank to save in the program directory, use [-e] followed by export directory)
  - Separate each argument with a single space
  - ex. `./FileParser <first_file_directory> <operation> <second_file_directory> -q <first_delimiter> -w <second_delimiter> -e <export_directory>`

- Output will be in the same file directory as (results.txt)

- In case of different file lengths, arrays are concatenated with either 1s - in case of division and multiplication - or 0s - in case of addition or subtraction-

## FMT library

-to install the library:
<http://www.nrstickley.com/the-fmt-library/>

-FMT syntax:
<https://fmt.dev/latest/syntax.html>

- to compile Reading_file.cpp:
g++ -O2 --std=c++11 -DFMT_HEADER_ONLY -o Reading_file Reading_file.cpp

## Clara Library 

-to install the library:
<https://github.com/catchorg/Clara>

-sudo mkdir /usr/local/include/clara
-sudo cp Clara/include/clara.* /usr/local/include/clara/
-sudo cp Clara/include/clara_textflow.* /usr/local/include/clara/

