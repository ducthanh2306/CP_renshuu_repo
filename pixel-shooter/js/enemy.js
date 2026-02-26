// ── Enemies ──────────────────────────────────────────
// Enemy types and wave spawner

class BaseEnemy {
    constructor(x, y, config) {
        this.x = x;
        this.y = y;
        this.speed = config.speed;
        this.maxHealth = config.health;
        this.health = config.health;
        this.size = config.size;
        this.points = config.points;
        this.color = config.color;
        this.glowColor = config.glowColor;
        this.type = config.type;
        this.alive = true;
        this.flashTimer = 0;
        this.angle = 0;
        this.shootCooldown = config.shootCooldown || 0;
        this.shootRate = config.shootRate || 999;
        this.canShoot = config.canShoot || false;
        this.bulletSpeed = config.bulletSpeed || 200;
    }

    update(dt, playerX, playerY) {
        // Move toward player
        const dx = playerX - this.x;
        const dy = playerY - this.y;
        const dist = Math.sqrt(dx * dx + dy * dy);
        if (dist > 0) {
            this.x += (dx / dist) * this.speed * dt;
            this.y += (dy / dist) * this.speed * dt;
        }
        this.angle = Math.atan2(dy, dx);

        if (this.flashTimer > 0) this.flashTimer -= dt;

        // Shooting
        if (this.canShoot) {
            this.shootCooldown -= dt;
        }
    }

    tryShoot(playerX, playerY) {
        if (!this.canShoot || this.shootCooldown > 0) return null;
        this.shootCooldown = this.shootRate;
        const dx = playerX - this.x;
        const dy = playerY - this.y;
        const dist = Math.sqrt(dx * dx + dy * dy);
        if (dist === 0) return null;
        const { Projectile } = this._projModule;
        return new Projectile(
            this.x, this.y,
            (dx / dist) * this.bulletSpeed,
            (dy / dist) * this.bulletSpeed,
            false
        );
    }

    takeDamage(amount = 1) {
        this.health -= amount;
        this.flashTimer = 0.1;
        if (this.health <= 0) {
            this.alive = false;
            return true; // died
        }
        return false;
    }

    draw(ctx) {
        ctx.save();
        ctx.translate(Math.floor(this.x), Math.floor(this.y));

        const isFlashing = this.flashTimer > 0;
        this._drawSprite(ctx, isFlashing);

        ctx.restore();
    }

    _drawSprite(ctx, flash) {
        // Override in subclasses
        const c = flash ? '#fff' : this.color;
        const s = this.size;
        ctx.fillStyle = this.glowColor;
        ctx.fillRect(-s / 2 - 1, -s / 2 - 1, s + 2, s + 2);
        ctx.fillStyle = c;
        ctx.fillRect(-s / 2, -s / 2, s, s);
    }

    getBounds() {
        return {
            x: this.x - this.size / 2,
            y: this.y - this.size / 2,
            width: this.size,
            height: this.size
        };
    }
}

// ── Enemy Types ──

class BasicEnemy extends BaseEnemy {
    constructor(x, y) {
        super(x, y, {
            speed: 80,
            health: 1,
            size: 16,
            points: 100,
            color: '#f44',
            glowColor: '#a00',
            type: 'basic'
        });
    }

    _drawSprite(ctx, flash) {
        const c = flash ? '#fff' : this.color;
        // Diamond-shaped enemy
        ctx.fillStyle = this.glowColor;
        ctx.beginPath();
        ctx.moveTo(0, -10);
        ctx.lineTo(10, 0);
        ctx.lineTo(0, 10);
        ctx.lineTo(-10, 0);
        ctx.closePath();
        ctx.fill();

        ctx.fillStyle = c;
        ctx.beginPath();
        ctx.moveTo(0, -8);
        ctx.lineTo(8, 0);
        ctx.lineTo(0, 8);
        ctx.lineTo(-8, 0);
        ctx.closePath();
        ctx.fill();

        // Eye
        ctx.fillStyle = '#ff0';
        ctx.fillRect(-2, -2, 4, 4);
    }
}

class FastEnemy extends BaseEnemy {
    constructor(x, y) {
        super(x, y, {
            speed: 160,
            health: 1,
            size: 12,
            points: 150,
            color: '#f0f',
            glowColor: '#808',
            type: 'fast'
        });
    }

    _drawSprite(ctx, flash) {
        const c = flash ? '#fff' : this.color;
        // Triangle arrow shape
        ctx.save();
        ctx.rotate(this.angle);

        ctx.fillStyle = this.glowColor;
        ctx.beginPath();
        ctx.moveTo(8, 0);
        ctx.lineTo(-8, -7);
        ctx.lineTo(-4, 0);
        ctx.lineTo(-8, 7);
        ctx.closePath();
        ctx.fill();

        ctx.fillStyle = c;
        ctx.beginPath();
        ctx.moveTo(6, 0);
        ctx.lineTo(-6, -5);
        ctx.lineTo(-3, 0);
        ctx.lineTo(-6, 5);
        ctx.closePath();
        ctx.fill();

        ctx.restore();
    }
}

class TankEnemy extends BaseEnemy {
    constructor(x, y) {
        super(x, y, {
            speed: 40,
            health: 4,
            size: 24,
            points: 300,
            color: '#f80',
            glowColor: '#a50',
            type: 'tank',
            canShoot: true,
            shootRate: 2.5,
            shootCooldown: 1.5,
            bulletSpeed: 180
        });
    }

