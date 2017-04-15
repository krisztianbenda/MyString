//
//  mystring.cpp
//  mystring
//
//  Created by Benda Krisztián on 2017. 03. 24..
//  Copyright © 2017. Benda Krisztián. All rights reserved.
//

#include <iostream>
#include <cstring>
#include <map>
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

 BinaryTree MyString::create_BinaryTree(){
     BinaryTree binarytree;
     return binarytree;
}
//unsigned int MyString::key_index = 0;
BinaryTree MyString::database = MyString::create_BinaryTree();

/* Letrehozas uresen*/
MyString::MyString(){
    auto search = MyString::database.find("");
    if(search != MyString::database.end()) {
        search->second->refcount++;
    }
    else {
        stringvalue = new StringValue;
        MyString::database[""] = stringvalue;
    }
   
}

/* Letrehozas karaktertombbol*/
MyString::MyString(const char *exp){
    auto search = MyString::database.find(exp);
    if(search != MyString::database.end()) {
        search->second->refcount++;
        stringvalue = search->second;
    }
    else {
        stringvalue = new StringValue{exp};
        MyString::database[exp] = stringvalue;
    }
}

/* Destruktor*/
MyString::~MyString(){
    /* Csokkentjuk a referenciaszamlalot. Ha elerte a 0-at,
     akkor toroljuk az objektumot (lefoglalt memoriateruletet).
     Egyebkent csak a szamlalot csokkentjuk.
     */
    if (stringvalue != nullptr && --stringvalue->refcount == 0){
        auto it = MyString::database.find(stringvalue->data_);
        if (it != MyString::database.end()){
            delete stringvalue;
            MyString::database.erase(it);
        }
    } else {
        stringvalue = nullptr;
    }
}

/* Copy konstruktor*/
MyString::MyString(const MyString& other) noexcept :stringvalue(other.stringvalue){
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
        if (--stringvalue->refcount == 0){
            delete stringvalue;
        }
        stringvalue = other.stringvalue;
        stringvalue->refcount++;
    }
    return *this;
}

/* Mozgato ertekadas*/
MyString& MyString::operator=(MyString&& other){
    if (this != &other){
        this->~MyString();
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
const char & MyString::operator[](unsigned int idx) const noexcept{
    return stringvalue->data_[idx];
}

// Ha modositanank a [] zarojelek segitsegevel, akkor uj sztringet kell letrehozni
Proxy& MyString::operator[](const unsigned int idx){
    Proxy *proxy = new Proxy{*this, stringvalue->data_[idx], idx};
    return *proxy;
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
inline size_t MyString::length() const noexcept{
    return stringvalue->size_;
}

unsigned int MyString::how_many() const noexcept {
    return stringvalue->refcount;
}

const char* MyString::get_data() const {
    return stringvalue->data_;
}


Proxy::Proxy(MyString &string, char& c, unsigned int idx){
    fromthis = &string;
    idx_ = idx;
}

//Ertekdaskor szetvalasztjuk a modositando es a regebbi
// (map-ben tarolt) sztringeket
void Proxy::operator=(const char& rhs){
    char* text = new char[fromthis->length()+1];
    strcpy(text, fromthis->get_data());
    text[idx_] = rhs;
    *fromthis = text;
    delete [] text;
    delete this;
}

Proxy::operator const char() const {
    return fromthis->get_data()[idx_];
}

Proxy::~Proxy(){
    fromthis = nullptr;
    idx_ = 0;
}

std::ostream& operator<<(std::ostream& os, Proxy& proxy){
    os << char(proxy);
    delete &proxy;
    return os;
}
