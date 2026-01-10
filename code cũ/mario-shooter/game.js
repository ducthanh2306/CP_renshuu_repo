// ============================================
// SUPER MARIO SHOOTER - GAME ENGINE
// ============================================

const canvas = document.getElementById('game-canvas');
const ctx = canvas.getContext('2d');

// Set canvas size
canvas.width = 960;
canvas.height = 640;

// ============================================
// GAME CONSTANTS
// ============================================
const GRAVITY = 0.6;
const FRICTION = 0.8;
const TILE_SIZE = 40;
const PLAYER_SPEED = 5;
const JUMP_FORCE = -14;
const BULLET_SPEED = 12;
const MAX_BULLETS = 10;

// ============================================
// GAME STATE
// ============================================
let gameState = 'menu'; // menu, playing, paused, levelComplete, gameOver, victory
let currentLevel = 1;
let score = 0;
let coins = 0;
let lives = 3;
let levelStartTime = 0;

// ============================================
// AUDIO CONTEXT (Web Audio API for sounds)
// ============================================
const AudioContext = window.AudioContext || window.webkitAudioContext;
let audioCtx = null;

function initAudio() {
    if (!audioCtx) {
        audioCtx = new AudioContext();
    }
}

function playSound(type) {
    if (!audioCtx) return;
    const osc = audioCtx.createOscillator();
    const gain = audioCtx.createGain();
    osc.connect(gain);
    gain.connect(audioCtx.destination);

    switch (type) {
        case 'jump':
            osc.frequency.setValueAtTime(400, audioCtx.currentTime);
            osc.frequency.exponentialRampToValueAtTime(600, audioCtx.currentTime + 0.1);
            gain.gain.setValueAtTime(0.3, audioCtx.currentTime);
            gain.gain.exponentialRampToValueAtTime(0.01, audioCtx.currentTime + 0.1);
            osc.start();
            osc.stop(audioCtx.currentTime + 0.1);
            break;
        case 'shoot':
            osc.type = 'square';
            osc.frequency.setValueAtTime(800, audioCtx.currentTime);
            osc.frequency.exponentialRampToValueAtTime(200, audioCtx.currentTime + 0.1);
            gain.gain.setValueAtTime(0.2, audioCtx.currentTime);
            gain.gain.exponentialRampToValueAtTime(0.01, audioCtx.currentTime + 0.1);
            osc.start();
            osc.stop(audioCtx.currentTime + 0.1);
            break;
        case 'hit':
            osc.type = 'sawtooth';
            osc.frequency.setValueAtTime(200, audioCtx.currentTime);
            osc.frequency.exponentialRampToValueAtTime(50, audioCtx.currentTime + 0.2);
            gain.gain.setValueAtTime(0.3, audioCtx.currentTime);
            gain.gain.exponentialRampToValueAtTime(0.01, audioCtx.currentTime + 0.2);
            osc.start();
            osc.stop(audioCtx.currentTime + 0.2);
            break;
        case 'coin':
            osc.frequency.setValueAtTime(988, audioCtx.currentTime);
            osc.frequency.setValueAtTime(1319, audioCtx.currentTime + 0.1);
            gain.gain.setValueAtTime(0.3, audioCtx.currentTime);
            gain.gain.exponentialRampToValueAtTime(0.01, audioCtx.currentTime + 0.2);
            osc.start();
            osc.stop(audioCtx.currentTime + 0.2);
            break;
        case 'powerup':
            osc.frequency.setValueAtTime(400, audioCtx.currentTime);
            osc.frequency.exponentialRampToValueAtTime(800, audioCtx.currentTime + 0.2);
            gain.gain.setValueAtTime(0.3, audioCtx.currentTime);
            gain.gain.exponentialRampToValueAtTime(0.01, audioCtx.currentTime + 0.3);
            osc.start();
            osc.stop(audioCtx.currentTime + 0.3);
            break;
        case 'death':
            osc.type = 'sawtooth';
            osc.frequency.setValueAtTime(400, audioCtx.currentTime);
            osc.frequency.exponentialRampToValueAtTime(100, audioCtx.currentTime + 0.5);
            gain.gain.setValueAtTime(0.4, audioCtx.currentTime);
            gain.gain.exponentialRampToValueAtTime(0.01, audioCtx.currentTime + 0.5);
            osc.start();
            osc.stop(audioCtx.currentTime + 0.5);
            break;
        case 'levelup':
            osc.frequency.setValueAtTime(523, audioCtx.currentTime);
            osc.frequency.setValueAtTime(659, audioCtx.currentTime + 0.1);
            osc.frequency.setValueAtTime(784, audioCtx.currentTime + 0.2);
            osc.frequency.setValueAtTime(1047, audioCtx.currentTime + 0.3);
            gain.gain.setValueAtTime(0.3, audioCtx.currentTime);
            gain.gain.exponentialRampToValueAtTime(0.01, audioCtx.currentTime + 0.5);
            osc.start();
            osc.stop(audioCtx.currentTime + 0.5);
            break;
    }
}

// ============================================
// INPUT HANDLING
// ============================================
const keys = {};

document.addEventListener('keydown', (e) => {
    keys[e.code] = true;

    if ((e.code === 'KeyP' || e.code === 'Escape') && gameState === 'playing') {
        pauseGame();
        e.preventDefault();
    }
    if ((e.code === 'KeyP' || e.code === 'Escape') && gameState === 'paused') {
        resumeGame();
        e.preventDefault();
    }
});

document.addEventListener('keyup', (e) => {
    keys[e.code] = false;
});

// ============================================
// PLAYER CLASS
// ============================================
class Player {
    constructor(x, y) {
        this.x = x;
        this.y = y;
        this.width = 32;
        this.height = 48;
        this.vx = 0;
        this.vy = 0;
        this.onGround = false;
        this.facingRight = true;
        this.health = 100;
        this.maxHealth = 100;
        this.invincible = false;
        this.invincibleTimer = 0;
        this.animFrame = 0;
        this.animTimer = 0;
        this.shooting = false;
        this.shootCooldown = 0;

        // Power-ups
        this.powerup = null;
        this.powerupTimer = 0;
        this.doubleJump = false;
        this.hasDoubleJumped = false;
    }

