current_dir = $(shell pwd)

all: vgnr

vgnr: main.c operate.c
	gcc -Wall main.c operate.c -o vgnr

global: main.c operate.c
	gcc -Wall main.c operate.c -o vgnr
	sudo ln -s ${current_dir}/vgnr /bin/vgnr

clean:
	rm -f vgnr
