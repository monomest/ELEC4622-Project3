@ECHO OFF
cd Executables
ECHO:
ECHO Task 6 Greyscale Morphological Closing
ECHO -----------------------------------------------------------
ECHO Performing the following commands...
ECHO:
ECHO lenna_mono
ECHO Task6 ../Data/lenna_mono.bmp ../Data/out_6_5.bmp 5
Task6 ../Data/lenna_mono.bmp ../Data/out_6_5.bmp 5
ECHO:
ECHO Playing all the BMP files...
mi_pipe2 :: read_file -f ../Data/lenna_mono.bmp ../Data/out_6_5.bmp :: frame_repeat :: view -play -rate 1
cd ../
