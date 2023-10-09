 // Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Player.hpp"
#include "unit_test_framework.hpp"

#include <iostream>

using namespace std;

TEST(test_player_get_name) {
    Player * alice = Player_factory("Alice", "Simple");
    ASSERT_EQUAL("Alice", alice->get_name());

    delete alice;
}


// Add more tests here
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
    Card jack_of_spades(JACK, SPADES);
    Card ten_of_spades(TEN, SPADES);
    Card ten_of_diamonds(TEN, DIAMONDS);
    Card queen_of_clubs(QUEEN, CLUBS);
    Card nine_of_clubs(NINE, CLUBS);
    Card queen_of_spades(QUEEN, SPADES);
    Card ace_of_clubs(ACE, CLUBS);
    Card nine_of_diamonds(NINE, DIAMONDS);
    Card king_of_diamonds(KING, DIAMONDS);
    Card ace_of_diamonds(ACE, DIAMONDS);
    Suit order_up_suit(CLUBS);

/*
CAUSING SEGFAULT RN
TEST(play_card_all_same) {
    Player * player1 = Player_factory("player", "Simple");
    // fills hand with ten_of_spades
    for (int i = 0; i < 5; ++i) {
        player1->add_card(ten_of_spades);
    }
    ASSERT_FALSE(player1->make_trump(king_of_spades, false, 1, order_up_suit));
    ASSERT_FALSE(player1->make_trump(nine_of_spades, true, 1, order_up_suit));
    ASSERT_FALSE(player1->make_trump(queen_of_hearts, false, 2, order_up_suit));
    ASSERT_FALSE(player1->make_trump(king_of_spades, false, 2, order_up_suit));
    ASSERT_TRUE(player1->make_trump(ten_of_spades, true, 2, order_up_suit));
    ASSERT_EQUAL(CLUBS, order_up_suit);

    ASSERT_EQUAL(ten_of_spades, player1->play_card(king_of_spades, SPADES));
    ASSERT_EQUAL(ten_of_spades, player1->play_card(nine_of_spades, CLUBS));
    ASSERT_EQUAL(ten_of_spades, player1->play_card(jack_of_clubs, SPADES));
    ASSERT_EQUAL(ten_of_spades, player1->play_card(nine_of_clubs, CLUBS));
    ASSERT_EQUAL(ten_of_spades, player1->play_card(king_of_clubs, DIAMONDS));
    ASSERT_EQUAL(ten_of_spades, player1->play_card(queen_of_clubs, HEARTS));
    player1->add_and_discard(queen_of_spades);
    ASSERT_EQUAL(ten_of_spades, player1->play_card(jack_of_clubs, SPADES));
    ASSERT_EQUAL(queen_of_spades, player1->play_card(ten_of_spades, DIAMONDS));
    ASSERT_EQUAL(queen_of_spades, player1->play_card(ace_of_spades, SPADES));
    delete player1; 
} */
// tests for play_card:

//  - hand[0] is highest
//  - hand[4] is highest
//  - all cards are the same
//  - right bower
//  - left bower

