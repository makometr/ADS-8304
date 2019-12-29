#!/bin/bash
g++ -Wall -Werror Source/main.cpp -o main
./main
g++ -Wall -Werror Source/ReadStatistics.cpp -o ReadStatistics
./ReadStatistics
g++ -Wall -Werror Source/Generation.cpp -o Generation
./Generation
g++ -Wall -Werror Source/mainForRand.cpp -o mainForRand
./mainForRand
g++ -Wall -Werror Source/MediumTime.cpp -o MediumTime
./MediumTime
rm MediumTime
rm Generation
rm mainForRand
rm main
rm ReadStatistics