    update() {
        // Horizontal movement
        if (keys['ArrowLeft'] || keys['KeyA']) {
            this.vx = -PLAYER_SPEED * (this.powerup === 'speed' ? 1.5 : 1);
            this.facingRight = false;
        } else if (keys['ArrowRight'] || keys['KeyD']) {
            this.vx = PLAYER_SPEED * (this.powerup === 'speed' ? 1.5 : 1);
            this.facingRight = true;
        } else {
            this.vx *= FRICTION;
        }

        // Jumping
        if ((keys['ArrowUp'] || keys['KeyW'] || keys['Space']) && this.onGround) {
            this.vy = JUMP_FORCE;
            this.onGround = false;
            this.hasDoubleJumped = false;
            playSound('jump');
        } else if ((keys['ArrowUp'] || keys['KeyW'] || keys['Space']) &&
            this.powerup === 'doublejump' && !this.hasDoubleJumped && !this.onGround) {
            this.vy = JUMP_FORCE * 0.8;
            this.hasDoubleJumped = true;
            playSound('jump');
        }

        // Shooting
        if ((keys['KeyX'] || keys['Enter']) && this.shootCooldown <= 0) {
            this.shoot();
            this.shootCooldown = this.powerup === 'rapid' ? 8 : 15;
        }
        if (this.shootCooldown > 0) this.shootCooldown--;

        // Apply gravity
        this.vy += GRAVITY;
        if (this.vy > 15) this.vy = 15;

        // Update position
        this.x += this.vx;
        this.y += this.vy;

        // Boundaries
        if (this.x < 0) this.x = 0;
        if (this.x > canvas.width - this.width) this.x = canvas.width - this.width;

        // Ground collision
        const groundY = canvas.height - 80;
        if (this.y + this.height > groundY) {
            this.y = groundY - this.height;
            this.vy = 0;
            this.onGround = true;
        }

        // Platform collisions
        platforms.forEach(plat => {
            if (this.vy > 0 &&
                this.x + this.width > plat.x &&
                this.x < plat.x + plat.width &&
                this.y + this.height > plat.y &&
                this.y + this.height < plat.y + plat.height + this.vy) {
                this.y = plat.y - this.height;
                this.vy = 0;
                this.onGround = true;
            }
        });

        // Invincibility
        if (this.invincible) {
            this.invincibleTimer--;
            if (this.invincibleTimer <= 0) {
                this.invincible = false;
            }
        }

        // Power-up timer
        if (this.powerup) {
            this.powerupTimer--;
            if (this.powerupTimer <= 0) {
                this.powerup = null;
                document.getElementById('powerup-indicator').classList.add('hidden');
            }
        }

        // Animation
        this.animTimer++;
        if (this.animTimer >= 8) {
            this.animTimer = 0;
            this.animFrame = (this.animFrame + 1) % 4;
        }
    }

    shoot() {
        if (bullets.length < MAX_BULLETS) {
            const bulletX = this.facingRight ? this.x + this.width : this.x - 8;
            const bulletY = this.y + this.height / 2 - 4;

            if (this.powerup === 'double') {
                bullets.push(new Bullet(bulletX, bulletY - 10, this.facingRight));
                bullets.push(new Bullet(bulletX, bulletY + 10, this.facingRight));
            } else {
                bullets.push(new Bullet(bulletX, bulletY, this.facingRight));
            }
            playSound('shoot');
        }
    }

    takeDamage(amount) {
        if (this.invincible) return;
        if (this.powerup === 'shield') {
            this.powerup = null;
            this.invincible = true;
            this.invincibleTimer = 60;
            document.getElementById('powerup-indicator').classList.add('hidden');
            return;
        }

        this.health -= amount;
        this.invincible = true;
        this.invincibleTimer = 90;
        playSound('hit');

        // Screen shake
        shakeScreen(10, 10);

        if (this.health <= 0) {
            this.die();
        }

        updateHUD();
    }

    die() {
        lives--;
        playSound('death');

        if (lives <= 0) {
            gameOver();
        } else {
            // Respawn
            this.health = this.maxHealth;
            this.x = 100;
            this.y = canvas.height - 200;
            this.vx = 0;
            this.vy = 0;
            this.invincible = true;
            this.invincibleTimer = 120;
            updateHUD();
        }
    }

    draw() {
        ctx.save();

        // Flicker when invincible
        if (this.invincible && Math.floor(this.invincibleTimer / 4) % 2 === 0) {
            ctx.globalAlpha = 0.5;
        }

        const x = this.x;
        const y = this.y;

        // Draw Mario-style character
        if (!this.facingRight) {
            ctx.translate(x + this.width / 2, 0);
            ctx.scale(-1, 1);
            ctx.translate(-(x + this.width / 2), 0);
        }

        // Hat (red)
        ctx.fillStyle = '#E52521';
        ctx.fillRect(x + 6, y, 20, 8);
        ctx.fillRect(x + 2, y + 8, 28, 8);

        // Face (skin color)
        ctx.fillStyle = '#FDB974';
        ctx.fillRect(x + 4, y + 16, 24, 16);

        // Eyes
        ctx.fillStyle = '#000';
        ctx.fillRect(x + 8, y + 20, 4, 4);
        ctx.fillRect(x + 20, y + 20, 4, 4);

        // Mustache
        ctx.fillStyle = '#4A2E0E';
        ctx.fillRect(x + 6, y + 28, 20, 4);

        // Body (red shirt)
        ctx.fillStyle = '#E52521';
        ctx.fillRect(x + 4, y + 32, 24, 12);

        // Overalls (blue)
        ctx.fillStyle = '#049CD8';
        ctx.fillRect(x + 4, y + 36, 8, 12);
        ctx.fillRect(x + 20, y + 36, 8, 12);

        // Legs animation
        const legOffset = this.onGround ? (Math.abs(this.vx) > 0.5 ? Math.sin(this.animFrame * 0.8) * 4 : 0) : 4;
        ctx.fillStyle = '#049CD8';
        ctx.fillRect(x + 4, y + 44, 8, 4 + legOffset);
        ctx.fillRect(x + 20, y + 44, 8, 4 - legOffset);

        // Power-up glow
        if (this.powerup) {
            ctx.globalAlpha = 0.3;
            ctx.fillStyle = this.getPowerupColor();
            ctx.beginPath();
            ctx.arc(x + this.width / 2, y + this.height / 2, 30, 0, Math.PI * 2);
            ctx.fill();
        }

        ctx.restore();
    }

