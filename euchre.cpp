// Project UID 1d9f47bfc76643019cfbf037641defe1

#include <iostream>
#include "Player.h"
#include "Pack.h"
#include "Card.h"
#include <fstream>
using namespace std;

class Game {
 public:
  Game(istream& pack_input) :
    pack(pack_input)
    {
    maxPoints = 0;
    shuffle = false;
    handNum = 0;
    dealer = 0;
    round = 0;
    team1 = 0;
    team2 = 0;
    trickCounter = 1;
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
    cout << *player[dealer] << " deals" << endl;
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

  bool print_round() {
    if (round == 0) {
      while (!trumpMade) {
        for (int i = dealer + 1; i < dealer + 5; ++i) {
          make_trump(i);
        }
      }
      ++round;
      return true;
    }
    else if (round == 1) {
      if (trumpMade) {
        play_trick();
      }
      else {
        for (int i = dealer + 1; i < dealer + 5; ++i) {
          make_trump(i);
        }
      }
      //if round 1 either play a normal hand (1st card) 
      //OR if trump wasn't chosen choose trump
      ++round;
      return true;
    }
    else if (round == 2) {
      if (trumpMade) {
        play_trick();
        ++round;
        return true;
      }
      else {
        reset_round();
        return false;
      }
      //if round 2 either play normal hand (1st card if round 1 trump was made,
              //2nd if made round 0) OR discard hand (redeal, start new hand)
    }
    else if (round == 3) {
      play_trick();
      ++round;
      return true;
      //if round 3 play normal hand (2nd or 3rd card)
    }
    else if (round == 4) {
      play_trick();
      ++round;
      return true;
      //if round 4 play normal hand (3rd or 4th)
    }
    else if (round == 5) {
      play_trick();
      ++round;
      return true;
      //if round 5 play normal hand (4th or 5th)
    }
    else if (round == 6) {
      if (trickCounter == 5) {
        play_trick();
        ++round;
        return true;
      }
      else {
        reset_round();
        return false;
      }
      //if round 6 either play normal hand if trump was made round 1 
              //OR discard hand (redeal, start new hand)
    }
    else {
      reset_round();
      return false;
    }
  }

  void delete_players() {
    for (int i = 0; i < 4; ++i) {
      delete player[i];
    }
  }

  void play() {
    while ((team1 < maxPoints) && (team2 < maxPoints)){
      play_hand();
    }
    if (team1 >= maxPoints) {
      cout << player[0]->get_name() << " and " 
           << player[2]->get_name() << " win!";
    }
    else if (team2 >= maxPoints) {
      cout << player[1]->get_name() << " and " 
           << player[3]->get_name() << " win!";
    }
  }

  void player_maker(vector<pair<string, string>> playerPairs) {
    int playerCount = 0;
    while (playerCount < 4) {
      player.push_back(Player_factory(playerPairs[playerCount].first,
                                    playerPairs[playerCount].second));
      ++playerCount;
    }
  }

 private:
  vector<Player*> player;
  Pack pack;
  bool shuffle;
  int maxPoints;
  int handNum;
  int dealer;
  int round;
  int team1;
  int team2;
  int onePoints;
  int twoPoints;
  int orderUpPlayer;
  int trickCounter;
  Suit order_up_suit;
  bool trumpMade = false;

  void reset_round() {
    if (onePoints > twoPoints) {
      ++team1;
    }
    else if (twoPoints > onePoints) {
      ++team2;
    }
    round = 0;
    trumpMade = false;
    trickCounter = 1;
    onePoints = 0;
    twoPoints = 0;
  }

  bool is_dealer(int i) {
    if (i == dealer) {
      return true;
    }
    else {
      return false;
    }
  }
  
  void shuffleDeck() {
    if (shuffle) {
      pack.shuffle();
    }
  };
  void deal() {
    for (int i = 0; i < 3; ++i) {
      player[(dealer + 1)%4]->add_card(pack.deal_one());
    }
    for (int i = 0; i < 2; ++i) {
      player[(dealer + 2)%4]->add_card(pack.deal_one());
    }
    for (int i = 0; i < 3; ++i) {
      player[(dealer + 3)%4]->add_card(pack.deal_one());
    }
    for (int i = 0; i < 2; ++i) {
      player[dealer]->add_card(pack.deal_one());
    }
    for (int i = 0; i < 2; ++i) {
      player[(dealer + 1)%4]->add_card(pack.deal_one());
    }
    for (int i = 0; i < 3; ++i) {
      player[(dealer + 2)%4]->add_card(pack.deal_one());
    }
    for (int i = 0; i < 2; ++i) {
      player[(dealer + 3)%4]->add_card(pack.deal_one());
    }
    for (int i = 0; i < 3; ++i) {
      player[dealer]->add_card(pack.deal_one());
    }
  }
  void make_trump(int i) {
    Card upCard = pack.deal_one();
    if (!player[i % 4]->make_trump(upCard, is_dealer(i % 4), round, order_up_suit)) {
        cout << player[i % 4]->get_name() << " passes" << endl;
      }
    else {
      trumpMade = player[i % 4]->make_trump(upCard, is_dealer(i % 4), round, order_up_suit);
      cout << player[i % 4]->get_name() << " orders up " << order_up_suit << endl;
      orderUpPlayer = i % 4;
    }
  }

  void play_trick() {
    Card cardGreatest;
    vector<pair<Card, string>> trickInfo {
      {player[orderUpPlayer]->lead_card(order_up_suit),
       player[orderUpPlayer]->get_name()},
      {player[(orderUpPlayer + 1) % 4]->play_card(player[orderUpPlayer]->
       lead_card(order_up_suit), order_up_suit),
       player[(orderUpPlayer + 1) % 4]->get_name()},
      {player[(orderUpPlayer + 2) % 4]->play_card(player[orderUpPlayer]->
       lead_card(order_up_suit), order_up_suit),
       player[(orderUpPlayer + 2) % 4]->get_name()},
      {player[(orderUpPlayer + 3) % 4]->play_card(player[orderUpPlayer]->
       lead_card(order_up_suit), order_up_suit),
       player[(orderUpPlayer + 3) % 4]->get_name()}
    };
    
    cout << trickInfo[0].second << " led by "
         << trickInfo[0].first << endl;
    cout << trickInfo[1].second << " played by " 
         << trickInfo[1].first << endl;
    cout << trickInfo[2].second << " played by " 
         << trickInfo[2].first << endl;
    cout << trickInfo[3].second << " played by " 
         << trickInfo[3].first << endl;

    

    cardGreatest = trickInfo[0].first;
    string winningPlayer = "";
    
    for (int i = 1; i < 4; ++i) {
      if (Card_less(cardGreatest, trickInfo[i % 4].first, trickInfo[0].first, order_up_suit)) {
        cardGreatest = trickInfo[i % 4].first;
       }
    }
  
    //Compare all cards played, whichever has the highest value wins round
    //Player who won has name printed out below
    for (int i = 0; i < 4; ++i) {
      if (cardGreatest == trickInfo[i].first) {
        winningPlayer = trickInfo[i].second;
        if (i % 2 == 0) {
          ++onePoints;
        }
        else {
          ++twoPoints;
        }
      }
    }

    cout <<  winningPlayer << " takes the trick" << endl;
    ++trickCounter;
  }

  void play_hand() {
    print_opening();
    while (print_round()) {
      print_round();
    }
  }
};


int main(int argc, char **argv) {
  vector<pair<string, string>> playerPairs {
    {string(argv[4]), string(argv[5])},
    {string(argv[6]), string(argv[7])},
    {string(argv[8]), string(argv[9])},
    {string(argv[10]), string(argv[11])}
  };
  // Read command line args and check for errors

  ifstream input_file(argv[1]);
  Game game(input_file);
  game.set_shuffle(argv[2]);
  game.set_maxPoints(argv[3]);
  game.player_maker(playerPairs);
  game.play();
  game.delete_players();
}
