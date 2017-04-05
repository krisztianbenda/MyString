//
//  main.cpp
//  mystring
//
//  Created by Benda Krisztián on 2017. 03. 24..
//  Copyright © 2017. Benda Krisztián. All rights reserved.
//

#include <iostream>
#include "test.cpp"

int main(int argc, const char * argv[]) {
    Test::getInstance().test1();
    Test::getInstance().test2();
    Test::getInstance().test3();
    Test::getInstance().test4();
    Test::getInstance().test5();
    Test::getInstance().test6();
    return 0;
}
