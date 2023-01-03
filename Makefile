FLAGS = -g -Wshadow -Winit-self -Wredundant-decls -Wcast-align -Wundef -Wfloat-equal -Winline -Wunreachable-code -Wmissing-declarations    \
		-Wmissing-include-dirs -Wswitch-enum -Wswitch-default -Weffc++ -Wmain -Wextra -Wall -g -pipe -fexceptions -Wcast-qual -Wconversion \
		-Wctor-dtor-privacy -Wempty-body -Wformat-security -Wformat=2 -Wignored-qualifiers -Wlogical-op -Wmissing-field-initializers       \
		-Wnon-virtual-dtor -Woverloaded-virtual -Wpointer-arith -Wsign-promo -Wstack-usage=8192 -Wstrict-aliasing -Wstrict-null-sentinel   \
		-Wtype-limits -Wwrite-strings -D_DEBUG


СС = g++


language:
	@ g++ $(FLAGS) src/main.cpp src/file.cpp src/back_end.cpp src/middle_end.cpp src/front_end.cpp -o do.exe

ass:
	g++ $(FLAGS) assembler/main.cpp assembler/file.cpp assembler/assembler.cpp -o ass.exe 

cpu:
	@ g++ $(FLAGS) proc/main.cpp proc/processor.cpp stack/stack.cpp stack/debug.cpp  -o cpu.exe

run: asm_run cpu_run
	./do.exe 

asm_run:
	./ass.exe asm_output.txt 

cpu_run:
	./cpu.exe