all: clean bancoDeDados.o listaInvertida.o indiceSecundario.o indicePrimario.o controler.o main.o dump.o busca.o remove.o compile clean

compile:
	@gcc bancoDeDados.o listaInvertida.o indiceSecundario.o indicePrimario.o controler.o dump.o main.o busca.o remove.o -o trab3 -g -lm

main.o:
	@gcc -c main.c -g

bancoDeDados.o:
	@gcc -c bancoDeDados.c -g

indicePrimario.o:
	@gcc -c indicePrimario.c -g

indiceSecundario.o:
	@gcc -c indiceSecundario.c -g

listaInvertida.o:
	@gcc -c listaInvertida.c -g

dump.o:
	@gcc -c dump.c -g

remove.o:
	@gcc -c remove.c -g

busca.o:
	@gcc -c busca.c -g

controler.o:
	@gcc -c controler.c -g

clean:
	@find -name '*~' | xargs rm -rf {}
	@find -name '*.o' | xargs rm -rf {}

run:
	@./trab3

zip:
	zip -r trab3 *.c *.h Makefile
