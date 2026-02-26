// ── Leaderboard ──────────────────────────────────────
// High score storage and display using Firestore

import { isFirebaseConfigured } from './config.js';

let db = null;
let firestoreReady = false;

// Local fallback leaderboard when Firebase is not configured
let localScores = [];

export async function initLeaderboard() {
    if (!isFirebaseConfigured()) {
        console.warn('[Leaderboard] Firebase not configured. Using local storage.');
        _loadLocalScores();
        return;
    }

    try {
        const { getApp } = await import('https://www.gstatic.com/firebasejs/10.12.0/firebase-app.js');
        const { getFirestore } = await import('https://www.gstatic.com/firebasejs/10.12.0/firebase-firestore.js');
        db = getFirestore(getApp());
        firestoreReady = true;
    } catch (err) {
        console.error('[Leaderboard] Failed to initialize Firestore:', err);
    }
}

export async function saveHighScore(userId, displayName, score) {
    if (!firestoreReady) {
        _saveLocalScore(displayName || 'GUEST', score);
        return;
    }

    try {
        const { doc, getDoc, setDoc, serverTimestamp } = await import('https://www.gstatic.com/firebasejs/10.12.0/firebase-firestore.js');

        const ref = doc(db, 'highscores', userId);
        const existing = await getDoc(ref);

        if (!existing.exists() || existing.data().score < score) {
            await setDoc(ref, {
                displayName: displayName || 'Anonymous',
                score: score,
                updatedAt: serverTimestamp()
            });
        }
    } catch (err) {
        console.error('[Leaderboard] Failed to save score:', err);
        _saveLocalScore(displayName || 'GUEST', score);
    }
}

export async function getTopScores(limit = 10) {
    if (!firestoreReady) {
        return _getLocalScores(limit);
    }

    try {
        const { collection, query, orderBy, limit: firestoreLimit, getDocs } = await import('https://www.gstatic.com/firebasejs/10.12.0/firebase-firestore.js');

        const q = query(
            collection(db, 'highscores'),
            orderBy('score', 'desc'),
            firestoreLimit(limit)
        );
        const snap = await getDocs(q);
        return snap.docs.map((doc, i) => ({
            rank: i + 1,
            name: doc.data().displayName,
            score: doc.data().score
        }));
    } catch (err) {
        console.error('[Leaderboard] Failed to fetch scores:', err);
        return _getLocalScores(limit);
    }
}

// ── Local Storage Fallback ──

function _loadLocalScores() {
    try {
        const saved = localStorage.getItem('pixelblaster_scores');
        localScores = saved ? JSON.parse(saved) : [];
    } catch {
        localScores = [];
    }
}

function _saveLocalScore(name, score) {
    _loadLocalScores();
    const existing = localScores.find(s => s.name === name);
    if (existing) {
        if (score > existing.score) existing.score = score;
    } else {
        localScores.push({ name, score });
    }
    localScores.sort((a, b) => b.score - a.score);
    localScores = localScores.slice(0, 20);
    localStorage.setItem('pixelblaster_scores', JSON.stringify(localScores));
}

function _getLocalScores(limit) {
    _loadLocalScores();
    return localScores.slice(0, limit).map((s, i) => ({
        rank: i + 1,
        name: s.name,
        score: s.score
    }));
}

// ── Render Leaderboard to DOM ──

export function renderLeaderboard(scores, containerEl) {
    if (!containerEl) return;

    if (scores.length === 0) {
        containerEl.innerHTML = '<p class="lb-empty">No scores yet. Be the first!</p>';
        return;
    }

    let html = '<table class="lb-table"><thead><tr><th>#</th><th>PLAYER</th><th>SCORE</th></tr></thead><tbody>';
    scores.forEach(s => {
        const medal = s.rank === 1 ? '🥇' : s.rank === 2 ? '🥈' : s.rank === 3 ? '🥉' : s.rank;
        html += `<tr class="${s.rank <= 3 ? 'lb-top' : ''}"><td>${medal}</td><td>${_escapeHtml(s.name)}</td><td>${s.score.toLocaleString()}</td></tr>`;
    });
    html += '</tbody></table>';
    containerEl.innerHTML = html;
}

function _escapeHtml(str) {
    const div = document.createElement('div');
    div.textContent = str;
    return div.innerHTML;
}
