//
//  main.cpp
//  socialmedia
//
//  Created by Dang Anh Tu Nguyen on 7/25/19.
//  Copyright © 2019 Dang Anh Tu Nguyen. All rights reserved.
//

#include <iostream>
#include "List.h"
#include "BST.h"
using namespace std;

int main() {
    List<int> a;
    a.insertFirst(1);
    a.printList(cout);
    
    BST<int> b;
    b.insert(3);
    b.inOrderPrint(cout);
    return 0;
}
