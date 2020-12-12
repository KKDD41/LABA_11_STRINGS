#include <cstring>
#include <algorithm>
#include <exception>
#include <stdexcept>
#include <string>
#include <iostream>

#ifndef MY_STRING_H_
#define MY_STRING_H_

class String {
 public:
  // CONSTRUCTORS
  String();
  String(int count, char ch);
  explicit String(const char* string);

  String(const String& string);
  String(String&& string) noexcept;

  // DELETING
  ~String();
  void clear();

  // ASSIGNMENT OPERATORS
  String& operator=(const String& rhs);
  String& operator=(String&& string) noexcept;

  // GETTERS
  int length() const { return length_; }
  bool empty() const { return length_ == 0; }
  char* c_str() const;

  char& operator[](int index);
  const char& operator[](int index) const;

  char& front() { return string_[0]; }
  char& back() { return string_[length_ - 1]; }
  const char& front() const { return string_[0]; }
  const char& back() const { return string_[length_ - 1]; }

  // SIZE CHANGING
  void reserve(int capacity);
  void push_back(char ch);
  void pop_back();

  void insert(int index, const String& str);
  void insert(int index, const char* str, int count);
  void erase(int index, int count = 1);

  // COMPARING
  int compare(const String& str) const;
  int compare(const char* str) const;

  bool operator==(const String& rhs) const;
  bool operator!=(const String& rhs) const;
  bool operator>(const String& rhs) const;
  bool operator<(const String& rhs) const;
  bool operator>=(const String& rhs) const;
  bool operator<=(const String& rhs) const;

  bool operator==(const char* rhs) const;
  bool operator!=(const char* rhs) const;
  bool operator>(const char* rhs) const;
  bool operator<(const char* rhs) const;
  bool operator>=(const char* rhs) const;
  bool operator<=(const char* rhs) const;

  friend bool operator==(const char* lhs, const String& rhs);
  friend bool operator!=(const char* lhs, const String& rhs);
  friend bool operator<(const char* lhs, const String& rhs);
  friend bool operator>(const char* lhs, const String& rhs);
  friend bool operator>=(const char* lhs, const String& rhs);
  friend bool operator<=(const char* lhs, const String& rhs);

  // CONCATENATION
  String operator+(const String& str) const;
  String& operator+=(const String& str);

 private:
  char* string_{nullptr};
  int length_{0};  // without '\0'
  int capacity_{1};
};

#endif  // MY_STRING_H_
