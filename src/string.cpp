using namespace std;
#include "string.hpp"
#include <iostream>


String::String(const char *s) 
: head{list::from_string(s)} {}

String::String(const String &s)
: head{list::copy(s.head)} {}

String::String(String &&s) : head{s.head} 
{
    s.head = nullptr;
}

String::String(list::Node* h) 
: head{h} {}

void String::swap(String &s) 
{
    std::swap(head, s.head);
}

String &String::operator=(const String &s)
{
    if (this != &s)
    {
        list::free(head);
        head = list::copy(s.head);
    }
    return *this;
}

String &String::operator=(String &&s)
{
    if (this != &s)
    {
        list::free(head);
        head = s.head;
        s.head = nullptr;
    }
    return *this;
}

bool String::in_bounds(int index) const 
{
    return index >= 0 && index < size();
}

char String::operator[](int index) const
{
    if (in_bounds(index))
    {
        return list::nth(head, index)->data;
    }
    else
    {
        cout << "ERROR: Index Out of Bounds" << endl;
        return '\0';
    }
}

int String::size() const
{
    return list::length(head);
}


String String::reverse() const 
{
    return String(list::reverse(head));  
}


int String::indexOf(char c) const
{
    list::Node* found = list::find_char(head, c);
    return list::index(head, found);
}

int String::indexOf(const String &s) const 
{
    if (s.head == nullptr)
    {
        return 0;
    }
    list::Node* found = list::find_list(head, s.head);
    return list::index(head, found);
}

bool String::operator==(const String &s) const
{
    return list::compare(head, s.head) == 0;
}

std::strong_ordering String::operator<=>(const String &s) const
{
    int comparison_result = list::compare(head, s.head);
    if (comparison_result > 0)
    {
        return strong_ordering::greater;
    }
    else if (comparison_result < 0)
    {
        return strong_ordering::less;
    }
    else
    {
        return strong_ordering::equal;
    }
}

String String::operator+(const String &s) const
{
    return String(list::append(head, s.head));
}

String &String::operator+=(const String &s)
{
    if (s.head == nullptr)
    {
        return *this;
    }
    
    list::Node* copied = list::copy(s.head);

    if (head == nullptr)
    {
        head = copied;
    }
    else
    {
        list::Node* tail = list::last(head);
        tail->next = copied;
    }

    return *this;
}

void String::print(std::ostream &out) const
{
    list::print(out, head);
}

void String::read(std::istream &in)
{
    char input[2048];
    in >> input;
    list::free(head);
    head = list::from_string(input);
}

String::~String()
{
    list::free(head);
}

ostream &operator<<(ostream &out, const String &s)
{
    s.print(out);
    return out;
}

istream &operator>>(istream &in, String &s)
{
    s.read(in);
    return in;
}