    getPowerupColor() {
        switch (this.powerup) {
            case 'speed': return '#00ff00';
            case 'double': return '#ff8800';
            case 'shield': return '#00ffff';
            case 'rapid': return '#ff00ff';
            case 'doublejump': return '#ffff00';
            default: return '#ffffff';
        }
    }
}

// ============================================
// BULLET CLASS
// ============================================
class Bullet {
    constructor(x, y, goingRight) {
        this.x = x;
        this.y = y;
        this.width = 12;
        this.height = 8;
        this.speed = goingRight ? BULLET_SPEED : -BULLET_SPEED;
        this.active = true;
    }

    update() {
        this.x += this.speed;
        if (this.x < -20 || this.x > canvas.width + 20) {
            this.active = false;
        }
    }

    draw() {
        // Fireball style
        ctx.fillStyle = '#FF6600';
        ctx.beginPath();
        ctx.arc(this.x + 6, this.y + 4, 6, 0, Math.PI * 2);
        ctx.fill();

        ctx.fillStyle = '#FFFF00';
        ctx.beginPath();
        ctx.arc(this.x + 6, this.y + 4, 3, 0, Math.PI * 2);
        ctx.fill();

        // Trail
        ctx.fillStyle = 'rgba(255, 100, 0, 0.5)';
        ctx.beginPath();
        ctx.arc(this.x + 6 - this.speed * 0.5, this.y + 4, 4, 0, Math.PI * 2);
        ctx.fill();
    }
}

// ============================================
// ENEMY CLASSES
// ============================================
class Enemy {
    constructor(x, y, type) {
        this.x = x;
        this.y = y;
        this.type = type;
        this.width = 36;
        this.height = 36;
        this.vx = 0;
        this.vy = 0;
        this.health = this.getMaxHealth();
        this.maxHealth = this.health;
        this.active = true;
        this.animFrame = 0;
        this.animTimer = 0;
        this.shootTimer = 0;
        this.direction = -1;

        this.initType();
    }

    getMaxHealth() {
        switch (this.type) {
            case 'walker': return 1;
            case 'flyer': return 2;
            case 'shooter': return 2;
            default: return 1;
        }
    }

    initType() {
        switch (this.type) {
            case 'walker':
                this.vx = 1.5 * this.direction;
                break;
            case 'flyer':
                this.vx = 2 * this.direction;
                this.baseY = this.y;
                break;
            case 'shooter':
                this.shootTimer = 60;
                break;
        }
    }

    update() {
        this.animTimer++;
        if (this.animTimer >= 10) {
            this.animTimer = 0;
            this.animFrame = (this.animFrame + 1) % 2;
        }

        switch (this.type) {
            case 'walker':
                this.x += this.vx;
                if (this.x < 50 || this.x > canvas.width - 50) {
                    this.vx *= -1;
                    this.direction *= -1;
                }
                break;

            case 'flyer':
                this.x += this.vx;
                this.y = this.baseY + Math.sin(Date.now() * 0.005) * 30;
                if (this.x < 50 || this.x > canvas.width - 50) {
                    this.vx *= -1;
                    this.direction *= -1;
                }
                break;

            case 'shooter':
                this.shootTimer--;
                if (this.shootTimer <= 0) {
                    this.shootAtPlayer();
                    this.shootTimer = 90;
                }
                break;
        }
    }

    shootAtPlayer() {
        const dx = player.x - this.x;
        const dy = player.y - this.y;
        const dist = Math.sqrt(dx * dx + dy * dy);
        enemyBullets.push({
            x: this.x + this.width / 2,
            y: this.y + this.height / 2,
            vx: (dx / dist) * 5,
            vy: (dy / dist) * 5,
            width: 10,
            height: 10,
            active: true
        });
    }

    takeDamage() {
        this.health--;
        if (this.health <= 0) {
            this.die();
        }
    }

    die() {
        this.active = false;
        score += this.getScore();

        // Spawn particles
        for (let i = 0; i < 10; i++) {
            particles.push(new Particle(
                this.x + this.width / 2,
                this.y + this.height / 2,
                'explosion'
            ));
        }

        // Random chance to drop power-up or coin
        if (Math.random() < 0.3) {
            powerups.push(new Powerup(this.x, this.y));
        } else if (Math.random() < 0.5) {
            coinItems.push(new Coin(this.x + this.width / 2 - 10, this.y));
        }

        playSound('hit');
        updateHUD();
    }

    getScore() {
        switch (this.type) {
            case 'walker': return 100;
            case 'flyer': return 150;
            case 'shooter': return 200;
            default: return 100;
        }
    }

