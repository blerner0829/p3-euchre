// Project UID 1d9f47bfc76643019cfbf037641defe1
#include "Player.h"
Player * Player_factory(const std::string &name, 
                        const std::string &strategy) {
  // We need to check the value of strategy and return 
  // the corresponding player type.
  if (strategy == "Simple") {
    // The "new" keyword dynamically allocates an object.
    return new SimplePlayer(name);
  }
  // Repeat for each other type of Player
  ...
  // Invalid strategy if we get here
  assert(false);
  return nullptr;
}


std::ostream & operator<<(std::ostream &os, const Player &p) {
  assert(false);
}

void print_hand() const {
  for (size_t i=0; i < hand.size(); ++i)
    cout << "Human player " << name << "'s hand: "
         << "[" << i << "] " << hand[i] << "\n";
}

class Simple: public Player {
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
}

class Human: public Player {
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
}