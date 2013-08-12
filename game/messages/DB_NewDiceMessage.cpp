#include "DB_NewDiceMessage.hpp"

DB_NewDiceMessage::DB_NewDiceMessage(std::vector<Die> d)
    :Message(NewDiceMessage), dice(d)
{
}
