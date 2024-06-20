const express = require('express');
const fs = require('fs');
const cors = require('cors'); // Import cors package
const app = express();
const port = 3000;

// Load the list of valid words
const validAnswers = fs.readFileSync('Files/validAnswers.txt', 'utf-8').trim().split(/\r?\n/).map(word => word.trim());
console.log(validAnswers);

// Use CORS middleware
app.use(cors());

app.get('/random-word', (req, res) => {
    const randomIndex = Math.floor(Math.random() * validAnswers.length);
    const randomWord = validAnswers[randomIndex];
    res.json({ word: randomWord });
});

app.listen(port, () => {
    console.log(`Server is running at http://localhost:${port}`);
});