    draw() {
        ctx.save();

        if (this.direction > 0) {
            ctx.translate(this.x + this.width / 2, 0);
            ctx.scale(-1, 1);
            ctx.translate(-(this.x + this.width / 2), 0);
        }

        switch (this.type) {
            case 'walker':
                // Goomba-like
                ctx.fillStyle = '#8B4513';
                ctx.fillRect(this.x + 4, this.y + 8, 28, 20);

                ctx.fillStyle = '#654321';
                ctx.fillRect(this.x + 2, this.y, 32, 12);

                // Eyes
                ctx.fillStyle = '#fff';
                ctx.fillRect(this.x + 8, this.y + 12, 8, 8);
                ctx.fillRect(this.x + 20, this.y + 12, 8, 8);
                ctx.fillStyle = '#000';
                ctx.fillRect(this.x + 12, this.y + 14, 4, 4);
                ctx.fillRect(this.x + 20, this.y + 14, 4, 4);

                // Feet
                const footOffset = this.animFrame * 2;
                ctx.fillStyle = '#654321';
                ctx.fillRect(this.x + 4, this.y + 28, 12, 8 - footOffset);
                ctx.fillRect(this.x + 20, this.y + 28, 12, 8 + footOffset);
                break;

            case 'flyer':
                // Koopa-like flying
                ctx.fillStyle = '#00AA00';
                ctx.fillRect(this.x + 8, this.y + 4, 20, 24);

                // Shell
                ctx.fillStyle = '#228B22';
                ctx.beginPath();
                ctx.arc(this.x + 18, this.y + 16, 14, 0, Math.PI * 2);
                ctx.fill();

                // Wings
                const wingFlap = Math.sin(Date.now() * 0.02) * 8;
                ctx.fillStyle = '#fff';
                ctx.fillRect(this.x - 8, this.y + 8 + wingFlap, 12, 6);
                ctx.fillRect(this.x + 32, this.y + 8 - wingFlap, 12, 6);

                // Eyes
                ctx.fillStyle = '#fff';
                ctx.fillRect(this.x + 10, this.y + 8, 6, 6);
                ctx.fillRect(this.x + 20, this.y + 8, 6, 6);
                ctx.fillStyle = '#000';
                ctx.fillRect(this.x + 12, this.y + 10, 3, 3);
                ctx.fillRect(this.x + 22, this.y + 10, 3, 3);
                break;

            case 'shooter':
                // Hammer Bro-like
                ctx.fillStyle = '#006400';
                ctx.fillRect(this.x + 8, this.y, 20, 16);

                ctx.fillStyle = '#228B22';
                ctx.fillRect(this.x + 4, this.y + 16, 28, 20);

                // Helmet
                ctx.fillStyle = '#FFD700';
                ctx.fillRect(this.x + 6, this.y - 4, 24, 8);

                // Eyes
                ctx.fillStyle = '#fff';
                ctx.fillRect(this.x + 10, this.y + 4, 6, 6);
                ctx.fillRect(this.x + 20, this.y + 4, 6, 6);
                ctx.fillStyle = '#f00';
                ctx.fillRect(this.x + 12, this.y + 6, 3, 3);
                ctx.fillRect(this.x + 22, this.y + 6, 3, 3);
                break;
        }

        ctx.restore();

        // Health bar for multi-hit enemies
        if (this.maxHealth > 1) {
            ctx.fillStyle = '#333';
            ctx.fillRect(this.x, this.y - 10, this.width, 4);
            ctx.fillStyle = '#ff0000';
            ctx.fillRect(this.x, this.y - 10, this.width * (this.health / this.maxHealth), 4);
        }
    }
}

// ============================================
// BOSS CLASS
// ============================================
class Boss {
    constructor(level) {
        this.x = canvas.width - 120;
        this.y = canvas.height - 200;
        this.width = 80;
        this.height = 100;
        this.health = 10 + (level * 5);
        this.maxHealth = this.health;
        this.active = true;
        this.phase = 0;
        this.attackTimer = 0;
        this.moveTimer = 0;
        this.direction = -1;
        this.level = level;
    }

    update() {
        // Movement pattern
        this.moveTimer++;
        if (this.moveTimer >= 120) {
            this.direction *= -1;
            this.moveTimer = 0;
        }

        this.x += this.direction * 2;
        if (this.x < canvas.width / 2) this.x = canvas.width / 2;
        if (this.x > canvas.width - this.width - 20) this.x = canvas.width - this.width - 20;

        // Attack patterns based on phase
        this.attackTimer++;
        if (this.attackTimer >= 60 - this.level * 10) {
            this.attack();
            this.attackTimer = 0;
        }
    }

    attack() {
        // Different attack patterns
        const pattern = Math.floor(Math.random() * 3);

        switch (pattern) {
            case 0: // Single aimed shot
                this.shootAtPlayer();
                break;
            case 1: // Spread shot
                for (let angle = -30; angle <= 30; angle += 15) {
                    const rad = angle * Math.PI / 180;
                    enemyBullets.push({
                        x: this.x,
                        y: this.y + this.height / 2,
                        vx: Math.cos(rad) * -6,
                        vy: Math.sin(rad) * 6,
                        width: 12,
                        height: 12,
                        active: true
                    });
                }
                break;
            case 2: // Spawn minion
                if (enemies.length < 5) {
                    enemies.push(new Enemy(
                        this.x - 50,
                        this.y + 60,
                        'walker'
                    ));
                }
                break;
        }
    }

    shootAtPlayer() {
        const dx = player.x - this.x;
        const dy = player.y - this.y;
        const dist = Math.sqrt(dx * dx + dy * dy);
        enemyBullets.push({
            x: this.x,
            y: this.y + this.height / 2,
            vx: (dx / dist) * 7,
            vy: (dy / dist) * 7,
            width: 16,
            height: 16,
            active: true
        });
    }

    takeDamage() {
        this.health--;
        shakeScreen(5, 5);

        if (this.health <= 0) {
            this.die();
        }
    }

    die() {
        this.active = false;
        score += 1000 * this.level;

        // Big explosion
        for (let i = 0; i < 30; i++) {
            particles.push(new Particle(
                this.x + Math.random() * this.width,
                this.y + Math.random() * this.height,
                'explosion'
            ));
        }

        playSound('levelup');
        shakeScreen(20, 20);

        // Level complete
        setTimeout(() => {
            levelComplete();
        }, 1000);
    }

