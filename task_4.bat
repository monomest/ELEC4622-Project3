@ECHO OFF
cd Executables
ECHO:
ECHO Task 4 Zero Padding vs. Symmetric Extension
ECHO -----------------------------------------------------------
ECHO Performing the following commands...
ECHO:
ECHO lenna_bilevel
ECHO Task4 ../Data/lenna_bilevel.bmp ../Data/out_4_0.bmp 6 0
Task4 ../Data/lenna_bilevel.bmp ../Data/out_4_0.bmp 6 0
ECHO:
ECHO Task4 ../Data/lenna_bilevel.bmp ../Data/out_4_1.bmp 6 1
Task4 ../Data/lenna_bilevel.bmp ../Data/out_4_1.bmp 6 1
ECHO:
ECHO Playing all the BMP files...
mi_pipe2 :: read_file -f ../Data/out_4_0.bmp ../Data/out_4_1.bmp :: frame_repeat :: view -play -rate 1
ECHO:
ECHO TASKS COMPLETE
ECHO To view the output, use mi_viewer 'filepath'
cd ../
