#include <iostream>
#include <ctime>
#include "Card.h"
#include "Deck.h"
#include "Hand.h"

#ifndef BLACKHACK_H
#define BLACKJACK_H

class Blackjack
{
    public:
        Blackjack() 
        {
            handPlayer.setID(0);
            handDealer.setID(1);
            winStatusPlayer = 0;
            winStatusDealer = 0;
            winsPlayer = 0;
            winsDealer = 0;
            deck.initDeck();
            cout << "==================================================" << endl;
            cout << "|| Welcome to armac7's Black Jack Extraveganza! ||" << endl;
            cout << "==================================================" << endl;
        }
        void playGame() 
        {
            bool gameOver = false;
            bool roundEnd = false;
            int playerChoice = 0;
            do 
            {
                deck.initDeck();
                hit(handPlayer);
                hit(handDealer);
                int currTurn = 1;
                cout << "[--------------------INITIAL DRAW--------------------]" << endl;
                cout << "=PLAYER HAND============================" << endl;
                cout << handPlayer << endl;
                cout << "========================================" << endl << endl;
                cout << "=DEALER HAND============================" << endl;
                cout << handDealer << endl;
                cout << "========================================" << endl;
                cout << "[----------------------------------------------------]" << endl << endl;
                //for (int i = 0; i < 10; i++) {cout << endl;}
                do 
                {
                    cout << "[-----------------------TURN " << currTurn << "-----------------------]" << endl;
                    if (handPlayer.getStand() && !handDealer.getStand()) {cout << "Your Hands Sum: " << handPlayer.getSum() << endl;}
                    // if the player isn't standing, it is his/her turn.
                    if (!handPlayer.getStand()) 
                    {
                        bool valid = false;
                        // get user choice and validate
                        do 
                        {
                            playerChoice = 0;
                            cout << "Enter 1 for Hit or 2 for Stand: ";
                            cin >> playerChoice;
                            if (playerChoice > 0 && playerChoice < 3) {valid = true; break;}
                            else {valid = false;}
                        } while(!valid);
                        // if player choice == 1, proceed with turn.
                        // Hit, print hand, check win status.
                        if (playerChoice == 1) 
                        { 
                            hit(handPlayer);
                            cout << "=PLAYER HAND============================" << endl;
                            cout << handPlayer << endl;
                            cout << "========================================" << endl << endl;
                            winStatusPlayer = reportStatus(handPlayer);
                            if (winStatusPlayer == 0) 
                            { 
                                cout << "You hit Blackjack!" << endl;
                                handPlayer.setStand(true);
                            }
                            else if (winStatusPlayer == 1)
                            {
                                cout << "You bust!" << endl;
                                handPlayer.setStand(true);
                            }
                        }
                        // else, stand.
                        else 
                        {
                            handPlayer.setStand(true);
                            cout << "You chose to stand." << endl;
                        }
                    }

                    if (!handPlayer.getStand() && handDealer.getStand()) {cout << "The Dealers Hands Sum: " << handDealer.getSum() << endl;}
                    // if the dealer is not standing, it is his turn.
                    if (!handDealer.getStand()) 
                    {
                        srand(time(0));

                        // Gets probability to stand. If sum of cards is >= to 15, has an 80% chance to stand.
                        int probabilityStand;
                        if (handDealer.getSum() >= 15) {probabilityStand = 80;}
                        else {probabilityStand = 20;}

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
                            hit(handDealer);
                            cout << "=DEALER HAND============================" << endl;
                            cout << handDealer << endl;
                            cout << "========================================" << endl << endl;
                            winStatusDealer = reportStatus(handDealer);
                            if (winStatusDealer == 0) 
                            {
                                cout << "The dealer hit Blackjack!" << endl;
                                handDealer.setStand(true);
                            }
                            else if (winStatusDealer == 1)
                            {
                                cout << "The dealer bust!" << endl;
                                handDealer.setStand(true);
                            }
                        }
                    }
                    cout << "[----------------------------------------------------]" << endl << endl;
                    currTurn++;

                    if (handPlayer.getStand() && handDealer.getStand()) 
                    {
                        bool bustPlayer = winStatusPlayer == 1;
                        bool bustDealer = winStatusDealer == 1;
                        bool bustNeither = (winStatusPlayer != 1) && (winStatusDealer != 1);
                        bool blackjackPlayer = winStatusPlayer == 0;
                        bool blackjackDealer = winStatusDealer == 0;
                        cout << endl << "=GAME RESULTS============================" << endl;
                        if (blackjackDealer && blackjackPlayer) 
                        {
                            cout << "You tied with the Dealer with Blackjack!" << endl;
                        }
                        else if (bustPlayer && bustDealer) 
                        {
                            cout << "You and the Dealer both bust!" << endl;
                        }
                        else if (bustNeither && handPlayer > handDealer) 
                        {
                            cout << "You beat the Dealer!" << endl;
                            winsPlayer++;
                        }
                        else if (bustNeither && handPlayer < handDealer) 
                        {
                            cout << "You lost to the Dealer!" << endl;
                            winsDealer++;
                        }
                        else if (bustNeither && handPlayer == handDealer) 
                        {
                            cout << "You drew with the Dealer!" << endl;
                        }
                        else if (bustDealer && !bustPlayer) 
                        {
                            cout << "You beat the Dealer!" << endl;
                            winsPlayer++;
                        }
                        else if (!bustDealer && bustPlayer) 
                        {
                            cout << "You lost to the Dealer!" << endl;
                            winsDealer++;
                        }
                        else 
                        {
                            cout << "Unfound game win/loss condition." << endl;
                        }
                        cout << "Player Hand Sum: " << to_string(handPlayer.getSum()) << endl;
                        cout << "Dealer Hand Sum: " << to_string(handDealer.getSum()) << endl;
                        cout << "=========================================" << endl << endl;
                        roundEnd = true;
                    }
                } while (!roundEnd);
                bool valid = false;
                do 
                {
                    playerChoice = 0;
                    cout << "Play Again? (1 for Yes, 2 for No): ";
                    cin >> playerChoice;
                    if (playerChoice > 0 && playerChoice < 3) valid = true;
                } while(!valid);
                if (playerChoice == 2) 
                {
                    cout << "Thanks for playing!" << endl;
                    cout << "Player Wins: " << winsPlayer << endl;
                    cout << "Dealer Wins: " << winsDealer << endl;
                    gameOver = true;
                }
                else 
                {
                    for (int i = 0; i < 50; i++) {cout << endl;}
                    handPlayer.resetHand();
                    handDealer.resetHand();
                    deck.initDeck();
                    
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
        int reportStatus(const Hand &hand) 
        {
            /**
             * Win Status
             * 0 - Blackjack
             * 1 - Bus (Bust)
             * -1 - Continue
            */
            if (hand == 21) return 0;
            if (hand > 21) return 1;
            return -1;
        }
    private:
        Hand handPlayer;
        Hand handDealer;
        /**
         * 0 = Blackjack
         * 1 = Bust
        */
        int winStatusPlayer;
        int winStatusDealer;
        int winsPlayer;
        int winsDealer;
        Deck deck;
};

#endif