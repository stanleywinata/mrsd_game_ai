#include "Controller.h"
#include <cmath>
#include <iostream>
namespace mrsd
{
	void Controller::control(const mrsd::Game& g, float t)
	{
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
        tf = (-p.vy+sqrt(pow(p.vy,2)+4*g.gravity/2*p.y))/(g.gravity);
        pred.t = g.time + tf; // For if ask for game time, not time until explosion 
        pred.x = p.x + p.vx*tf;
		return pred;
	}

    std::Vector<int> Controller::determineSafeSpots(const Game& g)
	{ 
		// dangerZone = new int[w+1];
		// for(int i = 0; i < w+1; ++i) dangerZone[i] = 0;
        std::Vector<int> safespot(g.w,1);
        for(std::list<Projectile>::iterator it = projectiles.begin();
				it != projectiles.end();++it)
		{
            int idx = it - g.projectiles.begin();
            Prediction pred = trackProjectile(*it,g);
            if(pred.x == 0 && pred.t==g.time){
                safespot[idx] = 0;
            }
		}
        return safespot;
	}

	int Controller::pickSafeSpot(const Game& g)
	{
		return 0;
	}
}
