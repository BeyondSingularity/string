#include <algorithm>
#include <cstring>
#include <iostream>

class String {
  private:
    size_t size_, capacity_;
    char* string_;

    void expand_memory(size_t expand_size);
    size_t find_utility(const String& substr, size_t ind) const;

  public:
    String(int n, char c);
    String(const char* cstr);
    String();
    String(const String& other);
    String(char c);

    ~String();

    String& operator=(String other);

    char& operator[](size_t idx);
    const char& operator[](size_t idx) const;

    size_t length() const;
    size_t size() const;
    size_t capacity() const;

    void push_back(char c);

    void pop_back();

    char& front();
    const char& front() const;
    char& back();
    const char& back() const;
    const char* data() const;
    char* data();

    String& operator+=(const String& other);
    String& operator+=(char other);

    size_t find(const String& substr) const;
    size_t rfind(const String& substr) const;

    String substr(int start, int count) const;

    bool empty() const;
    void clear();

    void shrink_to_fit();
};

bool operator==(const String& a, const String& b);
bool operator!=(const String& a, const String& b);
bool operator<(const String& a, const String& b);
bool operator>(const String& a, const String& b);
bool operator>=(const String& a, const String& b);
bool operator<=(const String& a, const String& b);

String operator+(const String& a, const String& b);
String operator+(String a, char b);
String operator+(char a, const String& b);

std::ostream& operator<<(std::ostream& os, const String& obj);
std::istream& operator>>(std::istream& is, String& obj);