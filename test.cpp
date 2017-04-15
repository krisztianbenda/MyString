//
//  test.cpp
//  mystring
//
//  Created by Benda Krisztián on 2017. 03. 25..
//  Copyright © 2017. Benda Krisztián. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include "mystring.h"
/* Test osztaly Singleton mintaval*/
class Test{
    
/* A singleton miatt egy statikusobjektumor hozunk csak letre*/
public:
    static Test& getInstance(){
        static Test instance;
        return instance;
    }

    /* Letiltjuk a copy konstruktort es az ertekadast*/
    Test(Test const&) = delete;
    void operator=(Test const&) = delete;
    
private:
    /* Ne tudjunk letrehozni peldanyt kivulrol*/
    Test(){}
  
/* Tesztesetek implementalasa*/
public:
    /* Konstruktorok tesztelese*/
    void test1(){
        std::cout << "Test 1..." << std::endl;
        MyString mystring1;
        char exp[] = "Creation Test";
        MyString mystring2(exp);
        std::cout << " Empty string: " << mystring1 << std::endl;
        std::cout << " String with an expression: " << mystring2 << std::endl;
    }

    /* Copy konstruktor es ertekadas tesztelese*/
    void test2(){
        std::cout << "Test 2..." << std::endl;
        char exp[] = "ctor copy assigment",
             exp2[] = "Assigment test";
        MyString mystring1(exp);
        MyString mystring2(mystring1);
        MyString mystring3(exp2);
        
        mystring3 = mystring2;
        std::cout << " The 3 string: " << mystring1 << ", " << mystring2 << ", " << mystring3 << std::endl;
    }
    
    /* Ket sztring osszefuzesenek tesztje operator+
        es operator+= muveletekkel
     */
    void test3(){
        std::cout << "Test 3..." << std::endl;
        char exp[] = "Testing... ";
        MyString a(exp);
        
        char exp2[] = "operator+=";
        MyString b(exp2);
        
        a += b;
        
        MyString c;
        char exp3[] = " and operator+";
        MyString d(exp3);
        c = a + d;
        std::cout << " " << c << std::endl;
    }
    
    /* MyString es karaktertombbok osszefuzesenek tesztje*/
    void test4(){
        std::cout << "Test 4..." << std::endl;
        MyString a("Test: ");
        MyString b;
        b = a + "MyString + char*";
        a += "MyString += char*";
        std::cout << " " << b << std::endl;
        std::cout << " " << a << std::endl;
    }
    
    /* Beolvasas es kiiratas teszt*/
    void test5(){
        std::cout << "Test 5..." << std::endl;
        std::cout << " Type something:" << std::endl;
        MyString mystring;
        std::cin >> mystring;
        std::cout << "  You wrote this: \"";
        std::cout << mystring;
        std::cout << "\" with length: " << mystring.length() << std::endl;
    }
    
    void test6(){
        std::cout << "Test 6..." << std::endl;
        MyString a = "hello", b = a;
        a[0] = 'X';
        std::cout << " " << a << std::endl;
        std::cout << " " << b << std::endl;
    }
    
    void test7(){
        MyString a = "hello vilag";
        MyString b = "hello vilag";
        MyString c = b;
        MyString d(c);
        std::cout << "Test 7..." << std::endl;
        std::cout << " There are " << a.how_many();
        std::cout << " \"" << a <<"\" strings." << std::endl;
    }
    
    void test8(){
        std::cout << "Test 8..." << std::endl;
        MyString a = "helló világ";
        MyString b = a;
        std::cout << " " << b[1] << std::endl;  /* e */
    }
};
