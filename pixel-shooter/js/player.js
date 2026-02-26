// ── Player ────────────────────────────────────────────
// The player character — pixel art spaceship-like figure

import { Projectile } from './projectile.js';

export class Player {
    constructor(x, y) {
        this.x = x;
        this.y = y;
        this.width = 20;
        this.height = 20;
        this.speed = 200;
        this.maxHealth = 5;
        this.health = this.maxHealth;
        this.alive = true;
        this.shootCooldown = 0;
        this.shootRate = 0.18; // seconds between shots
        this.invincible = 0; // invincibility timer
        this.invincibleDuration = 1.0;
        this.angle = 0; // facing angle toward mouse
        this.bulletSpeed = 500;
    }

    update(dt, input, canvasWidth, canvasHeight) {
        // Movement
        let dx = 0, dy = 0;
        if (input.isKeyDown('w') || input.isKeyDown('arrowup')) dy = -1;
        if (input.isKeyDown('s') || input.isKeyDown('arrowdown')) dy = 1;
        if (input.isKeyDown('a') || input.isKeyDown('arrowleft')) dx = -1;
        if (input.isKeyDown('d') || input.isKeyDown('arrowright')) dx = 1;

        // Normalize diagonal
        if (dx !== 0 && dy !== 0) {
            const len = Math.sqrt(dx * dx + dy * dy);
            dx /= len;
            dy /= len;
        }

        this.x += dx * this.speed * dt;
        this.y += dy * this.speed * dt;

        // Clamp to canvas
        this.x = Math.max(this.width / 2, Math.min(canvasWidth - this.width / 2, this.x));
        this.y = Math.max(this.height / 2, Math.min(canvasHeight - this.height / 2, this.y));

        // Face toward mouse
        this.angle = Math.atan2(input.mouse.y - this.y, input.mouse.x - this.x);

        // Cooldowns
        if (this.shootCooldown > 0) this.shootCooldown -= dt;
        if (this.invincible > 0) this.invincible -= dt;
    }

    shoot(input) {
        if (this.shootCooldown > 0) return null;
        if (!input.mouse.down) return null;

        this.shootCooldown = this.shootRate;
        const vx = Math.cos(this.angle) * this.bulletSpeed;
        const vy = Math.sin(this.angle) * this.bulletSpeed;
        const spawnDist = 14;
        return new Projectile(
            this.x + Math.cos(this.angle) * spawnDist,
            this.y + Math.sin(this.angle) * spawnDist,
            vx, vy, true
        );
    }

    takeDamage() {
        if (this.invincible > 0) return false;
        this.health--;
        this.invincible = this.invincibleDuration;
        if (this.health <= 0) {
            this.alive = false;
        }
        return true;
    }

    reset(x, y) {
        this.x = x;
        this.y = y;
        this.health = this.maxHealth;
        this.alive = true;
        this.invincible = 0;
        this.shootCooldown = 0;
    }

    draw(ctx) {
        // Blink when invincible
        if (this.invincible > 0 && Math.floor(this.invincible * 10) % 2 === 0) return;

        ctx.save();
        ctx.translate(Math.floor(this.x), Math.floor(this.y));
        ctx.rotate(this.angle);

        // Body
        ctx.fillStyle = '#4af';
        ctx.fillRect(-10, -8, 20, 16);

        // Core
        ctx.fillStyle = '#2d8cf0';
        ctx.fillRect(-8, -6, 16, 12);

        // Cockpit / visor
        ctx.fillStyle = '#0ff';
        ctx.fillRect(2, -4, 6, 8);
        ctx.fillStyle = '#aff';
        ctx.fillRect(4, -2, 4, 4);

        // Wings
        ctx.fillStyle = '#36c';
        ctx.fillRect(-8, -12, 4, 4);
        ctx.fillRect(-8, 8, 4, 4);

        // Engine glow
        ctx.fillStyle = '#f80';
        ctx.fillRect(-12, -3, 4, 6);
        ctx.fillStyle = '#ff0';
        ctx.fillRect(-12, -1, 2, 2);

        // Gun barrel
        ctx.fillStyle = '#888';
        ctx.fillRect(8, -2, 6, 4);
        ctx.fillStyle = '#aaa';
        ctx.fillRect(10, -1, 4, 2);

        ctx.restore();
    }

    getBounds() {
        return {
            x: this.x - this.width / 2,
            y: this.y - this.height / 2,
            width: this.width,
            height: this.height
        };
    }
}
