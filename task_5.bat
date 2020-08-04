@ECHO OFF
cd Executables
ECHO:
ECHO Task 5 Morphological Opening
ECHO -----------------------------------------------------------
ECHO Performing the following commands...
ECHO:
ECHO lenna_bilevel circular
ECHO Task5 ../Data/lenna_bilevel.bmp ../Data/out_5_5.bmp 5
Task5 ../Data/lenna_bilevel.bmp ../Data/out_5_5.bmp 5
ECHO:
ECHO Task5 ../Data/lenna_bilevel.bmp ../Data/out_5_10.bmp 10
Task5 ../Data/lenna_bilevel.bmp ../Data/out_5_10.bmp 10
ECHO:
ECHO Playing all the BMP files...
mi_pipe2 :: read_file -f ../Data/lenna_bilevel.bmp ../Data/out_5_5.bmp ../Data/out_5_10.bmp :: frame_repeat :: view -play -rate 1
ECHO:
ECHO lenna_bilevel square
ECHO Task5 ../Data/lenna_bilevel.bmp ../Data/out_5_square.bmp 0 0 0 1 0 -1 1 0 -1 0 1 1 1 -1 -1 1 -1 -1 
Task5 ../Data/lenna_bilevel.bmp ../Data/out_5_square.bmp 0 0 0 1 0 -1 1 0 -1 0 1 1 1 -1 -1 1 -1 -1  
ECHO:
ECHO Playing all the BMP files...
mi_pipe2 :: read_file -f ../Data/lenna_bilevel.bmp ../Data/out_5_square.bmp :: frame_repeat :: view -play -rate 1
ECHO TASKS COMPLETE
ECHO To view the output, use mi_viewer 'filepath'
cd ../
