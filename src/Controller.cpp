#include "Controller.h"
#include <cmath>
#include <iostream>
#include <algorithm>
#include <typeinfo>
namespace mrsd
{
	void Controller::control(const mrsd::Game& g, float t)
	{
        std::vector<Player*> players = g.getPlayers();
		if(!players.empty())
        {
            int des_pos = pickSafeSpot(g);
            if(players[0]->x < des_pos)
			    players[0]->x += g.playerSpeed;

            else if(players[0]->x > des_pos)
			    players[0]->x -= g.playerSpeed;
        }
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
        pred.t = p.vy+sqrt(pow(p.vy,2)+19.6*p.y)/9.8;
        pred.x = p.x + p.vx*pred.t;
		return pred;
        std::cout<<pred.t;
    }

    std::vector<int> Controller::determineSafeSpots(const Game& g)
	{ 
        std::vector<int> safespot(g.getWidth(),1);
        std::list<Projectile> projectiles = g.getProjectiles();
        std::list<Explosion> exps = g.getExplosions();
        for(std::list<Projectile>::iterator it = projectiles.begin(); it != projectiles.end(); ++it)
		{
            Prediction pred = trackProjectile(*it,g);
            if(pred.t<3.5){
                for(int i = std::floor(pred.x-g.explosionSize-5);i<std::ceil(pred.x+g.explosionSize+5);i++)
                {
                	int idx = i;
                	if(idx<0)
                		idx = 0;
                	if(idx>g.getWidth())
                		idx = g.getWidth()-1;
                    safespot[idx] = 0;                
                }
            }
        }
	    for(std::list<Explosion>::iterator it = exps.begin(); it != exps.end(); ++it)
		{
				Explosion exp = *it;
                for(int i = std::floor(exp.x-g.explosionSize-5);i<std::ceil(exp.x+g.explosionSize+5);i++)
                {
                	int idx = i;
                	if(idx<0)
                		idx = 0;
                	if(idx>g.getWidth())
                		idx = g.getWidth()-1;
                    safespot[idx] = 0;                
                }
            }
        // for(int i=0;i<g.getWidth();i++){
        //     std::cout<<safespot[i];
        // }
        // std::cout<<"\n\n";
        return safespot;
	}

	int Controller::pickSafeSpot(const Game& g)
	{
       int dist_min = g.getWidth();
       int pos;
	   std::vector<int>  safespot = determineSafeSpots(g);
	   std::vector<Player*> players = g.getPlayers();
       for(int i=0;i<g.getWidth();i++)
       {
        if(safespot[i]==1){
            int dist = std::abs(i-players[0]->x);
            if(dist<dist_min){
                dist_min = dist;
                pos = i;
            }
        }
       }
       return pos;
	}
}
