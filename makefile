all: vgnr

vgnr: main.c operate.c
	gcc main.c operate.c -o vgnr

clean:
	rm -f vgnr
