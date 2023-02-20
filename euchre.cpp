// Project UID 1d9f47bfc76643019cfbf037641defe1

#include <iostream>
using namespace std;

class Game {
 public:
  Game(/* ... */);
  void play();


 private:
  std::vector<Player*> players;
  Pack pack;
  // ...


  void shuffle();
  void deal(/* ... */);
  void make_trump(/* ... */);
  void play_hand(/* ... */);
  // ...
};


