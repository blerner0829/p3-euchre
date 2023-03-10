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

    Suit trump(CLUBS);

TEST(play_card_all_same) {
    Player * player = Player_factory("player", "Simple");
    // fills hand with ten_of_spades
    for (int i = 0; i < 5; ++i) {
        player->add_card(ten_of_spades);
    }
    ASSERT_EQUAL(ten_of_spades, player->play_card(king_of_spades, SPADES));
    ASSERT_EQUAL(ten_of_spades, player->play_card(nine_of_spades, CLUBS));
    ASSERT_EQUAL(ten_of_spades, player->play_card(jack_of_clubs, SPADES));
    ASSERT_EQUAL(ten_of_spades, player->play_card(nine_of_clubs, CLUBS));
    ASSERT_EQUAL(ten_of_spades, player->play_card(king_of_clubs, DIAMONDS));
    ASSERT_EQUAL(ten_of_spades, player->play_card(queen_of_clubs, HEARTS));
    player->add_and_discard(queen_of_spades);
    ASSERT_EQUAL(ten_of_spades, player->play_card(jack_of_clubs, SPADES));
    ASSERT_EQUAL(queen_of_spades, player->play_card(ten_of_spades, DIAMONDS));
    ASSERT_EQUAL(queen_of_spades, player->play_card(ace_of_spades, SPADES));
    delete player;
}
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
    ASSERT_EQUAL(ten_of_clubs, player->play_card(jack_of_hearts, DIAMONDS));
    ASSERT_EQUAL(ten_of_clubs, player->play_card(ten_of_hearts, DIAMONDS));
    ASSERT_EQUAL(nine_of_diamonds, player->play_card(ten_of_hearts, CLUBS));
    ASSERT_EQUAL(nine_of_diamonds, player->play_card(jack_of_hearts, SPADES));
    ASSERT_EQUAL(nine_of_diamonds, player->play_card(ace_of_hearts, HEARTS));
    player->add_and_discard(nine_of_spades);
    // ten_of_clubs, jack_of_diamonds, jack_of_spades,
    // ten_of_spades, nine_of_spades
    ASSERT_EQUAL(nine_of_spades, player->play_card(nine_of_hearts, CLUBS));
    ASSERT_EQUAL(nine_of_spades, player->play_card(nine_of_hearts, DIAMONDS));
    ASSERT_EQUAL(nine_of_spades, player->play_card(nine_of_hearts, HEARTS));
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
    ASSERT_EQUAL(jack_of_diamonds, player->play_card(ten_of_diamonds, HEARTS));
    player->add_and_discard(queen_of_clubs);
    // jack_of_spades, jack_of_diamonds, 
    // jack_of_clubs, ace_of_spades, queen_of_clubs
    player->add_and_discard(queen_of_hearts);
    // jack_of_diamonds, jack_of_clubs,
    // ace_of_spades, queen_of_clubs, queen_of_hearts
    player->add_and_discard(nine_of_clubs);
    // jack_of_clubs, ace_of_spades, 
    // queen_of_clubs, queen_of_hearts, nine_of_clubs
    ASSERT_EQUAL(queen_of_hearts, player->play_card(king_of_clubs, HEARTS));
    ASSERT_EQUAL(jack_of_clubs, player->play_card(king_of_hearts, SPADES));
    ASSERT_EQUAL(jack_of_clubs, player->play_card(king_of_hearts, CLUBS));
    player->add_and_discard(king_of_hearts);
    // jack_of_clubs, ace_of_spades, 
    // queen_of_clubs, queen_of_hearts, king_of_hearts
    ASSERT_EQUAL(king_of_hearts, player->play_card(ten_of_spades, HEARTS));
    player->add_and_discard(jack_of_spades);
    // jack_of_clubs, ace_of_spades, 
    // queen_of_hearts, king_of_hearts, jack_of_spades
    ASSERT_EQUAL(jack_of_spades, player->play_card(queen_of_clubs, SPADES));
    delete player;
}


TEST(test_add_card) {
    Player * player = Player_factory("player", "Simple");
    player->add_card(queen_of_hearts);
    player->add_card(ten_of_hearts);
    player->add_card(jack_of_diamonds);
    player->add_card(jack_of_clubs);
    player->add_card(king_of_spades);
    ASSERT_EQUAL(jack_of_clubs, player->play_card(ten_of_hearts, trump));
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
    // true because if hearts is made trump,
    // and queen_of_hearts is face
    // and jack_of_diamonds is left
    ASSERT_TRUE(player->make_trump(ace_of_spades, false, 2, trump));
    ASSERT_TRUE(player->make_trump(ace_of_spades, true, 2, trump));
    cout << "(order_up_suit) Expected: Clubs, Actual: " << trump << endl;
    ASSERT_TRUE(player->make_trump(ace_of_spades, true, 1, trump));
    delete player;
}

