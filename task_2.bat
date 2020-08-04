@ECHO OFF
cd Executables
ECHO:
ECHO Task 2 Morphological Erosion
ECHO -----------------------------------------------------------
ECHO Performing the following commands...
ECHO:
ECHO lenna_bilevel
ECHO Task2 ../Data/lenna_bilevel.bmp ../Data/out_2_cross.bmp 0 0 0 1 0 -1 1 0 -1 0
Task2 ../Data/lenna_bilevel.bmp ../Data/out_2_cross.bmp 0 0 0 1 0 -1 1 0 -1 0
ECHO:
ECHO Task2 ../Data/lenna_bilevel.bmp ../Data/out_2_square.bmp 0 0 0 1 0 -1 1 0 -1 0 1 1 1 -1 -1 1 -1 -1
Task2 ../Data/lenna_bilevel.bmp ../Data/out_2_square.bmp 0 0 0 1 0 -1 1 0 -1 0 1 1 1 -1 -1 1 -1 -1
ECHO:
ECHO Playing all the BMP files...
mi_pipe2 :: read_file -f ../Data/lenna_bilevel.bmp ../Data/out_2_cross.bmp ../Data/out_2_square.bmp :: frame_repeat :: view -play -rate 1
ECHO:
ECHO TASKS COMPLETE
ECHO To view the output, use mi_viewer 'filepath'
cd ../
