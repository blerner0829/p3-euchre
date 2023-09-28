// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Pack.hpp"
#include "unit_test_framework.hpp"

#include <iostream>

using namespace std;

TEST(test_pack_default_ctor) {
    Pack pack;
    Card first = pack.deal_one();
    ASSERT_EQUAL(NINE, first.get_rank());
    ASSERT_EQUAL(SPADES, first.get_suit());
    Card second = pack.deal_one();
    ASSERT_EQUAL(TEN, second.get_rank());
}
// from public tests
TEST(test_pack_shuffle) {
    Pack pack;
    pack.shuffle();
    Card arr[24];
    for (int i = 0; i < 24; ++i) {
        arr[i] = pack.deal_one();
        cout << "i = " << i << " " << arr[i].get_rank()
            << " of " << arr[i].get_suit() << endl;
    }
    }
    /*
    vector<pair<int, Card>> v;
    for (int i = 0; i < 24; ++i) {
        v.push_back(make_pair(i, pack.deal_one()));
    }
    pack.shuffle();
    for (int i = 0; i < 24; ++i) {
        v[i].second = pack.deal_one();
        cout << "i = " << v[i].first << " " << v[i].second.get_rank()
            << " of " << v[i].second.get_suit() << endl;
    }
    }
    */
    /*
    Card arr[24];
    Pack pack;
    pack.shuffle();
    for (int i = 0; i < 24; ++i) {
        arr[i] = pack.deal_one();
        cout << "i = " << i << " " << arr[i].get_rank()
            << " of " << arr[i].get_suit() << endl;
    }
    ASSERT_EQUAL(arr[0], Card(NINE, CLUBS));
    ASSERT_EQUAL(arr[1], Card(NINE, SPADES));
    ASSERT_EQUAL(arr[2], Card(TEN, CLUBS));
    ASSERT_EQUAL(arr[3], Card(TEN, SPADES));

    // second shuffle
    cout << "\n\nSecond Shuffle" << endl;
    pack.shuffle();
    for (int i = 0; i < 24; ++i) {
        arr[i] = pack.deal_one();
        cout << "i = " << i << " " << arr[i].get_rank()
            << " of " << arr[i].get_suit() << endl;
    }
    // third shuffle
    pack.shuffle();
    // fourth shuffle
    pack.shuffle();
    // fifth shuffle
    pack.shuffle();
    // sixth shuffle
    pack.shuffle();
    cout << "\n\nSixth Shuffle" << endl;
    for (int i = 0; i < 24; ++i) {
        arr[i] = pack.deal_one();
        cout << "i = " << i << " " << arr[i].get_rank()
            << " of " << arr[i].get_suit() << endl;
    }
    // seventh shuffle
    pack.shuffle();
    cout << "\n\nSeventh Shuffle" << endl;
    for (int i = 0; i < 24; ++i) {
        arr[i] = pack.deal_one();
        cout << "i = " << i << " " << arr[i].get_rank()
            << " of " << arr[i].get_suit() << endl;

    }
    // eighth shuffle
    pack.shuffle();
    cout << "\n\nEighth Shuffle" << endl;
    for (int i = 0; i < 24; ++i) {
        arr[i] = pack.deal_one();
        cout << "i = " << i << " " << arr[i].get_rank()
            << " of " << arr[i].get_suit() << endl;
    }
*/

/*
TEST(test_pack_ctor) {
    Pack pack;
    Card first = pack.deal_one();
    ASSERT_EQUAL(NINE, first.get_rank());
    ASSERT_EQUAL(SPADES, first.get_suit());
}
*/





TEST_MAIN()
