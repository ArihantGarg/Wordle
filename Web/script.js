// Storing guesses and result

let guessesLog = [];

// Best guess

async function runCpp(req, res) {
    try {
        const queryParam = encodeURIComponent(JSON.stringify(guessesLog));
        const response = await fetch('http://localhost:3000/runCpp?guesses=' + queryParam);
        await new Promise(resolve => setTimeout(resolve, 1000));
        if (!response.ok) {
            throw new Error(`HTTP error! status: ${response.status}`);
        }
    } catch (error) {
        console.error('Error running C++:', error);
        throw error; // Re-throw error to propagate it if needed
    }
}

async function fetchBestGuess() {
    try {
        const response = await fetch('http://localhost:3000/getBestGuess');
        await new Promise(resolve => setTimeout(resolve, 1000));
        if (!response.ok) {
            throw new Error(`HTTP error! status: ${response.status}`);
        }
        const data = await response.json();
        console.log("Best guess : " + data.guess.toUpperCase());
        return data.guess.toUpperCase();
    } catch (error) {
        console.error('Error fetching best guess:', error);
        throw error; // Re-throw error to propagate it if needed
    }
}

// async function compute() {
//     try {
//         await runCpp(); // Wait for C++ computation to finish
//         await fetchBestGuess(); // After C++ computation, fetch best guess
//     } catch (error) {
//         console.error('Main process error:', error);
//         throw error; // Re-throw error to propagate it if needed
//     }
// }




// Define the function to fetch a random word from the server
async function fetchRandomWord() {
    try {
        const response = await fetch('http://localhost:3000/random-word');
        if (!response.ok) {
            throw new Error(`HTTP error! status: ${response.status}`);
        }
        const data = await response.json();
        return data.word.toUpperCase();
    } catch (error) {
        console.error('Error fetching random word:', error);
    }
}

async function checkValidWord(guessedWord) {
    try {
        const response = await fetch(`http://localhost:3000/check-word?word=${guessedWord}`);
        if (!response.ok) {
            throw new Error(`HTTP error! status: ${response.status}`);
        }

        const data = await response.json();
        return data.isValid;
    }
    catch (error) {
        console.error('Error checking valid word:', error);
    }
}

let gameEnded = false;


