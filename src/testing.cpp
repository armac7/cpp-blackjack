// #include <iostream>
// #include "../headers/Card.h"
// #include "../headers/Deck.h"
// #include "../headers/Hand.h"
// using namespace std;

// int main() 
// {
//     // Testing Card
//     Card ace(1, 4, "Ace");
//     Card king(10, 4, "King");
//     cout << ace << endl;
//     cout << king << endl;
//     cout << ace + king << endl;

//     // Testing Deck
//     Deck deck;
//     // cout << deck << endl;
//     // Card temp;
//     // for (int i = 0; i < 52; i++) 
//     // {
//     //     temp = deck.drawCard();
//     //     cout << temp << endl;
//     // }
//     // cout << endl;
//     // cout << deck << endl;

//     // Testing Hand
//     Hand handPlayer;
//     cout << handPlayer << endl;

//     for (int i = 0; i < 3; i++) {
//         Card temp = deck.drawCard();
//         handPlayer.addCard(temp);
//     }
//     Card temp = Card(1, 3, "Ace");
//     handPlayer.addCard(temp);
//     cout << handPlayer << endl;


//     return 0;
// }