#include <iostream>
#include "string"
#include "src/Types/Integer.h"
#include "src/DataStructures/LinkedList.h"
#include "src/Types/GenericType.h"
#include "src/Types/Char.h"
#include "src/MemoryManagement/MemoryManager.h"
#include "src/DataStructures/ExpressionTree.h"
#include "src/Types/Float.h"

using namespace std;

int main() {
    //creo el espacio de memoria
    auto *mem = new MemoryManager(1000);
    //creo dos instancias de tipos de dato diferentes
    auto *var = new Integer("VAR", "2000");
    auto *var2 = new Float("VAR_2", "2.4");
    auto *var3 = new Char("VAR_3", "c");

    //agrego los elementos a el espacio de memoria
    mem->addElementDigits<int>(var);
    mem->addElementDigits<float>(var2);
    mem->addElementChar(var3);
    //print del mapa de memoria :)
    mem->show();
    return 0;
}