document.addEventListener("DOMContentLoaded", async () => {
    const board = document.getElementById('board');
    const keyboard = document.getElementById('keyboard');
    const rows = 6;
    const cols = 5;
    const targetWord = await fetchRandomWord();
    let currentRow = 0;
    let currentCol = 0;
    const guesses = Array(rows).fill().map(() => Array(cols).fill(''));

    // Create game board
    for (let i = 0; i < rows * cols; i++) {
        const cell = document.createElement('div');
        board.appendChild(cell);
    }

    // Update the board display
    function updateBoard() {
        for (let r = 0; r < rows; r++) {
            for (let c = 0; c < cols; c++) {
                const cell = board.children[r * cols + c];
                cell.textContent = guesses[r][c];
            }
        }
    }

    // Check the guess against the target word
    async function checkGuess() {
        const guessedWord = guesses[currentRow].join('');
        if (guessedWord.length !== cols) return;

        // Check if the guessed word is valid, wait for promise
        const isValid = await checkValidWord(guessedWord);
        if (!isValid) {
            alert('Invalid word! Please try again.');
            return;
        }

        const targetArray = targetWord.split('');
        const guessArray = guessedWord.split('');
        const rowCells = Array.from(board.children).slice(currentRow * cols, (currentRow + 1) * cols);

        // console.log("Guess:", guessedWord);

        // Logging guess

        guessesLog[currentRow] = [guessedWord.toString().toLowerCase(), "BBBBB"];

        // Create arrays to track the status of each letter
        let targetUsed = Array(cols).fill(false);
        let guessStatus = Array(cols).fill('grey'); // Default to grey

        // First pass: mark correct letters (green)
        guessArray.forEach((letter, index) => {
            if (letter === targetArray[index]) {
                guessStatus[index] = 'green';
                targetUsed[index] = true;
                guessesLog[currentRow][1] = guessesLog[currentRow][1].substring(0, index) + 'G' + guessesLog[currentRow][1].substring(index + 1);
            }
        });

        // Second pass: mark misplaced letters (yellow) and incorrect (grey)
        guessArray.forEach((letter, index) => {
            if (guessStatus[index] !== 'green') {
                const targetIndex = targetArray.findIndex((targetLetter, targetIndex) => targetLetter === letter && !targetUsed[targetIndex]);
                if (targetIndex > -1) {
                    guessStatus[index] = 'yellow';
                    targetUsed[targetIndex] = true;
                    guessesLog[currentRow][1] = guessesLog[currentRow][1].substring(0, index) + 'Y' + guessesLog[currentRow][1].substring(index + 1);
                }
            }
        });

        // Apply colors to cells
        guessStatus.forEach((status, index) => {
            if (status === 'green') {
                rowCells[index].style.backgroundColor = '#538d4e'; // Green
            } else if (status === 'yellow') {
                rowCells[index].style.backgroundColor = '#b59f3b'; // Yellow
            } else {
                rowCells[index].style.backgroundColor = '#3a3a3c'; // Grey
            }

            // Update the keyboard colors
            updateKeyboardColor(guessArray[index], status);
        });

        // Check for win or lose condition
        if (guessedWord === targetWord) {
            setTimeout(() => alert('Congratulations! You guessed the word!'), 100);
            gameEnded = true;
        } else if (currentRow === rows - 1) {
            setTimeout(() => alert(`Game Over! The word was: ${targetWord}`), 100);
            gameEnded = true;
        } else {
            currentRow++;
            currentCol = 0;
        }
    }

    // RGB color values for comparison
    const COLORS = {
        green: 'rgb(83, 141, 78)',  // #538d4e
        yellow: 'rgb(181, 159, 59)',  // #b59f3b
        grey: 'rgb(58, 58, 60)'  // #3a3a3c
    };

    // Update the keyboard color based on the status
    function updateKeyboardColor(letter, status) {
        const buttons = document.querySelectorAll('#keyboard button');
        buttons.forEach(button => {
            if (button.textContent === letter) {
                const currentColor = window.getComputedStyle(button).backgroundColor;

                if (status === 'green' && currentColor !== COLORS.green) {
                    button.style.backgroundColor = COLORS.green;
                } else if (status === 'yellow' && currentColor !== COLORS.green && currentColor !== COLORS.yellow) {
                    button.style.backgroundColor = COLORS.yellow;
                } else if (status === 'grey' && ![COLORS.green, COLORS.yellow].includes(currentColor)) {
                    button.style.backgroundColor = COLORS.grey;
                }
            }
        });
    }

    // Handle keyboard input
    function handleKeyInput(key) {
        if (gameEnded) return;

        if (key === 'Enter') {
            checkGuess();
        } else if (key === 'Backspace' || key === '⌫') {
            if (currentCol > 0) {
                currentCol--;
                guesses[currentRow][currentCol] = '';
            }
        } else if (/^[a-zA-Z]$/.test(key)) { // Check if key is a letter
            if (currentCol < cols) {
                guesses[currentRow][currentCol] = key.toUpperCase();
                currentCol++;
            }
        }

        updateBoard();
    }

    keyboard.addEventListener('click', (event) => {
        if(gameEnded) return;
        const target = event.target;
        if (target.tagName === 'BUTTON') {
            const key = target.textContent;
            handleKeyInput(key);
        }
    });

    document.addEventListener('keydown', (event) => {
        if(gameEnded) return;
        handleKeyInput(event.key);
    });

    // Fill Best Guess button click handler
    const fillBestGuessButton = document.getElementById('fillBestGuess');
    fillBestGuessButton.addEventListener('click', async () => {
        if (!gameEnded) {
            try {
                // Disable button to prevent multiple clicks
                fillBestGuessButton.disabled = true;
                fillBestGuessButton.style.backgroundColor = '#3a3a3c'; // Grey

                // Ensure C++ computation is completed
                await runCpp();
                
                // Now fetch the best guess
                const bestGuess = await fetchBestGuess();
                
                if (bestGuess) {
                    guesses[currentRow] = bestGuess.split('');
                    updateBoard();
                    await checkGuess(); // Wait for checkGuess to finish
                }
            } catch (error) {
                console.error('Error filling best guess:', error);
            } finally {
                // Enable button after async operations complete (success or error)
                fillBestGuessButton.disabled = false;
                fillBestGuessButton.style.backgroundColor = '#538d4e'; // Green
            }
        }
    });


    // New Game button click handler
    const newGameButton = document.getElementById('newGame');
    newGameButton.addEventListener('click', () => {
        window.location.reload();
    });

    updateBoard();
});
