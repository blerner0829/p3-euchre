// Project UID 1d9f47bfc76643019cfbf037641defe1

#include <iostream>
#include "Player.cpp"
#include "Pack.h"
using namespace std;


int main(int argc, char **argv) {
  vector<pair<string, string>> playerPairs {
    {string(argv[4]), string(argv[5])},
    {string(argv[6]), string(argv[7])},
    {string(argv[8]), string(argv[9])},
    {string(argv[10]), string(argv[11])}
  };
  // Read command line args and check for errors
  Game game;
  game.set_filename(argv[1]);
  game.set_shuffle(argv[2]);
  game.set_maxPoints(argv[3]);
  game.player_maker(playerPairs);
  game.play();
}





class Game {
 public:
  Game() {
    filename = "";
    maxPoints = 0;
    shuffle = false;
    player;
    handNum = 0;
    dealer = 0;
    round = 0;
  }

  void set_filename(string str) {
    filename = str;
  }

  void set_shuffle(string str) {
    if (str == "shuffle") {
      shuffle = true;
    }
  }

  void set_maxPoints(string str) {
    maxPoints = stoi(str);
  }

  void print_opening() {
    cout << "Hand " << handNum << endl;
    cout << player[dealer] << " deals" << endl;
    cout << pack.deal_one() << " turned up" << endl;
    ++handNum;
    if (dealer < 4) {
      ++dealer;
    }
    else {
      dealer = 0;
    }
  }

  void decision(int round, int player) {
    cout << "hello";
  }

  void print_round() {
    cout << player[(dealer + 1) % 4] << decision(round, (dealer + 1) % 4);
    cout << player[(dealer + 2) % 4] << decision(round, (dealer + 2) % 4);
    cout << player[(dealer + 3) % 4] << decision(round, (dealer + 3) % 4);
    cout << player[dealer] << decision(round, (dealer) % 4);
  }

  void play() {
    print_opening();
    print_round();
  };

  void player_maker(vector<pair<string, string>> playerPairs) {
    int playerCount = 0;
    while (playerCount < 4) {
      player.push_back(*Player_factory(playerPairs[playerCount].first,
                                    playerPairs[playerCount].second));
      ++playerCount;
    }
  }

 private:
  vector<Player> player;
  Pack pack;
  bool shuffle;
  int maxPoints;
  string filename;
  int handNum;
  int dealer;
  int round;

  void shuffle();
  void deal(/* ... */);
  void make_trump(/* ... */);
  void play_hand(/* ... */);
  // ...
};