TEST(test_make_trump_false) {
    Player * player = Player_factory("player", "Simple");
    player->add_card(nine_of_spades);
    player->add_card(ten_of_hearts);
    player->add_card(jack_of_clubs);
    player->add_card(king_of_spades);
    ASSERT_FALSE(player->make_trump(queen_of_hearts, false, 1, trump));
    ASSERT_TRUE(player->make_trump(nine_of_spades, false, 1, trump));
    delete player;
}

TEST(test_make_trump_round_1) {
    Player * player = Player_factory("player", "Simple");
    player->add_card(jack_of_spades);
    player->add_card(queen_of_hearts);
    player->add_card(king_of_diamonds);
    player->add_card(jack_of_clubs);
    player->add_card(ace_of_diamonds);
    ASSERT_TRUE(player->make_trump(ten_of_clubs, false, 1, trump));
    ASSERT_EQUAL(clubs, trump);
    ASSERT_FALSE()
    delete player;
}

TEST(test_make_trump_round_2) {
    Player * player = Player_factory("player", "Simple");
    player->add_card(queen_of_hearts);
    player->add_card(jack_of_hearts);
    player->add_card(king_of_clubs);
    player->add_card(ace_of_spades);
    player->add_card(king_of_diamonds);
    ASSERT_TRUE(player->make_trump(ten_of_hearts, false, 2, trump));
    ASSERT_EQUAL(DIAMONDS, trump);
    ASSERT_TRUE(player->make_trump(queen_of_hearts, false, 2, trump));
    ASSERT_EQUAL(DIAMONDS, trump);
    player->add_and_discard(ten_of_spades);
    ASSERT_FALSE(player->make_trump(ten_of_hearts, false, 2, trump));
    ASSERT_TRUE(player->make_trump(king_of_diamonds, true, 2, trump));
    ASSERT_EQUAL(SPADES, trump);
    delete player;
}

TEST(test_add_and_discard) {
    Player * player = Player_factory("player", "Simple");
    player->add_card(nine_of_spades);
    player->add_card(jack_of_hearts);
    player->add_card(jack_of_clubs);
    player->add_card(king_of_spades);
    ASSERT_FALSE(player->make_trump(queen_of_hearts, false, 1, trump));
    player->add_and_discard(ace_of_hearts);
    ASSERT_TRUE(player->make_trump(queen_of_hearts, false, 1, trump));
    ASSERT_FALSE(player->make_trump(ten_of_clubs, false, 1, trump));
    player->add_and_discard(king_of_clubs);
    ASSERT_TRUE(player->make_trump(ten_of_clubs, false, 1, trump));
    delete player;
}

TEST(test_lead_card_basic) {
    Player * player = Player_factory("player", "Simple");
    player->add_card(queen_of_hearts);
    player->add_card(jack_of_diamonds);
    player->add_card(jack_of_clubs);
    player->add_card(king_of_clubs);
    ASSERT_EQUAL(king_of_clubs, player->lead_card(SPADES));
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
    // jack_of_clubs, jack_of_diamonds, ten_of_hearts, 
    //queen_of_hearts, king_of_hearts
    ASSERT_EQUAL(jack_of_diamonds, player->lead_card(HEARTS));
    player->add_and_discard(nine_of_hearts);
    // nine_of_hearts, ten_of_hearts, queen_of_hearts, 
    //jack_of_diamonds, king_of_hearts
    ASSERT_EQUAL(jack_of_diamonds, player->lead_card(HEARTS));
    player->add_and_discard(jack_of_hearts);
    // jack_of_hearts, ten_of_hearts, queen_of_hearts, 
    //jack_of_diamonds, king_of_hearts
    ASSERT_EQUAL(jack_of_hearts, player->lead_card(HEARTS));
    ASSERT_EQUAL(king_of_hearts, player->lead_card(CLUBS));
    // jack of diamods, jack_of_clubs, jack_of_hearts, 
    //queen_of_hearts, king_of_hearts
    player->add_and_discard(ace_of_hearts);
    // jack_of_hearts, queen_of_hearts, king_of_hearts, 
    //ace_of_hearts, jack_of_diamonds
    ASSERT_EQUAL(jack_of_hearts, player->play_card(nine_of_hearts, HEARTS));
    ASSERT_EQUAL(jack_of_hearts, player->lead_card(HEARTS));
    ASSERT_EQUAL(ace_of_hearts, player->lead_card(CLUBS));
    delete player;
}

TEST_MAIN()
