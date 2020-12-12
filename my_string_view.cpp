#include "my_string_view.h"

const int StringView::npos = std::numeric_limits<int>::max();

// CONSTRUCTORS
StringView::StringView() {
  length_ = 0;
  string_ = nullptr;
}

StringView::StringView(const char* str, int count) {
  string_ = str;
  length_ = std::min(size_t(count), strlen(str));  // 1ul * count
  std::cout << string_ << std::endl;
}

StringView::StringView(const StringView& rhs) {
  (*this) = rhs;
}

StringView::StringView(StringView&& rhs) noexcept {
  (*this) = std::move(rhs);
}

// ASSIGNMENT OPERATORS

StringView& StringView::operator=(const StringView& rhs) {
  if (this == &rhs) {
    return *this;
  }
  length_ = rhs.length_;
  string_ = rhs.string_;
  return *this;
}

StringView& StringView::operator=(StringView&& rhs) noexcept {
  if (this == &rhs) {
    return *this;
  }
  length_ = rhs.length_;
  string_ = rhs.string_;
  rhs.string_ = nullptr;
  rhs.length_ = 0;
  return *this;
}

// GETTERS
int StringView::length() const {
  return length_;
}

bool StringView::empty() const {
  return length_ == 0;
}

const char* StringView::data() const {
  return string_;
}


const char& StringView::operator[](int index) {
  return string_[index];
}

const char& StringView::operator[](int index) const {
  return string_[index];
}

const char& StringView::at(int index) {
  if (index < 0 || index >= length_) {
    throw std::out_of_range("incorrect input");
  }
  return string_[index];
}

const char& StringView::at(int index) const {
  if (index < 0 || index >= length_) {
    throw std::out_of_range("Incorrect input");
  }
  return string_[index];
}

int StringView::find(const StringView& string_view, int position) const {
  for (int i = position; i <= length_ - string_view.length_; i++) {
    bool is_equal = true;
    for (int j = 0, k = i; j < string_view.length_; j++, k++) {
      if (string_[k] != string_view.string_[j]) {
        is_equal = false;
      }
    }
    if (is_equal) {
      return i;
    }
  }
  return npos;
}

int StringView::find(char ch, int position) const {
  for (int i = position; i < length_; ++i) {
    bool is_equal = true;
    if (string_[i] != ch) {
      is_equal = false;
    }
    if (is_equal) {
      return i;
    }
  }
  return npos;
}

StringView StringView::substr(int position, int count) const {
  int substr_length = std::min(count, length_ - position);
  return StringView(&string_[position], substr_length);
}

bool StringView::starts_with(const StringView& string_view) const {
  if (string_view.length_ > length_) {
    return false;
  }
  for (int i = 0; i < string_view.length_; i++) {
    if (string_[i] != string_view.string_[i]) {
      return false;
    }
  }
  return true;
}

bool StringView::ends_with(const StringView& string_view) const {
  if (string_view.length_ > length_) {
    return false;
  }
  for (int i = string_view.length_ - 1; i >= 0; i--) {
    // string_[length_ - 1 - (string_view.length_ - i - 1)]
    if (string_view.string_[i] != string_[length_ - string_view.length_ + i]) {
      return false;
    }
  }
  return true;
}

// DELETING

void StringView::remove_prefix(int count) {
  if (count > length_) {
    throw std::runtime_error("Incorrect input");
  }
  string_ = &string_[count];
  length_ -= count;
}

void StringView::remove_suffix(int count) {
  if (count > length_) {
    throw std::runtime_error("Incorrect input");
  }
  length_ -= count;
}

// COMPARING
int StringView::compare(const StringView& string_view) const {
  int min_length = std::min(length_, string_view.length_);
  int comparing_result = strncmp(string_, string_view.string_, min_length);
  if (comparing_result == 0) {
    if (length_ == string_view.length_) {
      comparing_result = 0;
    } else {
      comparing_result = (length_ < string_view.length_) ? -1 : 1;
    }
  }
  return comparing_result;
}

bool StringView::operator==(const StringView& rhs) const {
  return compare(rhs) == 0;
}

bool StringView::operator!=(const StringView& rhs) const {
  return !((*this) == rhs);
}

bool StringView::operator<=(const StringView& rhs) const {
  return !((*this) > rhs);
}

bool StringView::operator>=(const StringView& rhs) const {
  return !((*this) < rhs);
}

bool StringView::operator<(const StringView& rhs) const {
  return compare(rhs) < 0;
}

bool StringView::operator>(const StringView& rhs) const {
  return compare(rhs) > 0;
}