    draw() {
        // Bowser-like boss
        ctx.save();

        // Body
        ctx.fillStyle = '#228B22';
        ctx.fillRect(this.x + 10, this.y + 30, 60, 50);

        // Shell
        ctx.fillStyle = '#8B4513';
        ctx.beginPath();
        ctx.arc(this.x + 40, this.y + 50, 35, 0, Math.PI * 2);
        ctx.fill();

        // Shell spikes
        ctx.fillStyle = '#FFD700';
        for (let i = 0; i < 5; i++) {
            const angle = (i / 5) * Math.PI - Math.PI / 2;
            const spX = this.x + 40 + Math.cos(angle) * 30;
            const spY = this.y + 50 + Math.sin(angle) * 30;
            ctx.beginPath();
            ctx.moveTo(spX, spY);
            ctx.lineTo(spX + Math.cos(angle) * 15, spY + Math.sin(angle) * 15);
            ctx.lineTo(spX + 5, spY + 5);
            ctx.closePath();
            ctx.fill();
        }

        // Head
        ctx.fillStyle = '#228B22';
        ctx.fillRect(this.x, this.y, 50, 40);

        // Horns
        ctx.fillStyle = '#FFD700';
        ctx.beginPath();
        ctx.moveTo(this.x + 5, this.y);
        ctx.lineTo(this.x - 10, this.y - 20);
        ctx.lineTo(this.x + 15, this.y);
        ctx.closePath();
        ctx.fill();

        ctx.beginPath();
        ctx.moveTo(this.x + 35, this.y);
        ctx.lineTo(this.x + 50, this.y - 20);
        ctx.lineTo(this.x + 45, this.y);
        ctx.closePath();
        ctx.fill();

        // Eyes
        ctx.fillStyle = '#fff';
        ctx.fillRect(this.x + 8, this.y + 10, 12, 12);
        ctx.fillRect(this.x + 28, this.y + 10, 12, 12);
        ctx.fillStyle = '#f00';
        ctx.fillRect(this.x + 12, this.y + 14, 6, 6);
        ctx.fillRect(this.x + 32, this.y + 14, 6, 6);

        // Mouth with teeth
        ctx.fillStyle = '#000';
        ctx.fillRect(this.x + 5, this.y + 28, 40, 10);
        ctx.fillStyle = '#fff';
        for (let i = 0; i < 5; i++) {
            ctx.fillRect(this.x + 7 + i * 8, this.y + 28, 5, 5);
        }

        ctx.restore();

        // Health bar
        ctx.fillStyle = '#333';
        ctx.fillRect(this.x - 20, this.y - 30, this.width + 40, 12);
        ctx.fillStyle = this.health > this.maxHealth * 0.3 ? '#ff0000' : '#ff4444';
        ctx.fillRect(this.x - 18, this.y - 28, (this.width + 36) * (this.health / this.maxHealth), 8);

        // Boss name
        ctx.fillStyle = '#fff';
        ctx.font = '12px "Press Start 2P"';
        ctx.textAlign = 'center';
        ctx.fillText('BOSS', this.x + this.width / 2, this.y - 40);
    }
}

// ============================================
// POWER-UP CLASS
// ============================================
class Powerup {
    constructor(x, y) {
        this.x = x;
        this.y = y;
        this.width = 24;
        this.height = 24;
        this.vy = -3;
        this.active = true;
        this.type = this.randomType();
    }

    randomType() {
        const types = ['speed', 'double', 'shield', 'rapid', 'doublejump'];
        return types[Math.floor(Math.random() * types.length)];
    }

    update() {
        this.vy += 0.2;
        this.y += this.vy;

        const groundY = canvas.height - 80;
        if (this.y + this.height > groundY) {
            this.y = groundY - this.height;
            this.vy = 0;
        }
    }

    draw() {
        ctx.save();

        // Glow effect
        ctx.globalAlpha = 0.5 + Math.sin(Date.now() * 0.01) * 0.3;
        ctx.fillStyle = this.getColor();
        ctx.beginPath();
        ctx.arc(this.x + 12, this.y + 12, 18, 0, Math.PI * 2);
        ctx.fill();

        ctx.globalAlpha = 1;

        // Box
        ctx.fillStyle = '#FFD700';
        ctx.fillRect(this.x, this.y, 24, 24);
        ctx.fillStyle = '#FFA500';
        ctx.fillRect(this.x + 2, this.y + 2, 20, 20);

        // Question mark
        ctx.fillStyle = '#000';
        ctx.font = '14px "Press Start 2P"';
        ctx.textAlign = 'center';
        ctx.fillText('?', this.x + 12, this.y + 18);

        ctx.restore();
    }

    getColor() {
        switch (this.type) {
            case 'speed': return '#00ff00';
            case 'double': return '#ff8800';
            case 'shield': return '#00ffff';
            case 'rapid': return '#ff00ff';
            case 'doublejump': return '#ffff00';
            default: return '#ffffff';
        }
    }

    getIcon() {
        switch (this.type) {
            case 'speed': return '⚡';
            case 'double': return '🔥';
            case 'shield': return '🛡️';
            case 'rapid': return '💥';
            case 'doublejump': return '🦘';
            default: return '?';
        }
    }
}

// ============================================
// COIN CLASS
// ============================================
class Coin {
    constructor(x, y) {
        this.x = x;
        this.y = y;
        this.width = 20;
        this.height = 20;
        this.vy = -5;
        this.active = true;
        this.animFrame = 0;
    }

    update() {
        this.vy += 0.3;
        this.y += this.vy;

        const groundY = canvas.height - 80;
        if (this.y + this.height > groundY) {
            this.y = groundY - this.height;
            this.vy = 0;
        }

        this.animFrame = (this.animFrame + 0.2) % 4;
    }

    draw() {
        ctx.save();

        // Spinning effect
        const scaleX = Math.abs(Math.cos(this.animFrame));
        ctx.translate(this.x + 10, this.y + 10);
        ctx.scale(scaleX, 1);

        // Coin
        ctx.fillStyle = '#FFD700';
        ctx.beginPath();
        ctx.arc(0, 0, 10, 0, Math.PI * 2);
        ctx.fill();

        ctx.fillStyle = '#FFA500';
        ctx.beginPath();
        ctx.arc(0, 0, 6, 0, Math.PI * 2);
        ctx.fill();

        ctx.restore();
    }
}

// ============================================
// PARTICLE CLASS
// ============================================
class Particle {
    constructor(x, y, type) {
        this.x = x;
        this.y = y;
        this.type = type;
        this.life = 30;
        this.maxLife = 30;

        if (type === 'explosion') {
            this.vx = (Math.random() - 0.5) * 10;
            this.vy = (Math.random() - 0.5) * 10;
            this.size = 4 + Math.random() * 6;
            this.color = Math.random() > 0.5 ? '#FF6600' : '#FFFF00';
        } else if (type === 'dust') {
            this.vx = (Math.random() - 0.5) * 3;
            this.vy = -Math.random() * 3;
            this.size = 3 + Math.random() * 3;
            this.color = '#8B7355';
        }
    }

