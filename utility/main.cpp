#include <iostream>
#include <string>
#include "IniParser.hpp"


using namespace std;
using namespace tinys::utility;

int main(int argc, char** argv) {

    Value v1;
    v1 = true;
    v1 = 2;
    v1 = 2.1;
    v1 = "kdjfkdjf";
    cout << string(v1);
    return 0;
}
