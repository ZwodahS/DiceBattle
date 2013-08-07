#include <stdlib.h>
#include <time.h>
#include "game/Game.hpp"
#include "game/logic/Rules.hpp"
int main(int argc , char * argv[])
{
    Rules rules;
    rules.loadFromFile("data/default.rule");
    rules.print();
    srand(time(NULL));
    
    Game g;
    g.run();
}