    update() {
        this.x += this.vx;
        this.y += this.vy;
        this.vy += 0.2;
        this.life--;
    }

    draw() {
        ctx.save();
        ctx.globalAlpha = this.life / this.maxLife;
        ctx.fillStyle = this.color;
        ctx.beginPath();
        ctx.arc(this.x, this.y, this.size, 0, Math.PI * 2);
        ctx.fill();
        ctx.restore();
    }
}

// ============================================
// GAME OBJECTS
// ============================================
let player;
let bullets = [];
let enemyBullets = [];
let enemies = [];
let boss = null;
let bossActive = false;
let powerups = [];
let coinItems = [];
let particles = [];
let platforms = [];
let cameraX = 0;
let screenShake = { x: 0, y: 0 };

// ============================================
// LEVEL DATA
// ============================================
const levels = [
    {
        // Level 1
        platforms: [
            { x: 150, y: 450, width: 120, height: 20 },
            { x: 350, y: 380, width: 120, height: 20 },
            { x: 550, y: 320, width: 120, height: 20 },
            { x: 750, y: 400, width: 120, height: 20 },
        ],
        enemies: [
            { x: 300, y: 500, type: 'walker' },
            { x: 500, y: 500, type: 'walker' },
            { x: 400, y: 300, type: 'flyer' },
            { x: 700, y: 500, type: 'walker' },
        ],
        bgColor1: '#5C94FC',
        bgColor2: '#00A800'
    },
    {
        // Level 2
        platforms: [
            { x: 100, y: 480, width: 100, height: 20 },
            { x: 280, y: 400, width: 100, height: 20 },
            { x: 450, y: 350, width: 100, height: 20 },
            { x: 620, y: 300, width: 100, height: 20 },
            { x: 800, y: 420, width: 100, height: 20 },
        ],
        enemies: [
            { x: 200, y: 500, type: 'walker' },
            { x: 400, y: 500, type: 'walker' },
            { x: 300, y: 250, type: 'flyer' },
            { x: 600, y: 500, type: 'shooter' },
            { x: 750, y: 200, type: 'flyer' },
        ],
        bgColor1: '#8B4513',
        bgColor2: '#654321'
    },
    {
        // Level 3
        platforms: [
            { x: 120, y: 500, width: 80, height: 20 },
            { x: 250, y: 420, width: 80, height: 20 },
            { x: 380, y: 340, width: 80, height: 20 },
            { x: 510, y: 280, width: 80, height: 20 },
            { x: 650, y: 360, width: 80, height: 20 },
            { x: 800, y: 450, width: 100, height: 20 },
        ],
        enemies: [
            { x: 200, y: 500, type: 'walker' },
            { x: 350, y: 500, type: 'walker' },
            { x: 500, y: 500, type: 'shooter' },
            { x: 400, y: 200, type: 'flyer' },
            { x: 650, y: 150, type: 'flyer' },
            { x: 750, y: 500, type: 'shooter' },
        ],
        bgColor1: '#2F4F4F',
        bgColor2: '#1a1a1a'
    }
];

// ============================================
// SCREEN EFFECTS
// ============================================
function shakeScreen(x, y) {
    screenShake.x = x;
    screenShake.y = y;
}

// ============================================
// PARALLAX BACKGROUND
// ============================================
let bgOffset = 0;
let clouds = [];

function initClouds() {
    clouds = [];
    for (let i = 0; i < 6; i++) {
        clouds.push({
            x: Math.random() * canvas.width,
            y: 50 + Math.random() * 150,
            width: 60 + Math.random() * 80,
            speed: 0.3 + Math.random() * 0.5
        });
    }
}

function drawBackground() {
    const level = levels[currentLevel - 1];

    // Sky gradient
    const gradient = ctx.createLinearGradient(0, 0, 0, canvas.height);
    gradient.addColorStop(0, level.bgColor1);
    gradient.addColorStop(0.6, level.bgColor1);
    gradient.addColorStop(0.6, level.bgColor2);
    gradient.addColorStop(1, level.bgColor2);
    ctx.fillStyle = gradient;
    ctx.fillRect(0, 0, canvas.width, canvas.height);

    // Clouds (parallax layer 1)
    ctx.fillStyle = 'rgba(255, 255, 255, 0.8)';
    clouds.forEach(cloud => {
        cloud.x -= cloud.speed;
        if (cloud.x + cloud.width < 0) cloud.x = canvas.width;

        // Draw puffy cloud
        ctx.beginPath();
        ctx.arc(cloud.x + cloud.width * 0.3, cloud.y, cloud.width * 0.25, 0, Math.PI * 2);
        ctx.arc(cloud.x + cloud.width * 0.5, cloud.y - 10, cloud.width * 0.3, 0, Math.PI * 2);
        ctx.arc(cloud.x + cloud.width * 0.7, cloud.y, cloud.width * 0.25, 0, Math.PI * 2);
        ctx.fill();
    });

    // Hills (parallax layer 2)
    ctx.fillStyle = 'rgba(0, 150, 0, 0.5)';
    for (let i = 0; i < 5; i++) {
        const hillX = (i * 250 - bgOffset * 0.2) % (canvas.width + 200) - 100;
        ctx.beginPath();
        ctx.arc(hillX, canvas.height - 60, 100 + i * 20, 0, Math.PI, true);
        ctx.fill();
    }

    // Ground
    ctx.fillStyle = '#8B4513';
    ctx.fillRect(0, canvas.height - 80, canvas.width, 80);

    // Grass on top
    ctx.fillStyle = '#228B22';
    ctx.fillRect(0, canvas.height - 80, canvas.width, 15);

    // Ground details
    ctx.fillStyle = '#654321';
    for (let x = 0; x < canvas.width; x += 40) {
        ctx.fillRect(x + 10, canvas.height - 60, 20, 10);
    }
}

