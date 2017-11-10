default:
	make clean
	make build

build:
	gcc -g simpleShell.c -o shell 
	gcc -g mc.c -o MonteCarlo
	clear

clean:
	clear
	rm -f shell MonteCarlo a.out
	clear

run:
	clear
	./shell

