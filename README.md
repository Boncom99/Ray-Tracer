# TFG

to run :

´´´
g++ -Wall -g -O3 -std=c++17 \*.cpp -o main &&./main
´´´
Transform ppm to png :

´´´
mogrify -format png \*.ppm  
´´´
Delete ppm

´´´
find . -name "\*.ppm" -type f -delete
´´´
