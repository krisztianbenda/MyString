//
//  mystring.hpp
//  mystring
//
//  Created by Benda Krisztián on 2017. 03. 24..
//  Copyright © 2017. Benda Krisztián. All rights reserved.
//

#ifndef mystring_h
#define mystring_h

#include <stdio.h>

/* Az osztaly hierarhia ket osztalybol all.
    A MyString osztaly tartalmazza a StringValue osztalyt.
    Megvalositas soran arra torekedtem, hogy minel kevesebb
        "inteligencia" legyen a StringValue osztalyban.
*/
struct StringValue{
public:
    char * data_;
    unsigned int refcount;
    size_t size_;
    
    StringValue();
    explicit StringValue(const char *);
    ~StringValue();
    StringValue(StringValue const &) = delete;
    StringValue & operator=(StringValue const &) = delete;
    StringValue(StringValue&&) noexcept;

};


class MyString{
private:
    StringValue *stringvalue;
public:
    
    MyString();
    
    MyString(const MyString &) noexcept;
    
    MyString(const char *);
    
    MyString(MyString&&) noexcept;
    
    ~MyString();
    
    const char& operator[] (size_t) const noexcept;
    
    MyString& operator=(const MyString&);
    
    MyString& operator=(MyString&&);
    
    MyString operator+(const MyString&);
    
    MyString& operator+=(const MyString&);
    
    MyString operator+(const char*);
    
    MyString& operator+=(const char*);
    
    MyString& operator+=(const char &);
    
    size_t length() const noexcept;
    
};

std::istream& operator>> (std::istream&, MyString&);
std::ostream& operator<<(std::ostream&, const MyString&);

#endif /* mystring_h */
