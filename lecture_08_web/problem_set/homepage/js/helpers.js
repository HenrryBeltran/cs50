export function getCombo(event) {
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

export function getCorrectWords(words, wordsLength) {
  let correctWords = 0;
  for (let i = 0; i < wordsLength; i++) {
    const word = words.children[i];
    const classes = word.classList;
    if (classes.contains("completed") && !classes.contains("wrong")) {
      correctWords++;
    }
  }
  return correctWords;
}

export function getWPM(endTime, startTime, correctWords) {
  const elapsedTimeInSeconds = (endTime - startTime) / 1000;
  return (correctWords / elapsedTimeInSeconds) * 60;
}

export function getRawWPM(endTime, startTime, totalIndex) {
  const elapsedTimeInSeconds = (endTime - startTime) / 1000;
  return totalIndex / 5 / (elapsedTimeInSeconds / 60);
}

export function getAccuracy(totalIndex, incorrectCharacters) {
  const correctCharacters = totalIndex - incorrectCharacters;
  const accuracy = (correctCharacters / totalIndex) * 100;
  return accuracy.toFixed(2);
}

// Timestamp formatter - DEBUGGING PORPOSES
export function formatClockTimeFromPerf(perfNow) {
  const baseTime = Date.now();
  const estimatedTime = new Date(baseTime - performance.now() + perfNow);

  const hours = String(estimatedTime.getHours()).padStart(2, "0");
  const minutes = String(estimatedTime.getMinutes()).padStart(2, "0");
  const seconds = String(estimatedTime.getSeconds()).padStart(2, "0");
  const millis = String(estimatedTime.getMilliseconds()).padStart(3, "0");

  return `${hours}:${minutes}:${seconds}.${millis}`;
}
