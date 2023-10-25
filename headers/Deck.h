#include <iostream>
#include <vector>
#include <ctime>
#include "Card.h"

#ifndef DECK_H
#define DECK_H

class Deck 
{
    public:
        Deck() 
        {
            initDeck();
            deck = nullptr;
            drawn = Card();
        }
        ~Deck() 
        {
            delete[] deck;
        }
        void initDeck() 
        {
            /**
             * @brief [Initializes the deck of 52 cards, of 4 types of cards.]
             * @return [Nothing returned, void method.]
            */
            // f = face (Ex. Hearts); p = points (Ex. 1);
            deck = new Card[52];
            int i = 0;
            for (int f = 1; f < 5; f++) 
            {
                for (int p = 1; p < 14; p++) 
                {
                    if (p == 1) 
                    { 
                        deck[i] = Card(p, f, "Ace"); 
                    }
                    else if (p > 10) 
                    {
                        string faces[] = {"Jack", "Queen", "King"};
                        deck[i] = Card(10, f, faces[(p % 10) - 1]);
                        // if (p == 11) { deck[i] = Card(10, f, "Jack"); }
                        // else if (p == 12) { deck[i] = Card(10, f, "Queen"); }
                        // else if (p == 13) { deck[i] = Card(10, f, "King"); }
                    } 
                    else 
                    {
                        string faces[] = {"Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten"};
                        deck[i] = Card(p, f, faces[p - 2]);
                    } 
                    i++;
                }
            }
        }
        Card drawCard() 
        {
            /**
             * @brief [Draws a card from the deck, sets that card to null in the deck, and returns the card (before turned to null).]
             * @return [Card representing the card drawn from the deck.]
            */
            srand(time(0));
            bool validCard = false;
            Card temp;
            do {
                int cardToDraw = rand() % 52;
                // if card is null, not valid card
                if (deck[cardToDraw].getNumber() == 0) { validCard = false; }
                // if valid card, grab card and set that card in deck to null.
                else 
                {
                    temp = Card(deck[cardToDraw]);
                    deck[cardToDraw] = Card();
                    validCard = true;
                }
            } while(!validCard);
            return temp;
        }
        friend ostream &operator <<(ostream &os, const Deck &deck)
        {
            /**
             * @brief [Prints the deck and size of the deck (excluding null cards).]
             * @param os [Member of ostream class used to print to console.]
             * @param deck [Member of Deck class.]
             * @return [OS Stream representing the entire deck and the size of the deck (exclusing null cards).]
            */
            int size = 0;
            for (int i = 0; i < 52; i++) 
            {
                os << deck.deck[i] << endl;
                if (deck.deck[i].getNumber() != 0) size++; 
            }
            os << "Size of Deck: " << size << endl;
            return os;
        }
    private:
        Card *deck;
        Card drawn;
};

#endif