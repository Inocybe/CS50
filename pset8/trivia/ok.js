const wrongButtons = document.querySelectorAll("#wrong-button");
wrongButtons.forEach(button => {
    button.addEventListener("click", function() {
        this.style.backgroundColor = "red";
    });
});

const correctButtons = document.querySelectorAll("#correct-button");
correctButtons.forEach(button => {
    button.addEventListener("click", function() {
        this.style.backgroundColor = "green";
    });
});