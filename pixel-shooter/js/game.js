// ── Game State Machine ───────────────────────────────
// Core game logic: states, scoring, collision detection

import { Player } from './player.js';
import { WaveSpawner } from './enemy.js';
import { ParticleSystem } from './particles.js';
import * as ProjectileModule from './projectile.js';

export const GameState = {
    MENU: 'menu',
    PLAYING: 'playing',
    WAVE_INTRO: 'wave_intro',
    GAME_OVER: 'game_over'
};

export class Game {
    constructor(canvasWidth, canvasHeight, audio) {
        this.width = canvasWidth;
        this.height = canvasHeight;
        this.audio = audio;

        this.state = GameState.MENU;
        this.player = new Player(canvasWidth / 2, canvasHeight / 2);
        this.spawner = new WaveSpawner(canvasWidth, canvasHeight);
        this.particles = new ParticleSystem();

        this.projectiles = [];
        this.enemies = [];
        this.score = 0;
        this.combo = 0;
        this.comboTimer = 0;
        this.comboDecay = 2.0; // seconds before combo resets
        this.waveIntroTimer = 0;
        this.gameOverTimer = 0;
        this.personalBest = 0;
    }

    startGame() {
        this.state = GameState.PLAYING;
        this.player.reset(this.width / 2, this.height / 2);
        this.projectiles = [];
        this.enemies = [];
        this.particles.clear();
        this.score = 0;
        this.combo = 0;
        this.comboTimer = 0;
        this.spawner = new WaveSpawner(this.width, this.height);
        this.audio.init();
        this.audio.startMusic();
        this._startNextWave();
    }

    _startNextWave() {
        this.spawner.startWave();
        this.state = GameState.WAVE_INTRO;
        this.waveIntroTimer = 2.0;
        this.audio.playWaveComplete();
    }

    update(dt, input, renderer) {
        switch (this.state) {
            case GameState.MENU:
                this._updateMenu(input);
                break;
            case GameState.WAVE_INTRO:
                this._updateWaveIntro(dt, input);
                break;
            case GameState.PLAYING:
                this._updatePlaying(dt, input, renderer);
                break;
            case GameState.GAME_OVER:
                this._updateGameOver(dt, input);
                break;
        }
    }

    _updateMenu(input) {
        if (input.isKeyDown('enter') || input.consumeClick()) {
            this.startGame();
        }
    }

    _updateWaveIntro(dt, input) {
        this.waveIntroTimer -= dt;
        // Player can still move during intro
        this.player.update(dt, input, this.width, this.height);
        this.particles.update(dt);
        if (this.waveIntroTimer <= 0) {
            this.state = GameState.PLAYING;
        }
    }

    _updatePlaying(dt, input, renderer) {
        // Update player
        this.player.update(dt, input, this.width, this.height);

        // Player shooting
        const bullet = this.player.shoot(input);
        if (bullet) {
            this.projectiles.push(bullet);
            this.audio.playShoot();
            this.particles.muzzleFlash(
                this.player.x + Math.cos(this.player.angle) * 14,
                this.player.y + Math.sin(this.player.angle) * 14,
                this.player.angle
            );
        }

        // Update spawner
        this.spawner.update(dt, this.enemies, ProjectileModule);

        // Update enemies
        this.enemies.forEach(enemy => {
            enemy.update(dt, this.player.x, this.player.y);
            // Enemy shooting
            const eBullet = enemy.tryShoot(this.player.x, this.player.y);
            if (eBullet) this.projectiles.push(eBullet);
        });

        // Update projectiles
        this.projectiles.forEach(p => p.update(dt, this.width, this.height));
        this.projectiles = this.projectiles.filter(p => p.alive);

        // Collision: player bullets vs enemies
        for (let i = this.projectiles.length - 1; i >= 0; i--) {
            const p = this.projectiles[i];
            if (!p.isPlayerBullet) continue;

            for (let j = this.enemies.length - 1; j >= 0; j--) {
                const e = this.enemies[j];
                if (this._checkCollision(p, e)) {
                    p.alive = false;
                    this.particles.spark(p.x, p.y, e.color);
                    this.audio.playHit();

                    if (e.takeDamage(p.damage)) {
                        // Enemy killed
                        this.combo++;
                        this.comboTimer = this.comboDecay;
                        const points = e.points * Math.max(1, this.combo);
                        this.score += points;
                        this.spawner.onEnemyKilled();
                        this.particles.explode(e.x, e.y, [e.color, e.glowColor, '#fff', '#ff0']);
                        this.audio.playExplosion();
                        renderer.shake(4, 0.15);
                    }
                    break;
                }
            }
        }

        // Remove dead enemies
        this.enemies = this.enemies.filter(e => e.alive);

        // Collision: enemy bullets vs player
        for (let i = this.projectiles.length - 1; i >= 0; i--) {
            const p = this.projectiles[i];
            if (p.isPlayerBullet) continue;
            if (this._checkCollisionWithPlayer(p)) {
                p.alive = false;
                this._handlePlayerHit(renderer);
            }
        }

        // Collision: enemies vs player (contact damage)
        this.enemies.forEach(e => {
            if (this._checkCollisionWithPlayer(e)) {
                this._handlePlayerHit(renderer);
            }
        });

        // Combo decay
        if (this.comboTimer > 0) {
            this.comboTimer -= dt;
            if (this.comboTimer <= 0) this.combo = 0;
        }

        // Update particles
        this.particles.update(dt);

        // Check wave complete
        if (this.spawner.isWaveComplete()) {
            this._startNextWave();
        }

        // Check player death
        if (!this.player.alive) {
            this.state = GameState.GAME_OVER;
            this.gameOverTimer = 0;
            this.audio.stopMusic();
            this.audio.playGameOver();
            renderer.shake(8, 0.5);
            this.particles.explode(this.player.x, this.player.y, ['#4af', '#0ff', '#fff', '#08f'], 30);
            if (this.score > this.personalBest) {
                this.personalBest = this.score;
            }
        }
    }

