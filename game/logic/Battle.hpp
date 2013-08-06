#ifndef _GAME_LOGIC_BATTLE_H_
#define _GAME_LOGIC_BATTLE_H_
#include "Unit.hpp"
#include "Ability.hpp"
#include "../constants.hpp"
class GameViewer;
class GameUpdater;
class BattleServer;
class Battle
{
public:
    /**
     * Create a battle object using a battle server.
     * This will make this battle object a client
     */
    Battle(BattleServer& battleServer);
    /**
     * Create a battle object using 2 units.
     * This will create a battle object locally.
     */
    Battle();
    ~Battle();
    void addGameViewer(GameViewer* viewer);
    void addGameUpdater(GameUpdater* updater);

    const bool isServer;
    const PlayerRole::ePlayerRole& currentPlayer;

private:
    Unit& getUnit(PlayerRole::ePlayerRole player);
    /**
     * If this is not a server, then this will store the server that this battle object 
     * can get the updates from.
     * If this is a server, then this value is 0.
     */
    BattleServer* _server;
    /**
     * Stores the list of units.
     */
    Unit _units[2];
    /**
     * Store whose turn it is.
     */
    PlayerRole::ePlayerRole _currentPlayer;
    /**
     * Store the current list of dices
     */
    std::vector<Die> _currentDice; 
    /**
     * Stores the list of viewers
     */
    std::vector<GameViewer*> _viewers;
    /**
     * Stores the list of updaters
     */
    std::vector<GameUpdater*> _updaters;

    ///// Message Sending to viewers /////
    void viewer_sendStartGameMessages(const Unit& player1, const Unit& player2);
    void viewer_sendActiveTurnMessages(const PlayerRole::ePlayerRole& currentPlayer, sf::Int32 burn, sf::Int32 available, sf::Int32 frozen);
    void viewer_sendDiceRolledMessages(std::vector<Die> dice);
    void viewer_sendAbilityUsedMessages(const PlayerRole::ePlayerRole& user, const Ability& abilityUsed, std::vector<sf::Int32> diceUsed);
    void viewer_sendEndTurnMessages();
    void viewer_sendEndGameMessages(PlayerRole::ePlayerRole winner);

    ///// Game Logic code, similar to receiving a update message from battle server ////
    // All the following will send messages to their viewer.
    /**
     * Initialize the game.
     */
    void gamelogic_startGame(const Unit& player1, const Unit& player2);
    /**
     * Set the active player turn
     */
    void gamelogic_setActiveTurn(const PlayerRole::ePlayerRole& currentPlayer, sf::Int32 burn, sf::Int32 available, sf::Int32 frozen);
    /**
     * Set the dice rolled
     */
    void gamelogic_setDiceRolled(std::vector<Die> dices);
    void gamelogic_setDiceRolled(Die& die);
    /**
     * Trigger an ability used.
     */
    void gamelogic_abilityUsed(const PlayerRole::ePlayerRole& user, const Ability& abilityUsed, std::vector<sf::Int32> diceUsed);
    // sub-method of gamelogic_abilityUsed
    void gamelogic_removeDice(std::vector<sf::Int32> dice);
    /**
     * End the turn.
     */
    void gamelogic_endTurn();
    /**
     * End the game.
     */
    void gamelogic_endGame(PlayerRole::ePlayerRole winner);
};
#endif