function drawPlatforms() {
    platforms.forEach(plat => {
        // Platform top (grass)
        ctx.fillStyle = '#228B22';
        ctx.fillRect(plat.x, plat.y, plat.width, 8);

        // Platform body (brick)
        ctx.fillStyle = '#8B4513';
        ctx.fillRect(plat.x, plat.y + 8, plat.width, plat.height - 8);

        // Brick pattern
        ctx.fillStyle = '#654321';
        for (let bx = plat.x; bx < plat.x + plat.width; bx += 20) {
            ctx.fillRect(bx + 8, plat.y + 10, 2, 8);
        }
    });
}

// ============================================
// HUD UPDATE
// ============================================
function updateHUD() {
    // Health bar
    const healthPercent = (player.health / player.maxHealth) * 100;
    document.getElementById('health-fill').style.width = healthPercent + '%';

    // Lives
    let livesStr = '';
    for (let i = 0; i < lives; i++) livesStr += '❤️';
    document.getElementById('lives').textContent = livesStr;

    // Score and coins
    document.getElementById('score').textContent = score;
    document.getElementById('coins').textContent = coins;
    document.getElementById('level').textContent = currentLevel;
}

// ============================================
// GAME FLOW
// ============================================
function startGame() {
    initAudio();
    gameState = 'playing';
    currentLevel = 1;
    score = 0;
    coins = 0;
    lives = 3;

    loadLevel(currentLevel);

    document.getElementById('main-menu').classList.add('hidden');
    document.getElementById('game-hud').classList.remove('hidden');

    updateHUD();
    levelStartTime = Date.now();
}

function loadLevel(level) {
    const levelData = levels[level - 1];

    // Reset game objects
    player = new Player(100, canvas.height - 200);
    bullets = [];
    enemyBullets = [];
    enemies = [];
    boss = null;
    bossActive = false;
    powerups = [];
    coinItems = [];
    particles = [];

    // Load platforms
    platforms = levelData.platforms.map(p => ({ ...p }));

    // Load enemies
    levelData.enemies.forEach(e => {
        enemies.push(new Enemy(e.x, e.y, e.type));
    });

    initClouds();
}

function spawnBoss() {
    if (!bossActive) {
        bossActive = true;

        // Show warning
        const warning = document.getElementById('boss-warning');
        warning.classList.remove('hidden');
        setTimeout(() => {
            warning.classList.add('hidden');
            boss = new Boss(currentLevel);
        }, 2000);
    }
}

function pauseGame() {
    gameState = 'paused';
    document.getElementById('pause-menu').classList.remove('hidden');
}

function resumeGame() {
    gameState = 'playing';
    document.getElementById('pause-menu').classList.add('hidden');
}

function levelComplete() {
    gameState = 'levelComplete';

    const timeBonus = Math.max(0, 5000 - Math.floor((Date.now() - levelStartTime) / 100));
    score += timeBonus;

    document.getElementById('level-score').textContent = score;
    document.getElementById('level-coins').textContent = coins;
    document.getElementById('time-bonus').textContent = timeBonus;
    document.getElementById('level-complete').classList.remove('hidden');

    playSound('levelup');
}

function nextLevel() {
    currentLevel++;

    if (currentLevel > 3) {
        victory();
        return;
    }

    document.getElementById('level-complete').classList.add('hidden');
    loadLevel(currentLevel);
    gameState = 'playing';
    levelStartTime = Date.now();
    updateHUD();
}

function gameOver() {
    gameState = 'gameOver';

    document.getElementById('final-score').textContent = score;
    document.getElementById('final-level').textContent = currentLevel;
    document.getElementById('game-over').classList.remove('hidden');

    saveHighScore(score);
}

function victory() {
    gameState = 'victory';

    document.getElementById('victory-score').textContent = score;
    document.getElementById('victory-coins').textContent = coins;
    document.getElementById('victory-screen').classList.remove('hidden');

    saveHighScore(score);
}

function returnToMenu() {
    gameState = 'menu';

    document.getElementById('game-hud').classList.add('hidden');
    document.getElementById('pause-menu').classList.add('hidden');
    document.getElementById('game-over').classList.add('hidden');
    document.getElementById('level-complete').classList.add('hidden');
    document.getElementById('victory-screen').classList.add('hidden');
    document.getElementById('main-menu').classList.remove('hidden');
}

// ============================================
// HIGH SCORES
// ============================================
function saveHighScore(newScore) {
    let scores = JSON.parse(localStorage.getItem('marioShooterScores') || '[]');
    scores.push(newScore);
    scores.sort((a, b) => b - a);
    scores = scores.slice(0, 10);
    localStorage.setItem('marioShooterScores', JSON.stringify(scores));
}

function loadHighScores() {
    const scores = JSON.parse(localStorage.getItem('marioShooterScores') || '[]');
    const list = document.getElementById('highscore-list');
    list.innerHTML = '';

    if (scores.length === 0) {
        list.innerHTML = '<p style="color: #888; font-size: 10px;">No scores yet!</p>';
        return;
    }

    scores.forEach((score, i) => {
        const item = document.createElement('div');
        item.className = 'highscore-item';
        item.innerHTML = `<span>#${i + 1}</span><span>${score}</span>`;
        list.appendChild(item);
    });
}

// ============================================
// COLLISION DETECTION
// ============================================
function checkCollision(a, b) {
    return a.x < b.x + b.width &&
        a.x + a.width > b.x &&
        a.y < b.y + b.height &&
        a.y + a.height > b.y;
}

