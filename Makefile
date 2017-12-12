do:
	rm -rf *.o
	gfortran fortran/math.f90 -c
	g++ -std=c++17 main.cpp math.o -fpermissive -I /opt/OpenBLAS/include/ -L /opt/OpenBLAS/lib -l openblas  -lpthread -o main.o -llapack -lgfortran
	./main.o

test:
	rm -rf *.o
	gfortran fortran/math.f90 -c
	g++ -std=c++17 test.cpp math.o -fpermissive -I /opt/OpenBLAS/include/ -L /opt/OpenBLAS/lib -l openblas  -lpthread -o test.o -llapack -lgfortran 
	./test.o

clean:
	rm -rf *.o