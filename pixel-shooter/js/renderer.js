// ── Renderer ─────────────────────────────────────────
// Canvas rendering, starfield background, screen shake, HUD

export class Renderer {
    constructor(canvas) {
        this.canvas = canvas;
        this.ctx = canvas.getContext('2d');
        this.ctx.imageSmoothingEnabled = false; // pixel-perfect

        // Screen shake
        this.shakeAmount = 0;
        this.shakeDuration = 0;
        this.shakeOffsetX = 0;
        this.shakeOffsetY = 0;
        this.shakeActive = false;

        // Starfield
        this.stars = [];
        for (let i = 0; i < 100; i++) {
            this.stars.push({
                x: Math.random() * canvas.width,
                y: Math.random() * canvas.height,
                speed: 10 + Math.random() * 40,
                size: Math.random() < 0.3 ? 2 : 1,
                brightness: 0.3 + Math.random() * 0.7
            });
        }
    }

    clear() {
        this.ctx.fillStyle = '#0a0a1a';
        this.ctx.fillRect(0, 0, this.canvas.width, this.canvas.height);
    }

    applyShake(dt) {
        if (this.shakeDuration > 0) {
            this.shakeDuration -= dt;
            this.shakeOffsetX = (Math.random() - 0.5) * this.shakeAmount * 2;
            this.shakeOffsetY = (Math.random() - 0.5) * this.shakeAmount * 2;
            this.ctx.save();
            this.ctx.translate(this.shakeOffsetX, this.shakeOffsetY);
            this.shakeActive = true;
        } else {
            this.shakeActive = false;
        }
    }

    endShake() {
        if (this.shakeActive) {
            this.ctx.restore();
            this.shakeActive = false;
        }
    }

    shake(amount, duration) {
        this.shakeAmount = amount;
        this.shakeDuration = duration;
    }

    drawStarfield(dt) {
        this.stars.forEach(star => {
            star.y += star.speed * dt;
            if (star.y > this.canvas.height) {
                star.y = 0;
                star.x = Math.random() * this.canvas.width;
            }
            this.ctx.fillStyle = `rgba(255,255,255,${star.brightness})`;
            this.ctx.fillRect(Math.floor(star.x), Math.floor(star.y), star.size, star.size);
        });
    }

    drawHUD(player, score, wave, combo) {
        const ctx = this.ctx;
        const w = this.canvas.width;

        // Health bar
        ctx.fillStyle = '#333';
        ctx.fillRect(10, 10, 104, 14);
        ctx.fillStyle = '#222';
        ctx.fillRect(12, 12, 100, 10);
        const healthPercent = player.health / player.maxHealth;
        const healthColor = healthPercent > 0.5 ? '#0f0' : healthPercent > 0.25 ? '#ff0' : '#f00';
        ctx.fillStyle = healthColor;
        ctx.fillRect(12, 12, 100 * healthPercent, 10);
        // Health text
        ctx.fillStyle = '#fff';
        ctx.font = '10px "Press Start 2P", monospace';
        ctx.fillText('HP', 120, 21);

        // Score
        ctx.fillStyle = '#0ff';
        ctx.font = '12px "Press Start 2P", monospace';
        ctx.textAlign = 'right';
        ctx.fillText(`SCORE: ${score}`, w - 10, 22);
        ctx.textAlign = 'left';

        // Wave
        ctx.fillStyle = '#ff0';
        ctx.font = '10px "Press Start 2P", monospace';
        ctx.fillText(`WAVE ${wave}`, 10, 40);

        // Combo
        if (combo > 1) {
            ctx.fillStyle = '#f80';
            ctx.font = '10px "Press Start 2P", monospace';
            ctx.textAlign = 'right';
            ctx.fillText(`x${combo} COMBO`, w - 10, 40);
            ctx.textAlign = 'left';
        }
    }

