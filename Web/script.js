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
        
        // Check if the guessed word is valid ,  wait for promise
        const isValid = await checkValidWord(guessedWord);
        if (!isValid) {
            alert('Invalid word! Please try again.');
            return;
        }

        const targetArray = targetWord.split('');
        const guessArray = guessedWord.split('');
        const rowCells = Array.from(board.children).slice(currentRow * cols, (currentRow + 1) * cols);

        console.log("Guess:", guessedWord);

        // First pass: mark correct letters
        guessArray.forEach((letter, index) => {
            if (letter === targetArray[index]) {
                rowCells[index].style.backgroundColor = '#538d4e'; // Green
                targetArray[index] = null; // Remove matched letter
                guessArray[index] = null; // Remove matched letter
            }
        });

        // Second pass: mark misplaced letters
        guessArray.forEach((letter, index) => {
            if (letter && targetArray.includes(letter)) {
                rowCells[index].style.backgroundColor = '#b59f3b'; // Yellow
                targetArray[targetArray.indexOf(letter)] = null; // Remove matched letter
            } else if (letter) {
                rowCells[index].style.backgroundColor = '#3a3a3c'; // Grey
            }
        });

        // Check for win or lose condition
        if (guessedWord === targetWord) {
            setTimeout(() => alert('Congratulations! You guessed the word!'), 100);
        } else if (currentRow === rows - 1) {
            setTimeout(() => alert(`Game Over! The word was: ${targetWord}`), 100);
        } else {
            currentRow++;
            currentCol = 0;
        }
    }

    // Handle keyboard input
    function handleKeyInput(key) {
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
        const target = event.target;
        if (target.tagName === 'BUTTON') {
            const key = target.textContent;
            handleKeyInput(key);
        }
    });

    document.addEventListener('keydown', (event) => {
        handleKeyInput(event.key);
    });

    updateBoard();
});
