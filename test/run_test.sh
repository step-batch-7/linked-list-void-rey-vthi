gcc -c test.c ../$1.c
gcc -o test ./*.o
./test
rm ./*.o
rm ./test