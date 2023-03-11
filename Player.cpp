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

    // if round 1
    if (round == 1) {
      // counts face cards, aces, and cards of trump suit
      for (int i = 0; i < hand.size(); ++i) {
        if (hand[i].is_trump(upcard.get_suit()) &&
           hand[i].is_face_or_ace()) {
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
  // if round 2
    else if (round == 2) {
    // players can order up any suit other than upcard suit
      for (int i = 0; i < MAX_HAND_SIZE; ++i) {
        if (hand[i].is_face_or_ace() &&
          hand[i].get_suit() == Suit_next(upcard.get_suit())) {
            ++numFaceAceLeft;
            }
            }

      if (numFaceAceLeft >= 1) {
        order_up_suit = Suit_next(upcard.get_suit());
        return true;
            }

      else {
        if (is_dealer) {
          order_up_suit = Suit_next(upcard.get_suit());
          return true;
        }
        else {
          return false;
        }
      }
    }
    else {
      return false;
    }
  }

  void add_and_discard(const Card &upcard) {
    int cardNum = 0;
    hand.push_back(upcard);
    // find lowest value card
    for (int i = 1; i < hand.size(); ++i) {
      if (Card_less(hand[i], hand[cardNum], upcard.get_suit())) {
        cardNum = i;
      }
    }
    hand.erase(hand.begin() + cardNum);
  }

  Card lead_card(Suit trump) {
    int trump_count = 0;
    int val = 0;
    //checks if there is at least one card of non trump
    for (int i = 0; i < MAX_HAND_SIZE; ++i) {
      if (hand[i].is_trump(trump)) {
        ++trump_count;
      }
    }
    // chooses lead card for all trump
    if (trump_count == 5) {
      for (int i = 1; i < MAX_HAND_SIZE; ++i) {
        if (Card_less(hand[val], hand[i - 1], trump)) {
          val = i - 1;
        }
      }
    }
    // chooses lead card for when it's not all trump
    // should this one account for left bower
    // or would the left bower count as a trump card?
    else {
      for (int i = 0; i < hand.size(); ++i) {
        if (!hand[i].is_trump(trump)) {
          val = i;
        }
      }
      for (int i = 1; i < MAX_HAND_SIZE; ++i) {
        if (hand[i - 1] > hand[val] && !hand[i - 1].is_trump(trump)) {
            val = i - 1;
        }
      }
    }
      hand.erase(hand.begin() + val);
    return hand[val];
  }

  Card play_card(const Card &led_card, Suit trump) {
    //check for cards of led suit
    int count = 0;
    int val = 0;
    for (int i = 0; i < hand.size(); ++i) {
      if (hand[i].get_suit() == led_card.get_suit()) {
        // if hand contains card of led suit, increments by 1
        ++count;
        val = i;
      }
    }
    // if count > 0, plays highest card
    if (count > 0) {
    for (int i = 0; i < hand.size(); ++i) {
      if (Card_less(hand[val], hand[i], led_card, trump) && hand[i].get_suit() == led_card.get_suit()) {
        val = i;
      }
    }
    }
    // if count == 0, plays lowest card
    else {
      for (int i = 0; i < hand.size(); ++i) {
      if (Card_less(hand[i], hand[val], led_card, trump)) {
        val = i;
      }
    }
    }
    hand.erase(hand.begin() + val);
    return hand[val];
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
      cout << "Human player " << name
          << ", please enter a suit, or \"pass\":\n";
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
    
    void add_and_discard(const Card &upcard) {
      int cardNum = 0;

      hand.push_back(upcard);
      print_hand();
      cout << "Discard upcard: [-1]\n";
      cout << "Human player " << name
          << ", please select a card to discard:\n";
      cin >> cardNum;

      if (cardNum == -1) {
        hand.erase(hand.begin() + 5);
      }
      else {
        hand.erase(hand.begin() + cardNum);
      }

    }

    Card lead_card(Suit trump) {
      int cardNum = 0;

      print_hand();
      cout << "Human player " << name << ", please select a card:\n";
      cin >> cardNum;

      return hand[cardNum];
    }

    Card play_card(const Card &led_card, Suit trump) {
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
