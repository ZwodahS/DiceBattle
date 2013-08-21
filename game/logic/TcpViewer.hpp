#ifndef _GAME_LOGIC_TCPVIEWER_H_
#define _GAME_LOGIC_TCPVIEWER_H_
#include "BattlePacketLayer.hpp"
#include "../../z_framework/zf_network/Connection.hpp"
#include "../messages/g_messages.hpp"
#include "GameViewer.hpp"
#include <SFML/Network.hpp>
class TcpClient;
class TcpViewer : public GameViewer
{
public:
    TcpViewer(TcpClient& parent, PlayerRole::ePlayerRole role);
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
    TcpClient& _parent;
};
#endif
