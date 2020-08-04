@ECHO OFF
cd Executables
ECHO:
ECHO Task 3 Morphological Erosion with Circular Structuring Sets
ECHO -----------------------------------------------------------
ECHO Performing the following commands...
ECHO:
ECHO lenna_bilevel
ECHO Task3 ../Data/lenna_bilevel.bmp ../Data/out_3_0.bmp 0
Task3 ../Data/lenna_bilevel.bmp ../Data/out_3_0.bmp 0
ECHO:
ECHO Task3 ../Data/lenna_bilevel.bmp ../Data/out_3_3.bmp 3
Task3 ../Data/lenna_bilevel.bmp ../Data/out_3_3.bmp 3
ECHO:
ECHO Task3 ../Data/lenna_bilevel.bmp ../Data/out_3_6.bmp 6
Task3 ../Data/lenna_bilevel.bmp ../Data/out_3_6.bmp 6
ECHO:
ECHO Playing all the BMP files...
mi_pipe2 :: read_file -f ../Data/lenna_bilevel.bmp ../Data/out_3_0.bmp ../Data/out_3_3.bmp ../Data/out_3_6.bmp :: frame_repeat :: view -play -rate 1
ECHO:
ECHO TASKS COMPLETE
ECHO To view the output, use mi_viewer 'filepath'
cd ../
