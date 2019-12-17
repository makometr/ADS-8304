g++ -Wall -Werror Source/Lab5.cpp -o Lab5
cat /dev/null > TestData.txt
echo "25 58 35 86 36 25" >> TestData.txt #1 тест
./Lab5
cat /dev/null > TestData.txt
echo "58 15 73 26 35" >> TestData.txt #2 тест
./Lab5
cat /dev/null > TestData.txt
echo "12 74 63 25" >> TestData.txt #3 тест
./Lab5
rm Lab5
