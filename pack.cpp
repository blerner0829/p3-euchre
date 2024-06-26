// Project UID 1d9f47bfc76643019cfbf037641defe1
#include "Pack.hpp"
// EFFECTS: Initializes the Pack to be in the following standard order:
  //          the cards of the lowest suit arranged from lowest rank to
  //   /       highest rank, followed by the cards of the next lowest suit
  //          in order from lowest to highest rank, and so on.
  // NOTE: The standard order is the same as that in pack.in.
  // NOTE: Do NOT use pack.in in your implementation of this function
  Pack::Pack() {
    int count = 0;
    for (int s = SPADES; s <= DIAMONDS; ++s) {
        for (int r = NINE; r <= ACE; ++r) {
            cards[count] = Card(static_cast<Rank>(r), static_cast<Suit>(s));
            ++count;
    }
    }
    next = 0;
  }
  // REQUIRES: pack_input contains a representation of a Pack in the
  //           format required by the project specification
  // MODIFIES: pack_input
  // EFFECTS: Initializes Pack by reading from pack_input.
  Pack::Pack(std::istream& pack_input) {
    int i = 0;
    Card card;
    while (pack_input >> card) {
      cards[i] = card;
      ++i;
    }
    next = 0;
  }

  // REQUIRES: cards remain in the Pack
  // EFFECTS: Returns the next card in the pack and increments the next index
  Card Pack::deal_one() {
    Card first = cards[next];
    ++next;
    return first;
  }

  // EFFECTS: Resets next index to first card in the Pack
  void Pack::reset() {
    next = 0;
  }

  // EFFECTS: Shuffles the Pack and resets the next index. This
  //          performs an in shuffle seven times. See
  //          https://en.wikipedia.org/wiki/In_shuffle.

  void Pack::shuffle() {
    Card newDeck[PACK_SIZE];
    int shuffleTimes = 0;
    int halfPack = PACK_SIZE / 2;
    while (shuffleTimes < 7) {
      /*for (int i = 0; i < PACK_SIZE - 1; ++i) {
        if ((i + 1) % 2 == 0) {
            newDeck[i] = cards[((i + 1) / 2) - 1];
        }
        else if ((i + 1) % 2 == 1) {
            newDeck[i] = cards[j];
            ++j;
        }
        }
      for (int i = 0; i < PACK_SIZE - 1; i++) {
        cards[i] = newDeck[i];
      }
      ++shuffleTimes;
      j = PACK_SIZE / 2; */
      for (int i = 0; i < PACK_SIZE; ++i) {
        if (i - halfPack < 0) {
          newDeck[((i + 1) * 2) - 1] = cards[i];
        }
        else {
          newDeck[(i - halfPack) * 2] = cards[i];
        }
      }
      ++shuffleTimes;

      for (int i = 0; i < PACK_SIZE; i++) {
        cards[i] = newDeck[i];
      }
   }
   reset();
  }


// EFFECTS: returns true if there are no more cards left in the pack
  bool Pack::empty() const {
    return next == PACK_SIZE;
  }