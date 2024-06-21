const express = require('express');
const fs = require('fs');
const cors = require('cors'); // Import cors package
const app = express();
const port = 3000;

// Load the list of valid words
const validAnswers = fs.readFileSync('Files/validAnswers.txt', 'utf-8').trim().split(/\r?\n/).map(word => word.trim());
const validWords = fs.readFileSync('Files/allWords.txt', 'utf-8').trim().split(/\r?\n/).map(word => word.trim());
// console.log(validWords);

// Use CORS middleware
app.use(cors());

app.get('/random-word', (req, res) => {
    const randomIndex = Math.floor(Math.random() * validAnswers.length);
    const randomWord = validAnswers[randomIndex];
    // const randomWord = 'rover'; // Hardcoded word for testing
    res.json({ word: randomWord });
    console.log(`Random word: ${randomWord}`);
});

app.get('/check-word', (req, res) => {
    const word = req.query.word.toLowerCase();

    console.log(req.query);

    // Using binary search to check if the word is valid
    let left = 0;
    let right = validWords.length - 1;
    let isValid = false;

    while (left < right) {
        const mid = Math.floor((left + right) / 2);
        if (validWords[mid] < word) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }

    if (validWords[left] === word) {
        isValid = true;
    }

    console.log(`Checking word: ${word}, isValid: ${isValid}`);

    res.json({ isValid: isValid });
});


// GET BEST GUESS

function getGuessFromFile() {
    const guess = fs.readFileSync('Files/bestGuess.txt', 'utf-8').trim();
    return guess;
}

app.get('/getBestGuess', (req, res) => {
    // console.log(req.query);
    const guess = getGuessFromFile();
    res.json({ guess: guess });
    console.log(`Best guess: ${guess}`);
});


const { exec } = require('child_process');
const path = require('path');

const cppFile = './Game/getBestGuess.cpp';
const outputFile = './Executables/getBestGuess.exe';

app.get('/runCpp', (req, res) => {
    // Check if the executable file already exists
    fs.access(outputFile, fs.constants.F_OK, (err) => {
        if (err) {
            // File does not exist, compile the C++ file

            console.log('Compiling C++ program...');

            exec(`g++ -o ${outputFile} ${cppFile}`, (compileError, compileStdout, compileStderr) => {
                if (compileError) {
                    console.error(`Error compiling C++ program: ${compileError.message}`);
                    res.status(500).json({ error: 'Error compiling C++ program' });
                    return;
                }

                if (compileStderr) {
                    console.error(`Compile stderr: ${compileStderr}`);
                    res.status(500).json({ error: 'Compilation error' });
                    return;
                }

                // Proceed to run the compiled executable
                runExecutable(req, res);
            });
        } else {
            // File exists, run the executable directly
            runExecutable(req, res);
        }
    });
});

function runExecutable(req, res) {
    // Get the absolute path to the executable
    const exePath = path.resolve(outputFile);

    // Example guessesLog string
    const guessesLog = req.query.guesses;

    console.log('Guesses log:', guessesLog);

    // Parse the guessesLog string into a JavaScript array
    const guesses = JSON.parse(guessesLog);

    // Construct command with arguments
    const command = `${exePath} ${guesses.map(arr => arr.join(' ')).join(' ')}`;

    console.log('Executing command:', command);

    // Run the compiled executable with arguments
    exec(command, (runError, runStdout, runStderr) => {
        if (runError) {
            console.error(`Error executing C++ program: ${runError.message}`);
            res.status(500).json({ error: 'Error executing C++ program' });
            return;
        }

        if (runStderr) {
            console.error(`Run stderr: ${runStderr}`);
            res.status(500).json({ error: 'Execution error' });
            return;
        }

        res.json({ success: true, output: runStdout });
    });
}















app.listen(port, () => {
    console.log(`Server is running at http://localhost:${port}`);
});