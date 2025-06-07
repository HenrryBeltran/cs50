// Init data
const words = document.querySelector(".words");
const inputElement = document.querySelector("#typing-input");
const caretElement = document.querySelector("#caret");

const listOfWords = [];
const cursorState = {
  wordIndex: 0,
  charIndex: 0,
  totalIndex: 0,
  correctWords: 0,
};
const testState = {
  startTime: null,
  isRunning: false,
  isFinished: false,
};
const inputHandlers = {
  controlBackspace: (_) => {},
  metaBackspace: (_) => {},
  altBackspace: (_) => {},
  space: (_) => {},
  backspace: (_) => {},
  default: (_) => {},
};

let wordsCount = 0;
let lettersCount = 0;
let lettersCountByCurrentWord = 0;
let lastKey;

const res = await fetch("/words.json");
const data = await res.json();

// Setup the test
generateNewWords();

words.addEventListener("click", () => {
  inputElement.focus();
  caretElement.classList.add("focus");
});

inputElement.addEventListener("blur", () => {
  caretElement.classList.remove("focus");
});

// Listening for keydown values, and building key combos for the 'inputHandlers'
inputElement.addEventListener("keydown", (event) => {
  lastKey = {
    key: event.key,
    keyCode: event.keyCode,
    ctrl: event.ctrlKey,
    shift: event.shiftKey,
    alt: event.altKey,
  };

  const combo = getCombo(event);
  const handler = inputHandlers[combo] || inputHandlers.default;

  handler(event.key);

  console.log("key -> ", event.key);
  console.log(cursorState);

  renderCursor();
});

// TODO: Try to pass the elements for the parameters to cache the much as possible.
// TODO: Bug when trying to delete a whole word (alt+backspace) when the word has extra letters (wrong typed).
// TODO: Make the lines move every time you jump to the next line (determinate when is new line).
// TODO: Generate new lines every time your close to the end.
// TODO: Add transtion to the caret on displacement.
// TODO: Hide the input, and finish the UI and restart feature (the button below).
// TODO: Check the raw speed, wpm (words mode) and accuracy.
// TODO: Add a counter.
// TODO: Display and save the results on local storage.
// TODO: Finish the last pages.

// Input handlers running the main logic
inputHandlers.altBackspace = () => {
  jumpCursorAtWordStart();

  //  Delete word new behaviour
  const currentWord = words.childNodes[cursorState.wordIndex];
  inputElement.value = inputElement.value.slice(
    0,
    inputElement.value.length - currentWord.childNodes.length,
  );

  renderOnDeleteWord(currentWord);
};

inputHandlers.controlBackspace = inputHandlers.altBackspace;
inputHandlers.metaBackspace = inputHandlers.altBackspace;

inputHandlers.backspace = () => {
  moveCursorPreviousCharacter();
  const currentWord =
    words.childNodes[cursorState.wordIndex].childNodes[cursorState.charIndex];
  renderOnDeleteCharacter(currentWord);
};

inputHandlers.space = () => {
  jumpCursorToNextWord();
};

inputHandlers.default = (value) => {
  if (value.length !== 1) {
    return;
  }

  moveCursorNextCharacter();
  renderNewCharacter(value);
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

function getCombo(event) {
  let combo = "";

  if (event.ctrlKey) combo += "control";
  if (event.metaKey) combo += "meta";
  if (event.shiftKey) combo += "shift";
  if (event.altKey) combo += "alt";
  if (event.key === "ArrowLeft") event.preventDefault();
  if (event.key === "ArrowRight") event.preventDefault();
  if (event.key === "Backspace") {
    if (combo.length > 1) {
      event.preventDefault();
      return combo + "Backspace";
    }
    return combo + "backspace";
  }
  if (event.key === " ") {
    event.preventDefault();
    return "space";
  }

  return combo + event.key;
}

function moveCursorNextCharacter() {
  cursorState.charIndex++;
  cursorState.totalIndex++;
}

function moveCursorPreviousCharacter() {
  if (cursorState.wordIndex === 0 && cursorState.charIndex === 0) return;
  if (cursorState.charIndex === 0) {
    cursorState.wordIndex--;
    const prevWordElement = words.childNodes[cursorState.wordIndex];
    const letters = prevWordElement.querySelectorAll("letter");
    cursorState.charIndex = letters.length;
    return;
  }

  cursorState.charIndex--;
  cursorState.totalIndex--;
}

function jumpCursorToNextWord() {
  cursorState.wordIndex++;
  cursorState.charIndex = 0;
}

function jumpCursorAtWordStart() {
  if (cursorState.wordIndex === 0 && cursorState.charIndex === 0) return;

  if (cursorState.charIndex !== 0) {
    const prevWordElement = words.childNodes[cursorState.wordIndex];
    cursorState.totalIndex -= prevWordElement.childNodes.length;
    cursorState.charIndex = 0;
    return;
  }

  cursorState.wordIndex--;
  cursorState.charIndex = 0;
}

function renderCursor() {
  const currentLetterElement =
    words.childNodes[cursorState.wordIndex].childNodes[cursorState.charIndex];

  if (currentLetterElement === undefined) {
    const previousLetterElement =
      words.childNodes[cursorState.wordIndex].childNodes[
        cursorState.charIndex - 1
      ];
    const prevRect = previousLetterElement.getBoundingClientRect();
    caretElement.style.transform = `translate(${prevRect.x + prevRect.width}px, ${prevRect.y}px)`;
    return;
  }

  const rect = currentLetterElement.getBoundingClientRect();
  caretElement.style.transform = `translate(${rect.x}px, ${rect.y}px)`;

  if (cursorState.totalIndex === 1) {
    caretElement.classList.add("typing");
  }
}

function renderNewCharacter(value) {
  const previousLetterElement =
    words.childNodes[cursorState.wordIndex].childNodes[
      cursorState.charIndex - 1
    ];

  if (previousLetterElement !== undefined) {
    if (previousLetterElement.textContent === value) {
      previousLetterElement.classList.add("typed");
    } else {
      previousLetterElement.classList.add("wrong");
    }
  } else {
    const newLetterElement = document.createElement("letter");
    newLetterElement.innerText = value;
    newLetterElement.classList.add("wrong");
    newLetterElement.classList.add("extra");

    const newEl =
      words.childNodes[cursorState.wordIndex].childNodes[
        cursorState.charIndex - 2
      ];
    newEl.parentNode.insertBefore(newLetterElement, newEl.nextSibling);
  }
}

function renderOnDeleteCharacter(letterElement) {
  if (letterElement.classList.contains("extra")) {
    letterElement.remove();
    return;
  }
  letterElement.classList.remove("typed", "wrong");
}

function renderOnDeleteWord(wordElement) {
  const len = wordElement.childNodes.length;
  for (let i = 0; i < len; i++) {
    const letterElement = wordElement.childNodes[i];
    if (letterElement.classList.contains("extra")) {
      letterElement.remove();
      continue;
    }
    letterElement.classList.remove("typed", "wrong");
  }
}

// Running the 'renderCursor' one time to position the caret
renderCursor();
