// ── Particle System ──────────────────────────────────
// Pixel-style particle effects for explosions, hits, and muzzle flashes

class Particle {
    constructor(x, y, vx, vy, color, size, life) {
        this.x = x;
        this.y = y;
        this.vx = vx;
        this.vy = vy;
        this.color = color;
        this.size = size;
        this.life = life;
        this.maxLife = life;
        this.alive = true;
    }

    update(dt) {
        this.x += this.vx * dt;
        this.y += this.vy * dt;
        this.life -= dt;
        // Slow down
        this.vx *= 0.98;
        this.vy *= 0.98;
        if (this.life <= 0) this.alive = false;
    }

    draw(ctx) {
        const alpha = Math.max(0, this.life / this.maxLife);
        ctx.globalAlpha = alpha;
        ctx.fillStyle = this.color;
        const s = Math.max(1, this.size * alpha);
        ctx.fillRect(Math.floor(this.x), Math.floor(this.y), s, s);
        ctx.globalAlpha = 1;
    }
}

export class ParticleSystem {
    constructor() {
        this.particles = [];
    }

    // Explosion when enemy dies
    explode(x, y, colors, count = 12) {
        for (let i = 0; i < count; i++) {
            const angle = (Math.PI * 2 / count) * i + Math.random() * 0.5;
            const speed = 80 + Math.random() * 160;
            const color = colors[Math.floor(Math.random() * colors.length)];
            this.particles.push(new Particle(
                x, y,
                Math.cos(angle) * speed,
                Math.sin(angle) * speed,
                color,
                2 + Math.random() * 3,
                0.3 + Math.random() * 0.4
            ));
        }
    }

    // Small spark when bullet hits
    spark(x, y, color = '#fff') {
        for (let i = 0; i < 5; i++) {
            const angle = Math.random() * Math.PI * 2;
            const speed = 40 + Math.random() * 80;
            this.particles.push(new Particle(
                x, y,
                Math.cos(angle) * speed,
                Math.sin(angle) * speed,
                color, 2, 0.15 + Math.random() * 0.1
            ));
        }
    }

    // Muzzle flash when player shoots
    muzzleFlash(x, y, angle) {
        for (let i = 0; i < 3; i++) {
            const spread = angle + (Math.random() - 0.5) * 0.5;
            const speed = 100 + Math.random() * 60;
            const colors = ['#ff0', '#ffa500', '#fff'];
            this.particles.push(new Particle(
                x, y,
                Math.cos(spread) * speed,
                Math.sin(spread) * speed,
                colors[Math.floor(Math.random() * colors.length)],
                2, 0.08 + Math.random() * 0.06
            ));
        }
    }

    // Damage indicator on player
    damageFlash(x, y) {
        for (let i = 0; i < 8; i++) {
            const angle = Math.random() * Math.PI * 2;
            const speed = 60 + Math.random() * 100;
            this.particles.push(new Particle(
                x, y,
                Math.cos(angle) * speed,
                Math.sin(angle) * speed,
                '#f00', 3, 0.3 + Math.random() * 0.2
            ));
        }
    }

    update(dt) {
        for (let i = this.particles.length - 1; i >= 0; i--) {
            this.particles[i].update(dt);
            if (!this.particles[i].alive) {
                this.particles.splice(i, 1);
            }
        }
    }

    draw(ctx) {
        this.particles.forEach(p => p.draw(ctx));
    }

    clear() {
        this.particles = [];
    }
}
