#include <iostream>
using namespace std;

#ifndef BET_H
#define BET_H

class Bet 
{
    public:
        Bet() 
        {
            /**
             * @brief [Default Constructor.]
            */
            this->startingCash = 0;
            this->money = 0;
            this->isBroke = true;
        }
        Bet(int startingCash) 
        {
            /**
             * @brief [Sets money and starting cash to param.]
             * @param startingCash [The amount a player starts with.]
            */
            this->startingCash = startingCash;
            this->money = startingCash;
            this->isBroke = false;
        }
        Bet(const Bet &otherBet) 
        {
            /**
             * @brief [Copy constructor. Copies values of otherBet to this instance of Bet.]
             * @param otherBet [The Bet to be copied.]
            */
            this->startingCash = otherBet.startingCash;
            this->money = otherBet.money;
            this->bet = otherBet.bet;
            this->isBroke = otherBet.isBroke;
        }
        void initBet(int startingCash) 
        {
            /**
             * @brief [Initializes an instance of Bet (just like constructor).]
             * @param startingCash [The amount of money a player should start with.]
            */
            this->startingCash = startingCash;
            this->money = startingCash;
            this->bet = 0;
            (startingCash > 0) ? this->isBroke = false : this->isBroke = true;
        }
        void addBet(int bet) 
        {
            /**
             * @brief [Adds amount param bet to instance value bet.]
             * @param bet [The amount to add to the bet.]
            */
            if (bet >= money) { brokeBet(bet); }
            else 
            {
                this->bet += bet;
                this->money -= bet;
            }
        }
        void resetBet() {this->bet = 0;}
        void addMoney(int money) 
        {
            /**
             * @brief [Adds money to the current money of this instance.]
             * @param money [The amount of money to be added.]
            */
            this->money += money;
            areBroke();
        }
        void resetMoney() {this->money = this->startingCash;}
        void doubleBet() 
        {
            /**
             * @brief [Doubles the bet.]
            */
            if (this->bet >= this->money) { brokeBet(bet); }
            else 
            {
                this->money -= this->bet;
                this->bet *= 2;
            }
        }
        void matchBet(const Bet &otherBet) 
        {
            /**
             * @brief [Matches the bet of the opposite hand.]
             * @param otherBet [Another instance of Bet to compare current instance of Bet's bet to.]
            */
            int matchAmount = otherBet.bet - this->bet;
            if (matchAmount > 0) 
            {
                if (matchAmount >= this->money) { brokeBet(bet); }
                else 
                {
                    this->bet += matchAmount;
                    this->money -= matchAmount;
                }
            }
        }
        void operator =(int bet) 
        {
            /**
             * @brief [Sets the Bet of the LHS instance of Bet to the paramater "bet".]
             * @param bet [The amount bet is to be set to.]
            */
            this->bet = bet;
        }
        Bet operator =(const Bet &otherBet) 
        {
            /**
             * @brief [The same as a copy constructor.]
             * @param otherBet [The Bet instance to be copied.]
            */
            Bet temp(otherBet);
            return temp;
        }
        // Compares the bet of this instance of the Bet object and another.
        int getMoney() const {return this->money;}
        int getBet() const {return this->bet;}
        bool areBroke()
        {
            /**
             * @brief [Checks if the player is broke (updates isBroke), and returns the value.]
            */
            if (this->money <= 0) isBroke = true;
            else isBroke = false;
            return this->isBroke;
        }
        int getStartingCash() const {return this->startingCash;}
        void setStartingCash(int startingCash) {this->startingCash = startingCash;}
        bool operator <(const Bet &otherBet) {return this->bet < otherBet.bet;}
        bool operator >(const Bet &otherBet) {return this->bet > otherBet.bet;}
        // Adds the int bet to the current bet of the instance.
        // This first + operator DOES NOT work properly.
        void operator +(int bet) {addBet(bet);}
        int operator +(const Bet &otherBet) {return this->bet + otherBet.bet;}
        friend ostream &operator<<(ostream &os, const Bet &someBet) 
        {
            os << "\tCurrent Money:   $" << someBet.getMoney() << endl
               << "\tCurrent Bet:     $" << someBet.getBet();
            return os;
        }
    private:
        int startingCash;
        int money;
        int bet;
        bool isBroke;
        void brokeBet(int bet) 
        {
            /**
             * @brief [Used where money may be less than bet.]
             * @param bet [Bet to check.]
            */
            bet = bet - (bet - this->money);
            this->bet += bet;
            this->money -= bet;
            this->isBroke = true;
        }
};

#endif