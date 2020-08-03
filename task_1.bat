@ECHO OFF
ECHO:
ECHO Task 1 Black and White
ECHO ---------------------------------------------------
cd Executables
ECHO Performing the following commands...
ECHO:
ECHO: pens_rgb
ECHO Task1 ../Data/pens_rgb.bmp ../Data/out_1_1.bmp 100
Task1 ../Data/pens_rgb.bmp ../Data/out_1_1.bmp 100
ECHO:
ECHO: lenna_mono
ECHO Task1 ../Data/lenna_mono.bmp ../Data/out_1_2.bmp 50
Task1 ../Data/lenna_mono.bmp ../Data/out_1_2.bmp 50
ECHO:
ECHO Task1 ../Data/lenna_mono.bmp ../Data/out_1_3.bmp 100
Task1 ../Data/lenna_mono.bmp ../Data/out_1_3.bmp 100
ECHO:
ECHO TASKS COMPLETE
ECHO To view the output, use mi_viewer 'filepath'
cd ../
