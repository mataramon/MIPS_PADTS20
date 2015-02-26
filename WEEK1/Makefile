all:
	g++ -Wall -m32 -g -c -std=c++11 elf_reader.cpp
	g++ -Wall -m32 -g -c -std=c++11 platform_mips.cpp
	g++ -Wall -m32 -g -c -std=c++11 mips32.cpp
	g++ -Wall -m32 -std=c++11 elf_reader.o platform_mips.o mips32.o main.cpp  -o platform

clean:
	rm -rf platform *o
