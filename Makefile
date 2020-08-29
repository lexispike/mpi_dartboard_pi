# compile Q3.c
Q3: Q3.c
	mpicc Q3.c -o Q3

# run Q3
run_Q3: Q3
	mpirun Q3

# clean the directory
clean:
	rm -f Q3
