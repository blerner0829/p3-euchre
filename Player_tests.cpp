 // Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Player.h"
#include "unit_test_framework.h"

#include <iostream>

using namespace std;

TEST(test_player_get_name) {
    Player * alice = Player_factory("Alice", "Simple");
    ASSERT_EQUAL("Alice", alice->get_name());

    delete alice;
}

// Add more tests here

TEST(test_player_get_name) {
Player * alice = Player_factory("Alice", "Simple");
ASSERT_EQUAL("Alice", alice->get_name());
delete alice;
}

TEST(test_player_make_trump) {
Player * alice = Player_factory("Alice", "Simple");
Card upcard(SPADES, JACK);
Suit order_up_suit;
bool order_up = alice->make_trump(upcard, true, 1, order_up_suit);
ASSERT_TRUE(order_up);
ASSERT_EQUAL(SPADES, order_up_suit);
Card upcard2(DIAMONDS, QUEEN);
Suit order_up_suit2;
bool order_up2 = alice->make_trump(upcard2, true, 1, order_up_suit2);
ASSERT_FALSE(order_up2);

delete alice;
}

TEST(test_human_player_make_trump) {
Player * alice = Player_factory("Alice", "Human");
// replace standard input and output with our own for testing
stringstream ss;
string input = "DIAMONDS\n";
ss << input;
cin.rdbuf(ss.rdbuf());
stringstream out;
streambuf* old_cout = cout.rdbuf(out.rdbuf());

Card upcard(SPADES, JACK);
Suit order_up_suit;
bool order_up = alice->make_trump(upcard, true, 1, order_up_suit);
ASSERT_TRUE(order_up);
ASSERT_EQUAL(DIAMONDS, order_up_suit);

// restore standard output
cout.rdbuf(old_cout);

delete alice;
}
TEST(test_player_add_and_discard) {
Player * alice = Player_factory("Alice", "Simple");
Card upcard(SPADES, JACK);
alice->add_and_discard(upcard);
ASSERT_EQUAL(1, alice->get_hand().size());
ASSERT_FALSE(alice->get_hand()[0] == upcard);
delete alice;
}



TEST_MAIN()
