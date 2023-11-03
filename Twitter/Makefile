# Compiler/linker comfig and object/depfile directory:
CXX = clang++
LD = clang++
OBJS_DIR = .objs

# -MMD and -MP asks clang++ to generate a .d file listing the headers used in the source code for use in the Make process.
#   -MMD: "Write a depfile containing user headers"
#   -MP : "Create phony target for each dependency (other than main file)"
#   (https://clang.llvm.org/docs/ClangCommandLineReference.html)
DEPFILE_FLAGS = -MMD -MP -std=c++11

# Provide lots of helpful warning/errors:
WARNINGS = -pedantic -Wall -Werror -Wfatal-errors -Wextra -Wno-unused-parameter -Wno-unused-variable -Wno-unused-function

final: main.o  Node.o PageRank.o 
	g++ main.o Node.o PageRank.o -o final -std=c++11

PageRank.o: PageRank.cpp PageRank.h
	g++ -c PageRank.cpp -std=c++11

Node.o: Node.cpp Node.h
	g++ -c Node.cpp -std=c++11

main.o: main.cpp PageRank.h Node.h 
	g++ -c main.cpp -std=c++11

clean:
	rm *.o final
