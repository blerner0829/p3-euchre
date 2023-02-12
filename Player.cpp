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


