// ── Input Handler ──────────────────────────────────────
// Tracks keyboard and mouse state for the game

export class InputHandler {
    constructor(canvas) {
        this.canvas = canvas;
        this.keys = {};
        this.mouse = { x: 0, y: 0, clicked: false, down: false };

        // Keyboard
        window.addEventListener('keydown', (e) => {
            this.keys[e.key.toLowerCase()] = true;
            // Prevent scrolling with game keys
            if (['w', 'a', 's', 'd', ' ', 'arrowup', 'arrowdown', 'arrowleft', 'arrowright'].includes(e.key.toLowerCase())) {
                e.preventDefault();
            }
        });

        window.addEventListener('keyup', (e) => {
            this.keys[e.key.toLowerCase()] = false;
        });

        // Mouse
        canvas.addEventListener('mousemove', (e) => {
            const rect = canvas.getBoundingClientRect();
            const scaleX = canvas.width / rect.width;
            const scaleY = canvas.height / rect.height;
            this.mouse.x = (e.clientX - rect.left) * scaleX;
            this.mouse.y = (e.clientY - rect.top) * scaleY;
        });

        canvas.addEventListener('mousedown', (e) => {
            if (e.button === 0) {
                this.mouse.down = true;
                this.mouse.clicked = true;
            }
        });

        canvas.addEventListener('mouseup', (e) => {
            if (e.button === 0) {
                this.mouse.down = false;
            }
        });

        // Prevent context menu on right-click
        canvas.addEventListener('contextmenu', (e) => e.preventDefault());
    }

    isKeyDown(key) {
        return this.keys[key.toLowerCase()] || false;
    }

    consumeClick() {
        if (this.mouse.clicked) {
            this.mouse.clicked = false;
            return true;
        }
        return false;
    }

    resetFrame() {
        this.mouse.clicked = false;
    }
}
