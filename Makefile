.SILENT:

all: main

CXX = clang++
override CXXFLAGS += -g -Wmost -Werror

SRCS = $(shell find . -name '.ccls-cache' -type d -prune -o -type f -name '*.cpp' -print | sed -e 's/ /\\ /g')
HEADERS = $(shell find . -name '.ccls-cache' -type d -prune -o -type f -name '*.h' -print)

main: $(SRCS) $(HEADERS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o "$@"

main-debug: $(SRCS) $(HEADERS)
	$(CXX) $(CXXFLAGS) -U_FORTIFY_SOURCE -O0 $(SRCS) -o "$@"

clean:
	rm -f main main-debug


# My commands


cleanExecutables:
	rm Executables/*

play:
	g++ Game/playGame.cpp -o Executables/playWordle
	./Executables/playWordle
	$(MAKE) cleanExecutables

run:
	g++ Game/wordle.cpp -o Executables/wordle
	./Executables/wordle
	$(MAKE) cleanExecutables

# Define a variable for the number of iterations
NUM_ITERATIONS := 1000

# Define a target that runs the command `NUM_ITERATIONS` times
run_command_multiple_times:
		@for i in $$(seq 1 $(NUM_ITERATIONS)); do \
				$(MAKE) run; \
		done

average:
	g++ Test/averageGuess.cpp -o Executables/averageGuess
	./Executables/averageGuess
	$(MAKE) cleanExecutables
