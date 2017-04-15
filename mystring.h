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
#include <map>

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

class Proxy;

typedef std::map<std::string, StringValue*> BinaryTree;

class MyString{
private:
    StringValue *stringvalue;
    static BinaryTree database;
    static BinaryTree create_BinaryTree();
public:
    
    MyString();
    
    MyString(const MyString &) noexcept;
    
    MyString(const char *);
    
    MyString(MyString&&) noexcept;
    
    ~MyString();
    
    const char& operator[] (unsigned int) const noexcept;
    Proxy& operator[] (unsigned int);
    
    MyString& operator=(const MyString&);
    
    MyString& operator=(MyString&&);
    
    MyString operator+(const MyString&);
    
    MyString& operator+=(const MyString&);
    
    MyString operator+(const char*);
    
    MyString& operator+=(const char*);
    
    MyString& operator+=(const char &);
    
    size_t length() const noexcept;
    
    unsigned int how_many() const noexcept;
    
    const char * get_data() const;
};

class Proxy{
private:
    MyString* fromthis;
    unsigned int idx_;
//    gyakorlatilag nincs szukseg arra, hogy a konkret
//    karaktert taroljuk. Eleg csak a mystring es egy index,
//    arra, hogy hanyadik karaktert tariljuk.
//    char* char_;
public:
    Proxy() = default;
    Proxy(MyString &, char&, unsigned int);
    void operator=(const char &);
    explicit operator const char() const;
    ~Proxy();
};

std::ostream& operator<<(std::ostream&,  Proxy&);

std::istream& operator>> (std::istream&, MyString&);
std::ostream& operator<<(std::ostream&, const MyString&);

#endif /* mystring_h */