    _drawSprite(ctx, flash) {
        const c = flash ? '#fff' : this.color;
        const s = this.size;
        // Big chunky square with details
        ctx.fillStyle = this.glowColor;
        ctx.fillRect(-s / 2 - 1, -s / 2 - 1, s + 2, s + 2);
        ctx.fillStyle = c;
        ctx.fillRect(-s / 2, -s / 2, s, s);
        // Inner details
        ctx.fillStyle = '#c60';
        ctx.fillRect(-s / 2 + 3, -s / 2 + 3, s - 6, s - 6);
        // Health pips
        ctx.fillStyle = '#f00';
        for (let i = 0; i < this.health; i++) {
            ctx.fillRect(-s / 2 + 4 + i * 5, s / 2 - 5, 4, 3);
        }
        // Eye
        ctx.fillStyle = '#ff0';
        ctx.fillRect(-3, -3, 6, 6);
        ctx.fillStyle = '#f00';
        ctx.fillRect(-1, -1, 2, 2);
    }
}

class ShooterEnemy extends BaseEnemy {
    constructor(x, y) {
        super(x, y, {
            speed: 50,
            health: 2,
            size: 18,
            points: 200,
            color: '#8f0',
            glowColor: '#480',
            type: 'shooter',
            canShoot: true,
            shootRate: 1.8,
            shootCooldown: 1.0,
            bulletSpeed: 220
        });
    }

    update(dt, playerX, playerY) {
        // Shooter tries to maintain distance
        const dx = playerX - this.x;
        const dy = playerY - this.y;
        const dist = Math.sqrt(dx * dx + dy * dy);
        this.angle = Math.atan2(dy, dx);

        if (dist > 180) {
            // Move closer
            this.x += (dx / dist) * this.speed * dt;
            this.y += (dy / dist) * this.speed * dt;
        } else if (dist < 120) {
            // Back away
            this.x -= (dx / dist) * this.speed * 0.7 * dt;
            this.y -= (dy / dist) * this.speed * 0.7 * dt;
        } else {
            // Strafe
            this.x += (-dy / dist) * this.speed * 0.5 * dt;
            this.y += (dx / dist) * this.speed * 0.5 * dt;
        }

        if (this.flashTimer > 0) this.flashTimer -= dt;
        if (this.canShoot) this.shootCooldown -= dt;
    }

    _drawSprite(ctx, flash) {
        const c = flash ? '#fff' : this.color;
        // Hexagon-ish shape
        ctx.save();
        ctx.rotate(this.angle);

        ctx.fillStyle = this.glowColor;
        ctx.fillRect(-10, -10, 20, 20);

        ctx.fillStyle = c;
        ctx.fillRect(-8, -8, 16, 16);
        ctx.fillStyle = '#6c0';
        ctx.fillRect(-6, -6, 12, 12);

        // Gun barrel
        ctx.fillStyle = '#888';
        ctx.fillRect(6, -2, 8, 4);

        // Eye
        ctx.fillStyle = '#ff0';
        ctx.fillRect(-2, -2, 4, 4);

        ctx.restore();
    }
}

// ── Wave Spawner ──

export class WaveSpawner {
    constructor(canvasWidth, canvasHeight) {
        this.canvasWidth = canvasWidth;
        this.canvasHeight = canvasHeight;
        this.wave = 0;
        this.enemiesRemaining = 0;
        this.spawnTimer = 0;
        this.spawnInterval = 1.2;
        this.waveDelay = 0;
        this.waveActive = false;
        this.totalEnemiesThisWave = 0;
        this.spawnedThisWave = 0;
    }

    startWave() {
        this.wave++;
        this.totalEnemiesThisWave = 4 + this.wave * 2;
        this.spawnedThisWave = 0;
        this.enemiesRemaining = this.totalEnemiesThisWave;
        this.spawnTimer = 0;
        this.spawnInterval = Math.max(0.3, 1.2 - this.wave * 0.05);
        this.waveActive = true;
        this.waveDelay = 0;
    }

    update(dt, enemies, projectileModule) {
        if (!this.waveActive) return;

        if (this.spawnedThisWave < this.totalEnemiesThisWave) {
            this.spawnTimer -= dt;
            if (this.spawnTimer <= 0) {
                this.spawnTimer = this.spawnInterval;
                const enemy = this._spawnEnemy();
                enemy._projModule = projectileModule;
                enemies.push(enemy);
                this.spawnedThisWave++;
            }
        }
    }

    onEnemyKilled() {
        this.enemiesRemaining--;
    }

    isWaveComplete() {
        return this.waveActive && this.enemiesRemaining <= 0 && this.spawnedThisWave >= this.totalEnemiesThisWave;
    }

    _spawnEnemy() {
        // Spawn from random edge
        const side = Math.floor(Math.random() * 4);
        let x, y;
        const margin = 30;
        switch (side) {
            case 0: x = -margin; y = Math.random() * this.canvasHeight; break;
            case 1: x = this.canvasWidth + margin; y = Math.random() * this.canvasHeight; break;
            case 2: x = Math.random() * this.canvasWidth; y = -margin; break;
            case 3: x = Math.random() * this.canvasWidth; y = this.canvasHeight + margin; break;
        }

        // Pick enemy type based on wave
        const roll = Math.random();
        if (this.wave >= 5 && roll < 0.15) {
            return new TankEnemy(x, y);
        } else if (this.wave >= 3 && roll < 0.35) {
            return new ShooterEnemy(x, y);
        } else if (this.wave >= 2 && roll < 0.5) {
            return new FastEnemy(x, y);
        }
        return new BasicEnemy(x, y);
    }
}