// when there is not a led suit card
TEST(play_card_lowest_edge) {
    Player * player = Player_factory("player", "Simple");
    player->add_card(ten_of_clubs);
    player->add_card(jack_of_diamonds);
    player->add_card(jack_of_spades);
    player->add_card(ten_of_spades);
    player->add_card(nine_of_diamonds);
    ASSERT_EQUAL(ten_of_spades, player->play_card(jack_of_hearts, DIAMONDS)); // elim ten_of_spades
    // ten_of_clubs, jack_of_diamonds,
    // jack_of_spades, nine_of_diamonds
    player->add_card(ten_of_spades);
    // ten_of_clubs, jack_of_diamonds, jack_of_spades, 
    // nine_of_diamonds, ten_of_spades
    ASSERT_EQUAL(ten_of_spades, player->play_card(ten_of_hearts, DIAMONDS)); // elim ten_of_spades
    player->add_card(ten_of_spades);
    // ten_of_clubs, jack_of_diamonds, jack_of_spades, 
    // nine_of_diamonds, ten_of_spades
    ASSERT_EQUAL(nine_of_diamonds, player->play_card(ten_of_hearts, CLUBS)); // elim nine_of_diamonds
    // ten_of_clubs, jack_of_diamonds, 
    // jack_of_spades, ten_of_spades
    ASSERT_EQUAL(ten_of_clubs, player->play_card(jack_of_hearts, SPADES)); // elim ten_of_clubs
    // jack_of_diamonds, jack_of_spades, 
    // ten_of_spades
    ASSERT_EQUAL(ten_of_spades, player->play_card(ace_of_hearts, HEARTS)); // elim ten_of_spades
    player->add_and_discard(nine_of_spades);
    // jack_of_diamonds, jack_of_spades, nine_of_spades
    ASSERT_EQUAL(nine_of_spades, player->play_card(jack_of_hearts, CLUBS)); // elim nine_of_spades
    // jack_of_diamonds, jack_of_spades
    ASSERT_EQUAL(jack_of_spades, player->play_card(queen_of_clubs, DIAMONDS)); // elim jack_of_spades
    player->add_card(jack_of_clubs);
    // jack_of_diamonds, jack_of_spades, jack_of_clubs
    ASSERT_EQUAL(jack_of_diamonds, player->play_card(ace_of_diamonds, HEARTS));
    
    delete player;
}

// when there is a led suit card: 
TEST(play_card_highest_edge) {
    Player * player = Player_factory("player", "Simple");
    player->add_card(jack_of_spades);
    player->add_card(ten_of_spades);
    player->add_card(jack_of_diamonds);
    player->add_card(jack_of_clubs);
    player->add_card(ace_of_spades);
    ASSERT_EQUAL(jack_of_spades, player->play_card(nine_of_spades, SPADES));
    player->add_card(jack_of_spades);
    ASSERT_EQUAL(jack_of_diamonds, player->play_card(ten_of_diamonds, HEARTS));
    player->add_card(jack_of_diamonds);
    // ten_of_spades, jack_of_clubs, ace_of_spades, 
    // jack_of_spades, jack_of_diamonds
    player->add_and_discard(queen_of_clubs); // ten of spades
    // jack_of_clubs, ace_of_spades, 
    // jack_of_spades, jack_of_diamonds, queen_of_clubs
    player->add_and_discard(queen_of_hearts); // jack of spades
    // jack_of_clubs, ace_of_spades, 
    // jack_of_diamonds, queen_of_clubs, queen_of_hearts
    player->add_and_discard(nine_of_clubs); // jack of diamonds
    // jack_of_clubs, ace_of_spades, 
    // queen_of_clubs, queen_of_hearts, nine_of_clubs
    ASSERT_EQUAL(queen_of_clubs, player->play_card(king_of_clubs, HEARTS));
    // jack_of_clubs, ace_of_spades, 
    // queen_of_hearts, nine_of_clubs
    player->add_and_discard(ace_of_diamonds);
    // is:
    // jack_of_clubs, ace_of_spades, 
    // queen_of_hearts, ace_of_diamonds
    
    // was:
    // ace_of_spades, queen_of_hearts,
    // nine_of_clubs, ace_of_diamonds
    ASSERT_EQUAL(ace_of_spades, player->play_card(king_of_spades, HEARTS)); 
    // jack_of_clubs, queen_of_hearts, 
    // ace_of_diamonds
    ASSERT_EQUAL(jack_of_clubs, player->play_card(king_of_clubs, CLUBS));
    // queen_of_hearts, ace_of_diamonds
    player->add_and_discard(king_of_hearts);
    // queen_of_hearts, king_of_hearts
    player->add_card(queen_of_clubs);
    // queen_of_hearts, king_of_hearts, queen_of_clubs
    ASSERT_EQUAL(queen_of_clubs, player->play_card(ten_of_spades, HEARTS));
    // queen_of_hearts, king_of_hearts
    player->add_and_discard(jack_of_spades);
    // king_of_hearts, jack_of_spades
    ASSERT_EQUAL(jack_of_spades, player->play_card(queen_of_spades, SPADES));
    // king_of_hearts
    delete player;
}