// ============================================
// GAME UPDATE
// ============================================
function update() {
    if (gameState !== 'playing') return;

    // Update player
    player.update();

    // Update bullets
    bullets.forEach(b => b.update());
    bullets = bullets.filter(b => b.active);

    // Update enemy bullets
    enemyBullets.forEach(b => {
        b.x += b.vx;
        b.y += b.vy;
        if (b.x < -50 || b.x > canvas.width + 50 || b.y < -50 || b.y > canvas.height + 50) {
            b.active = false;
        }
    });
    enemyBullets = enemyBullets.filter(b => b.active);

    // Update enemies
    enemies.forEach(e => e.update());
    enemies = enemies.filter(e => e.active);

    // Update boss
    if (boss && boss.active) {
        boss.update();
    }

    // Check if all enemies dead -> spawn boss
    if (enemies.length === 0 && !bossActive && !boss) {
        spawnBoss();
    }

    // Update power-ups
    powerups.forEach(p => p.update());
    powerups = powerups.filter(p => p.active);

    // Update coins
    coinItems.forEach(c => c.update());
    coinItems = coinItems.filter(c => c.active);

    // Update particles
    particles.forEach(p => p.update());
    particles = particles.filter(p => p.life > 0);

    // ============================================
    // COLLISIONS
    // ============================================

    // Bullets vs Enemies
    bullets.forEach(b => {
        enemies.forEach(e => {
            if (b.active && e.active && checkCollision(b, e)) {
                b.active = false;
                e.takeDamage();
            }
        });

        // Bullets vs Boss
        if (boss && boss.active && b.active && checkCollision(b, boss)) {
            b.active = false;
            boss.takeDamage();
        }
    });

    // Enemy bullets vs Player
    enemyBullets.forEach(b => {
        if (b.active && checkCollision(b, player)) {
            b.active = false;
            player.takeDamage(20);
        }
    });

    // Enemies vs Player
    enemies.forEach(e => {
        if (e.active && checkCollision(e, player)) {
            player.takeDamage(25);
        }
    });

    // Boss vs Player
    if (boss && boss.active && checkCollision(boss, player)) {
        player.takeDamage(30);
    }

    // Power-ups vs Player
    powerups.forEach(p => {
        if (p.active && checkCollision(p, player)) {
            p.active = false;
            player.powerup = p.type;
            player.powerupTimer = 600; // 10 seconds

            const indicator = document.getElementById('powerup-indicator');
            document.getElementById('powerup-icon').textContent = p.getIcon();
            indicator.classList.remove('hidden');

            // Reset timer animation
            const timer = document.getElementById('powerup-timer');
            timer.style.animation = 'none';
            timer.offsetHeight; // Trigger reflow
            timer.style.animation = 'timerDrain 10s linear forwards';

            playSound('powerup');
        }
    });

    // Coins vs Player
    coinItems.forEach(c => {
        if (c.active && checkCollision(c, player)) {
            c.active = false;
            coins++;
            score += 50;
            playSound('coin');
            updateHUD();
        }
    });

    // Screen shake decay
    screenShake.x *= 0.9;
    screenShake.y *= 0.9;

    // Background parallax
    bgOffset += 0.5;
}

// ============================================
// GAME RENDER
// ============================================
function render() {
    ctx.save();

    // Apply screen shake
    ctx.translate(Math.random() * screenShake.x - screenShake.x / 2,
        Math.random() * screenShake.y - screenShake.y / 2);

    // Clear canvas
    ctx.clearRect(0, 0, canvas.width, canvas.height);

    // Draw background
    drawBackground();

    // Draw platforms
    drawPlatforms();

    // Draw coins
    coinItems.forEach(c => c.draw());

    // Draw power-ups
    powerups.forEach(p => p.draw());

    // Draw enemies
    enemies.forEach(e => e.draw());

    // Draw boss
    if (boss && boss.active) {
        boss.draw();
    }

    // Draw player
    player.draw();

    // Draw bullets
    bullets.forEach(b => b.draw());

    // Draw enemy bullets
    enemyBullets.forEach(b => {
        ctx.fillStyle = '#ff0000';
        ctx.beginPath();
        ctx.arc(b.x + b.width / 2, b.y + b.height / 2, b.width / 2, 0, Math.PI * 2);
        ctx.fill();

        ctx.fillStyle = '#ffff00';
        ctx.beginPath();
        ctx.arc(b.x + b.width / 2, b.y + b.height / 2, b.width / 4, 0, Math.PI * 2);
        ctx.fill();
    });

    // Draw particles
    particles.forEach(p => p.draw());

    ctx.restore();
}

// ============================================
// GAME LOOP
// ============================================
function gameLoop() {
    update();
    render();
    requestAnimationFrame(gameLoop);
}

// ============================================
// EVENT LISTENERS
// ============================================
document.getElementById('start-btn').addEventListener('click', startGame);

document.getElementById('controls-btn').addEventListener('click', () => {
    document.getElementById('main-menu').classList.add('hidden');
    document.getElementById('controls-screen').classList.remove('hidden');
});

document.getElementById('back-controls').addEventListener('click', () => {
    document.getElementById('controls-screen').classList.add('hidden');
    document.getElementById('main-menu').classList.remove('hidden');
});

document.getElementById('highscore-btn').addEventListener('click', () => {
    loadHighScores();
    document.getElementById('main-menu').classList.add('hidden');
    document.getElementById('highscore-screen').classList.remove('hidden');
});

document.getElementById('back-highscore').addEventListener('click', () => {
    document.getElementById('highscore-screen').classList.add('hidden');
    document.getElementById('main-menu').classList.remove('hidden');
});

document.getElementById('resume-btn').addEventListener('click', resumeGame);

document.getElementById('restart-btn').addEventListener('click', () => {
    document.getElementById('pause-menu').classList.add('hidden');
    loadLevel(currentLevel);
    gameState = 'playing';
    updateHUD();
});

document.getElementById('quit-btn').addEventListener('click', returnToMenu);

document.getElementById('next-level-btn').addEventListener('click', nextLevel);

document.getElementById('retry-btn').addEventListener('click', () => {
    document.getElementById('game-over').classList.add('hidden');
    score = 0;
    coins = 0;
    lives = 3;
    currentLevel = 1;
    loadLevel(1);
    gameState = 'playing';
    updateHUD();
});

document.getElementById('menu-btn').addEventListener('click', returnToMenu);

document.getElementById('play-again-btn').addEventListener('click', () => {
    document.getElementById('victory-screen').classList.add('hidden');
    score = 0;
    coins = 0;
    lives = 3;
    currentLevel = 1;
    loadLevel(1);
    gameState = 'playing';
    updateHUD();
});

document.getElementById('victory-menu-btn').addEventListener('click', returnToMenu);

// ============================================
// START
// ============================================
gameLoop();
