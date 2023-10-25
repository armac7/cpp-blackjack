// #ifndef CARD_H
// #define CARD_H
// #include <iostream>
// using namespace std;

// class Card 
// {
//     public:
//         Card() 
//         {
//             /**
//              * @brief [Default constructor. Creates null card.]
//              * @return [No return, is a constructor.]
//             */
//            number = 0;
//            cardType = 1;
//            cardFace = "null";
//         }
//         Card(int number, int cardType, string cardFace) 
//         {
//             /**
//              * @brief [Constructor for class Card.]
//              * @param number [An integer representing the amount of points the card is worth (should be between 1 and 10).]
//              * @param cardType [An integer (1-4) representing the type of card. (Ex. Hearts). 1 = Hearts | 2 = Clubs | 3 = Spades | 4 = Diamonds. ]
//              * @param cardFace [A string representing the face of the card. Either reflects the number (Ex. 10) or other (Ex. Ace, King, etc.).]
//              * @return [No return, is a constructor.]
//             */
//             if (number < 1 || number > 10) 
//             {
//                 cout << "Error: invalid card number." << endl;
//                 cout << "Number set to 0, type set to 1, and face set to null." << endl;
//                 this->number = 0;
//                 this->cardType = 1;
//                 this->cardFace = "null";
//             } 
//             else 
//             {
//                 this->number = number;
//                 this->cardType = cardType;
//                 this->cardFace = cardFace;
//             }
//         }
//         int getNumber() const
//         {
//             /**
//              * @brief [Returns the card number.]
//              * @return [An integer representing the card number.]
//             */
//             return number;
//         }
//         string getType() const
//         {
//             /**
//              * @brief [Converts cardType number into corresponding string and returns it.]
//              * @return [String representing card type based on cardType number.]
//             */
//             string type;
//             string typeList[] = {"Hearts", "Clubs", "Spades", "Diamonds"};
//             for (int i = 0; i < 4; i++) { if (cardType - 1 == i) type = typeList[i]; }
//             return type;
//         }
//         string getFace() const 
//         {
//             return cardFace;
//         }
//         void setNumber(int number) 
//         { 
//             /**
//              * @brief [Sets the card number.]
//              * @param number [Integer to set number equal to, should be 1-11]
//             */
//            if (number < 0 || number > 11) { cout << "Error: number must be greater than 0 but less than 12." << endl; }
//            else { this->number = number; }
//         }
//         int operator +(const Card &card) const
//         {
//             /**
//              * @brief [Overrides the + operator to add the points together.]
//              * @param card [A card to be used to add to another card, will not be changed.]
//              * @return [An integer value representing the 2 point values of the cards being added together.]
//             */
//             return number + card.number;
//         }
//         friend ostream &operator <<(ostream &os, const Card &card)
//         {
//             os << card.cardFace << " of " << card.getType();
//             return os;
//         }
//     private:
//         int number; // points for the card
//         string cardFace;
//         int cardType;
//         /**
//          * 1 - Hearts
//          * 2 - Clubs
//          * 3 - Spades
//          * 4 - Diamonds
//         */
// };

// #endif