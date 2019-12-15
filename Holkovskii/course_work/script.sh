#! /bin/bash
make
./cw Tests/Test1 code_test1
echo ""
./cw code_test1 decode_test1
echo ""
./cw Tests/Test2 code_test2
echo ""
./cw code_test2 decode_test2
echo ""
./cw Tests/Test3 code_test3
echo ""
./cw code_test3 decode_test3
rm -f cw
