// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Card.hpp"
#include "unit_test_framework.hpp"
#include <iostream>

using namespace std;

Card ace_of_spades(ACE, SPADES);
Card ten_of_hearts(TEN, HEARTS);
Card nine_of_spades(NINE, SPADES);
Card jack_of_diamonds(JACK, DIAMONDS);
Card king_of_clubs(KING, CLUBS);
Card jack_of_hearts(JACK, HEARTS);
Card queen_of_hearts(QUEEN, HEARTS);
Card king_of_spades(KING, SPADES);
Card jack_of_clubs(JACK, CLUBS);
Card ace_of_hearts(ACE, HEARTS);
Card ten_of_clubs(TEN, CLUBS);
Card king_of_hearts(KING, HEARTS);
Card nine_of_hearts(NINE, HEARTS);
Card ten_of_spades(TEN, SPADES);
Card ten_of_diamonds(TEN, DIAMONDS);
Card queen_of_clubs(QUEEN, CLUBS);
Card nine_of_clubs(NINE, CLUBS);
Card queen_of_spades(QUEEN, SPADES);
Card ace_of_clubs(ACE, CLUBS);
Card nine_of_diamonds(NINE, DIAMONDS);
Card king_of_diamonds(KING, DIAMONDS);
Card ace_of_diamonds(ACE, DIAMONDS);
Card queen_of_diamonds(QUEEN, DIAMONDS);
Card two_of_spades(TWO, SPADES);
Card two_of_hearts(TWO, HEARTS);
Card three_of_clubs(THREE, CLUBS);
Card two_of_diamonds(TWO, DIAMONDS);
Card jack_of_spades(JACK, SPADES);

TEST(test_card_ctor) {
    Card card;
    ASSERT_EQUAL(SPADES, card.get_suit());
    ASSERT_EQUAL(TWO, card.get_rank());
}

TEST(test_card_ctor_parameters) {
    Card card(TWO, SPADES);
    ASSERT_EQUAL(SPADES, card.get_suit());
    ASSERT_EQUAL(TWO, card.get_rank());

    Card cardTwo(TEN, CLUBS);
    ASSERT_EQUAL(CLUBS, cardTwo.get_suit());
    ASSERT_EQUAL(TEN, cardTwo.get_rank());

}

TEST(test_suit) {
    ASSERT_EQUAL(HEARTS, jack_of_hearts.get_suit());
    ASSERT_EQUAL(DIAMONDS, jack_of_diamonds.get_suit());
    ASSERT_EQUAL(SPADES, jack_of_spades.get_suit());
    ASSERT_EQUAL(CLUBS, jack_of_clubs.get_suit());
    ASSERT_EQUAL(DIAMONDS, two_of_diamonds.get_suit());
    ASSERT_EQUAL(SPADES, nine_of_spades.get_suit());
    ASSERT_NOT_EQUAL(DIAMONDS, jack_of_spades.get_suit());
}

TEST(tests_suit_trump) {
    ASSERT_EQUAL(DIAMONDS, jack_of_hearts.get_suit(DIAMONDS));
    ASSERT_EQUAL(HEARTS, jack_of_diamonds.get_suit(HEARTS));
    ASSERT_EQUAL(CLUBS, jack_of_spades.get_suit(CLUBS));
    ASSERT_EQUAL(SPADES, jack_of_clubs.get_suit(SPADES));
    ASSERT_EQUAL(DIAMONDS, two_of_diamonds.get_suit(DIAMONDS));
    ASSERT_EQUAL(SPADES, nine_of_spades.get_suit(DIAMONDS));
    ASSERT_NOT_EQUAL(DIAMONDS, jack_of_spades.get_suit(SPADES));
}

TEST(tests_is_face) {
    ASSERT_TRUE(jack_of_hearts.is_face_or_ace());
    ASSERT_TRUE(queen_of_spades.is_face_or_ace());
    ASSERT_TRUE(king_of_clubs.is_face_or_ace());
    ASSERT_TRUE(ace_of_diamonds.is_face_or_ace());
    ASSERT_FALSE(two_of_hearts.is_face_or_ace());
}

TEST(test_is_right_bower) {
    ASSERT_TRUE(jack_of_hearts.is_right_bower(HEARTS));
    ASSERT_FALSE(jack_of_hearts.is_right_bower(DIAMONDS));
    ASSERT_FALSE(queen_of_diamonds.is_right_bower(DIAMONDS));
    ASSERT_TRUE(jack_of_diamonds.is_right_bower(DIAMONDS));
    ASSERT_TRUE(jack_of_clubs.is_right_bower(CLUBS));
    ASSERT_TRUE(jack_of_spades.is_right_bower(SPADES));
}

TEST(tests_is_left_bower) {
    ASSERT_TRUE(jack_of_hearts.is_left_bower(DIAMONDS));
    ASSERT_FALSE(jack_of_hearts.is_left_bower(SPADES));
    ASSERT_TRUE(jack_of_diamonds.is_left_bower(HEARTS));
    ASSERT_TRUE(jack_of_spades.is_left_bower(CLUBS));
    ASSERT_TRUE(jack_of_clubs.is_left_bower(SPADES));
    ASSERT_FALSE(ace_of_hearts.is_left_bower(DIAMONDS));
}

