// ── Main Entry Point ─────────────────────────────────
// Initializes all systems and runs the game loop

import { InputHandler } from './input.js';
import { AudioEngine } from './audio.js';
import { Renderer } from './renderer.js';
import { Game, GameState } from './game.js';
import { initAuth, registerUser, loginUser, logoutUser, getCurrentUser, onAuthChange } from './auth.js';
import { initLeaderboard, saveHighScore, getTopScores, renderLeaderboard } from './leaderboard.js';

// ── Canvas Setup ──
const canvas = document.getElementById('gameCanvas');
const GAME_WIDTH = 800;
const GAME_HEIGHT = 600;
canvas.width = GAME_WIDTH;
canvas.height = GAME_HEIGHT;

// ── Systems ──
const input = new InputHandler(canvas);
const audio = new AudioEngine();
const renderer = new Renderer(canvas);
const game = new Game(GAME_WIDTH, GAME_HEIGHT, audio);

// Store mouse position on canvas for crosshair
canvas.addEventListener('mousemove', (e) => {
    const rect = canvas.getBoundingClientRect();
    const scaleX = canvas.width / rect.width;
    const scaleY = canvas.height / rect.height;
    canvas._mouseX = (e.clientX - rect.left) * scaleX;
    canvas._mouseY = (e.clientY - rect.top) * scaleY;
});

// ── Auth UI ──
const authModal = document.getElementById('authModal');
const loginForm = document.getElementById('loginForm');
const registerForm = document.getElementById('registerForm');
const showRegisterBtn = document.getElementById('showRegister');
const showLoginBtn = document.getElementById('showLogin');
const authError = document.getElementById('authError');
const userInfo = document.getElementById('userInfo');
const userName = document.getElementById('userName');
const logoutBtn = document.getElementById('logoutBtn');
const guestBtn = document.getElementById('guestBtn');
const loginBtn = document.getElementById('loginBtn');
const leaderboardPanel = document.getElementById('leaderboardPanel');
const leaderboardContent = document.getElementById('leaderboardContent');
const toggleLeaderboard = document.getElementById('toggleLeaderboard');
const soundToggle = document.getElementById('soundToggle');

// Toggle forms
showRegisterBtn?.addEventListener('click', () => {
    loginForm.classList.add('hidden');
    registerForm.classList.remove('hidden');
    authError.textContent = '';
});

showLoginBtn?.addEventListener('click', () => {
    registerForm.classList.add('hidden');
    loginForm.classList.remove('hidden');
    authError.textContent = '';
});

// Register
registerForm?.addEventListener('submit', async (e) => {
    e.preventDefault();
    const name = document.getElementById('regName').value.trim();
    const email = document.getElementById('regEmail').value.trim();
    const password = document.getElementById('regPassword').value;
    authError.textContent = '';

    try {
        await registerUser(email, password, name);
        authModal.classList.add('hidden');
    } catch (err) {
        authError.textContent = err.message;
    }
});

// Login
loginForm?.addEventListener('submit', async (e) => {
    e.preventDefault();
    const email = document.getElementById('loginEmail').value.trim();
    const password = document.getElementById('loginPassword').value;
    authError.textContent = '';

    try {
        await loginUser(email, password);
        authModal.classList.add('hidden');
    } catch (err) {
        authError.textContent = err.message;
    }
});

// Guest mode
guestBtn?.addEventListener('click', () => {
    authModal.classList.add('hidden');
    userName.textContent = 'GUEST';
    userInfo.classList.remove('hidden');
    loginBtn.classList.add('hidden');
});

// Logout
logoutBtn?.addEventListener('click', async () => {
    await logoutUser();
    userInfo.classList.add('hidden');
    loginBtn.classList.remove('hidden');
});

// Login button (re-open modal)
loginBtn?.addEventListener('click', () => {
    authModal.classList.remove('hidden');
    loginForm.classList.remove('hidden');
    registerForm.classList.add('hidden');
});

// Auth state changes
onAuthChange((user) => {
    if (user) {
        userName.textContent = user.displayName || user.email;
        userInfo.classList.remove('hidden');
        loginBtn.classList.add('hidden');
        authModal.classList.add('hidden');
    } else {
        userInfo.classList.add('hidden');
        loginBtn.classList.remove('hidden');
    }
});

// Leaderboard toggle
toggleLeaderboard?.addEventListener('click', async () => {
    leaderboardPanel.classList.toggle('hidden');
    if (!leaderboardPanel.classList.contains('hidden')) {
        const scores = await getTopScores(10);
        renderLeaderboard(scores, leaderboardContent);
    }
});

// Sound toggle
soundToggle?.addEventListener('click', () => {
    const on = audio.toggle();
    soundToggle.textContent = on ? '🔊' : '🔇';
});

// ── Watch for game over to save score ──
let lastState = null;

// ── Game Loop ──
let lastTime = 0;

function gameLoop(timestamp) {
    const dt = Math.min((timestamp - lastTime) / 1000, 0.05); // cap delta
    lastTime = timestamp;

    // Detect state transition to game over
    if (game.state === GameState.GAME_OVER && lastState !== GameState.GAME_OVER) {
        const user = getCurrentUser();
        if (user) {
            saveHighScore(user.uid, user.displayName || user.email, game.score);
        } else {
            // Save as guest to local
            saveHighScore('guest', 'GUEST', game.score);
        }
        // Refresh leaderboard if visible
        if (!leaderboardPanel.classList.contains('hidden')) {
            getTopScores(10).then(scores => renderLeaderboard(scores, leaderboardContent));
        }
    }
    lastState = game.state;

    renderer.clear();
    renderer.applyShake(dt);
    game.update(dt, input, renderer);
    game.draw(renderer);
    renderer.endShake();

    input.resetFrame();
    requestAnimationFrame(gameLoop);
}

// ── Initialize ──
async function init() {
    await initAuth();
    await initLeaderboard();
    // Show auth modal only if Firebase is configured
    const { isFirebaseConfigured } = await import('./config.js');
    if (!isFirebaseConfigured()) {
        authModal.classList.add('hidden');
        userName.textContent = 'GUEST';
        userInfo.classList.remove('hidden');
        loginBtn.classList.add('hidden');
    }
    // Load initial leaderboard
    const scores = await getTopScores(10);
    renderLeaderboard(scores, leaderboardContent);

    requestAnimationFrame(gameLoop);
}

init();
