// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Pack.h"
#include "unit_test_framework.h"

#include <iostream>

using namespace std;

TEST(test_pack_default_ctor) {
    Pack pack;
    Card first = pack.deal_one();
    ASSERT_EQUAL(NINE, first.get_rank());
    ASSERT_EQUAL(SPADES, first.get_suit());
}
/*
TEST(test_pack_ctor) {
    Pack pack;
    Card first = pack.deal_one();
}
*/
// Add more tests here
//TEST(test_pack_ctor) {
    //std::istream pack_input;
    //Pack pack(pack_input);
   // Card first = pack.deal_one();
  //  ASSERT_EQUAL(SPADES , first.get_rank())



TEST_MAIN()
