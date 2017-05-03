#include <stdlib.h> // rand
#include <time.h> // for seeding rand
#include <Windows.h> // Sleep
#include <iostream> // std::cout
#include <functional> // std::greater

#include <Heap\Inc\Heap.h>
#include <Math\Inc\Vector3.h>
#include <cmath>

namespace
{
struct Player;
float Dist(const Player& player, const Math::Vector3& enemy);
float KillValue(const Player& player, const Math::Vector3& enemy);
const Math::Vector3 enemyLoc(500.0f, 500.0f, 500.0f);
enum Type
{
	Solder = 0,
	Sergeant = 2,
	Commander = 10
};
struct Player
{
	Math::Vector3 pos;
	Math::Vector3 vel; // direction is towards enemy in the middle, and speed is 1.f for solder, 0.5 for Sergeant, 0.1 for Commander type
	Type type;
	float killVal;

	void Instantiate(Type t,unsigned int seed)
	{
		type = t;
		killVal = 0;
		srand(seed);
		pos.x = rand() % 1000;
		pos.y = rand() % 1000;
		pos.z = rand() % 1000;
		vel.x = (enemyLoc.x - pos.x);
		vel.y = (enemyLoc.y - pos.y);
		vel.z = (enemyLoc.z - pos.z);
		vel = vel.Normal()*t;
	}
	void Update(float dt)
	{
		pos += vel*dt;
		killVal = KillValue(*this, enemyLoc);
	}

	friend bool operator==(const Player& L, const Player& R)
	{
		if (L.killVal != R.killVal)
			return false;
		if (L.pos != R.pos)
			return false;
		if (L.type != R.type)
			return false;
		return true;
	}
	friend bool operator!=(const Player& L, const Player& R) { return !(L == R); }
	friend bool operator<(const Player& L, const Player& R) { return L.killVal < R.killVal; }
	friend bool operator>(const Player& L, const Player& R) { return !(L < R); }
};

float Dist(const Player& player, const Math::Vector3& enemy)
{
	float xs = (player.pos.x - enemy.x);
	xs *= xs;
	float ys = (player.pos.y - enemy.y);
	ys *= ys;
	float zs = (player.pos.z - enemy.z);
	zs *= zs;
	float dist = sqrt(xs + ys + zs);
	return dist;
}

float KillValue(const Player& player, const Math::Vector3& enemy)
{
	return (Dist(player, enemy) + (10 * player.type)); // type == 0 for solder, 2 for Sergeant, and 10 for Commander. 
}

}

void main()
{
	std::vector<Player> players;
	int numPlayers = 1000;
	int numSerg = 100;
	int numCom = 10;
	players.reserve(numPlayers);

	Player p;
	while (players.size() < numCom && players.size() < numPlayers)
	{
		p.Instantiate(Type::Commander, time(NULL)+players.size());
		players.push_back(p);
		Sleep(10);
	}
	while (players.size() < numCom+numSerg && players.size() < numPlayers)
	{
		p.Instantiate(Type::Sergeant, time(NULL) + players.size());
		players.push_back(p);
		Sleep(10);
	}
	while (players.size() < numPlayers)
	{
		p.Instantiate(Type::Solder, time(NULL) + players.size());
		players.push_back(p);
		Sleep(10);
	}

	float dt = 0.03;
	while (numPlayers > 0)
	{
		Heap::Heap<Player,std::greater<Player>> heap;
		for (int i = 0; i < players.size(); ++i)
		{
			players[i].Update(dt); // update players' position: player.pos += player.vel * dt;
			heap.Push(players[i]); // sort them based on their killValue using heap sort.
		}
		Player top = heap.Pop(); // kill(delete) the closest player by remove the root of the heap.
		std::cout << top.type;
		int i = 0;
		while (top != players[i])
		{
			++i;
		}
		players.erase(players.begin() + i);
		--numPlayers;
		Sleep(30); // sleep for 30 ms.
	}
}

