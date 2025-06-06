// Init data
const words = document.querySelector(".words");
const inputElement = document.querySelector("#typing-input");

const listOfWords = [];
const inputHandlers = {
  controlBackspace: (_) => { },
  metaBackspace: (_) => { },
  altBackspace: (_) => { },
  space: (_) => { },
  backspace: (_) => { },
  default: (_) => { },
};

let wordsCount = 0;
let lettersCount = 0;
let lettersCountByCurrentWord = 0;
let lastKey;

const res = await fetch("/words.json");
const data = await res.json();

// Setup the test
generateNewWords();
words.addEventListener("click", () => inputElement.focus());

// Listening for keydown values, and building key combos for the 'inputHandlers'
inputElement.addEventListener("keydown", (event) => {
  lastKey = {
    key: event.key,
    keyCode: event.keyCode,
    ctrl: event.ctrlKey,
    shift: event.shiftKey,
    alt: event.altKey,
  };

  let combo = "";
  if (event.ctrlKey) combo += "control";
  if (event.metaKey) combo += "meta";
  if (event.shiftKey) combo += "shift";
  if (event.altKey) combo += "alt";

  inputElement.addEventListener("keyup", restartCombo);
  inputElement.removeEventListener("keyup", restartCombo);

  function restartCombo() {
    if (combo.length > 0) {
      combo = "";
    }
  }

  if (event.key === " ") combo = "space";
  else if (event.key === "Backspace") combo = "backspace";
  else combo += event.key;

  const handler = inputHandlers[combo] || inputHandlers.default;
  handler(event.key);

  console.log("~ words count", wordsCount);
  console.log("~ letters count", lettersCount);
  console.log("~ letters count by current word", lettersCountByCurrentWord);
});

// Input handlers running the main logic
inputHandlers.metaBackspace = () => {
  console.log("~ Meta + Backspace");
  wordsCount = 0;
  lettersCount = 0;
  lettersCountByCurrentWord = 0;
};

inputHandlers.controlBackspace = inputHandlers.metaBackspace;

inputHandlers.altBackspace = () => {
  console.log("~ Alt + Backspace");
  if (wordsCount !== 0) wordsCount--;
  lettersCountByCurrentWord = 0;
};

inputHandlers.backspace = () => {
  console.log("~ Backspace");
  if (lettersCount !== 0) lettersCount--;
  if (lettersCountByCurrentWord !== 0) lettersCountByCurrentWord--;
};

inputHandlers.space = () => {
  console.log("~ Space");
  wordsCount++;
  lettersCountByCurrentWord = 0;
};

inputHandlers.default = (value) => {
  if (value.length !== 1) {
    return;
  }

  console.log("~ Default", value);
  lettersCount++;
  lettersCountByCurrentWord++;

  const currentLetterElement =
    words.childNodes[wordsCount].childNodes[lettersCountByCurrentWord - 1];

  if (currentLetterElement !== undefined) {
    if (currentLetterElement.textContent === value) {
      currentLetterElement.classList.add("typed");
    } else {
      currentLetterElement.classList.add("wrong");
    }
  } else {
    const newLetterElement = document.createElement("letter");
    newLetterElement.innerText = value;
    newLetterElement.classList.add("wrong");

    const previusLetterElement =
      words.childNodes[wordsCount].childNodes[lettersCountByCurrentWord - 2];
    previusLetterElement.parentNode.insertBefore(
      newLetterElement,
      previusLetterElement.nextSibling,
    );
  }
  console.log("->", currentLetterElement);
};

// Abstracting some logic
function generateNewWords() {
  for (let i = 0; i < 50; i++) {
    const randomIndex = Math.floor(Math.random() * 250);
    listOfWords.push(data[randomIndex]);
  }

  listOfWords.forEach((word) => {
    const wordElement = document.createElement("word");

    word.split("").forEach((letter) => {
      const letterElement = document.createElement("letter");
      letterElement.innerText = letter;
      wordElement.append(letterElement);
    });

    words.append(wordElement);
  });
}
