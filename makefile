current_dir = $(shell pwd)

all: vgnr

vgnr: main.c operate.c
	gcc -Wall main.c operate.c -o vgnr
	ln -s ${current_dir}/vgnr /bin/vgnr

clean:
	rm -f vgnr
