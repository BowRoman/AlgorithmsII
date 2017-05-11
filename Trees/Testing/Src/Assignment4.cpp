#include <stdlib.h> // rand
#include <time.h> // for seeding rand
#include <Windows.h> // Sleep
#include <iostream> // std::cout
#include <functional> // std::greater
#include <cmath>

#include <Heap\Inc\Heap.h>
#include <Math\Inc\Vector3.h>

namespace
{
struct Player;

const Math::Vector3 enemyLoc(500.0f, 500.0f, 500.0f);

float Dist(const Math::Vector3& player, const Math::Vector3& enemy = enemyLoc);
float KillValue(const Player& player, const Math::Vector3& enemy = enemyLoc);

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
		pos.x = (float)(rand() % 1000);
		pos.y = (float)(rand() % 1000);
		pos.z = (float)(rand() % 1000);
		vel.x = (enemyLoc.x - pos.x);
		vel.y = (enemyLoc.y - pos.y);
		vel.z = (enemyLoc.z - pos.z);
		vel = vel.Normal();
		if (type == Type::Sergeant)
			vel *= 0.5f;
		else if (type == Type::Commander)
			vel *= 0.1f;
	} // Instantiate()
	void Update(float dt)
	{
		pos += vel*dt;
		killVal = KillValue(*this, enemyLoc);
	} // Update()

	friend bool operator==(const Player& L, const Player& R)
	{
		if (L.killVal != R.killVal)
			return false;
		if (L.pos != R.pos)
			return false;
		if (L.type != R.type)
			return false;
		return true;
	} // operator==
	friend bool operator!=(const Player& L, const Player& R) { return !(L == R); }
	friend bool operator<(const Player& L, const Player& R) { return L.killVal < R.killVal; }
	friend bool operator>(const Player& L, const Player& R) { return !(L < R); }
}; // Player

float Dist(const Math::Vector3& player, const Math::Vector3& enemy)
{
	float xs = (player.x - enemy.x);
	xs *= xs;
	float ys = (player.y - enemy.y);
	ys *= ys;
	float zs = (player.z - enemy.z);
	zs *= zs;
	float dist = sqrt(xs + ys + zs);
	return dist;
}

float KillValue(const Player& player, const Math::Vector3& enemy)
{
	return (3000*(1/Dist(player.pos, enemy))) + (player.type); // type == 0 for solder, 2 for Sergeant, and 10 for Commander. 
} // KillValue()

} // namespace

void main()
{
	std::vector<Player> players;
	int numPlayers = 1000;
	int numSerg = 100;
	int numCom = 10;
	players.reserve(numPlayers);

	std::cout << "Total players: " << numPlayers << std::endl;
	std::cout << "Number of Sergeants: " << numSerg << "(" << "Serg" << ")" << std::endl;
	std::cout << "Number of Commanders: " << numCom << "(" << "Comm" << ")" << std::endl;
	std::cout << "Number of Soldiers: " << numPlayers - numSerg - numCom << "(" << "Sold" << ")" << std::endl;

	std::cout << "Creating players..." << std::endl;

	Player p;
	while ((int)players.size() < numCom && (int)players.size() < numPlayers)
	{
		p.Instantiate(Type::Commander, time(NULL)+players.size());
		players.push_back(p);
		Sleep(1);
	}
	while ((int)players.size() < numCom+numSerg && (int)players.size() < numPlayers)
	{
		p.Instantiate(Type::Sergeant, time(NULL) + players.size());
		players.push_back(p);
		Sleep(1);
	}
	while ((int)players.size() < numPlayers)
	{
		p.Instantiate(Type::Solder, time(NULL) + players.size());
		players.push_back(p);
		Sleep(1);
	}

	std::cout << "Running simulation. Printing and removing top each update." << std::endl;
	float dt = 0.03f;
	while (numPlayers > 0)
	{
		Heap::Heap<Player,std::greater<Player>> heap;
		for (int i = 0; i < (int)players.size(); ++i)
		{

			players[i].Update(dt); // update players' position: player.pos += player.vel * dt;
			heap.Push(players[i]); // sort them based on their killValue using heap sort.
		}
		Player top = heap.Pop(); // kill(delete) the closest player by remove the root of the heap.
		std::cout.precision(2);
		std::cout << "Type: ";
		switch (top.type)
		{
		case Type::Commander: std::cout << "Comm";
				break;
		case Type::Sergeant: std::cout << "Serg";
			break;
		default: std::cout << "Sold";
		}
		std::cout << " Position: (" << std::fixed << top.pos.x << ", " << top.pos.y << ", " << top.pos.z << ") Score: " << top.killVal << " Distance: " << Dist(top.pos) << "\n";
		int i = 0;
		while (top != players[i])
		{
			++i;
		}
		players.erase(players.begin() + i);
		--numPlayers;
		Sleep(30); // sleep for 30 ms.
	}
} // main()

