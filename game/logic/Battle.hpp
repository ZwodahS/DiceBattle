#ifndef _GAME_LOGIC_BATTLE_H_
#define _GAME_LOGIC_BATTLE_H_
#include "Unit.hpp"
#include "Ability.hpp"
#include "Rules.hpp"
#include "../constants.hpp"
#include "../messages/Message.hpp"
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
    enum BattleState
    {
        PreGame, // Before "startGame" is called.
        PreRoll, // When a player's turn has been set and he has not roll any dice yet.
        DiceRolled, // Dice has been rolled. Cannot reroll. Must choose use ability.
        DiceRolledAbilityUsed, // Dice has been rolled and at least one ability has been used. Either choose reroll / done / use ability
        GameEnded,
    };
    void addGameViewer(GameViewer* viewer);
    void addGameUpdater(GameUpdater* updater);

    const bool isServer;
    const PlayerRole::ePlayerRole& currentPlayer;

    /**
     * Check for all updater for message.
     */
    void update();
    void startGame(Rules& rule, std::string p1, std::string p2);
    /**
     * Returns a list of dice matching the id. This will return as many as possible.
     */
    std::vector<Die> findDice(std::vector<sf::Int32> ids);
    Die findDie(sf::Int32 dieId);
    Unit& getUnit(PlayerRole::ePlayerRole player);
private:
    /**
     * process message from server, if this is a client
     */
    void processServerMessage(Message* message);
    /** 
     * process message from any input.
     * only allow command type message.
     */
    void processClientMessage(PlayerRole::ePlayerRole actor, Message* message);

    Rules* _rules;
    BattleState _battleState;
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
    void viewer_sendStartGameMessages(const Rules& rules, const Unit& player1, const Unit& player2);
    void viewer_sendActiveTurnMessages(const PlayerRole::ePlayerRole& currentPlayer, sf::Int32 burn, sf::Int32 available, sf::Int32 frozen, std::vector<Die> dice);
    void viewer_sendDiceRolledMessages(std::vector<Die> dice);
    void viewer_sendAbilityUsedMessages(const PlayerRole::ePlayerRole& user, const Ability& abilityUsed, std::vector<sf::Int32> diceUsed);
    void viewer_sendEndTurnMessages();
    void viewer_sendEndGameMessages(PlayerRole::ePlayerRole winner);

    ///// Game Logic code, similar to receiving a update message from battle server ////
    // All the following will send messages to their viewer.
    /**
     * Initialize the game.
     */
    void gamelogic_startGame(Rules& rules, const Unit& player1, const Unit& player2);
    /**
     * Set the active player turn
     */
    void gamelogic_setActiveTurn(const PlayerRole::ePlayerRole& currentPlayer, sf::Int32 burn, sf::Int32 available, sf::Int32 frozen, std::vector<Die> dice);
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

    //// The following are for receiving commands from gameupdater ////

    bool gamelogic_receivedDoneCommand();
    bool gamelogic_receivedRollCommand(const std::vector<sf::Int32>& diceId);
    bool gamelogic_receivedUseAbilityCommand(const Ability& abilityUsed, const std::vector<sf::Int32>& diceUsed);
};
#endif
