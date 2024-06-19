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
	@rm Executables/*

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

bot:
	g++ Game/optimisedWordleBot.cpp -o Executables/optimisedWordleBot
	./Executables/optimisedWordleBot
	$(MAKE) cleanExecutables

# Define a variable for the number of iterations
NUM_ITERATIONS2 := 500

# Define a target that runs the command `NUM_ITERATIONS` times
run_bot_multiple_times:
	@for i in $$(seq 1 $(NUM_ITERATIONS2)); do \
			$(MAKE) bot; \
	done

fails:
	g++ Test/calculateFails.cpp -o Executables/calculateFails
	./Executables/calculateFails
	$(MAKE) cleanExecutables

start:
	g++ Game/optimisedWordleBot2.cpp -o Executables/optimisedWordleBot2
	./Executables/optimisedWordleBot2
	$(MAKE) cleanExecutables

# Define a variable for the number of iterations
NUM_ITERATIONS3 := 100

# Define a target that runs the command `NUM_ITERATIONS` times
run_start_multiple_times:
	@for i in $$(seq 1 $(NUM_ITERATIONS3)); do \
			$(MAKE) start; \
	done

# Define a variable for the number of iterations
NUM_ITERATIONS4 := 2315

# Define a target that runs the command `NUM_ITERATIONS` times
start_all:
	@for i in $$(seq 1454 $(NUM_ITERATIONS4)); do \
		echo $$i; \
		g++ Game/optimisedWordleBot2.cpp -o Executables/optimisedWordleBot2; \
		./Executables/optimisedWordleBot2 $$i; \
	done
	$(MAKE) cleanExecutables