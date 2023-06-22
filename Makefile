all: file
file: metrorec-runner.c metrorec.c
		gcc -o metrorec metrorec-runner.c -lpthread
clean:
		rm -f metrorec