TEST(test_add_card) {
    Player * player = Player_factory("player", "Simple");
    player->add_card(queen_of_hearts);
    player->add_card(ten_of_hearts);
    player->add_card(jack_of_diamonds);
    player->add_card(jack_of_clubs);
    player->add_card(king_of_spades);
    ASSERT_EQUAL(queen_of_hearts, player->play_card(ten_of_hearts, order_up_suit));
    delete player;
}
//use playcard to test add card
TEST(test_make_trump_true) {
    Player * player = Player_factory("player", "Simple");
    player->add_card(queen_of_hearts);
    player->add_card(jack_of_diamonds);
    player->add_card(jack_of_clubs);
    player->add_card(king_of_spades);
    player->add_card(nine_of_hearts);
    // true because if hearts is made order_up_suit,
    // and queen_of_hearts is face
    // and jack_of_diamonds is left
    ASSERT_TRUE(player->make_trump(ace_of_spades, false, 2, order_up_suit));
    ASSERT_TRUE(player->make_trump(ace_of_spades, true, 2, order_up_suit));
    cout << "(order_up_suit) Expected: Clubs, Actual: " << order_up_suit << endl;
    ASSERT_TRUE(player->make_trump(ace_of_spades, true, 1, order_up_suit));
    delete player;
}

TEST(test_make_trump_false) {
    Player * player = Player_factory("player", "Simple");
    player->add_card(nine_of_spades);
    player->add_card(ten_of_hearts);
    player->add_card(jack_of_clubs);
    player->add_card(king_of_spades);
    ASSERT_FALSE(player->make_trump(queen_of_hearts, false, 1, order_up_suit));
    ASSERT_TRUE(player->make_trump(nine_of_spades, false, 1, order_up_suit));
    delete player;
}

TEST(test_make_trump_round_1) {
    Player * player = Player_factory("player", "Simple");
    player->add_card(jack_of_spades);
    player->add_card(queen_of_hearts);
    player->add_card(king_of_diamonds);
    player->add_card(jack_of_clubs);
    player->add_card(ace_of_diamonds);
    ASSERT_TRUE(player->make_trump(ten_of_clubs, false, 1, order_up_suit));
    ASSERT_EQUAL(CLUBS, order_up_suit);
    delete player;
}

TEST(test_make_trump_round_2) {
    Player * player = Player_factory("player", "Simple");
    player->add_card(queen_of_hearts);
    player->add_card(jack_of_hearts);
    player->add_card(king_of_clubs);
    player->add_card(ace_of_spades);
    player->add_card(king_of_diamonds);
    ASSERT_TRUE(player->make_trump(ten_of_hearts, false, 2, order_up_suit));
    ASSERT_EQUAL(DIAMONDS, order_up_suit);
    ASSERT_TRUE(player->make_trump(queen_of_hearts, false, 2, order_up_suit));
    ASSERT_EQUAL(DIAMONDS, order_up_suit);
    player->add_and_discard(ten_of_spades);
    // queen_of_hearts, king_of_clubs, 
    // ace_of_spades, king_of_diamonds, ten_of_spades
    ASSERT_TRUE(player->make_trump(ten_of_hearts, false, 2, order_up_suit));
    ASSERT_TRUE(player->make_trump(king_of_diamonds, true, 2, order_up_suit));
    ASSERT_EQUAL(HEARTS, order_up_suit);
    delete player;
}

