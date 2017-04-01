#include "gameUtil.h"
#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
#include <set>

using std::vector;

int GameUtil::compute(Square* square, Player* player) {
	// TODO: Part 1 debug
	double chi = player->getChi();
	double weight = player->getWeight();
	double teleporterEnergy = square->getTeleporterEnergy();
	double cannonPowder = square->getCannonPowder();

	double teleporterCompute = 0;
	for (double i = 0.0; i < floor(chi) + 1.0; i = i + 1.0) {
		teleporterCompute += sqrt(chi * i * teleporterEnergy);
	}
	teleporterCompute *= 1.0 / (1.0 + chi);


	double cannonCompute = pow((pow(cannonPowder, 1.7) / pow(weight, 1.5)), 2.0) / 9.8;

	return std::max(cannonCompute > teleporterCompute ? cannonCompute : teleporterCompute, 1.0);
}

bool GameUtil::isValidPath(std::vector<int>& path, Player* player, Game* game) {
	int count = 1;
	std::vector<Square*> gameVec = game->getBoard();

	for (int i = 0; i < path.size() - 1; i++) {
		if (path.at(i) > path.at(i + 1)) {
			return false;
		}
	}//Check if each move moves forward

	if (path.at(0) == 0 && path.back() == gameVec.size() - 1) {
		if (!(compute(gameVec.at(path.at(0)), player)
			>= (path.at(1) - path.at(0)))) {
			return false;
		}//Check you can move from path 0 to path 1

		for (int i = 1; i < path.size() - 1; i++) {
			if (path.at(i) < gameVec.size() - 1 && compute(gameVec.at(path.at(i - 1)), player)
				>= (path.at(i + 1) - path.at(i))) {
			}
			else {
				return false;
			}
		}

	}
	else {
		return false;
	}
	return true;
}

int GameUtil::shortestPathDistance(Game* game, Player* player) {
	vector<Square*> board = game->getBoard();// The games board
	Square* current = 0;// Current square
	int maxDis = 0;
	int boardSize = board.size();
	std::vector<int> distances(boardSize, -1);
	distances.at(0) = 0;

	for (int i = 0; i < boardSize; i++) {
		current = board.at(i);
		maxDis = compute(current, player);
		if (i + maxDis > boardSize - 1) {
			maxDis = (boardSize - 1) - i;
		}
		for (int j = i; j < i + maxDis+1; j++) {
			if (distances.at(j) == -1 || distances.at(i) + 1 < distances.at(j)) {
				distances.at(j) = distances.at(i) + 1;
			}
		}
	}
	return distances.at(boardSize-1);
}