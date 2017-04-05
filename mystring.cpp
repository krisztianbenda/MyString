//
//  mystring.cpp
//  mystring
//
//  Created by Benda Krisztián on 2017. 03. 24..
//  Copyright © 2017. Benda Krisztián. All rights reserved.
//

#include <iostream>
#include <cstring>
#include "mystring.h"

    
StringValue::StringValue(){
    size_ = 0;
    data_ = new char[size_ + 1];
    data_[0] = '\0';
    refcount = 1;
}
    
StringValue::StringValue(const char * init){
    size_ = strlen(init);
    data_ = new char[size_ + 1];
    strcpy(data_, init);
    refcount = 1;
}
    
StringValue::~StringValue(){
    size_ = 0;
    refcount = 0;
    delete [] data_;
}

StringValue::StringValue(StringValue&& other) noexcept{
    size_ = other.size_;
    other.size_ = 0;
    data_ = other.data_;
    other.data_ = nullptr;
}

/* MyString osztaly implementlasa*/

/* Letrehozas uresen*/
MyString::MyString(){
    stringvalue = new StringValue;
}

/* Letrehozas karaktertombbol*/
MyString::MyString(const char *exp){
    stringvalue = new StringValue{exp};
}

/* Destruktor*/
MyString::~MyString(){
    /* Csokkentjuk a referenciaszamlalot. Ha elerte a 0-at,
     akkor toroljuk az objektumot (lefoglalt memoriateruletet).
     Egyebkent csak a szamlalot csokkentjuk.
     */
    if (stringvalue != nullptr && --stringvalue->refcount == 0)
        delete stringvalue;
}

/* Copy konstruktor*/
MyString::MyString(const MyString& other) noexcept :stringvalue(other.stringvalue) {
    /* Az uj objektum megkapja a masik ertekere mutato pointert,
        valamint a referenciaszamlalot noveljuk egyel
     */
    stringvalue->refcount++;
}

/* Ertekadas*/
MyString& MyString::operator=(const MyString& other){
    if (this != &other){
        /* Ha a referenciak szama eleri a 0-t,
            akkor mar nincs szukseg a stringvalue-ra. Toroloni lehet.
         */
        if (--stringvalue->refcount == 0)
            delete stringvalue;
        stringvalue = other.stringvalue;
        stringvalue->refcount++;
    }
    return *this;
}

/* Mozgato ertekadas*/
MyString& MyString::operator=(MyString&& other){
    if (this != &other){
        if (--stringvalue->refcount == 0)
            delete stringvalue;
        stringvalue = std::move(other.stringvalue);
        other.stringvalue = nullptr;
    }
    return *this;
}

/* Mozgato konstruktor*/
MyString::MyString(MyString&& other) noexcept :stringvalue{other.stringvalue}{
    other.stringvalue = nullptr;
}

/* Operator[] a konnyebb kezelhetosegert*/
const char & MyString::operator[](const unsigned int idx) const noexcept{
    return stringvalue->data_[idx];
}

// Ha modositanank a [] zarojelek segitsegevel, akkor uj sztringet kell letrehozni
char& MyString::operator[](const unsigned int idx){
    if (stringvalue->refcount > 1){
        auto *newStr = new char[stringvalue->size_ + 1];
        newStr[0] = '\0';
        strcat(newStr, this->stringvalue->data_);
        MyString tmp{newStr};
        *this = tmp;
        delete [] newStr;
    }
    return stringvalue->data_[idx];
}

/* Ket MyString osszeuzese eseten a referenciszamlalok nem valtoznak,
    mivel csak egy uj objektum keletkezik. Regebbi, nem szabadul fel.
*/
MyString MyString::operator+(const MyString & rhs){
    MyString ret{*this};
    return std::move(ret += rhs);
}

/* A megirt operator+-t felhasznalva az konnyu dolgunk van.
    A felulirt balertekre kell figyelni, hogy csokkentsuk 
    a referencia szamlalot.
*/
MyString& MyString::operator+=(const MyString& rhs){
    auto new_len = stringvalue->size_ + rhs.stringvalue->size_;
    auto *newStr = new char[new_len + 1];
    //  A lezaro nullara valo tekintettel eggyel nagyobb teruletet foglalunk
    newStr[0] = '\0';
    strcat(newStr, this->stringvalue->data_);
    strcat(newStr, rhs.stringvalue->data_);
    MyString tmp{newStr};
    *this = tmp;
    delete [] newStr;
    return *this;
}

/* A karaktertombbol egy ujabb MyStringet hozunk letre,
    majd ezt hasznaljuk az osszeadasban.
 */
MyString MyString::operator+(const char * text){
    MyString other{text};
    return *this + other;
}

/* Hasonloan az operator+(const char *) fuggvenyhez*/
MyString& MyString::operator+=(const char* text){
    MyString other{text};
    *this += other;
    return *this;
}

/* Beolvasas implementalasa.
    A mar megirt operator= elvegzi a referenciszamlalo csokkenteset
    szukseg eseten
*/
std::istream& operator>>(std::istream& is, MyString& target){
    char c[1024];
    is.getline(c, 1024, '\n');
    MyString mystring{c};
    target = mystring;
    return is;
}

/* Kiiras*/
std::ostream& operator<<(std::ostream& os, const MyString& mystring)
{
    for (auto i = 0; i < mystring.length(); ++i)
        os << mystring[i];
    return os;
}

/* Hossz lekerdezese*/
size_t MyString::length() const noexcept{
    return stringvalue->size_;
}
