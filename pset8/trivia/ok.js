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