// #include <iostream>
// #include <vector>
// #include <ctime>
// #include "Card.h"

// #ifndef DECK_H
// #define DECK_H

// class Deck 
// {
//     public:
//         Deck() 
//         {
//             initDeck();
//             drawn = Card();
//         }
//         void initDeck() 
//         {
//             /**
//              * @brief [Initializes the deck of 52 cards, of 4 types of cards.]
//              * @return [Nothing returned, void method.]
//             */
//             // f = face (Ex. Hearts); p = points (Ex. 1);
//             for (int f = 1; f < 5; f++) 
//             {
//                 for (int p = 1; p < 14; p++) 
//                 {
//                     if (p == 1) { deck.push_back(Card(p, f, "Ace")); }
//                     else if (p > 10) 
//                     {
//                         string faces[] = {"Jack", "Queen", "King"};
//                         deck.push_back(Card(10, f, faces[(p % 10) - 1]));
//                     }
//                     else 
//                     {
//                         string faces[] = {"Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten"};
//                         deck.push_back(Card(p, f, faces[p - 2]));
//                     }
//                 }
//             }
//         }
//         Card drawCard() 
//         {
//             srand(time(0));
//             bool validCard = false;
//             do {
//                 int cardToDraw = rand() % 52;
//                 if (deck.at(cardToDraw).getNumber() == 0) { validCard = false; }
//                 else 
//                 {

//                     return deck.at(cardToDraw);
//                 }
//             } while(!validCard);
//         }
//         friend ostream &operator <<(ostream &os, const Deck &deck)
//         {
//             /**
//              * @brief [Prints the deck and size of the deck (excluding null cards).]
//              * @param os [Member of ostream class used to print to console.]
//              * @param deck [Member of Deck class.]
//              * @return [OS Stream representing the entire deck and the size of the deck (exclusing null cards).]
//             */
//             int size;
//             for (int i = 0; i < deck.deck.size(); i++) 
//             {
//                 os << deck.deck.at(i) << endl;
//                 if (deck.deck.at(i).getNumber() != 0) size++; 
//             }
//             os << "Size of Deck: " << size << endl;
//             return os;
//         }
//     private:
//         vector<Card> deck;
//         Card drawn;
// };

// #endif