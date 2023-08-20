compRun:
	g++ -std=c++11 -pedantic Code/*.cpp  -o r.out

run: clean compRun; ./r.out

compTest:
	g++ -std=c++11 -pedantic Code/*.cpp -o a.out

test: clean compTest; ./a.out

clean:
	rm -f *.out