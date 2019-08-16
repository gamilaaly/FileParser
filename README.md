# FileParser

## Using FileParser

- Arguments required are:

  - Directory of the first text file (ex: /home/user/directory/txtfile.txt)
  - One of the following operations ("+" | "-" | "m" | "d")
  - Directory of the second text file
  - Delimiter if any exists (use [-f] followed by first delimiter and [-s] followed by second delimiter)
  - Output Directory (Leave blank to save in the program directory, use [-e] followed by export directory)
  - Separate each argument with a single space
  - ex. `./FileParser <first_file_directory> <operation> <second_file_directory> -f <first_delimiter> -s <second_delimiter> -e <export_directory>`

- Output will be in the same file directory as (results.txt)

- In case of different file lengths, arrays are concatenated with either 1s - in case of division and multiplication - or 0s - in case of addition or subtraction-

## FMT library

- To install the library:
       <http://www.nrstickley.com/the-fmt-library/>

- FMT syntax:
       <https://fmt.dev/latest/syntax.html>

- To compile Reading_file.cpp:
      - g++ -O2 --std=c++11 -DFMT_HEADER_ONLY -o Reading_file Reading_file.cpp

## Clara Library

- To install the library and check documentation:
  - <https://github.com/catchorg/Clara>

- To be able to include the library:
  - sudo mkdir /usr/local/include/clara
  - sudo cp Clara/include/clara.* /usr/local/include/clara/
  - sudo cp Clara/include/clara_textflow.* /usr/local/include/clara/
