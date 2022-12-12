FLAGS = -g -Wshadow -Winit-self -Wredundant-decls -Wcast-align -Wundef -Wfloat-equal -Winline -Wunreachable-code -Wmissing-declarations    \
		-Wmissing-include-dirs -Wswitch-enum -Wswitch-default -Weffc++ -Wmain -Wextra -Wall -g -pipe -fexceptions -Wcast-qual -Wconversion \
		-Wctor-dtor-privacy -Wempty-body -Wformat-security -Wformat=2 -Wignored-qualifiers -Wlogical-op -Wmissing-field-initializers       \
		-Wnon-virtual-dtor -Woverloaded-virtual -Wpointer-arith -Wsign-promo -Wstack-usage=8192 -Wstrict-aliasing -Wstrict-null-sentinel   \
		-Wtype-limits -Wwrite-strings -D_DEBUG
СС = g++

ass:
	@$(СС) $(FLAGS) assembler/main.cpp assembler/file.cpp assembler/assembler.cpp -o ass.exe 
cpu:
	@$(СС) $(FLAGS) proc/main.cpp proc/processor.cpp stack/stack.cpp stack/debug.cpp  -o cpu.exe 
disass:
	@$(СС) $(FLAGS) disassembler/main.cpp assembler/file.cpp disassembler/disassembler.cpp -o disass.exe
