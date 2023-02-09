// Project UID 1d9f47bfc76643019cfbf037641defe1
#include "Pack.h"
void Pack::reset() {
  assert(false);
  assert(next); // DELETEME: avoid error "private field is not used"
}
// EFFECTS: Initializes the Pack to be in the following standard order:
  //          the cards of the lowest suit arranged from lowest rank to
  //          highest rank, followed by the cards of the next lowest suit
  //          in order from lowest to highest rank, and so on.
  // NOTE: The standard order is the same as that in pack.in.
  // NOTE: Do NOT use pack.in in your implementation of this function
  Pack::Pack() {
   for (int i = 0; i < PACK_SIZE - 1; i++) {
    if (cards[i] > cards[i + 1]) {
        cards[i] = cards[i + 1];
    }
    }
  }
  // REQUIRES: pack_input contains a representation of a Pack in the
  //           format required by the project specification
  // MODIFIES: pack_input
  // EFFECTS: Initializes Pack by reading from pack_input.
  Pack::Pack(std::istream& pack_input) {
    int i = 0;
    while (pack_input >> cards[i]) {
        ++i;
    }
    next = 0;
  }

  // REQUIRES: cards remain in the Pack
  // EFFECTS: Returns the next card in the pack and increments the next index
  Card Pack::deal_one() {
    Card card = cards[next];
    ++next;
    return card;
  }

  // EFFECTS: Resets next index to first card in the Pack
  void Pack::reset() {
    next = 0;
  }

  // EFFECTS: Shuffles the Pack and resets the next index. This
  //          performs an in shuffle seven times. See
  //          https://en.wikipedia.org/wiki/In_shuffle.
  void Pack::shuffle() {
    //Cut deck in half
    //Set first element equal to value of the first of the cut deck
    //Set the second element equal to the original first element
    //Alternate cards from each half until deck is fully shuffled
    //Final card should be last card of first half
  }