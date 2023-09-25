CC = g++


all: out

out: karatsuba.cpp
	$(CC) -o out karatsuba.cpp
	./out
	iverilog -o test solution.v testSolution.v
	vvp test

isinput: karatsuba.cpp
	$(CC) -o out -Disinput karatsuba.cpp
	./out
	iverilog -o test solution.v testSolution.v
	vvp test

autotest: karatsuba.cpp
	$(CC) -o out -Dautotest karatsuba.cpp
	./out
	iverilog -o test solution.v testSolution.v
	vvp test

clean:
	rm -f out test solution.* testSolution.*
