 // Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Player.h"
#include "Player.cpp"
#include "unit_test_framework.h"

#include <iostream>

using namespace std;

TEST(test_player_get_name) {
    Player * alice = Player_factory("Alice", "Simple");
    ASSERT_EQUAL("Alice", alice->get_name());

    delete alice;
}

// Add more tests here
TEST(tests_add_and_discard) {
    // test 1
    Card upcard(ACE, SPADES);
    Card ten_of_hearts(TEN, HEARTS);
    Card nine_of_spades(NINE, SPADES);
    Card jack_of_diamonds(JACK, DIAMONDS);
    Card king_of_clubs(KING, CLUBS);
    Card queen_of_hearts(QUEEN, HEARTS);
    Suit trump(CLUBS);
    vector<Card> hand;
    HumanPlayer person1("person1");
    person1.add_card(ten_of_hearts);
    person1.add_card(nine_of_spades);
    person1.add_card(jack_of_diamonds);
    person1.add_card(king_of_clubs);
    person1.add_card(queen_of_hearts);
    person1.add_and_discard(upcard);
    ASSERT_EQUAL(hand.size(), 5); // Hand size should remain the same after the function
    ASSERT_EQUAL(find(hand.begin(), hand.end(), upcard) != hand.end(), true); // The upcard should be in the hand
    ASSERT_EQUAL(find(hand.begin(), hand.end(), ten_of_hearts) != hand.end(), true); // The card to discard should be removed

    // test 2
    Card upcard(ACE, HEARTS);
    Card card_to_discard(KING, CLUBS);
    HumanPlayer person2("person2");
    person2.add_card(upcard);
    person2.add_card(card_to_discard);
    person2.add_and_discard(upcard);
    ASSERT_EQUAL(2, hand.size());
    ASSERT_EQUAL(upcard, hand[0]);
    }



TEST(tests_simple_lead_card) {
    // test 1
    Card ten_of_hearts(TEN, HEARTS);
    Card nine_of_spades(NINE, SPADES);
    Card jack_of_diamonds(JACK, DIAMONDS);
    Card king_of_clubs(KING, CLUBS);
    Card queen_of_hearts(QUEEN, HEARTS);
    Suit trump(CLUBS);
    
    vector<Card> hand;
    HumanPlayer person1("person1");
    person1.add_card(ten_of_hearts);
    person1.add_card(nine_of_spades);
    person1.add_card(jack_of_diamonds);
    person1.add_card(king_of_clubs);
    person1.add_card(queen_of_hearts);
    Card expected_card = ten_of_hearts;
    ASSERT_EQUAL(expected_card, person1.lead_card(SPADES));

    // test 2
    Card led_suit(KING, CLUBS);
    Card ten_of_hearts(TEN, HEARTS);
    Card nine_of_spades(NINE, SPADES);
    Card jack_of_diamonds(JACK, DIAMONDS);
    Card king_of_clubs(KING, CLUBS);
    Card queen_of_hearts(QUEEN, HEARTS);
    Suit trump(CLUBS);
    vector<Card> hand;
    HumanPlayer person2("person2");
    person2.add_card(ten_of_hearts);
    person2.add_card(nine_of_spades);
    person2.add_card(jack_of_diamonds);
    person2.add_card(king_of_clubs);
    person2.add_card(queen_of_hearts);
    ASSERT_EQUAL(nine_of_spades, person2.lead_card(trump));
    ASSERT_EQUAL(nine_of_spades, person2.play_card(nine_of_spades, trump));
}

TEST(tests_simple_play_card) {
    // test 1
   Card led_suit(ACE, HEARTS);
   Card ten_of_hearts(TEN, HEARTS);
   Card nine_of_spades(NINE, SPADES);
   Card jack_of_diamonds(JACK, DIAMONDS);
   Card king_of_clubs(KING, CLUBS);
   Card queen_of_hearts(QUEEN, HEARTS);
   Suit trump(CLUBS);
   vector<Card> hand;
   HumanPlayer person1("person1");
   person1.add_card(ten_of_hearts);
   person1.add_card(nine_of_spades);
   person1.add_card(jack_of_diamonds);
   person1.add_card(king_of_clubs);
   person1.add_card(queen_of_hearts);
   ASSERT_EQUAL(nine_of_spades, person1.play_card(led_suit, trump));
}



/*
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

*/

TEST_MAIN()
