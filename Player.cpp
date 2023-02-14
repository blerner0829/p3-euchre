// Project UID 1d9f47bfc76643019cfbf037641defe1
#include "Player.h"
using namespace std;


std::ostream & operator<<(std::ostream &os, const Player &p) {
  assert(false);
}

void Player::print_hand() const {
  for (size_t i=0; i < MAX_HAND_SIZE; ++i)
    cout << "Human player " << name << "'s hand: "
         << "[" << i << "] " << hand[i] << "\n";
}

class Simple: public Player {
 public:

  const std::string & get_name() override const {
    
  }

  void add_card(const Card &c) override {
    hand.push_back(c);
  }

  bool make_trump(const Card &upcard, bool is_dealer,
                  int round, Suit &order_up_suit) override const {
    
    //Find amount of face cards, aces, and bowers of trump suit
    int numFaceAceLeft = 0;
    for (int i = 0; i < MAX_HAND_SIZE; ++i) {
      if ((upcard.get_suit() == hand[i] && (hand[i].is_face_or_ace))
                      || (hand(i).is_left_bower(upcard.get_suit())))
      ++numFaceAceLeft;
    }
    if (numFaceAceLeft >= 2) {
      order_up_suit = upcard.get_suit()
      return true;
    }
  }
    
  void add_and_discard(const Card &upcard) override {

  }

  Card lead_card(Suit trump) override {

  }

  Card play_card(const Card &led_card, Suit trump) override {

  }

 private:

  string name = "";
  vector<Card> hand(Card());
};

class Human: public Player {
  public:
    const std::string & get_name() override const {

    }

    void add_card(const Card &c) override {

    }

    bool make_trump(const Card &upcard, bool is_dealer,
                          int round, Suit &order_up_suit) override const {
    
    }
    
    void add_and_discard(const Card &upcard) override {

    }

    Card lead_card(Suit trump) override {

    }

    Card play_card(const Card &led_card, Suit trump) override {
        
    }

 private:

  string name = "";
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