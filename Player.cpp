// Project UID 1d9f47bfc76643019cfbf037641defe1
#include "Player.h"
#include <string>
#include <cassert>
#include <iostream>
#include <array>
#include <vector>
using namespace std;


std::ostream & operator<<(std::ostream &os, const Player &p) {
  return os << p.get_name();
}


class SimplePlayer: public Player {
 public:

  SimplePlayer(string name_in) 
  : name(name_in) {}

  const string & get_name() const override {
    return name;
  }

  void add_card(const Card &c) override{
    hand.push_back(c);
  }

  bool make_trump(const Card &upcard, bool is_dealer,
                  int round, Suit &order_up_suit) const override{
    int numFaceAceLeft = 0;
    if (round == 1) {
      for (int i = 0; i < MAX_HAND_SIZE; ++i) {
        if ((upcard.get_suit() == hand[i].get_suit() && (hand[i].is_face_or_ace()))
                                    || (hand[i].is_left_bower(upcard.get_suit()))) {
            ++numFaceAceLeft;
        }
      }
      if (numFaceAceLeft >= 2) {
        order_up_suit = upcard.get_suit();
        return true;
      }
      else {
        return false;
      }
    }
    else {
      for (int i = 0; i < MAX_HAND_SIZE; ++i) {
        if ((Suit_next(upcard.get_suit()) == hand[i].get_suit() && (hand[i].is_face_or_ace()))
                                    || (hand[i].is_right_bower(upcard.get_suit()))) {
            ++numFaceAceLeft;
        }
      }
      if ((numFaceAceLeft >= 1) || (is_dealer)) {
        order_up_suit = Suit_next(upcard.get_suit());
        return true;
      }
      else {
        return false;
      }
    }
  }
    
  void add_and_discard(const Card &upcard) override{
    int cardNum = 0;
    hand.push_back(upcard);

    for (int i = 0; i < hand.size(); ++i) {
      if (hand[i] < hand[cardNum]) {
        cardNum = i;
      }
    }
    hand.erase(hand.begin() + cardNum);
  }

  Card lead_card(Suit trump) override{
    Card lead_card;
    int trump_count = 0;
    //checks if there is at least one card of non trump
    for (int i = 0; i < MAX_HAND_SIZE; ++i) {
      if (hand[i].is_trump(trump)) {
        ++trump_count;
      }
    }
    //chooses lead card for not all trump
    if (trump_count == 5) { 
      for (int i = 1; i < MAX_HAND_SIZE; ++i) {
        if ((hand[i-1] < hand[i]) && !(hand[i-1].is_trump(trump))) {
         lead_card = hand[i-1];
        }
      }
    }
    //chooses lead card for only trump
    else {
      for (int i = 1; i < MAX_HAND_SIZE; ++i) {
        if (hand[i-1] < hand[i]) {
          lead_card = hand[i];
        }
      }
    }
    return lead_card;
  }

  Card play_card(const Card &led_card, Suit trump) override{
    //check for cards of led suit

    Card previous = hand[0];
    for (int j = 0; j < hand.size(); ++j) {
      for (int i = 1; i < MAX_HAND_SIZE; ++i) {
        if (Card_less(previous, hand[i], led_card, trump)) {
        } 
        else {
          previous = hand[i];
        }
     }
    }
    return previous;
  }


 private:
  string name;
  vector<Card> hand;
};

class HumanPlayer: public Player {
  public:

    HumanPlayer(string name_in) 
    : name(name_in) {}

    const string & get_name() const override{
      return name;
    }

    void add_card(const Card &c) override{
      hand.push_back(c);
    }

    bool make_trump(const Card &upcard, bool is_dealer,
                          int round, Suit &order_up_suit) const override{
      print_hand();
      cout << "Human player " << name << ", please enter a suit, or \"pass\":\n";
      string decision;
      cin >> decision;

      if (decision != "pass") {
        order_up_suit = string_to_suit(decision);
        return true;
      }
      else {
        return false;
      }
    }
    
    void add_and_discard(const Card &upcard) override{
      int cardNum = 0;

      hand.push_back(upcard);
      print_hand();
      cout << "Discard upcard: [-1]\n";
      cout << "Human player " << name << ", please select a card to discard:\n";
      cin >> cardNum;

      if (cardNum == -1) {
        hand.erase(hand.begin() + 5);
      }
      else {
        hand.erase(hand.begin() + cardNum);
      }

    }

    Card lead_card(Suit trump) override{
      int cardNum = 0;

      print_hand();
      cout << "Human player " << name << ", please select a card:\n";
      cin >> cardNum;

      return hand[cardNum];
    }

    Card play_card(const Card &led_card, Suit trump) override{
      int cardNum = 0;

      print_hand();
      cout << "Human player " << name << ", please select a card:\n";
      cin >> cardNum;

      return hand[cardNum];
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
    return new SimplePlayer(name);
  }
  else if (strategy == "Human") {
    return new HumanPlayer(name);
  }
  else{
    assert(false);
    return nullptr;
  }
}