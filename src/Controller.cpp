#include "Controller.h"
#include <cmath>
#include <iostream>
#include <algorithm>
#include <typeinfo>
#include <eigen3/Eigen/Dense>
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
	        // std::cout<<players[0]->x<<"\n";
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
        pred.t = (p.vy+sqrt(pow(p.vy,2)+19.62*p.y))/9.81;
        pred.x = p.x + p.vx*pred.t;
		return pred;
    }

    std::vector<int> Controller::determineSafeSpots(const Game& g)
	{ 
        std::vector<int> safespot(g.getWidth(),1);
        std::list<Projectile> projectiles = g.getProjectiles();
        std::list<Explosion> exps = g.getExplosions();
        for(std::list<Projectile>::iterator it = projectiles.begin(); it != projectiles.end(); ++it)
		{
            Prediction pred = trackProjectile(*it,g);
            if(pred.t<4){
                // std::cout<<"hi"<<pred.x<<"\n\n";
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
	 //    for(std::list<Explosion>::iterator it = exps.begin(); it != exps.end(); ++it)
		// {
		// 		Explosion exp = *it;
  //               for(int i = std::floor(exp.x-g.explosionSize-5);i<std::ceil(exp.x+g.explosionSize+5);i++)
  //               {
  //               	int idx = i;
  //               	if(idx<0)
  //               		idx = 0;
  //               	if(idx>g.getWidth())
  //               		idx = g.getWidth()-1;
  //                   safespot[idx] = 0;                
  //               }
  //           }
        }
            return safespot;
		}
	

	int Controller::pickSafeSpot(const Game& g)
	{
       int dist_min = 1000000;
       int pos;
	   std::vector<int>  safespot = determineSafeSpots(g);
	   std::vector<Player*> players = g.getPlayers();
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
