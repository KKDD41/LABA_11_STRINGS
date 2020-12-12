#include <gtest/gtest.h>
#include <string>
#include "my_string.h"

TEST(Test_0, WhatIsWrongWithConstructors) {
  {
    std::string s;
    String s1;
    EXPECT_STREQ(s.c_str(), s1.c_str());
    EXPECT_EQ(s.length(), s1.length());
  }
  {
    std::string s{"kek"};
    String s1{"kek"};
    EXPECT_STREQ(s.c_str(), s1.c_str());
    EXPECT_EQ(s.length(), s1.length());
  }
  {
    char s[] = "kek";
    String s1(s);
    EXPECT_STREQ(s, s1.c_str());
    EXPECT_EQ(strlen(s), s1.length());
  }
  {
    char s[] = "AAA";
    String s1(3, 'A');
    EXPECT_STREQ(s, s1.c_str());
    EXPECT_EQ(strlen(s), s1.length());
  }
  {
    char* s;
    String s1(s);
    EXPECT_STREQ(s, s1.c_str());
    EXPECT_EQ(strlen(s), s1.length());
  }
  {
    char s[] = {'\0', '\0', '\a', '\0'};
    String s1(s);
    EXPECT_STREQ(s1.c_str(), s);
    EXPECT_EQ(strlen(s), s1.length());
  }
  {
    char s[] = {'p', 'o', 'm', 'i', 'd', 'o', 'r', '\0'};
    String s1(s);
    EXPECT_STREQ(s1.c_str(), s);
    EXPECT_EQ(strlen(s), s1.length());
  }
  {
    String s1("ha-ha-ha");
    String s2(s1);
    EXPECT_STREQ(s1.c_str(), s2.c_str());
    EXPECT_EQ(s1.length(), s2.length());
  }
  {
    String s1("ha-ha-ha");
    String s2(std::move(s1));
    EXPECT_STREQ("ha-ha-ha", s2.c_str());
    EXPECT_EQ(8, s2.length());
    EXPECT_STREQ("", s1.c_str());
    EXPECT_EQ(0, s1.length());
  }
}

TEST(Test_1, PushPop) {
  {
    String s("BS");
    s.push_back('U');
    EXPECT_STREQ("BSU", s.c_str());
    EXPECT_EQ(3, s.length());
    s.pop_back();
    EXPECT_STREQ("BS", s.c_str());
    EXPECT_EQ(2, s.length());
    s.pop_back();
    EXPECT_STREQ("B", s.c_str());
    EXPECT_EQ(1, s.length());
    s.pop_back();
    EXPECT_STREQ("", s.c_str());
    EXPECT_ANY_THROW(s.pop_back());
    EXPECT_EQ(0, s.length());
    s.push_back('A');
    EXPECT_STREQ("A", s.c_str());
    s.push_back('B');
    EXPECT_STREQ("AB", s.c_str());
    for (int i = 0; i < 10; i++) {
      s.push_back('Z');
    }
    EXPECT_STREQ("ABZZZZZZZZZZ", s.c_str());
    s.pop_back();
    EXPECT_STREQ("ABZZZZZZZZZ", s.c_str());
    for (int i = 0; i < 9; i++) {
      s.pop_back();
    }
    EXPECT_STREQ("AB", s.c_str());
  }
  {
    String s;
    s.push_back('X');
    EXPECT_STREQ("X", s.c_str());
  }
}

TEST(Test_2, InsertingStrings) {
  {
    String s;
    s.insert(0, "abc", 3);
    EXPECT_STREQ("abc", s.c_str());
    EXPECT_EQ(3, s.length());
    s.insert(1, "123", 2);
    EXPECT_STREQ("a12bc", s.c_str());
    EXPECT_EQ(5, s.length());
    s.insert(3, "34567", 5);
    EXPECT_STREQ("a1234567bc", s.c_str());
    EXPECT_EQ(10, s.length());
    s.insert(10, "kek", 3);
    EXPECT_STREQ("a1234567bckek", s.c_str());
    EXPECT_EQ(13, s.length());
    s.insert(8, "haha", 0);
    EXPECT_STREQ("a1234567bckek", s.c_str());
    EXPECT_EQ(13, s.length());
  }
  {
    String s;
    s.insert(0, String("abc"));
    EXPECT_STREQ("abc", s.c_str());
    s.insert(1, String("12"));
    EXPECT_STREQ("a12bc", s.c_str());
    s.insert(3, String("34567"));
    EXPECT_STREQ("a1234567bc", s.c_str());
    s.insert(10, String("kek"));
    EXPECT_STREQ("a1234567bckek", s.c_str());
  }
}

TEST(Test_3, Erase) {
  {
    String s("01234567");
    s.erase(0, 1);
    EXPECT_STREQ("1234567", s.c_str());
    EXPECT_EQ(7, s.length());
    s.erase(2, 3);
    EXPECT_STREQ("1267", s.c_str());
    EXPECT_EQ(4, s.length());
    s.erase(2, 3);
    EXPECT_STREQ("12", s.c_str());
    EXPECT_EQ(2, s.length());
    EXPECT_ANY_THROW(s.erase(2, 6));
    EXPECT_STREQ("12", s.c_str());
    EXPECT_EQ(2, s.length());
    s.erase(0, 5);
    EXPECT_STREQ("", s.c_str());
    EXPECT_EQ(0, s.length());
  }
}

TEST(Test_4, Concatenation) {
  {
    String a("haha");
    String b("hehe");
    EXPECT_STREQ("hahahehe", (a + b).c_str());
    EXPECT_EQ(8, (a + b).length());
    EXPECT_STREQ("haha", a.c_str());
    EXPECT_STREQ("hehe", b.c_str());
    b += a;
    EXPECT_STREQ("hehehaha", b.c_str());
  }
  {
    String s;
    String t("smile");
    EXPECT_TRUE(t == s + t);
    EXPECT_TRUE(t == t + s);
    t += s;
    EXPECT_STREQ("smile", t.c_str());
    s += t;
    EXPECT_STREQ(s.c_str(), t.c_str());
  }
}

