document.addEventListener('DOMContentLoaded', () => {
    const button = document.getElementById('action-btn');
    const message = document.getElementById('response-msg');

    button.addEventListener('click', () => {
        message.textContent = "🚀 JavaScript loaded and executing successfully!";
        message.classList.remove('hidden');

        // Optional: Log to browser console to help you debug requests
        console.log("Button clicked! Static files are serving nicely.");
    });
});