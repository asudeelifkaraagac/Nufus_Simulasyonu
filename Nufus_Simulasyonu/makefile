hepsi: derle calistir

derle:
	
	gcc -I ./include/ -o ./lib/Yerlesim.o -c ./src/Yerlesim.c
	gcc -I ./include/ -o ./lib/Kisi.o -c ./src/Kisi.c
	gcc -I ./include/ -o ./lib/Mahalle.o -c ./src/Mahalle.c
	gcc -I ./include/ -o ./lib/Ilce.o -c ./src/Ilce.c
	gcc -I ./include/ -o ./lib/Sehir.o -c ./src/Sehir.c
	gcc -I ./include/ -o ./lib/VeriHavuzu.o -c ./src/VeriHavuzu.c
	gcc -I ./include/ -o ./lib/Oyun.o -c ./src/Oyun.c
	gcc -I ./include/ -o ./lib/Main.o -c ./src/Main.c
	
	gcc ./lib/Yerlesim.o ./lib/Kisi.o ./lib/Mahalle.o ./lib/Ilce.o ./lib/Sehir.o ./lib/VeriHavuzu.o ./lib/Oyun.o ./lib/Main.o -o ./bin/program.exe

calistir:
	.\bin\program.exe