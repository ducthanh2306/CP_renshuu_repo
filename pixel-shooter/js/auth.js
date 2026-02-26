// ── Authentication ───────────────────────────────────
// Firebase Auth: register, login, logout, state management

import { firebaseConfig, isFirebaseConfigured } from './config.js';

let auth = null;
let currentUser = null;
let onAuthChangeCallback = null;

export async function initAuth() {
    if (!isFirebaseConfigured()) {
        console.warn('[Auth] Firebase not configured. Running in guest mode.');
        _notifyAuthChange(null);
        return;
    }

    try {
        const { initializeApp } = await import('https://www.gstatic.com/firebasejs/10.12.0/firebase-app.js');
        const { getAuth, onAuthStateChanged } = await import('https://www.gstatic.com/firebasejs/10.12.0/firebase-auth.js');

        const app = initializeApp(firebaseConfig);
        auth = getAuth(app);

        onAuthStateChanged(auth, (user) => {
            currentUser = user;
            _notifyAuthChange(user);
        });
    } catch (err) {
        console.error('[Auth] Failed to initialize Firebase:', err);
        _notifyAuthChange(null);
    }
}

export async function registerUser(email, password, displayName) {
    if (!auth) throw new Error('Firebase not configured');

    const { createUserWithEmailAndPassword, updateProfile } = await import('https://www.gstatic.com/firebasejs/10.12.0/firebase-auth.js');

    const cred = await createUserWithEmailAndPassword(auth, email, password);
    await updateProfile(cred.user, { displayName });
    currentUser = cred.user;
    return cred.user;
}

export async function loginUser(email, password) {
    if (!auth) throw new Error('Firebase not configured');

    const { signInWithEmailAndPassword } = await import('https://www.gstatic.com/firebasejs/10.12.0/firebase-auth.js');

    const cred = await signInWithEmailAndPassword(auth, email, password);
    currentUser = cred.user;
    return cred.user;
}

export async function logoutUser() {
    if (!auth) return;
    const { signOut } = await import('https://www.gstatic.com/firebasejs/10.12.0/firebase-auth.js');
    await signOut(auth);
    currentUser = null;
}

export function getCurrentUser() {
    return currentUser;
}

export function onAuthChange(callback) {
    onAuthChangeCallback = callback;
}

function _notifyAuthChange(user) {
    if (onAuthChangeCallback) onAuthChangeCallback(user);
}
