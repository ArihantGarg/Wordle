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
    res.json({ word: randomWord });
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

app.listen(port, () => {
    console.log(`Server is running at http://localhost:${port}`);
});