TEST(tests_is_trump) {
    ASSERT_TRUE(ace_of_spades.is_trump(SPADES));
    ASSERT_FALSE(ace_of_spades.is_trump(CLUBS));
    ASSERT_TRUE(jack_of_hearts.is_trump(HEARTS));
    ASSERT_TRUE(jack_of_hearts.is_trump(DIAMONDS));
    ASSERT_FALSE(jack_of_hearts.is_trump(SPADES));
    ASSERT_TRUE(three_of_clubs.is_trump(CLUBS));
}

TEST(test_suit_next) {
    ASSERT_EQUAL(SPADES, Suit_next(CLUBS));
    ASSERT_EQUAL(CLUBS, Suit_next(SPADES));
    ASSERT_EQUAL(HEARTS, Suit_next(DIAMONDS));
    ASSERT_EQUAL(DIAMONDS, Suit_next(HEARTS));
}

TEST(tests_card_less) {
    // Test Case 1: Cards are equal and have the same suit
    Card card1(TWO, SPADES);
    Card card2(TWO, SPADES);
    Suit trumpSuit = HEARTS;
    ASSERT_FALSE(Card_less(card1, card2, trumpSuit));

    // Test Case 2: a is right bower, b is not
    Card rightBower(JACK, trumpSuit);
    Card notRightBower(TEN, CLUBS);
    ASSERT_FALSE(Card_less(rightBower, notRightBower, trumpSuit));

    // Test Case 3: a is not right bower, b is left bower
    Card leftBower(JACK, DIAMONDS);
    ASSERT_TRUE(Card_less(card1, leftBower, trumpSuit));

    // Test Case 4: a is left bower, b is right bower
    ASSERT_TRUE(Card_less(leftBower, rightBower, trumpSuit));

    // Test Case 5: a is left bower, b is not right bower
    ASSERT_FALSE(Card_less(leftBower, notRightBower, trumpSuit));

    // Test Case 6: a is not right bower, b is right bower
    ASSERT_TRUE(Card_less(notRightBower, rightBower, trumpSuit));

    // Test Case 7: a and b are both trump, a < b
    Card trumpCard1(QUEEN, trumpSuit);
    Card trumpCard2(KING, trumpSuit);
    ASSERT_TRUE(Card_less(trumpCard1, trumpCard2, trumpSuit));

    // Test Case 8: a is trump, b is not
    Card nonTrumpCard(TEN, CLUBS);
    ASSERT_FALSE(Card_less(trumpCard1, nonTrumpCard, trumpSuit));

    // Test Case 9: a is not trump, b is trump
    ASSERT_TRUE(Card_less(nonTrumpCard, trumpCard1, trumpSuit));

    // Test Case 10: a < b
    Card lowCard(TWO, SPADES);
    Card highCard(ACE, DIAMONDS);
    ASSERT_TRUE(Card_less(lowCard, highCard, trumpSuit));

    // Test Case 11: a >= b
    ASSERT_FALSE(Card_less(highCard, lowCard, trumpSuit));
}

TEST(tests_card_less_led) {

    ASSERT_FALSE(Card_less(king_of_hearts, ten_of_clubs, king_of_hearts,
    DIAMONDS));
    ASSERT_FALSE(Card_less(ten_of_clubs, ace_of_spades, ten_of_clubs,
    DIAMONDS));
    ASSERT_TRUE(Card_less(two_of_spades, ace_of_spades, two_of_spades,
    DIAMONDS));
    ASSERT_FALSE(Card_less(ace_of_spades, two_of_spades, two_of_spades,
    DIAMONDS));

    ASSERT_FALSE(Card_less(ace_of_spades, ace_of_spades, two_of_spades, SPADES));
    ASSERT_FALSE(Card_less(jack_of_clubs, queen_of_clubs, ace_of_spades, CLUBS));
    ASSERT_TRUE(Card_less(king_of_hearts, jack_of_spades, ten_of_clubs, CLUBS));
    ASSERT_TRUE(Card_less(jack_of_hearts, jack_of_diamonds, nine_of_spades, DIAMONDS));
    ASSERT_TRUE(Card_less(queen_of_diamonds, jack_of_hearts, ace_of_spades, HEARTS));
    ASSERT_FALSE(Card_less(jack_of_clubs, queen_of_clubs, king_of_hearts, SPADES));
    ASSERT_TRUE(Card_less(ten_of_hearts, king_of_hearts, nine_of_clubs, HEARTS));
    ASSERT_FALSE(Card_less(king_of_spades, nine_of_spades, ten_of_clubs, SPADES));
    ASSERT_FALSE(Card_less(ace_of_spades, king_of_diamonds, queen_of_spades, SPADES));
    ASSERT_TRUE(Card_less(ten_of_clubs, jack_of_diamonds, ten_of_hearts, DIAMONDS));

    ASSERT_FALSE(Card_less(nine_of_spades, jack_of_diamonds, queen_of_spades, CLUBS));
    ASSERT_TRUE(Card_less(king_of_diamonds, ace_of_hearts, ten_of_hearts, CLUBS));
    ASSERT_TRUE(Card_less(nine_of_spades, ten_of_spades, king_of_spades, HEARTS));
    ASSERT_FALSE(Card_less(king_of_clubs, queen_of_clubs, ten_of_clubs, DIAMONDS));

    ASSERT_TRUE(Card_less(jack_of_clubs, queen_of_diamonds, ten_of_hearts, HEARTS));
    ASSERT_FALSE(Card_less(king_of_spades, nine_of_diamonds, ten_of_clubs, CLUBS));

}

TEST_MAIN()
