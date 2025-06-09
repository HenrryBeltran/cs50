import { simulateWordsFromSpace } from "./cursor.js";
import {
  formatClockTimeFromPerf,
  getAccuracy,
  getCorrectWords,
  getRawWPM,
  getWPM,
} from "./helpers.js";
import { setInputHandlers, setInputListeners } from "./input.js";
import {
  generateNewWords,
  renderCursor,
  repositionInputElement,
} from "./render.js";

// TODO: Assemble all the parts to get this baby going.

// TODO ✅: Bug when trying to delete a whole word (alt+backspace) when the word has extra letters (wrong typed).
// TODO ✅: Try to pass the elements for the parameters to cache the much as possible.
// TODO ✅: Update cursor rendering position on resize.
// TODO ✅: Make the lines move every time you jump to the next line (determinate when is new line).
// TODO ✅: Generate new lines every time your close to the end.
// TODO ✅: Add transtion to the caret on displacement.
// TODO: Hide the input, and finish the UI and restart feature (the button below).
// TODO ✅: Check the raw speed, wpm (words mode) and accuracy.
// TODO ✅: Add a counter.
// TODO ⏳: Display and save the results on local storage.
// TODO: Finish the last pages.
// TODO: Fix lines going up when you are deleting the words.

// Init data
const counter = document.querySelector("#counter");
const words = document.querySelector(".words");
const inputElement = document.querySelector("#typing-input");
const caretElement = document.querySelector("#caret");

const listOfWords = [];
const cursorState = {
  numberOfLines: 0,
  lineIndex: 0,
  lastLineIndex: 0,
  lineHeight: 0,
  numberOfWords: 0,
  numberOfNewWords: 0,
  wordIndex: 0,
  charIndex: 0,
  totalIndex: 0,
  correctWords: 0,
  incorrectCharacters: 0,
};
const testState = {
  timeoutId: null,
  startTime: null,
  endTime: null,
  startTest: (_) => { },
  isRunning: false,
  isFinished: false,
};
const inputHandlers = {
  controlBackspace: (_) => { },
  metaBackspace: (_) => { },
  altBackspace: (_) => { },
  space: (_) => { },
  backspace: (_) => { },
  default: (_) => { },
};
const lastKey = {
  key: "",
  keyCode: "",
  ctrl: "",
  shift: "",
  alt: "",
};
const initialAmountOfWords = 150;
const increaseWordsBy = 150;

const res = await fetch("/words.json");
const data = await res.json();

// Setup the test
generateNewWords(data, initialAmountOfWords, cursorState, words);
repositionInputElement(words, inputElement);
simulateWordsFromSpace(cursorState, listOfWords, words);

// Set Input
setInputListeners(
  words,
  inputElement,
  caretElement,
  inputHandlers,
  listOfWords,
  cursorState,
  testState,
  lastKey,
);
setInputHandlers(
  data,
  inputHandlers,
  words,
  inputElement,
  listOfWords,
  cursorState,
  increaseWordsBy,
);

// Initial caret rendering - calls one time to position the caret
renderCursor(caretElement, cursorState, words);

testState.startTest = () => {
  displayCounter();

  console.log("Test Started!!!", formatClockTimeFromPerf(testState.startTime));
  testState.timeoutId = setTimeout(() => {
    testState.endTime = performance.now();
    testState.isFinished = true;
    inputElement.blur();
    cursorState.correctWords = getCorrectWords(
      words,
      cursorState.numberOfWords,
    );

    localStorage.setItem(
      "WPM",
      getWPM(testState.endTime, testState.startTime, cursorState.correctWords),
    );
    localStorage.setItem(
      "rawWPM",
      getRawWPM(testState.endTime, testState.startTime, cursorState.totalIndex),
    );
    localStorage.setItem(
      "accuracy",
      getAccuracy(cursorState.totalIndex, cursorState.incorrectCharacters),
    );

    console.log("Test Ended!!!", formatClockTimeFromPerf(testState.endTime));
    console.log(JSON.stringify(cursorState, null, 2));
    console.log(
      "WPM",
      getWPM(testState.endTime, testState.startTime, cursorState.correctWords),
    );
    console.log(
      "Raw WPM",
      getRawWPM(testState.endTime, testState.startTime, cursorState.totalIndex),
    );
    console.log(
      "ACCURACY",
      getAccuracy(cursorState.totalIndex, cursorState.incorrectCharacters),
    );
  }, 60_000);
};

async function displayCounter() {
  for (let i = 60; i > 0; i--) {
    counter.innerText = i.toString();
    await new Promise((resolve) => setTimeout(resolve, 1_000));
  }
  counter.innerText = "0";
}
