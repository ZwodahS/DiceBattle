#include <stdlib.h>
#include <time.h>
#include "game/Game.hpp"
int main(int argc , char * argv[])
{
    srand(time(NULL));
    
    Game g;
    g.run();
}
