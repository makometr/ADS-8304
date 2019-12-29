#!/bin/bash
g++ -Wall -Werror Source/HierarchicalListTest.cpp -o HierarchicalListTest
cat /dev/null > test.txt
echo "(bcx) (adwdadaw)" >> test.txt #1 тест
./HierarchicalListTest < test.txt >> result.txt
cat /dev/null > test.txt
echo "(adwdadaw) (bcx)" >> test.txt #2 тест
./HierarchicalListTest < test.txt  >> result.txt
cat /dev/null > test.txt
echo "(a) (a)" >> test.txt #3 тест
./HierarchicalListTest < test.txt  >> result.txt
cat /dev/null > test.txt
echo "(a(d)zx) (a(d)zx)" >> test.txt #4 тест
./HierarchicalListTest < test.txt  >> result.txt
cat /dev/null > test.txt
echo "(a(d)zx) (a(d)z()x)" >> test.txt #5 тест
./HierarchicalListTest < test.txt  >> result.txt
cat /dev/null > test.txt
echo "(a(d)zx) (a(vd()))" >> test.txt #6 тест
./HierarchicalListTest < test.txt  >> result.txt
cat /dev/null > test.txt
echo "(a(vd())) (a(vd()))" >> test.txt #7 тест
./HierarchicalListTest < test.txt  >> result.txt
cat /dev/null > test.txt
echo "(a(vd()x)) (a(vd()z))" >> test.txt #8 тест
./HierarchicalListTest < test.txt  >> result.txt
cat /dev/null > test.txt
echo "(((cda))) (((cda)))" >> test.txt #9 тест
./HierarchicalListTest < test.txt  >> result.txt
cat /dev/null > test.txt
echo "(((cda)daw)dz(())) (((cda)daw)dz(()))" >> test.txt #10 тест
./HierarchicalListTest < test.txt  >> result.txt
cat /dev/null > test.txt
echo "(((cda)daw)dz(()cx)z) (((cda)daw)dz(()xc)z)" >> test.txt #11 тест
./HierarchicalListTest < test.txt  >> result.txt
cat /dev/null > test.txt
echo "(((cda)daw)dz(()cx)z) (((cda)daw)dz(()cx)z)" >> test.txt #12 тест
./HierarchicalListTest < test.txt  >> result.txt
cat /dev/null > test.txt
echo "(dawdhwau(hd(za(xc(qd)gr))d)dhwuo(ad)aw) (dawdhwau(hd(za(xc(qd)gr))d)dhwuo(ad)aw)" >> test.txt #13 тест
./HierarchicalListTest < test.txt  >> result.txt
cat /dev/null > test.txt
echo "(dawdhwau(hd(zaxc(qd)gr)d)dhwuo(ad)aw) (dawdhwau(hd(za(xc(qd)gr))d)dhwuo(ad)aw)" >> test.txt #14 тест
./HierarchicalListTest < test.txt  >> result.txt
rm HierarchicalListTest
