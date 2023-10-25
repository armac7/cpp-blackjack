#include <iostream>
#include <ctime>
#include "Card.h"
using namespace std;

#ifndef HAND_H
#define HAND_H

class Hand 
{
    public:
        Hand() 
        {
            maxCards = 11;
            hand = new Card[maxCards];
            currCards = 0;
            stand = false;
            sum = 0;
        }
        void setID(int playerID) { this->playerID = playerID; }
        int getID() {return playerID;}
        void addCard(Card &card, int playerNumber) 
        {
            /**
             * @brief [Adds a card to the hand. Changes hand allocation if needed.]
             * @param card [An instance of Card to add to the class. If Ace, the player can choose for it to be a 1 or an 11.]
             * @param playerNumber [0 for player, 1 for Dealer.]
             * @return [No return, void.]
            */
           // Lets the player decide if an ace is worth 1 or 11.
           if(playerNumber == 0) 
           {
                if (card.getFace() == "Ace") 
                {
                    bool valid = false;
                    int userChoice = 0;
                    do {
                        cout << "Drew an Ace: Do you want it to be a 1 or an 11? "; 
                        cin >> userChoice;
                        cout << userChoice << endl;

                        if (userChoice == 1 || userChoice == 11) {valid = true;}
                        else {valid = false;}
                    } while (!valid);
                    card.setNumber(userChoice);
                }
           }

           // Lets AI decide if an ace is worth 1 or 11.
           if (playerNumber == 1) 
           {
                if (card.getFace() == "Ace") 
                {
                    if(sum <= 10) {card.setNumber(11);}
                }
           }
            // If the hand has reached max capacity, double max capacity and reallocate.
            if (currCards == maxCards) 
            {
                maxCards *= 2;
                Card *temp = new Card[maxCards];
                for (int i = 0; i < currCards; i++) 
                {
                    temp[i] = hand[i];
                }
                delete[] hand;
                hand = temp;
                // potential dangling pointer?
                cout << "New Size: " << maxCards << endl; // debug
            }
            else 
            {
                hand[currCards] = card;
                currCards++;
                sum = sum + card;
            }
        }
        void resetHand() 
        {
            delete[] hand;
            maxCards = 11;
            hand = new Card[maxCards];
            currCards = 0;
            stand = false;
            sum = 0;
        }
        int getSum() {return sum;} const
        int getCurrCards() {return currCards;} const
        int getMaxCards() {return maxCards;} const
        bool getStand() {return stand;} const
        void setStand(bool stand) {this->stand = stand;}
        bool operator <(const Hand &hand) const {return sum < hand.sum;}
        bool operator >(const Hand &hand) const {return sum > hand.sum;}
        bool operator ==(const Hand &hand) const {return sum == hand.sum;}
        friend bool operator <(const Hand &hand, int intToCheck) {return hand.sum < intToCheck;}
        friend bool operator >(const Hand &hand, int intToCheck) {return hand.sum > intToCheck;}
        friend bool operator ==(const Hand &hand, int intToCheck) {return hand.sum == intToCheck;}
        friend ostream &operator <<(ostream &os, const Hand &hand) 
        {
            /**
             * @brief [Used to print out the hand.]
             * @param os [ostream variable.]
             * @param hand [Instance of Hand class.]
             * @return [Returns an ostream variable (cout, essentially).]
            */
            for (int i = 0; i < hand.currCards; i++) 
            {
                os << hand.hand[i] << endl;
            }
            os << "Sum of Hand: " << hand.sum;
            return os;
        }
    private:
        Card *hand;
        bool stand;
        /**
         * 0 for player
         * 1 for Dealer
        */
        int playerID;
        int currCards;
        int maxCards;
        int sum;

};

#endif