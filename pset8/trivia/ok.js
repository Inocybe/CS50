const wrongButtons = document.querySelectorAll("#wrong-button");
wrongButtons.forEach(button => {
    button.addEventListener("click", function() {
        let originalColor = this.style.backgroundColor;
        this.style.backgroundColor = "red";
        setTimeout(() => {
            this.style.backgroundColor = originalColor;
        }, 2000);
    });
});

const correctButtons = document.querySelectorAll("#correct-button");
correctButtons.forEach(button => {
    button.addEventListener("click", function() {
        this.style.backgroundColor = "green";
    });
});