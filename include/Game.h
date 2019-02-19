#pragma once
#include <vector>
#include <list>
#include "Player.h"
#include "Game.h"
#include "Enemy.h"
#include "Projectile.h"
#include "Explosion.h"

namespace mrsd
{
class Frontend;

class Game
{
	public:
	Game(int w, int h, float timestep);
	~Game();
	void newPlayer(Player*);
	Enemy& newEnemy(int x, int y);
	void tick();
	void setGravity(float g) { gravity = g; }
	float getGravity() const { return gravity; }
	int getWidth() const { return w; }
	int getHeight() const { return h; }
	float getGameTime() const { return time; }
	float getTimeStep() const { return timestep; }
	const std::vector<Player*>& getPlayers() const { return players; }
	const std::vector<Enemy>& getEnemies() const { return enemies; }
	const std::list<Projectile>& getProjectiles() const { return projectiles; }
	const std::list<Explosion>& getExplosions() const { return explosions; }
	float explosionSize;
	float explosionTime;
	float playerSpeed;
    private:
	    int w, h;
	    float gravity;
	    float time;
        bool tickProjectile(Projectile& p);
		bool tickExplosion(Explosion& e);
		bool tickPlayer(Player& p);
		bool tickEnemy(Enemy& e);
		void explode(float x);
		int *dangerZone;
		float timestep;
		std::vector<Player*> players;
		std::vector<Enemy> enemies;
		std::list<Explosion> explosions;
	    std::list<Projectile> projectiles;
};

}
