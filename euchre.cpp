// Project UID 1d9f47bfc76643019cfbf037641defe1

#include <iostream>
#include "Player.h"
#include "Pack.h"

using namespace std;

main(int argc, char **argv) {
  pair <string, string> players;

  for (int i = 0; i < argc; ++i) { 
    
  }
}


class Game {
 public:
  Game();
  void play();
  void set_file_name()


 private:
  std::vector<Player*> players;
  Pack pack;
  bool maxPoints = 0;
  string fileName = "";




  void shuffle();
  void deal(/* ... */);
  void make_trump(/* ... */);
  void play_hand(/* ... */);
  // ...
};



