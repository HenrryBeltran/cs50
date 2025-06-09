export function moveCursorNextCharacter(cursorState) {
  cursorState.charIndex++;
  cursorState.totalIndex++;
}

export function moveCursorPreviousCharacter(cursorState, words) {
  if (cursorState.wordIndex === 0 && cursorState.charIndex === 0) return;

  if (cursorState.charIndex === 0) {
    cursorState.wordIndex--;
    cursorState.totalIndex--;
    cursorState.charIndex =
      words.children[cursorState.wordIndex].children.length;
    return;
  }

  cursorState.totalIndex--;
  cursorState.charIndex--;
}

export function jumpCursorToNextWord(cursorState, words) {
  if (cursorState.charIndex === 0) return;

  const currentLetter =
    words.children[cursorState.wordIndex].children[cursorState.charIndex];
  if (currentLetter !== undefined) {
    cursorState.incorrectCharacters++;
  }

  cursorState.wordIndex++;
  cursorState.totalIndex++;
  cursorState.charIndex = 0;
}

export function jumpCursorAtWordStart(cursorState, words) {
  if (cursorState.wordIndex === 0 && cursorState.charIndex === 0) return;

  if (cursorState.charIndex !== 0) {
    cursorState.totalIndex -=
      words.children[cursorState.wordIndex].children.length;
    cursorState.charIndex = 0;
    return;
  }

  cursorState.wordIndex--;
  cursorState.charIndex = 0;
}

export function increaseIncorrectCharacters(cursorState, words) {
  const letter =
    words.children[cursorState.wordIndex].children[cursorState.charIndex - 1];
  if (letter.classList.contains("wrong")) {
    cursorState.incorrectCharacters++;
  }
}

export function setCurrentLineIndex(
  cursorState,
  listOfWords,
  setLastIndex = false,
) {
  cursorState.lineIndex = listOfWords[cursorState.wordIndex].lineIndex;
  if (setLastIndex) {
    cursorState.lastLineIndex = listOfWords[cursorState.wordIndex].lineIndex;
  }
}

export function simulateWordsFromSpace(cursorState, listOfWords, words) {
  const wordsWidth = words.getBoundingClientRect().width;
  const wordsChildren = words.children;
  const wordsLength = wordsChildren.length;
  const startIndex =
    cursorState.numberOfNewWords > 0
      ? wordsChildren.length - cursorState.numberOfNewWords
      : 0;

  let wordByWordSize = 0;
  let wordIndexByLine = 0;
  // console.log(wordsWidth, wordsChildren[0]);

  console.log("sim - new words ->", cursorState.numberOfNewWords);
  for (let i = startIndex; i < wordsLength; i++) {
    // but i starts at 5
    // I need the index 20
    const word = wordsChildren[i];
    const wordRect = word.getBoundingClientRect();
    const simulateAddedWord = wordByWordSize + wordRect.width;

    // console.log(`child [${i}]: ${wordRect.width} - ${simulateAddedWord}`);

    if (simulateAddedWord <= wordsWidth) {
      wordByWordSize = simulateAddedWord;

      // console.log(`[${cursorState.numberOfLines}][${wordIndexByLine}]`);
      // if (!listOfWords[cursorState.numberOfLines]) {
      //   listOfWords[cursorState.numberOfLines] = [];
      // }

      // listOfWords[cursorState.numberOfLines][wordIndexByLine] = word;
      listOfWords.push({ lineIndex: cursorState.numberOfLines, word });
      wordIndexByLine++;

      if (i === wordsLength - 1) {
        cursorState.numberOfLines++;
      }
      continue;
    }
    // console.log("new line on:", word);

    i--;
    cursorState.numberOfLines++;
    wordIndexByLine = 0;
    wordByWordSize = 0;
  }

  console.log("List of words", listOfWords);
  console.log(cursorState.numberOfLines, wordByWordSize);
}
