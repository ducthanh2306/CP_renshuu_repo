// ── Audio Engine ──────────────────────────────────────
// Retro 8-bit sound effects using Web Audio API

export class AudioEngine {
    constructor() {
        this.ctx = null;
        this.enabled = true;
        this.musicPlaying = false;
        this.musicGain = null;
        this.musicOscillators = [];
    }

    init() {
        if (!this.ctx) {
            this.ctx = new (window.AudioContext || window.webkitAudioContext)();
        }
        if (this.ctx.state === 'suspended') {
            this.ctx.resume();
        }
    }

    toggle() {
        this.enabled = !this.enabled;
        if (!this.enabled) this.stopMusic();
        return this.enabled;
    }

    // ── Sound Effects ──

    playShoot() {
        if (!this.enabled || !this.ctx) return;
        const osc = this.ctx.createOscillator();
        const gain = this.ctx.createGain();
        osc.connect(gain);
        gain.connect(this.ctx.destination);
        osc.type = 'square';
        osc.frequency.setValueAtTime(880, this.ctx.currentTime);
        osc.frequency.exponentialRampToValueAtTime(220, this.ctx.currentTime + 0.1);
        gain.gain.setValueAtTime(0.15, this.ctx.currentTime);
        gain.gain.exponentialRampToValueAtTime(0.001, this.ctx.currentTime + 0.1);
        osc.start(this.ctx.currentTime);
        osc.stop(this.ctx.currentTime + 0.1);
    }

    playHit() {
        if (!this.enabled || !this.ctx) return;
        const osc = this.ctx.createOscillator();
        const gain = this.ctx.createGain();
        osc.connect(gain);
        gain.connect(this.ctx.destination);
        osc.type = 'sawtooth';
        osc.frequency.setValueAtTime(200, this.ctx.currentTime);
        osc.frequency.exponentialRampToValueAtTime(50, this.ctx.currentTime + 0.2);
        gain.gain.setValueAtTime(0.2, this.ctx.currentTime);
        gain.gain.exponentialRampToValueAtTime(0.001, this.ctx.currentTime + 0.2);
        osc.start(this.ctx.currentTime);
        osc.stop(this.ctx.currentTime + 0.2);
    }

    playExplosion() {
        if (!this.enabled || !this.ctx) return;
        const bufferSize = this.ctx.sampleRate * 0.3;
        const buffer = this.ctx.createBuffer(1, bufferSize, this.ctx.sampleRate);
        const data = buffer.getChannelData(0);
        for (let i = 0; i < bufferSize; i++) {
            data[i] = (Math.random() * 2 - 1) * (1 - i / bufferSize);
        }
        const noise = this.ctx.createBufferSource();
        noise.buffer = buffer;
        const gain = this.ctx.createGain();
        noise.connect(gain);
        gain.connect(this.ctx.destination);
        gain.gain.setValueAtTime(0.25, this.ctx.currentTime);
        gain.gain.exponentialRampToValueAtTime(0.001, this.ctx.currentTime + 0.3);
        noise.start(this.ctx.currentTime);
        noise.stop(this.ctx.currentTime + 0.3);
    }

    playPlayerHit() {
        if (!this.enabled || !this.ctx) return;
        const osc = this.ctx.createOscillator();
        const gain = this.ctx.createGain();
        osc.connect(gain);
        gain.connect(this.ctx.destination);
        osc.type = 'square';
        osc.frequency.setValueAtTime(150, this.ctx.currentTime);
        osc.frequency.setValueAtTime(100, this.ctx.currentTime + 0.1);
        osc.frequency.setValueAtTime(60, this.ctx.currentTime + 0.2);
        gain.gain.setValueAtTime(0.25, this.ctx.currentTime);
        gain.gain.exponentialRampToValueAtTime(0.001, this.ctx.currentTime + 0.3);
        osc.start(this.ctx.currentTime);
        osc.stop(this.ctx.currentTime + 0.3);
    }

