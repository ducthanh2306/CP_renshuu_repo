// ── Projectile ───────────────────────────────────────
// Bullet class for player and enemy projectiles

export class Projectile {
    constructor(x, y, vx, vy, isPlayerBullet = true) {
        this.x = x;
        this.y = y;
        this.vx = vx;
        this.vy = vy;
        this.isPlayerBullet = isPlayerBullet;
        this.alive = true;
        this.size = isPlayerBullet ? 4 : 5;
        this.damage = isPlayerBullet ? 1 : 1;
        this.trail = [];
    }

    update(dt, canvasWidth, canvasHeight) {
        // Store trail position
        this.trail.push({ x: this.x, y: this.y });
        if (this.trail.length > 4) this.trail.shift();

        this.x += this.vx * dt;
        this.y += this.vy * dt;

        // Out of bounds check
        const margin = 20;
        if (this.x < -margin || this.x > canvasWidth + margin ||
            this.y < -margin || this.y > canvasHeight + margin) {
            this.alive = false;
        }
    }

    getBounds() {
        return {
            x: this.x - this.size / 2,
            y: this.y - this.size / 2,
            width: this.size,
            height: this.size
        };
    }

    draw(ctx) {
        // Draw trail
        this.trail.forEach((pos, i) => {
            const alpha = (i + 1) / (this.trail.length + 1) * 0.4;
            ctx.globalAlpha = alpha;
            ctx.fillStyle = this.isPlayerBullet ? '#0ff' : '#f44';
            const s = this.size * (i / this.trail.length) * 0.6;
            ctx.fillRect(Math.floor(pos.x - s / 2), Math.floor(pos.y - s / 2), Math.max(1, s), Math.max(1, s));
        });
        ctx.globalAlpha = 1;

        // Draw bullet
        const color = this.isPlayerBullet ? '#0ff' : '#f44';
        const glow = this.isPlayerBullet ? '#08f' : '#a00';
        ctx.fillStyle = glow;
        ctx.fillRect(
            Math.floor(this.x - this.size / 2 - 1),
            Math.floor(this.y - this.size / 2 - 1),
            this.size + 2, this.size + 2
        );
        ctx.fillStyle = color;
        ctx.fillRect(
            Math.floor(this.x - this.size / 2),
            Math.floor(this.y - this.size / 2),
            this.size, this.size
        );
        ctx.fillStyle = '#fff';
        ctx.fillRect(
            Math.floor(this.x - 1),
            Math.floor(this.y - 1),
            2, 2
        );
    }
}
