comp = gcc -std=c99 -Wall -Wextra

all: primelister

primelister: primelister.c
	$(comp) primelister.c -o primelister.exe
