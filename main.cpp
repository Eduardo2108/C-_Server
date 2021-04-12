#include <iostream>
#include "string"
#include "src/Types/Integer.h"
#include "src/DataStructures/LinkedList.h"
#include "src/Types/GenericType.h"
#include "src/Types/Char.h"

using namespace std;

int main() {

    Integer *integer = new Integer("var", "134");
    Char *character = new Char("char", "c");

    auto *list = new LinkedList<GenericType>();
    list->append(*integer);
    list->append(*character);
    list->show();

    return 0;
}
