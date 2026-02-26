// ── Firebase Config ──────────────────────────────────
// Replace these values with your own Firebase project config
// Get them from: Firebase Console → Project Settings → Your App → Config

export const firebaseConfig = {
    apiKey: "YOUR_API_KEY",
    authDomain: "YOUR_PROJECT.firebaseapp.com",
    projectId: "YOUR_PROJECT_ID",
    storageBucket: "YOUR_PROJECT.appspot.com",
    messagingSenderId: "YOUR_SENDER_ID",
    appId: "YOUR_APP_ID"
};

// Check if Firebase is configured
export function isFirebaseConfigured() {
    return firebaseConfig.apiKey !== "YOUR_API_KEY";
}