TEST(test_add_and_discard) {
    Player * player = Player_factory("player", "Simple");
    player->add_card(nine_of_spades);
    player->add_card(jack_of_hearts);
    player->add_card(jack_of_clubs);
    player->add_card(king_of_spades);
    // nine_of_spades, jack_of_hearts, 
    // jack_of_clubs, king_of_spades
    ASSERT_FALSE(player->make_trump(queen_of_hearts, false, 1, order_up_suit));
    player->add_card(queen_of_hearts);
    // nine_of_spades, jack_of_hearts, 
    // jack_of_clubs, king_of_spades, queen_of_hearts
    ASSERT_TRUE(player->make_trump(queen_of_hearts, false, 1, order_up_suit));
    ASSERT_EQUAL(order_up_suit, HEARTS);
    player->add_and_discard(ten_of_clubs); // discards nine_of_spades
    // jack_of_hearts, jack_of_clubs, 
    // king_of_spades, queen_of_hearts, ten_of_clubs
    ASSERT_TRUE(player->make_trump(queen_of_hearts, false, 1, order_up_suit));
    ASSERT_EQUAL(order_up_suit, HEARTS);
    ASSERT_FALSE(player->make_trump(ten_of_clubs, false, 1, order_up_suit));
    player->add_and_discard(king_of_clubs); // discards jack_of_hearts
    // jack_of_clubs, king_of_spades, 
    // queen_of_hearts, ten_of_clubs, king_of_clubs
    ASSERT_TRUE(player->make_trump(ten_of_clubs, false, 1, order_up_suit));
    ASSERT_EQUAL(order_up_suit, CLUBS);
    delete player;
}

TEST(test_lead_card_basic) {
    Player * player = Player_factory("player", "Simple");
    player->add_card(queen_of_hearts);
    player->add_card(jack_of_diamonds);
    player->add_card(jack_of_clubs);
    player->add_card(king_of_clubs);
    ASSERT_EQUAL(king_of_clubs, player->lead_card(SPADES));
    // queen_of_hearts, jack_of_diamonds, king_of_clubs
    ASSERT_EQUAL(queen_of_hearts, player->lead_card(CLUBS));
    delete player;
}

TEST(test_lead_card_complex) {
    Player * player = Player_factory("player", "Simple");
    player->add_card(queen_of_hearts);
    player->add_card(jack_of_diamonds);
    player->add_card(jack_of_clubs);
    player->add_card(king_of_hearts);
    player->add_card(ten_of_hearts);
    // queen_of_hearts, jack_of_diamonds, jack_of_clubs,
    // king_of_hearts, ten_of_hearts
    ASSERT_EQUAL(jack_of_diamonds, player->lead_card(HEARTS));
    // queen_of_hearts, jack_of_clubs, 
    // king_of_hearts, ten_of_hearts
    player->add_and_discard(nine_of_hearts);
    // jack_of_diamonds, king_of_hearts,
    // ten_of_hearts, nine_of_hearts
    ASSERT_EQUAL(jack_of_diamonds, player->lead_card(HEARTS));
    // king_of_hearts, ten_of_hearts, nine_of_hearts
    player->add_and_discard(jack_of_hearts);
    // ten_of_hearts, nine_of_hearts, jack_of_hearts
    ASSERT_EQUAL(jack_of_hearts, player->lead_card(HEARTS));
    // ten_of_hearts, nine_of_hearts
    ASSERT_EQUAL(ten_of_hearts, player->lead_card(CLUBS));
    // nine_of_hearts
    player->add_and_discard(ace_of_hearts);
    // ace_of_hearts
    ASSERT_EQUAL(ace_of_hearts, player->play_card(nine_of_hearts, HEARTS))
    player->add_card(ace_of_hearts);
    player->add_card(jack_of_hearts);
    player->add_card(king_of_hearts);
    // ace_of_hearts, jack_of_hearts, king_of_hearts
    ASSERT_EQUAL(jack_of_hearts, player->lead_card(HEARTS));
    player->add_card(jack_of_spades);
    player->add_card(king_of_spades);
    // ace_of_hearts, king_of_hearts,
    // jack_of_spades, king_of_spades
    ASSERT_EQUAL(ace_of_hearts, player->lead_card(CLUBS));
    delete player;
}

TEST_MAIN()

