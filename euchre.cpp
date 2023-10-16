// Project UID 1d9f47bfc76643019cfbf037641defe1

#include <iostream>
#include "Player.hpp"
#include "Pack.hpp"
#include "Card.hpp"
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
    onePoints = 0;
    twoPoints = 0;
    trickCounter = 1;
    trumpRound = 0;
    roundPlay = true;
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
    if ((handNum > 0) && (dealer < 3)) {
      ++dealer;
    }
    else {
      dealer = 0;
    }
    cout << "Hand " << handNum << endl;
    cout << *player[dealer] << " deals" << endl;
    deal();
    upCard = pack.deal_one();
    cout << upCard << " turned up" << endl;
    ++handNum;
    roundPlay = true;
  }

  void print_round() {
    if (round == 0) {
      for (int i = dealer + 1; i < dealer + 5;) {
          while ((!trumpMade) && (trumpRound < 4)) {
            make_trump(i);
            ++trumpRound;
            ++i;
          }
            if ((trumpMade)|| trumpRound >= 4) {
              break; // exit the loop if the condition becomes false
            }
        }
      trumpRound = 0;
      ++round;
      roundPlay = true;
    }
    else if (round == 1) {
      if (trumpMade) {
        play_trick();
      }
      else {
        for (int i = dealer + 1; i < dealer + 5;) {
          while ((!trumpMade) && (trumpRound < 4)) {
            make_trump(i);
            ++trumpRound;
            ++i;
          }
          if ((trumpMade) || trumpRound >= 4) {
              break; // exit the loop if the condition becomes false
            }
        }
      }
      //if round 1 either play a normal hand (1st card) 
      //OR if trump wasn't chosen choose trump
      trumpRound = 0;
      ++round;
      roundPlay = true;
    }
    else if (round == 2) {
      if (trumpMade) {
        play_trick();
        ++round;
        roundPlay = true;
      }
      else {
        reset_round();
        roundPlay = false;
      }
      //if round 2 either play normal hand (1st card if round 1
      // trump was made,
              //2nd if made round 0) OR discard hand (redeal, start new hand)
    }
    else if (round == 3) {
      play_trick();
      ++round;
      roundPlay = true;
      //if round 3 play normal hand (2nd or 3rd card)
    }
    else if (round == 4) {
      play_trick();
      ++round;
      roundPlay = true;
      //if round 4 play normal hand (3rd or 4th)
    }
    else if (round == 5) {
      play_trick();
      ++round;
      roundPlay = true;
      //if round 5 play normal hand (4th or 5th)
    }
    else if (round == 6) {
      if (trickCounter == 5) {
        play_trick();
        ++round;
        roundPlay = true;
      }
      else {
        reset_round();
        roundPlay = false;
      }
      //if round 6 either play normal hand if trump was made round 1 
              //OR discard hand (redeal, start new hand)
    }
    else {
      reset_round();
      roundPlay = false;
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
    cout << endl;
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
  Card upCard;
  bool shuffle;
  int maxPoints;
  int handNum;
  int dealer;
  int round;
  int team1;
  int team2;
  int onePoints;
  int twoPoints;
  int trickCounter;
  Suit order_up_suit;
  bool trumpMade = false;
  int trumpRound;
  int trumpTeam;
  bool roundPlay;
  int leadPlayer;

  void reset_round() {
    if (onePoints > twoPoints) {
      cout << player[0]->get_name() << " and " 
           << player[2]->get_name() << " win the hand" << endl;
      if (trumpTeam == 2){
        cout << "euchred!" << endl;
        team1 += 2;
      }
      else if (twoPoints == 0) {
        cout << "march!" << endl;
        team1 += 2;
      }
      else {
        ++team1;
      }
    }
    else if (twoPoints > onePoints) {
      cout << player[1]->get_name() << " and " 
           << player[3]->get_name() << " win the hand" << endl;
      if (trumpTeam == 1){
        cout << "euchred!" << endl;
        team2 += 2;
      }
      else if (onePoints == 0) {
        cout << "march!" << endl;
        team2 += 2;
      }
      else {
        ++team2;
      }
    }
    cout << player[0]->get_name() << " and " 
         << player[2]->get_name() << " have "
         << team1 << " points" << endl;
    cout << player[1]->get_name() << " and " 
         << player[3]->get_name() << " have "
         << team2 << " points" << endl << endl;
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
    if (!player[i % 4]->make_trump(upCard, is_dealer(i % 4), 
        (round + 1), order_up_suit)) {
        cout << player[i % 4]->get_name() << " passes" << endl;
      }
    else {
      trumpMade = true;
      player[i % 4]->make_trump(upCard, 
      is_dealer(i % 4), round, order_up_suit);
      cout << player[i % 4]->get_name() << " orders up " 
          << order_up_suit << endl << endl;
      if (round == 0) {
        player[dealer]->add_and_discard(upCard);
      }
      if (i % 2 == 0) {
        trumpTeam = 1;
      }
      else {
        trumpTeam = 2;
      }
    }
  }

  void play_trick() {
    Card cardGreatest;
    if (trickCounter == 1) {
      leadPlayer = ((dealer + 1) % 4);
    }
    Card ledCard = player[leadPlayer]->lead_card(order_up_suit);
    vector<pair<Card, string>> trickInfo {
      {ledCard,
       player[leadPlayer]->get_name()},
      {player[(leadPlayer + 1) % 4]->play_card(ledCard, order_up_suit),
       player[(leadPlayer + 1) % 4]->get_name()},
      {player[(leadPlayer + 2) % 4]->play_card(ledCard, order_up_suit),
       player[(leadPlayer + 2) % 4]->get_name()},
      {player[(leadPlayer + 3) % 4]->play_card(ledCard, order_up_suit),
       player[(leadPlayer + 3) % 4]->get_name()}
    };
    
    cout << trickInfo[0].first << " led by "
         << trickInfo[0].second << endl;
    cout << trickInfo[1].first << " played by " 
         << trickInfo[1].second << endl;
    cout << trickInfo[2].first << " played by " 
         << trickInfo[2].second << endl;
    cout << trickInfo[3].first << " played by " 
         << trickInfo[3].second << endl;

    

    cardGreatest = trickInfo[0].first;
    string winningPlayer = "";
    
    for (int j = 1; j < trickInfo.size(); ++j) {
      if (Card_less(cardGreatest, trickInfo[j].first, ledCard, order_up_suit)) {
        cardGreatest = trickInfo[j % 4].first;
      }
    }

  
    //Compare all cards played, whichever has the highest value wins round
    //Player who won has name printed out below
    for (int i = 0; i < 4; ++i) {
      if (cardGreatest == trickInfo[i].first && (cardGreatest.get_suit() == trickInfo[i].first.get_suit())) {
        winningPlayer = trickInfo[i].second;
        leadPlayer = (leadPlayer + i) % 4;
        if (leadPlayer % 2 == 0) {
          ++onePoints;
        }
        else {
          ++twoPoints;
        }
        break;
      }
    }

    cout <<  winningPlayer << " takes the trick" << endl << endl;
    ++trickCounter;
  }

  void play_hand() {
    if (shuffle) {
      pack.shuffle();
    }
    print_opening();
    while (roundPlay) {
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
  for (int i = 0; i < argc; ++i) {
    cout << argv[i] << " ";
  }

  ifstream input_file(argv[1]);
  Game game(input_file);
  game.set_shuffle(argv[2]);
  game.set_maxPoints(argv[3]);
  game.player_maker(playerPairs);
  game.play();
  game.delete_players();
}