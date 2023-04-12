#include "db.h"

#include <gtest/gtest.h>

#include <cstdlib>
#include <ctime>
#include <unordered_map>

using namespace textdb;

TEST(DB, Example) {
    srand(time(nullptr));

    auto db = DB::Open("store.textdb");
    std::unordered_map<std::string, std::string> map;

    // Put
    for (int i = 0; i < 5; i++) {
        std::string key = "key_" + std::to_string(i), value = "value_" + std::to_string(rand());
        db->Put(key, value);
        map[key] = value;
    }

    // Get
    for (int i = 0; i < 5; i++) {
        std::string key = "key_" + std::to_string(i);
        EXPECT_EQ(map[key], db->Get(key));
    }

    // Non-existent key
    for (int i = 5; i < 10; i++) {
        std::string key = "key_" + std::to_string(i);
        EXPECT_EQ("", db->Get(key));
    }

    db->Close();
}

TEST(Uvarint, EncodeUvarint) {
    EXPECT_EQ(std::string("\x00", 1), EncodeUvarint(0));
    EXPECT_EQ("\x01", EncodeUvarint(1));
    EXPECT_EQ("\x7f", EncodeUvarint(127));
    EXPECT_EQ("\x80\x01", EncodeUvarint(128));
    EXPECT_EQ("\xff\x01", EncodeUvarint(255));
    EXPECT_EQ("\x80\x02", EncodeUvarint(256));
    EXPECT_EQ("\xff\xff\xff\xff\xff\xff\xff\xff\xff\x01", EncodeUvarint(0xffffffffffffffff));
}