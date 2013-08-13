#include "Connection.hpp"

Connection::Connection()
    :name(""), socket(), role(PlayerRole::Observer)
{
}

Connection::~Connection()
{
    socket.disconnect();
}
