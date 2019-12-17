#!/bin/bash
for ((i = 1; i < 500; i++))
do
g++ -Wall -Werror Source/main.cpp -o main
./main
echo "test $i passed successful"
done
g++ -Wall -Werror Source/ReadStatistics.cpp -o ReadStatistics
./ReadStatistics
for ((a = 1; a < 100; a++))
do
g++ -Wall -Werror Source/Generation.cpp -o Generation
g++ -Wall -Werror Source/Generation.cpp -o Generation
echo "data $a was generated"
./Generation
done
g++ -Wall -Werror Source/mainForRand.cpp -o mainForRand
./mainForRand
g++ -Wall -Werror Source/MediumTime.cpp -o MediumTime
./MediumTime
rm MediumTime
rm Generation
rm mainForRand
rm main
rm ReadStatistics