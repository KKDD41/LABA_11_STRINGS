#include "my_string.h"

// CONSTRUCTORS

String::String() {
  length_ = 0;
  capacity_ = 1;
  string_ = new char[1];
  string_[0] = '\0';
}

String::String(const char* string) {
  length_ = strlen(string);
  capacity_ = length_ + 1;
  string_ = new char[capacity_];
  std::snprintf(string_, capacity_, "%s", string);
}

String::String(int count, char ch) {
  if (count < 0) {
    throw std::runtime_error("incorrect input");
  }
  length_ = count;
  capacity_ = length_ + 1;
  string_ = new char[capacity_];
  for (int i = 0; i < length_; i++) {
    string_[i] = ch;
  }
  string_[length_] = '\0';
}

String::String(const String& string) {
  (*this) = string;
}

String::String(String&& string) noexcept {
  (*this) = std::move(string);
}

// DELETING

String::~String() {
  delete [] string_;
  string_ = nullptr;
  length_ = 0;
  capacity_ = 1;
}

void String::clear() {
  if (length_ != 0) {
    delete [] string_;
    string_ = new char[1];
    string_[0] = '\0';
  }
  length_ = 0;
  capacity_ = 1;
}

// ASSIGNMENT OPERATORS

String& String::operator=(const String& rhs) {
  if (this == &rhs) {
    return *this;
  }
  delete[] string_;
  length_ = rhs.length_;
  capacity_ = rhs.length_ + 1;
  string_ = new char[capacity_];
  std::strncpy(string_, rhs.string_, length_);
  string_[length_] = '\0';
  return *this;
}

String& String::operator=(String&& rhs) noexcept {
  if (this == &rhs) {
    return *this;
  }
  delete[] string_;
  length_ = rhs.length_;
  capacity_ = rhs.length_ + 1;
  string_ = new char[capacity_];
  std::strncpy(string_, rhs.string_, length_);
  string_[length_] = '\0';
  rhs.clear();
  return *this;
}

// GETTERS

char& String::operator[](int index) {
  return string_[index];
}
const char& String::operator[](int index) const {
  return string_[index];
}

char* String::c_str() const {
  return string_;
}

// SIZE CHANGING

void String::reserve(int capacity) {
  // Here, according to the task, capacity is a required length of the string,
  // so we need real capacity_ at least (capacity + 1).
  if (capacity_ > capacity) {
    return;
  }
  capacity_ = capacity + 1;
  char* new_string = new char[capacity_];
  std::strncpy(new_string, string_, length_);
  string_[length_] = '\0';
  delete [] string_;
  string_ = new_string;
}

void String::push_back(char ch) {
  if (capacity_ <= length_ + 1) {
    this->reserve(2 * capacity_);
  }
  string_[length_++] = ch;
  string_[length_] = '\0';
}

void String::pop_back() {
  if (length_ == 0) {
    throw std::runtime_error("The string is empty!");
  }
  string_[length_ - 1] = '\0';
  length_--;
}

void String::insert(int index, const String& str) {
  this->insert(index, str.string_, str.length_);
}

void String::insert(int index, const char* str, int count) {
  if (index > length_) {
    throw std::runtime_error("The string is too short!");
  }
  if (count > strlen(str)) {
    throw std::runtime_error("Incorrect input");
  }
  this->reserve(length_ + count);
  char* buffer = new char[length_ - index];
  for (size_t i = index; i < length_; i++) {
    buffer[i - index] = string_[i];
  }
  for (size_t i = 0; i < count; i++) {
    string_[i + index] = str[i];
  }
  for (size_t i = 0; i < length_ - index; i++) {
    string_[i + index + count] = buffer[i];
  }
  length_ += count;
  string_[length_] = '\0';
  delete [] buffer;
}

void String::erase(int index, int count) {
  if (index >= length_) {
    throw std::runtime_error("The string is too short!");
  }
  if (index + count >= length_) {
    string_[index] = '\0';
    length_ = index;
    return;
  }
  for (size_t i = index + count; i < length_; i++) {
    string_[i - count] = string_[i];
  }
  length_ -= count;
  string_[length_] = '\0';
}

// COMPARING

int String::compare(const String& str) const {
  return strcmp(string_, str.string_);
}

int String::compare(const char* str) const {
  return compare(String(str));
}

// EQUALITY

bool String::operator==(const String& rhs) const {
  return this->compare(rhs) == 0;
}

bool String::operator!=(const String& rhs) const {
  return !((*this) == rhs);
}

bool operator==(const char* lhs, const String& rhs) {
  return rhs.compare(lhs) == 0;
}

bool operator!=(const char* lhs, const String& rhs) {
  return !(lhs == rhs);
}

// LEXICOGRAPHICAL COMPARING

bool String::operator<=(const String& rhs) const {
  return this->compare(rhs) <= 0;
}

bool String::operator>=(const String& rhs) const {
  return rhs <= (*this);
}

bool String::operator>(const String& rhs) const {
  return !((*this) <= rhs);
}

bool String::operator<(const String& rhs) const {
  return !((*this) >= rhs);
}

bool String::operator==(const char* rhs) const {
  return this->compare(rhs) == 0;
}

bool String::operator!=(const char* rhs) const {
  return !((*this) == rhs);
}

bool String::operator>(const char* rhs) const {
  return this->compare(rhs) > 0;
}

bool String::operator<(const char* rhs) const {
  return this->compare(rhs) < 0;
}

bool String::operator>=(const char* rhs) const {
  return this->compare(rhs) >= 0;
}

bool String::operator<=(const char* rhs) const {
  return this->compare(rhs) <= 0;
}

bool operator<=(const char* lhs, const String& rhs) {
  return !(rhs < lhs);
}

bool operator>=(const char* lhs, const String& rhs) {
  return !(rhs > lhs);
}

bool operator<(const char* lhs, const String& rhs) {
  return !(rhs <= lhs);
}

bool operator>(const char* lhs, const String& rhs) {
  return !(rhs >= lhs);
}

// CONCATENATION

String& String::operator+=(const String& str) {
  if (capacity_ <= length_ + str.length_ + 1) {
    this->reserve(length_ + str.length_);
  }
  strncpy(&string_[length_], str.string_, str.length_);
  length_ += str.length_;
  string_[length_] = '\0';
  return *this;
}

String String::operator+(const String& str) const {
  String result(*this);
  result += str;
  return result;
}











