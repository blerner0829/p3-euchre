// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Card.h"
#include "unit_test_framework.h"
#include <iostream>

using namespace std;


TEST(test_card_ctor) {
    Card c(ACE, HEARTS);
    ASSERT_EQUAL(ACE, c.get_rank());
    ASSERT_EQUAL(HEARTS, c.get_suit());
}

TEST(tests_suit_trump) {
    Card c(JACK, HEARTS);
    ASSERT_EQUAL(DIAMONDS, c.get_suit(DIAMONDS));
    Card c1(JACK, DIAMONDS);
    ASSERT_EQUAL(HEARTS, c1.get_suit(HEARTS));
    Card c2(JACK, SPADES);
    ASSERT_EQUAL(CLUBS, c2.get_suit(CLUBS));
    Card c3(JACK, CLUBS);
    ASSERT_EQUAL(SPADES, c3.get_suit(SPADES));
    Card c4(TWO, DIAMONDS);
    ASSERT_EQUAL(DIAMONDS, c4.get_suit(DIAMONDS));
    Card c5(NINE, SPADES);
    ASSERT_EQUAL(SPADES, c5.get_suit(DIAMONDS));
}

TEST(tests_is_face) {
    Card c(JACK, HEARTS);
    ASSERT_TRUE(c.is_face_or_ace());
    Card c1(QUEEN, SPADES);
    ASSERT_TRUE(c1.is_face_or_ace());
    Card c2(KING, CLUBS);
    ASSERT_TRUE(c2.is_face_or_ace());
    Card c3(ACE, DIAMONDS);
    ASSERT_TRUE(c3.is_face_or_ace()); 
    Card c4(TWO, HEARTS);
    ASSERT_FALSE(c4.is_face_or_ace());
}

TEST(test_is_right_bower) {
    Card c(JACK, HEARTS);
    ASSERT_TRUE(c.is_right_bower(HEARTS));
    ASSERT_FALSE(c.is_right_bower(DIAMONDS));
    Card c1(QUEEN, DIAMONDS);
    ASSERT_FALSE(c1.is_right_bower(DIAMONDS));
}

TEST(tests_is_left_bower) {
    Card c(JACK, HEARTS);
    ASSERT_TRUE(c.is_left_bower(DIAMONDS));
    ASSERT_FALSE(c.is_left_bower(SPADES));
    Card c1(JACK, DIAMONDS);
    ASSERT_TRUE(c1.is_left_bower(HEARTS));
    Card c2(JACK, SPADES);
    ASSERT_TRUE(c2.is_left_bower(CLUBS));
    Card c3(JACK, CLUBS);
    ASSERT_TRUE(c3.is_left_bower(SPADES));
    Card c4(ACE, HEARTS);
    ASSERT_FALSE(c4.is_left_bower(DIAMONDS));
}

TEST(tests_is_trump) {
    Card c(ACE, SPADES);
    ASSERT_TRUE(c.is_trump(SPADES));
    ASSERT_FALSE(c.is_trump(CLUBS));
    Card c1(JACK, HEARTS);
    ASSERT_TRUE(c1.is_trump(HEARTS));
    ASSERT_TRUE(c1.is_trump(DIAMONDS));
    ASSERT_FALSE(c1.is_trump(SPADES));
    Card c2(THREE, CLUBS);
    ASSERT_TRUE(c2.is_trump(CLUBS));
}

TEST(tests_card_less) {
    Card ace_of_spades = Card(ACE, SPADES);
    Card two_of_spades = Card(TWO, SPADES);
    Card king_of_hearts = Card(KING, HEARTS);
    ASSERT_TRUE(Card_less(two_of_spades, ace_of_spades, SPADES));
    ASSERT_FALSE(Card_less(ace_of_spades, two_of_spades, SPADES));
    ASSERT_FALSE(Card_less(king_of_hearts, ace_of_spades, HEARTS));
}

TEST(tests_card_less_led) {
    Card ace_of_spades = Card(ACE, SPADES);
    Card two_of_spades = Card(TWO, SPADES);
    Card king_of_hearts = Card(KING, HEARTS);
    Card ten_of_clubs = Card(TEN, CLUBS);
    ASSERT_FALSE(Card_less(king_of_hearts, ten_of_clubs, king_of_hearts, DIAMONDS));
    ASSERT_FALSE(Card_less(ten_of_clubs, ace_of_spades, ten_of_clubs, DIAMONDS));
    ASSERT_TRUE(Card_less(two_of_spades, ace_of_spades, two_of_spades, DIAMONDS));
    ASSERT_FALSE(Card_less(ace_of_spades, two_of_spades, two_of_spades, DIAMONDS));
}

TEST_MAIN()
