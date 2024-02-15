#include "string.h"

void String::expand_memory(size_t expand_size) {
    capacity_ += expand_size;
    char* temp_string = new char[capacity_];
    memcpy(temp_string, string_, size_ + 1);
    std::swap(temp_string, string_);
    delete[] temp_string;
}

String::String(int n, char c)
    : size_(n), capacity_(n + 1), string_(new char[n + 1]) {
    memset(string_, c, n);
    string_[n] = '\0';
}
String::String(const char* cstr)
    : size_(strlen(cstr)),
      capacity_(strlen(cstr) + 1),
      string_(new char[strlen(cstr) + 1]) {
    memcpy(string_, cstr, size_);
    string_[size_] = '\0';
}
String::String() : size_(0), capacity_(1), string_(new char[1]) {
    string_[0] = '\0';
}
String::String(const String& other)
    : size_(other.size_),
      capacity_(other.size_ + 1),
      string_(new char[other.size_ + 1]) {
    memcpy(string_, other.string_, other.size_ + 1);
}
String::String(char c) : size_(1), capacity_(2), string_(new char[2]) {
    string_[0] = c;
    string_[1] = '\0';
}
String::~String() {
    delete[] string_;
}
String& String::operator=(String other) {
    std::swap(string_, other.string_);
    std::swap(size_, other.size_);
    std::swap(capacity_, other.capacity_);
    return *this;
}
char& String::operator[](size_t idx) {
    return string_[idx];
}
const char& String::operator[](size_t idx) const {
    return string_[idx];
}
size_t String::length() const {
    return size_;
}
size_t String::size() const {
    return size_;
}
size_t String::capacity() const {
    return capacity_ - 1;
}
void String::push_back(char c) {
    if (size_ + 1 == capacity_) {
        expand_memory(capacity_);
    }
    string_[size_++] = c;
    string_[size_] = '\0';
}
void String::pop_back() {
    string_[--size_] = '\0';
}
char& String::front() {
    return string_[0];
};
const char& String::front() const {
    return string_[0];
};
char& String::back() {
    return string_[size_ - 1];
}
const char& String::back() const {
    return string_[size_ - 1];
}
const char* String::data() const {
    return string_;
}
char* String::data() {
    return string_;
}
String& String::operator+=(const String& other) {
    if (size_ + other.size_ + 1 > capacity_) {
        expand_memory(2 * (size_ + other.size_ + 1) - capacity_);
    }
    memcpy(string_ + size_, other.string_, other.size_);
    size_ += other.size_;
    string_[size_] = '\0';
    return *this;
}
String& String::operator+=(char other) {
    push_back(other);
    return *this;
}

size_t String::find_utility(const String& substr, size_t ind) const {
    bool equal = true;
    for (size_t j = 0; j < substr.size_; ++j) {
        equal = equal && (string_[ind + j] == substr.string_[j]);
    }
    if (equal) {
        return ind;
    }
    return length() + 1;
}

size_t String::find(const String& substr) const {
    for (size_t i = 0; i < size_ - substr.size_; ++i) {
        size_t result = find_utility(substr, i);
        if (result != length() + 1) {
            return result;
        }
    }
    return length();
}
size_t String::rfind(const String& substr) const {
    for (size_t i = size_ - substr.size_; i >= 0; --i) {
        size_t result = find_utility(substr, i);
        if (result != length() + 1) {
            return result;
        }
    }
    return length();
}
String String::substr(int start, int count) const {
    String result(count, '\0');
    memcpy(result.string_, string_ + start, count);
    return result;
}
bool String::empty() const {
    return size_ == 0;
}
void String::clear() {
    size_ = 0;
    string_[0] = '\0';
}

void String::shrink_to_fit() {
    if (size_ + 1 == capacity_) {
        return;
    }
    String copy(*this);
    std::swap(copy.string_, string_);
    std::swap(copy.size_, size_);
    std::swap(copy.capacity_, capacity_);
}

bool operator==(const String& a, const String& b) {
    if (a.size() != b.size()) {
        return false;
    }
    for (size_t i = 0; i < a.size(); ++i) {
        if (a[i] != b[i]) {
            return false;
        }
    }
    return true;
}
bool operator!=(const String& a, const String& b) {
    return !(a == b);
}
bool operator<(const String& a, const String& b) {
    for (size_t i = 0; i < std::min(a.size(), b.size()); ++i) {
        if (a[i] == b[i]) {
            continue;
        }
        return a[i] < b[i];
    }
    return a.size() < b.size();
}
bool operator>(const String& a, const String& b) {
    return b < a;
}
bool operator>=(const String& a, const String& b) {
    return !(a < b);
}
bool operator<=(const String& a, const String& b) {
    return !(a > b);
}
String operator+(const String& a, const String& b) {
    String new_string(a);
    new_string += b;
    return new_string;
}
String operator+(String a, char b) {
    a.push_back(b);
    return a;
}
String operator+(char a, const String& b) {
    String result(a);
    result += b;
    return result;
}

std::ostream& operator<<(std::ostream& os, const String& obj) {
    for (size_t i = 0; i < obj.size(); ++i) {
        os << obj[i];
    }
    return os;
}

std::istream& operator>>(std::istream& is, String& obj) {
    String result;
    char last_c = ' ', now_c;
    for (; is.get(now_c); last_c = now_c) {
        if (std::isspace(last_c) == 0) {
            result.push_back(last_c);
            if (std::isspace(now_c) != 0) {
                break;
            }
        }
    }
    if (std::isspace(now_c) == 0) {
        result.push_back(now_c);
    }
    obj = result;
    return is;
}