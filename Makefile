comp = gcc -std=c99
dbg = -Wall -Wextra -ggdb

all: primelister

primelister: primelister.c
	$(comp) $(dbg) primelister.c -o primelister.exe

final: primelister.c
	$(comp) -O3 primelister.c -o primelister.exe
