#ifndef MY_STRING_VIEW_H_
#define MY_STRING_VIEW_H_

#include <cstring>
#include <limits>
#include <algorithm>
#include <iostream>

class StringView {
 public:
  static const int npos;

  // CONSTRUCTORS
  StringView();
  explicit StringView(const char* str, int count = npos);
  StringView(const StringView& rhs);
  StringView(StringView&& rhs) noexcept;

  // ASSIGNMENT OPERATORS
  StringView& operator=(const StringView& rhs);
  StringView& operator=(StringView&& rhs) noexcept;

  // GETTERS
  int length() const;
  bool empty() const;
  const char* data() const;

  int find(const StringView& string_view, int position = 0) const;
  int find(char ch, int position = 0) const;

  StringView substr(int position, int count = npos) const;

  const char& at(int index);
  const char& at(int index) const;

  const char& operator[](int index);
  const char& operator[](int index) const;

  bool starts_with(const StringView& string_view) const;
  bool ends_with(const StringView& string_view) const;

  // DELETING PREFIX & SUFFIX
  void remove_prefix(int count);
  void remove_suffix(int count);

  // COMPARING
  int compare(const StringView& string_view) const;

  bool operator==(const StringView& rhs) const;
  bool operator!=(const StringView& rhs) const;
  bool operator<(const StringView& rhs) const;
  bool operator>(const StringView& rhs) const;
  bool operator<=(const StringView& rhs) const;
  bool operator>=(const StringView& rhs) const;


 private:
  int length_{};
  const char* string_{};
};

#endif  // MY_STRING_VIEW_H_
