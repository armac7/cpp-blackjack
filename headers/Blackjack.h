#include <iostream>
#include <ctime>
#include <chrono>
#include <thread>
#include "Card.h"
#include "Deck.h"
#include "Hand.h"
#include "Bet.h"

#ifndef BLACKHACK_H
#define BLACKJACK_H

class Blackjack
{
    public:
        Blackjack() 
        {
            handPlayer.setID(0);
            handDealer.setID(1);
            betPlayer.initBet(moneyStart);
            betDealer.initBet(moneyStart);
            winsPlayer = 0;
            winsDealer = 0;
            moneyPot = 0;
            deck.initDeck();
            cout << "\x1B[2J\x1B[H";
            cout << "==================================================" << endl;
            cout << "|| Welcome to armac7's Black Jack Extraveganza! ||" << endl;
            cout << "==================================================" << endl;
        }
        void playGame() 
        {
            using namespace std::this_thread;
            using namespace std::chrono;
            bool gameOver = false;
            bool roundEnd = false;
            int playerChoice = 0;
            do 
            {
                // Setting up deck and intiial draw
                deck.initDeck();
                betPlayer.setStartingCash(betPlayer.getMoney());
                betDealer.setStartingCash(betDealer.getMoney());
                hit(handPlayer);
                hit(handDealer);
                int currTurn = 1;
                // Intial Draw Print Statement
                cout << "[------------------INITIAL DRAW------------------]" << endl;
                cout << "=PLAYER HAND============================" << endl;
                cout << handPlayer << endl;
                cout << "========================================" << endl << endl;
                cout << "=DEALER HAND============================" << endl;
                cout << handDealer << endl;
                cout << "========================================" << endl;
                cout << "[------------------------------------------------]" << endl << endl;

                cout << "You paid $50 to join." << endl;
                cout << "Dealer paid $50 to join." << endl;
                betPlayer.addBet(50); betDealer.addBet(50);
                moneyPot = (betPlayer + betDealer);
                
                // pauses for 5 seconds then erases console.
                cout << "Game Starting..." << endl;
                sleep_for(5s);
                cout << "\x1B[2J\x1B[H";
                do 
                {
                    cout << "==================================================" << endl;
                    cout << "|| Welcome to armac7's Black Jack Extraveganza! ||" << endl;
                    cout << "==================================================" << endl;
                    cout << "[---------------------TURN " << currTurn << "---------------------]" << endl;
                    cout << "YOUR FINANCIALS: " << endl;
                    cout << betPlayer << endl;
                    cout << "DEALER'S FINANCIALS: " << endl;
                    cout << betDealer << endl; 
                    if (betPlayer < betDealer && !handPlayer.getStand() && !betPlayer.areBroke()) 
                    {
                        int userChoice = 0;
                        cout << endl;
                        cout << "Your Hands Sum:        " << handPlayer.getSum() << endl;
                        cout << "Dealers Current Sum:   " << handDealer.getSum() << endl;
                        do 
                        {
                            cout << "You've been raised! Do you want to match or stand (1 or 2)? ";
                            cin >> userChoice;
                        } while(userChoice < 0 && userChoice > 3);
                        if (userChoice == 1) 
                        {
                            betPlayer.matchBet(betDealer);
                            if (betPlayer.areBroke()) 
                            {
                                cout << "Out of money to match, going all in!" << endl;
                                handPlayer.setStand(true);
                            } 
                        } 
                        else {handPlayer.setStand(true);}
                        moneyPot = (betPlayer + betDealer);
                        cout << endl;
                    }
                    cout << "Current Money Pot:       $" << moneyPot << endl;
                    cout << endl;
                    bool printedPlayerHand = false;
                    // if the player isn't standing, it is his/her turn.
                    if (!handPlayer.getStand()) 
                    {
                        bool valid = false;
                        // get user choice and validate
                        do 
                        {
                            printedPlayerHand = false;
                            if (handPlayer.getStand()) cout << "[STANDING]" << endl;
                            cout << "=PLAYER HAND============================" << endl;
                            cout << handPlayer << endl;
                            cout << "========================================" << endl << endl;
                            if (handDealer.getStand()) cout << "[STANDING]" << endl;
                            cout << "=DEALER HAND============================" << endl;
                            cout << handDealer << endl;
                            cout << "========================================" << endl << endl;
                            printedPlayerHand = true;
                            playerChoice = 0;
                            cout << "Enter 1 to Hit, 2 to Double, 3 to Raise, 4 to Stand: ";
                            cin >> playerChoice;
                            if (playerChoice > 0 && playerChoice < 5) {valid = true; break;}
                            else {valid = false;}
                        } while(!valid);
                        // if player choice == 1, proceed with turn.
                        // Hit, print hand, check win status.
                        if (playerChoice == 1) 
                        { 
                            hit(handPlayer);
                            // cout << "=PLAYER HAND============================" << endl;
                            // cout << handPlayer << endl;
                            // cout << "========================================" << endl << endl;
                            cout << "You chose to HIT!" << endl;
                        }
                        //DOUBLE
                        else if (playerChoice == 2) 
                        {
                            if (!handDealer.getStand() && !betDealer.areBroke() && !betPlayer.areBroke()) 
                            {
                                betPlayer.doubleBet();
                                moneyPot = (betPlayer + betDealer);
                                hit(handPlayer);
                                handPlayer.setStand(true);
                                cout << "You chose to DOUBLE then STAND!" << endl;
                            }
                            else 
                            {
                                cout << "Can't DOUBLE! HITTING instead!" << endl;
                                hit(handPlayer);
                            }
                        }
                        // RAISE
                        else if (playerChoice == 3) 
                        {
                            if (!handDealer.getStand() && !betDealer.areBroke() && !betPlayer.areBroke()) 
                            {
                                int bet = 0;
                                do 
                                {
                                    cout << "Enter the amount to raise by: $";
                                    cin >> bet;
                                } while (bet < 0 && bet > betPlayer.getMoney());
                                betPlayer.addBet(bet);
                                moneyPot = (betPlayer + betDealer);
                                hit(handPlayer);
                                cout << "You chose to RAISE then HIT!" << endl;
                            }
                            else 
                            {
                                cout << "Can't RAISE! HITTING instead!" << endl;
                                hit(handPlayer);
                            }
                        }
                        // else, stand.
                        else
                        {
                            handPlayer.setStand(true);
                            cout << "You chose to STAND." << endl;
                        }

                        if (!handPlayer.getStand()) 
                        {
                            handPlayer.reportStatus();
                            if (handPlayer.getWinStatus() == 0) 
                            { 
                                cout << "You hit Blackjack!" << endl;
                                handPlayer.setStand(true);
                            }
                            else if (handPlayer.getWinStatus() == 1)
                            {
                                cout << "You bust!" << endl;
                                handPlayer.setStand(true);
                            }
                        }
                    }

                    /////////////////////////////// DEALERS CODE ///////////////////////////////
                    // if round is still going but dealer is standing, print dealers sum.
                    if (!handPlayer.getStand() && handDealer.getStand()) {cout << "The Dealers Hands Sum: " << handDealer.getSum() << endl;}
                    // If the player raised the dealer, see if dealer wants to match (and match if so).
                    if (betPlayer > betDealer && !handDealer.getStand() && !betDealer.areBroke()) 
                    {
                        int probabilityStand;

                        if (handDealer.getSum() >= 18) {probabilityStand = 80;}
                        else {probabilityStand = 10;}

                        int chance = rand() % 100 + 1;
                        if (chance <= probabilityStand) 
                        {
                            cout << "Dealer chose to STAND instead of MATCH!" << endl;
                            handDealer.setStand(true);
                        } 
                        else 
                        {
                            cout << "Dealer chose to MATCH your RAISE!" << endl;
                            betDealer.matchBet(betPlayer);
                            moneyPot = (betPlayer + betDealer);
                        }
                    } 
                    // If the dealer isn't standing, it's his turn.
                    if (!handDealer.getStand()) 
                    {
                        srand(time(0));

                        if (handPlayer.getStand() && printedPlayerHand == false && !handDealer.getStand()) 
                        {
                            if (handPlayer.getStand()) cout << "[STANDING]" << endl;
                            cout << "=PLAYER HAND============================" << endl;
                            cout << handPlayer << endl;
                            cout << "========================================" << endl << endl;
                            if (handDealer.getStand()) cout << "[STANDING]" << endl;
                            cout << "=DEALER HAND============================" << endl;
                            cout << handDealer << endl;
                            cout << "========================================" << endl << endl;
                        }

                        // Gets probability to stand. If sum of cards is >= to 15, has an 80% chance to stand.
                        int probabilityStand;
                        int probabilityRaise;
                        int probabilityDouble;

                        // 80% to stand if sum is 18 or over.
                        if (handDealer.getSum() >= 18) {probabilityStand = 80;}
                        else {probabilityStand = 10;}

                        int chance = rand() % 100 + 1;
                        //cout << "CHANCE: " << chance << endl; // debug
                        // if the chance is less than the probability to stand, then stand; else,
                        if (chance <= probabilityStand) 
                        {
                            handDealer.setStand(true);
                            cout << "The dealer chose to stand." << endl;    
                        }
                        // Hit, print hand, check win status
                        else 
                        {
                            // probability to raise
                            if (handDealer.getSum() >= 10 && handDealer.getSum() <= 15) {probabilityRaise = 50;}
                            else {probabilityRaise = 30;}

                            // probability to double
                            if (handDealer.getSum() >= 9 && handDealer.getSum() <= 12) {probabilityDouble = 40;}
                            else {probabilityDouble = 10;}

                            chance = rand() % 100 + 1;
                            // probability is referenced with chance, then further tested with checkRaise.
                            // The check variables gets a value between 0 and each respective probability
                            // Whichever is higher, as long a the probability is greater than chance, is the one to be acted upon.
                            int checkRaise = rand() % probabilityRaise;
                            int checkDouble = rand() % probabilityDouble;

                            // DEBUG STATEMENTS //
                            // cout << "\tCHANCE: " << chance << endl;
                            // cout << "\tprobabilityRaise: " << probabilityRaise << endl;
                            // cout << "\tprobabilityDouble" << probabilityDouble << endl;
                            // cout << "\tcheckRaise: " << checkRaise << endl;
                            // cout << "\tcheckDouble: " << checkDouble << endl;

                            // RAISING
                            if (chance <= probabilityRaise && checkRaise > checkDouble && !handPlayer.getStand() && !betDealer.areBroke() && !betPlayer.areBroke())
                            {
                                // gets the amount to be bet
                                int bet = 0;
                                int maxBet = 0;
                                int amountRaiseChance = rand() % 100 + 1;
                                // 1% chance
                                if (amountRaiseChance == 1) 
                                {
                                    bet = betDealer.getMoney();
                                    cout << "Dealer went all in!" << endl;
                                }
                                // 10% chance
                                else if (amountRaiseChance <= 11) 
                                {
                                    maxBet = betDealer.getMoney() * .60;
                                    bet = rand() % maxBet;
                                }
                                // 30% chance
                                else if (amountRaiseChance <= 42) 
                                {   
                                    maxBet = betDealer.getMoney() * .30;
                                    bet = rand() % maxBet;
                                }
                                // 60% chance (ish)
                                else 
                                {
                                    maxBet = betDealer.getMoney() * .10;
                                    bet = rand() & maxBet;
                                }
                                betDealer.addBet(bet);
                                moneyPot = (betPlayer + betDealer);
                                hit(handDealer);
                                cout << "Dealer chose to RAISE by $" << bet << " then HIT!" << endl;
                            }
                            // DOUBLING
                            else if (chance <= probabilityDouble && checkDouble > checkRaise && !handPlayer.getStand() && !betDealer.areBroke() && !betPlayer.areBroke())  
                            {
                                betDealer.doubleBet();
                                moneyPot = (betPlayer + betDealer);
                                hit(handDealer);
                                handDealer.setStand(true);
                                cout << "Dealer chose to DOUBLE then STAND!" << endl;
                            }
                            // HITTING
                            else 
                            {
                                cout << "Dealer chose to HIT!" << endl;
                                hit(handDealer);
                            }
                            // cout << "=DEALER HAND============================" << endl;
                            // cout << handDealer << endl;
                            // cout << "========================================" << endl << endl;
                            handDealer.reportStatus();
                            if (handDealer.getWinStatus() == 0) 
                            {
                                cout << "The dealer hit BLACKJACK!" << endl;
                                handDealer.setStand(true);
                            }
                            else if (handDealer.getWinStatus() == 1)
                            {
                                cout << "The dealer BUST!" << endl;
                                handDealer.setStand(true);
                            }
                        }
                    }
                    cout << "[------------------------------------------------]" << endl << endl;
                    currTurn++;
                    
                    // pause and erase
                    if (handPlayer.getStand() && handDealer.getStand()) {cout << "Determining Winner..." << endl;}
                    else {cout << "Dealing..." << endl;}
                    sleep_for(3s);
                    cout << "\x1B[2J\x1B[H";

                    if (handPlayer.getStand() && handDealer.getStand()) 
                    {
                        handPlayer.reportStatus();
                        handDealer.reportStatus();
                        bool bustPlayer = handPlayer.getWinStatus() == 1;
                        bool bustDealer = handDealer.getWinStatus() == 1;
                        bool bustNeither = (handPlayer.getWinStatus() != 1) && (handDealer.getWinStatus() != 1);
                        bool blackjackPlayer = handPlayer.getWinStatus() == 0;
                        bool blackjackDealer = handDealer.getWinStatus() == 0;
                        cout << endl << "=GAME RESULTS============================" << endl;
                        if (blackjackDealer && blackjackPlayer) 
                        {
                            int split = moneyPot / 2;
                            betDealer.addMoney(split);
                            betPlayer.addMoney(split);
                            cout << "You tied with the Dealer with Blackjack!" << endl;
                        }
                        else if (bustPlayer && bustDealer) 
                        {
                            cout << "You and the Dealer both bust!" << endl;
                        }
                        else if (bustNeither && handPlayer > handDealer) 
                        {
                            betPlayer.addMoney(moneyPot);
                            cout << "You beat the Dealer!" << endl;
                            winsPlayer++;
                        }
                        else if (bustNeither && handPlayer < handDealer) 
                        {
                            betDealer.addMoney(moneyPot);
                            cout << "You lost to the Dealer!" << endl;
                            winsDealer++;
                        }
                        else if (bustNeither && handPlayer == handDealer) 
                        {
                            int split = moneyPot / 2;
                            betDealer.addMoney(split);
                            betPlayer.addMoney(split);
                            cout << "You drew with the Dealer!" << endl;
                        }
                        else if (bustDealer && !bustPlayer) 
                        {
                            betPlayer.addMoney(moneyPot);
                            cout << "You beat the Dealer!" << endl;
                            winsPlayer++;
                        }
                        else if (!bustDealer && bustPlayer) 
                        {
                            betDealer.addMoney(moneyPot);
                            cout << "You lost to the Dealer!" << endl;
                            winsDealer++;
                        }
                        else 
                        {
                            cout << "Unfound game win/loss condition." << endl;
                        }
                        cout << endl;
                        cout << "[-YOUR RESULTS--------------------]" << endl;
                        cout << "HAND SUM:                " << handPlayer.getSum() << endl;
                        cout << "MONEY:                  $" << betPlayer.getMoney() << endl;
                        cout << "MATCH EARNINGS:         $" << betPlayer.getMoney() - betPlayer.getStartingCash() << endl;
                        cout << endl;
                        cout << "[-DEALER'S RESULTS----------------]" << endl;
                        cout << "HAND SUM:                " << handDealer.getSum() << endl;
                        cout << "MONEY:                  $" << betDealer.getMoney() << endl;
                        cout << "=========================================" << endl << endl;
                        roundEnd = true;
                    }
                } while (!roundEnd);

                bool bankrupt = false;
                bool valid = false;
                // Deciding what to do after round is over
                do 
                {
                    // if player or dealer is bankrupt, game over
                    if (betDealer.areBroke()) 
                    {
                        cout << "Dealer lost! He went bankrupt!" << endl;
                        playerChoice = 2;
                        valid = true;
                    }
                    else if (betPlayer.areBroke()) 
                    {
                        cout << "You lose! You went bankrupt!" << endl;
                        playerChoice = 2;
                        valid = true;
                    }
                    // else let player choose
                    else {
                        playerChoice = 0;
                        cout << "Play Again? (1 for Yes, 2 for No): ";
                        cin >> playerChoice;
                        if (playerChoice > 0 && playerChoice < 3) valid = true;
                    }
                } while(!valid);
                if (playerChoice == 2) 
                {
                    cout << endl;
                    cout << "Thanks for playing!" << endl;
                    cout << "==============================" << endl;
                    cout << "TOTAL EARNINGS: $" << betPlayer.getMoney() - moneyStart << endl;
                    cout << "WINS:            " << winsPlayer << endl;
                    cout << "LOSSES:          " << winsDealer << endl;
                    gameOver = true;
                }
                else 
                {
                    for (int i = 0; i < 50; i++) {cout << endl;}
                    handPlayer.resetHand();
                    handDealer.resetHand();
                    betPlayer.resetBet();
                    betDealer.resetBet();
                    deck.initDeck(); 
                    moneyPot = 0;                
                    roundEnd = false;
                    gameOver = false;
                }
            } while (!gameOver);
        }
        void hit(Hand &hand) 
        {
            Card drawn = deck.drawCard();
            hand.addCard(drawn, hand.getID());
        }
    private:
        Hand handPlayer;
        Hand handDealer;
        const int moneyStart = 500;
        Bet betPlayer;
        Bet betDealer;
        // int moneyPlayer;
        // int moneyDealer;
        int moneyPot;
        // int betPlayer;
        // int betDealer;
        /**
         * 0 = Blackjack
         * 1 = Bust
        */
        // int winStatusPlayer;
        // int winStatusDealer;
        int winsPlayer;
        int winsDealer;
        Deck deck;
};

#endif