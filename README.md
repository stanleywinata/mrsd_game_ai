# mrsd_game_ai

Question 1: How does the AI work

The AI works in 3 steps. The first step was predicting where the projectiles would land found in trackProjectile. It does it by calculating it through the equation of motion for constant acceleration:
s = ut + ½ at2
½ at2+ut-s =0
substituting in values and solving for quadratic equation and considering time cannot be negative:
t = (vy+√( vy2+4*4.905*y))/9.81
x = x0 + vx*t
After predicting when and where the projectiles would go to, it will combine those information with the information received from the getExplosion method to determine which area will be safe to go to, found in determineSafeSpots. After getting all the spots that are safe, it picks the spot to go to by seeing which spots are closest to the current positions, found in pickSafeSpot. Then it will move to the desired position by checking if the desired position is more to the left or to the right of the current position, and then it will send the velocity of the movement in that direction. 

Question 2: Challenges

The first challenge I had was accessing private members, as I did not read the header files properly, but after reading it more carefully, I realized there was pre-written methods to access these values. A second problem I had was, since familiarizing my self with CPP syntax again, for example, I spent a few hours working on a bug, which turns out was caused by erasing the wrong bracket, making the safespot being updated everytime the program iterate through the projectiles.

Question 3: Hard Scenario
It does not work on hard scenario. One potential reason for this is, since I have placed extra padding on to the explosion size, when there is too much explosions, the padding would overlap, leading to the AI thinking there is no other place to go.

Question 4: Assignment Goals:
I feel the goal of this assignment is to give everybody an equal chance to learn about programming, and also familiarize students with C++(The programming language choice for controls and robotics). I think this assignment meets its goals, as in some groups the people in charge of mechanical or electrical portion of the project do not have much chance to program, hence a small software project will give them the chance to hone their skills. Moreover, this assignment also expose us to C++ object oriented programming and also openGL library which is great.