    drawWaveAnnouncement(wave, timer) {
        const ctx = this.ctx;
        const alpha = Math.min(1, timer * 2);
        ctx.save();
        ctx.globalAlpha = alpha;
        ctx.fillStyle = '#ff0';
        ctx.font = '24px "Press Start 2P", monospace';
        ctx.textAlign = 'center';
        ctx.fillText(`WAVE ${wave}`, this.canvas.width / 2, this.canvas.height / 2 - 20);
        ctx.fillStyle = '#fff';
        ctx.font = '12px "Press Start 2P", monospace';
        ctx.fillText('GET READY!', this.canvas.width / 2, this.canvas.height / 2 + 15);
        ctx.textAlign = 'left';
        ctx.restore();
    }

    drawGameOver(score, highScore) {
        const ctx = this.ctx;
        const cx = this.canvas.width / 2;
        const cy = this.canvas.height / 2;

        // Overlay
        ctx.fillStyle = 'rgba(0,0,0,0.7)';
        ctx.fillRect(0, 0, this.canvas.width, this.canvas.height);

        // Game Over text
        ctx.fillStyle = '#f00';
        ctx.font = '28px "Press Start 2P", monospace';
        ctx.textAlign = 'center';
        ctx.fillText('GAME OVER', cx, cy - 40);

        // Score
        ctx.fillStyle = '#fff';
        ctx.font = '14px "Press Start 2P", monospace';
        ctx.fillText(`FINAL SCORE: ${score}`, cx, cy + 10);

        if (highScore && score >= highScore) {
            ctx.fillStyle = '#ff0';
            ctx.font = '12px "Press Start 2P", monospace';
            ctx.fillText('★ NEW HIGH SCORE! ★', cx, cy + 40);
        }

        ctx.fillStyle = '#0ff';
        ctx.font = '10px "Press Start 2P", monospace';
        ctx.fillText('PRESS ENTER OR CLICK TO RESTART', cx, cy + 75);
        ctx.textAlign = 'left';
    }

    drawMenu() {
        const ctx = this.ctx;
        const cx = this.canvas.width / 2;
        const cy = this.canvas.height / 2;

        // Title
        ctx.fillStyle = '#0ff';
        ctx.font = '22px "Press Start 2P", monospace';
        ctx.textAlign = 'center';
        ctx.fillText('PIXEL', cx, cy - 60);
        ctx.fillStyle = '#f80';
        ctx.fillText('BLASTER', cx, cy - 30);

        // Subtitle
        ctx.fillStyle = '#888';
        ctx.font = '8px "Press Start 2P", monospace';
        ctx.fillText('A RETRO SPACE SHOOTER', cx, cy);

        // Instructions
        ctx.fillStyle = '#fff';
        ctx.font = '9px "Press Start 2P", monospace';
        ctx.fillText('WASD / ARROWS - MOVE', cx, cy + 35);
        ctx.fillText('MOUSE AIM + CLICK - SHOOT', cx, cy + 52);

        // Start prompt
        const blink = Math.sin(Date.now() / 300) > 0;
        if (blink) {
            ctx.fillStyle = '#0f0';
            ctx.font = '11px "Press Start 2P", monospace';
            ctx.fillText('PRESS ENTER OR CLICK TO START', cx, cy + 85);
        }
        ctx.textAlign = 'left';
    }

    // Crosshair
    drawCrosshair(mouseX, mouseY) {
        const ctx = this.ctx;
        ctx.strokeStyle = '#0ff';
        ctx.lineWidth = 1;
        const s = 8;
        // Draw pixel crosshair
        ctx.fillStyle = '#0ff';
        ctx.fillRect(Math.floor(mouseX) - s, Math.floor(mouseY), s * 2 + 1, 1);
        ctx.fillRect(Math.floor(mouseX), Math.floor(mouseY) - s, 1, s * 2 + 1);
        // Dot
        ctx.fillStyle = '#fff';
        ctx.fillRect(Math.floor(mouseX), Math.floor(mouseY), 1, 1);
    }
}
