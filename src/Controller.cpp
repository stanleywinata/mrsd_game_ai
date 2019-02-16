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
			    players[0]->x = players[0]->x+g.playerSpeed;

            else if(players[0]->x > des_pos)
			    players[0]->x = players[0]->x-g.playerSpeed;
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
        pred.t = (-p.vy+sqrt(pow(p.vy,2)+4*g.getGravity()/2*p.y))/(g.getGravity());
        pred.x = p.x + p.vx*pred.t;
        if(pred.x < 0 ){
            pred.x = 0;
        }
		return pred;
	}

    std::vector<int> Controller::determineSafeSpots(const Game& g)
	{ 
        std::vector<int> safespot(g.getWidth(),1);
        std::list<Projectile> projectiles = g.getProjectiles();
        for(std::list<Projectile>::iterator it = projectiles.begin(); it != projectiles.end(); ++it)
		{
            Prediction pred = trackProjectile(*it,g);
            if(pred.t<1){
                for(int i = std::floor(pred.x-g.explosionSize);i<=std::ceil(pred.x+g.explosionSize);i++)
                {
                    safespot[i] = 0;                
                }
            }
		}
        // for(std::vector<int>::const_iterator it = safespot.begin();it != safespot.end();++it)
        //     std::cout<<*it<<' ';
        // std::cout<<"\n"<<"\n";
        return safespot;
	}

	int Controller::pickSafeSpot(const Game& g)
	{
       int dist_min = 1000000;
       int pos;
	   std::vector<int>  safespot = determineSafeSpots(g);
	   std::vector<Player*> players = g.getPlayers();
       // int index = players[0]->x;
       for(std::vector<int>::iterator it = safespot.begin();it != safespot.end();++it){
           if(*it==1){
               auto index = std::distance(safespot.begin(),it);
               int dist = std::abs(index-players[0]->x);
               if(dist<dist_min){
                   dist_min = dist;
                   pos = index;
               }
           }
       }
       return pos;
	}
}