    playGameOver() {
        if (!this.enabled || !this.ctx) return;
        const notes = [440, 370, 311, 261];
        notes.forEach((freq, i) => {
            const osc = this.ctx.createOscillator();
            const gain = this.ctx.createGain();
            osc.connect(gain);
            gain.connect(this.ctx.destination);
            osc.type = 'square';
            osc.frequency.value = freq;
            gain.gain.setValueAtTime(0.2, this.ctx.currentTime + i * 0.25);
            gain.gain.exponentialRampToValueAtTime(0.001, this.ctx.currentTime + i * 0.25 + 0.24);
            osc.start(this.ctx.currentTime + i * 0.25);
            osc.stop(this.ctx.currentTime + i * 0.25 + 0.25);
        });
    }

    playWaveComplete() {
        if (!this.enabled || !this.ctx) return;
        const notes = [523, 659, 784, 1047];
        notes.forEach((freq, i) => {
            const osc = this.ctx.createOscillator();
            const gain = this.ctx.createGain();
            osc.connect(gain);
            gain.connect(this.ctx.destination);
            osc.type = 'square';
            osc.frequency.value = freq;
            gain.gain.setValueAtTime(0.15, this.ctx.currentTime + i * 0.12);
            gain.gain.exponentialRampToValueAtTime(0.001, this.ctx.currentTime + i * 0.12 + 0.11);
            osc.start(this.ctx.currentTime + i * 0.12);
            osc.stop(this.ctx.currentTime + i * 0.12 + 0.12);
        });
    }

    playPowerUp() {
        if (!this.enabled || !this.ctx) return;
        const osc = this.ctx.createOscillator();
        const gain = this.ctx.createGain();
        osc.connect(gain);
        gain.connect(this.ctx.destination);
        osc.type = 'sine';
        osc.frequency.setValueAtTime(400, this.ctx.currentTime);
        osc.frequency.exponentialRampToValueAtTime(1200, this.ctx.currentTime + 0.2);
        gain.gain.setValueAtTime(0.15, this.ctx.currentTime);
        gain.gain.exponentialRampToValueAtTime(0.001, this.ctx.currentTime + 0.25);
        osc.start(this.ctx.currentTime);
        osc.stop(this.ctx.currentTime + 0.25);
    }

    // ── Background Music ──

    startMusic() {
        if (!this.enabled || !this.ctx || this.musicPlaying) return;
        this.musicPlaying = true;
        this.musicGain = this.ctx.createGain();
        this.musicGain.gain.value = 0.06;
        this.musicGain.connect(this.ctx.destination);
        this._playMusicLoop();
    }

    _playMusicLoop() {
        if (!this.musicPlaying) return;
        // Simple bass line loop
        const bassNotes = [130.81, 146.83, 164.81, 146.83, 130.81, 110, 130.81, 146.83];
        const noteLength = 0.25;
        const loopLen = bassNotes.length * noteLength;

        bassNotes.forEach((freq, i) => {
            const osc = this.ctx.createOscillator();
            const g = this.ctx.createGain();
            osc.connect(g);
            g.connect(this.musicGain);
            osc.type = 'square';
            osc.frequency.value = freq;
            const t = this.ctx.currentTime + i * noteLength;
            g.gain.setValueAtTime(0.5, t);
            g.gain.setValueAtTime(0.3, t + noteLength * 0.5);
            g.gain.exponentialRampToValueAtTime(0.001, t + noteLength - 0.01);
            osc.start(t);
            osc.stop(t + noteLength);
            this.musicOscillators.push(osc);
        });

        this.musicTimeout = setTimeout(() => this._playMusicLoop(), loopLen * 1000);
    }

    stopMusic() {
        this.musicPlaying = false;
        if (this.musicTimeout) clearTimeout(this.musicTimeout);
        this.musicOscillators.forEach(o => { try { o.stop(); } catch (e) { } });
        this.musicOscillators = [];
    }
}
