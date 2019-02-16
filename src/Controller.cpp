#include "Controller.h"
#include <cmath>
#include <iostream>
#include <algorithm>
namespace mrsd
{
	void Controller::control(const mrsd::Game& g, float t)
	{
        pickSafeSpot(g);
	}

	void Controller::createPlayer(Game& g)
	{
		if(p == 0)
		{
			p = new Player();
			p->dead = true;
		}
		if(p->dead)
		{
			p->dead = false;
			p->x = g.getWidth()/2;
			g.newPlayer(p);
		}
	}

	Prediction Controller::trackProjectile(const Projectile& p, const Game& g)
	{
        Prediction pred;
        double tf = (-p.vy+sqrt(pow(p.vy,2)+4*g.getGravity()/2*p.y))/(g.getGravity());
        pred.t = g.getGameTime() + tf; // For if ask for game time, not time until explosion 
        pred.x = p.x + p.vx*tf;
		return pred;
	}

    std::vector<int> Controller::determineSafeSpots(const Game& g)
	{ 
        std::vector<int> safespot(g.getWidth(),1);
        std::list<Projectile> projectiles = g.getProjectiles();
        for(std::list<Projectile>::iterator it = projectiles.begin(); it != projectiles.end(); ++it)
		{
            int idx = std::distance(projectiles.begin(), it);
            Prediction pred = trackProjectile(*it,g);
            if(pred.x == 0 && pred.t==g.getGameTime()){
                safespot[idx] = 0;
                safespot[idx+g.explosionSize] = 0;
                safespot[idx-g.explosionSize] = 0;
            }
		}
        return safespot;
	}

	int Controller::pickSafeSpot(const Game& g)
	{
	   std::vector<int>  safespot = determineSafeSpots(g);
       std::vector<int>::iterator it = std::find(safespot.begin(),safespot.end(),1);
       auto pos = std::distance(safespot.begin(),it);
       std::cout<<pos;
	}
}
