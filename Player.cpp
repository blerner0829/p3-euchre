// Project UID 1d9f47bfc76643019cfbf037641defe1
#include "Player.h"
#include <string>
#include <cassert>
#include <iostream>
#include <array>
using namespace std;


std::ostream & operator<<(std::ostream &os, const Player &p) {
  assert(false);
}


class SimplePlayer: public Player {
 public:

  SimplePlayer(string name_in) 
  : name(name_in) {}

  const string & get_name() const {
    return name;
  }

  void add_card(const Card &c) {
    hand.push_back(c);
  }

  bool make_trump(const Card &upcard, bool is_dealer,
                  int round, Suit &order_up_suit) const {
    
    //Find amount of face cards, aces, and bowers of trump suit
    int numFaceAceLeft = 0;
    for (int i = 0; i < MAX_HAND_SIZE; ++i) {
      if ((upcard.get_suit() == hand[i].get_suit() && (hand[i].is_face_or_ace()))
                      || (hand[i].is_left_bower(upcard.get_suit())))
      ++numFaceAceLeft;
    }
    if (numFaceAceLeft >= 2) {
      order_up_suit = upcard.get_suit();
      return true;
    }
    else {
      return false;
    }
  }
    
  void add_and_discard(const Card &upcard) {
    int cardNum = 0;
    hand.push_back(upcard);

    for (int i = 0; i < hand.size(); ++i) {
      if (hand[i] < hand[cardNum]) {
        cardNum = i;
      }
    }
    hand.erase(hand.begin() + cardNum);
  }

  Card lead_card(Suit trump) {

    //check for non trump cards
    //for all non trump cards compare values
    //play lowest of these
    //if only trump play highest trump card
  }

  Card play_card(const Card &led_card, Suit trump) {
    //check for cards of led suit
    //if has, play highest of these
    //if not, play lowest card in hand
  }

 private:
  string name;
  vector<Card> hand;
};

class HumanPlayer: public Player {
  public:

    HumanPlayer(string name_in) 
    : name(name_in) {}

    const string & get_name() const {
      return name;
    }

    void add_card(const Card &c) {
      hand.push_back(c);
    }

    bool make_trump(const Card &upcard, bool is_dealer,
                          int round, Suit &order_up_suit) const {
      print_hand();
      cout << "Human player " << name << ", please enter a suit, or \"pass\":\n";
      string decision;
      cin >> decision;

    if (decision != "pass") {
      Suit ordered_up = string_to_suit(decision);
    }
    else {

    }
    }
    
    void add_and_discard(const Card &upcard) override {

    }

    Card lead_card(Suit trump) override {

    }

    Card play_card(const Card &led_card, Suit trump) override {
        
    }

 private:
  string name;
  vector<Card> hand;

  void print_hand() const {
    for (size_t i=0; i < MAX_HAND_SIZE; ++i)
      cout << "Human player " << name << "'s hand: "
           << "[" << i << "] " << hand[i] << "\n";
}
};

Player * Player_factory(const std::string &name, 
                        const std::string &strategy) {
  // We need to check the value of strategy and return 
  // the corresponding player type.
  if (strategy == "Simple") {
    // The "new" keyword dynamically allocates an object.
    return new SimplePlayer(name);
  }
  else if (strategy == "Human") {
    return new HumanPlayer(name);
  }
  else {
    // Invalid strategy if we get here
    assert(false);
  }
  return nullptr;
}