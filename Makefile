.SILENT:

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
	@for i in $$(seq 1 $(NUM_ITERATIONS4)); do \
		echo $$i; \
		g++ Game/optimisedWordleBot2.cpp -o Executables/optimisedWordleBot2; \
		./Executables/optimisedWordleBot2 $$i; \
	done
	$(MAKE) cleanExecutables

guess:
	g++ Game/getBestGuess.cpp -o Executables/getBestGuess
	./Executables/getBestGuess
	$(MAKE) cleanExecutables

same:
	g++ Test/checkSame.cpp -o Executables/checkSame
	./Executables/checkSame
	$(MAKE) cleanExecutables