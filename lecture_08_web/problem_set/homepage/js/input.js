import {
  increaseIncorrectCharacters,
  jumpCursorAtWordStart,
  jumpCursorToNextWord,
  moveCursorNextCharacter,
  moveCursorPreviousCharacter,
  setCurrentLineIndex,
  simulateWordsFromSpace,
} from "./cursor.js";
import { getCombo } from "./helpers.js";
import {
  checkWordSpelling,
  generateNewWords,
  renderCursor,
  renderNewCharacter,
  renderOnDeleteCharacter,
  renderOnDeleteWord,
  renderWordsLineHeight,
  repositionInputElement,
} from "./render.js";

export function setInputListeners(
  words,
  inputElement,
  caretElement,
  inputHandlers,
  listOfWords,
  cursorState,
  testState,
  lastKey,
) {
  words.addEventListener("click", () => {
    inputElement.focus();
    caretElement.classList.add("focus");
  });

  window.addEventListener("resize", () => {
    repositionInputElement(words, inputElement);
    renderWordsLineHeight(cursorState, words);
    // There are duplicates on resize should be a cleaning first;
    simulateWordsFromSpace(cursorState, listOfWords, words);
    renderCursor(caretElement, cursorState, words);
  });

  inputElement.addEventListener("focus", () => {
    caretElement.classList.add("focus");
  });

  inputElement.addEventListener("blur", () => {
    caretElement.classList.remove("focus");
  });

  inputElement.addEventListener("keydown", (event) => {
    lastKey.key = event.key;
    lastKey.keyCode = event.keyCode;
    lastKey.ctrl = event.ctrlKey;
    lastKey.shift = event.shiftKey;
    lastKey.alt = event.altKey;

    const combo = getCombo(event);
    const handler = inputHandlers[combo] || inputHandlers.default;

    handler(event.key);
    console.log("key -> ", event.key);
    console.log(JSON.stringify(cursorState, null, 2));
    renderCursor(caretElement, cursorState, words);

    checkWordSpelling(cursorState, words);

    if (!testState.isRunning && event.key.length === 1 && event.key !== " ") {
      testState.isRunning = true;
      testState.startTime = performance.now();
      testState.startTest();
    }
  });
}

export function setInputHandlers(
  data,
  inputHandlers,
  words,
  inputElement,
  listOfWords,
  cursorState,
  increaseWordsBy,
) {
  inputHandlers.default = (value) => {
    if (value.length !== 1) return;

    moveCursorNextCharacter(cursorState);

    renderNewCharacter(value, cursorState, words);

    increaseIncorrectCharacters(cursorState, words);
  };

  inputHandlers.space = () => {
    jumpCursorToNextWord(cursorState, words);
    setCurrentLineIndex(cursorState, listOfWords, true);

    renderWordsLineHeight(cursorState, words);

    const wordsDistance = cursorState.numberOfWords * 0.5;
    if (cursorState.wordIndex >= wordsDistance) {
      generateNewWords(data, increaseWordsBy, cursorState, words, false);
      simulateWordsFromSpace(cursorState, listOfWords, words);
    }
  };

  inputHandlers.backspace = () => {
    moveCursorPreviousCharacter(cursorState, words);
    setCurrentLineIndex(cursorState, listOfWords);

    renderOnDeleteCharacter(cursorState, words);
  };

  inputHandlers.altBackspace = () => {
    jumpCursorAtWordStart(cursorState, words);

    renderOnDeleteWord(cursorState, words, inputElement);
  };

  inputHandlers.controlBackspace = inputHandlers.altBackspace;

  inputHandlers.metaBackspace = inputHandlers.altBackspace;
}
