if [ -f test.exe ]
then
	echo "deleting existing files..."
	rm test.exe
	echo "deleting finished"
fi;

echo "compiling ..."
g++ -std=c++11 -o test.exe *.cpp

if [ -f test.exe ]
then
	echo "compiling finished"
	echo "running program ..."
	./test.exe
else
	echo "compiling failed"
fi;
