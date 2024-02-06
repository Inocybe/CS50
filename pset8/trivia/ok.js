const buttonChangeTime = 200;

const buttons = document.querySelectorAll(".button");
buttons.forEach(button => {
    button.addEventListener("click", function() {
        let originalColor = this.style.backgroundColor;
        if (this.id == "correct-button") {
            this.style.backgroundColor = "green";
        } else {
            this.style.backgroundColor = "red";
        }
        this.disabled = true;
        setTimeout(() => {
            this.style.backgroundColor = originalColor;
            this.disabled = false;
        }, buttonChangeTime);
    });
});

function checkAnswer() {
    var answer = document.getElementById("userAnswer").value;
    var correctAnswer = "Three";
    var button = document.getElementById("submitButton");
    var result = document.getElementById("result");

    if (answer === correctAnswer) {
      button.style.backgroundColor = "green";
      result.textContent = "Correct!";
    } else {
      button.style.backgroundColor = "red"; // Optional: Change color to red for incorrect answers
      result.textContent = "Try again.";
    }
  }