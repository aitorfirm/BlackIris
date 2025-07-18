const express = require('express');
const fs = require('fs');
const app = express();
app.use(express.json());

const KEYS_FILE = './keys.json';

function getCurrentKeys() {
    if (!fs.existsSync(KEYS_FILE)) return { aes: null, xor: null };
    const data = fs.readFileSync(KEYS_FILE);
    return JSON.parse(data);
}

app.get('/keys', (req, res) => {
    const keys = getCurrentKeys();
    res.json(keys);
});

app.post('/update', (req, res) => {
    const { aes, xor } = req.body;
    if (!aes || !xor) return res.status(400).send("Missing keys");
    fs.writeFileSync(KEYS_FILE, JSON.stringify({ aes, xor }, null, 2));
    res.send("Updated");
});

app.listen(3000, () => {
    console.log("Syrial KeyServer running on port 3000");
});
