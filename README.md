# TFG

to run :

´´´
g++-11 -Wall -g -O3 -std=c++20 *.cpp -o main &&./main
´´´
Transform ppm to png :

´´´
mogrify -format png \*.ppm  
´´´
Delete ppm

´´´
find . -name "\*.ppm" -type f -delete
´´´
