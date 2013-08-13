#ifndef _GAME_LOGIC_TCPVIEWER_H_
#define _GAME_LOGIC_TCPVIEWER_H_
#include "../messages/g_messages.hpp"
#include "GameViewer.hpp"
#include <SFML/Network.hpp>
class TcpViewer : public GameViewer
{
public:
    /**
     * Create a viewer that is connected via a Tcp socket
     * It will use this socket as the destination.
     * the value prefix refers to the value that is added to the header to identify the message as a battle message.
     */
    TcpViewer(sf::Int32 prefix, sf::TcpSocket& connection, PlayerRole::ePlayerRole r);
    ~TcpViewer();

    bool isConnected();

    void sendMessage(DB_GameStartMessage message);
    void sendMessage(DB_ActiveTurnMessage message);
    void sendMessage(DB_AskForActionMessage message);
    void sendMessage(DB_AbilityUsedMessage message);
    void sendMessage(DB_DiceRolledResultMessage message);
    void sendMessage(DB_NewDiceMessage message);
    void sendMessage(DB_EndTurnMessage message);
    void sendMessage(DB_EndGameMessage message);
private:
    bool connected;
    sf::Int32 header;
    sf::TcpSocket* connection;
};
#endif
