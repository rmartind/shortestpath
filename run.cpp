#include "square.h"
#include "game.h"
#include "player.h"
#include "gameUtil.h"
#include <iostream>
#include <vector>
#include <ctime>

using std::clock;
using std::cout;
using std::cin;

int main(){
  std::vector<Square*> game_board;

  Game* game1 = new Game(game_board);
  Player* player1 = new Player(11, 3);

  std::vector<Square*> board = game1->getBoard();

  GameUtil* util = new GameUtil();

  int maxTravelDistance = util->compute(game_board.at(0), player1);
  std::cout << "max distance: " << maxTravelDistance << std::endl;



  clock_t startTime;
  clock_t endTime;
  double elapsedTime;

  //run and time each function

  startTime = clock();
  int length = util->shortestPathDistance(game1, player1);
  std::cout << "Length of shortest path: " << length << std::endl;
  elapsedTime = (double(clock() - startTime) / CLOCKS_PER_SEC)*1000.0;
  cout << elapsedTime << "ms constant\n";

  std::vector<int> path;
  path.push_back(0);
  path.push_back(3);
  path.push_back(6);
  path.push_back(8); 

  bool valid = util->isValidPath(path, player1, game1);
  std::cout << "Example path is valid (0/1): " << valid << std::endl;

  cin.get();
  return 0;
}