    _handlePlayerHit(renderer) {
        if (this.player.takeDamage()) {
            this.audio.playPlayerHit();
            renderer.shake(6, 0.2);
            this.particles.damageFlash(this.player.x, this.player.y);
            this.combo = 0;
        }
    }

    _updateGameOver(dt, input) {
        this.gameOverTimer += dt;
        this.particles.update(dt);
        if (this.gameOverTimer > 1.0 && (input.isKeyDown('enter') || input.consumeClick())) {
            this.state = GameState.MENU;
        }
    }

    _checkCollision(a, b) {
        const ab = typeof a.getBounds === 'function' ? a.getBounds() : { x: a.x - a.size / 2, y: a.y - a.size / 2, width: a.size, height: a.size };
        const bb = b.getBounds();
        return ab.x < bb.x + bb.width &&
            ab.x + ab.width > bb.x &&
            ab.y < bb.y + bb.height &&
            ab.y + ab.height > bb.y;
    }

    _checkCollisionWithPlayer(obj) {
        const pb = this.player.getBounds();
        const ob = typeof obj.getBounds === 'function' ? obj.getBounds() : { x: obj.x - obj.size / 2, y: obj.y - obj.size / 2, width: obj.size, height: obj.size };
        return pb.x < ob.x + ob.width &&
            pb.x + pb.width > ob.x &&
            pb.y < ob.y + ob.height &&
            pb.y + pb.height > ob.y;
    }

    draw(renderer) {
        const r = renderer;
        r.drawStarfield(1 / 60);

        switch (this.state) {
            case GameState.MENU:
                r.drawMenu();
                break;
            case GameState.WAVE_INTRO:
                this.player.draw(r.ctx);
                this.particles.draw(r.ctx);
                r.drawHUD(this.player, this.score, this.spawner.wave, this.combo);
                r.drawWaveAnnouncement(this.spawner.wave, this.waveIntroTimer);
                break;
            case GameState.PLAYING:
                // Draw entities
                this.enemies.forEach(e => e.draw(r.ctx));
                this.projectiles.forEach(p => p.draw(r.ctx));
                this.player.draw(r.ctx);
                this.particles.draw(r.ctx);
                r.drawHUD(this.player, this.score, this.spawner.wave, this.combo);
                r.drawCrosshair(r.ctx.canvas._mouseX || 0, r.ctx.canvas._mouseY || 0);
                break;
            case GameState.GAME_OVER:
                this.enemies.forEach(e => e.draw(r.ctx));
                this.projectiles.forEach(p => p.draw(r.ctx));
                this.particles.draw(r.ctx);
                r.drawGameOver(this.score, this.personalBest);
                break;
        }
    }
}
