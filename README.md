## ELEC4622 Project 3
Renee Lu, z5160268 | August, 2020

## Tasks Overview
1. **Task 1** Monochrome to Bi-level Conversion
2. **Task 2** Bi-level Morphological Erosion
3. **Task 3** Bi-level Morphological Erosion with Circular Structuring Sets
4. **Task 4 Bonus** Zero Padding vs. Symmetric Extension
5. **Task 5** Bi-level Morphological Opening
6. **Task 6 Bonus** Greyscale Morphological Closing

## Code Location
The solution file is found in:
- *Project3/Project3.sln*

The code for Task 1, 2 and 3 are in, respectively:
- *Project3/Task1/main1.cpp*
- *Project3/Task2/main2.cpp*
- *Project3/Task3/main3.cpp*
- *Project3/Task4/main4.cpp*
- *Project3/Task5/main5.cpp*
- *Project3/Task6/main6.cpp*
- *Project3/Task6/main6_inefficient.cpp* this is the inefficient version of main6.cpp

## Project Properties
In Visual Studio, the non-default property configuration for the projects are:
- **Configuration Properties > General > Output Directory = [executables output file path]**
e.g. "*..\..\Executables*"
- **Configuration Properties > Advanced > Character Set = Use Multi-Bye Character Set**
- **Configuration Properties > Debugging > Command Arguments = [input bmp file path] [output bmp file path] [threhold T]**
e.g. "*..\Data\lenna_mono.bmp ..\Data\out.bmp 100*"
- **C/C++ > Preprocessor > Preprocessor Definitions = WIN32; _CRT_SECURE_NO_DEPRECATE**

## Steps to Run
1. Open Visual Studio 
2. Open the Project3/Project3.sln
3. Configure the Project Properties as above
3. Run the desired tasks using the command line arguments below:

To run Task 1 give the following command line arguments:
[input bmp file path] [output bmp file path] [threshold T]

To run Task 2 give the following command line arguments:
[input bmp file path] [output bmp file path] [structuring set location pairs]

To run Task 3 give the following command line arguments:
[input bmp file path] [output bmp file path] [radius r]

To run Task 4 give the following command line arguments:
[input bmp file path] [output bmp file path] [zero pad = 1 or 0]

To run Task 5 give the following command line arguments:
[input bmp file path] [output bmp file path] [structuring set location pairs OR radius r]

To run Task 6 give the following command line arguments:
[input bmp file path] [output bmp file path] [structuring set location pairs OR radius r]
