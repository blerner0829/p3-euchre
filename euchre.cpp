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
    team1 = 0;
    team2 = 0;
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
    deal();
    cout << pack.deal_one() << " turned up" << endl;
    ++handNum;
    if (dealer < 4) {
      ++dealer;
    }
    else {
      dealer = 0;
    }
  }

  string decision(int round, int player) {
  }

  bool print_round() {
    if (round == 0) {
      //if round 0 make trump
      ++round;
      return true;
    }
    else if (round == 1) {
      //if round 1 either play a normal hand (1st card) 
      //OR if trump wasn't chosen choose trump
      ++round;
      return true;
    }
    else if ((round == 2) && (trumpMade)) {
      ++round;
      return true;
      //if round 2 either play normal hand (1st card if round 1 trump was made,
              //2nd if made round 0) OR discard hand (redeal, start new hand)
    }
    else if (round == 3) {
      ++round;
      return true;
      //if round 3 play normal hand (2nd or 3rd card)
    }
    else if (round == 4) {
      ++round;
      return true;
      //if round 4 play normal hand (3rd or 4th)
    }
    else if (round == 5) {
      ++round;
      return true;
      //if round 5 play normal hand (4th or 5th)
    }
    else if (round == 6) {
      ++round;
      return true;
      //if round 6 either play normal hand if trump was made round 1 
              //OR discard hand (redeal, start new hand)
    }
    else {
      reset_round();
      return false;
    }
  }

  void play() {
    while ((team1 < maxPoints) && (team2 < maxPoints)){
      play_hand();
    }
    if (team1 >= maxPoints) {
      cout << player[0].get_name() << " and " 
           << player[2].get_name() << " win!";
    }
    else if (team2 >= maxPoints) {
      cout << player[1].get_name() << " and " 
           << player[3].get_name() << " win!";
    }
  }

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
  int team1;
  int team2;
  bool trumpMade = false;

  void reset_round() {
    round = 0;
  }
  
  void shuffle();
  void deal() {
    for (int i = 0; i < 3; ++i) {
      player[(dealer + 1)%4].add_card(pack.deal_one());
    }
    for (int i = 0; i < 2; ++i) {
      player[(dealer + 2)%4].add_card(pack.deal_one());
    }
    for (int i = 0; i < 3; ++i) {
      player[(dealer + 3)%4].add_card(pack.deal_one());
    }
    for (int i = 0; i < 2; ++i) {
      player[dealer].add_card(pack.deal_one());
    }
    for (int i = 0; i < 2; ++i) {
      player[(dealer + 1)%4].add_card(pack.deal_one());
    }
    for (int i = 0; i < 3; ++i) {
      player[(dealer + 2)%4].add_card(pack.deal_one());
    }
    for (int i = 0; i < 2; ++i) {
      player[(dealer + 3)%4].add_card(pack.deal_one());
    }
    for (int i = 0; i < 3; ++i) {
      player[dealer].add_card(pack.deal_one());
    }
  }
  string make_trump(/* ... */) {
    if (!player[dealer + 1].make_trump()) {
        return "passes";
      }
    if () {
      trumpMade = true;
      return "orders up " ;
    }
    cout << player[(dealer + 1) % 4].get_name() 
         << decision(round, (dealer + 1) % 4);
    cout << player[(dealer + 2) % 4].get_name()
         << decision(round, (dealer + 2) % 4);
    cout << player[(dealer + 3) % 4].get_name()
         << decision(round, (dealer + 3) % 4);
    cout << player[dealer].get_name()
         << decision(round, (dealer) % 4);
  };

  void play_hand() {
    print_opening();
    while (print_round) {
      print_round();
    }
  }
};



