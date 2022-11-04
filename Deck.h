#ifndef TRUEDIMAMIC_DECK_H
#define TRUEDIMAMIC_DECK_H
#include <iostream>
#include <cstdlib>
#include <sstream>
#include <algorithm>

namespace Deck{
    enum Rang{
        ACE = 1,
        JACK = 11,
        QUEEN,
        KING
    };

    enum Suit{
        HEARTS = 3,
        CLUBS,
        DIAMONDS,
        SPADES
    };

    struct Card{
        int rang;
        int suit;

        Card();
        Card(int r, int s);

        void print(std::ostream& stream) const;
    };
    typedef struct Card Card;

    int transfer_rang(std::string rang_str);
    int transfer_suit(std::string suit_str);
    std::string retransfer_rang(int r);
    bool cmp(const Card& a, const Card& b);

    class Deck{
    private:
        int   amount = 0;
        Card* cards = nullptr;

        int generate_rang() const;
        int generate_suit() const;
        bool repeat_check(int r, int s) const;
    public:
        Deck();
        Deck(int n);
        Deck(Card c);
        Deck(const Deck& d);
        Deck(Deck && d);
        ~Deck();
        int get_amount() const;
        int get_rang(int n) const;
        int get_suit(int n) const;
        void add_card(Card c);
        void add_card();
        Card get_card(int n) const;
        void input(std::istream& stream);
        void print(std::ostream& stream) const;
        void sort();
        Deck given_suit_deck(int s) const;

        Deck &operator=(const Deck &other) noexcept;
        Deck &operator=(Deck&& d) noexcept;

        const Card& operator[](int number) const;

        const Deck operator++(int i);
        const Deck& operator++();

        const Deck operator--(int i);
        const Deck& operator--();

        //Deck operator+(const Card& c);
        //Deck operator+(const Deck& d);
        friend const Deck operator+(const Deck& first, const Deck& second);


        Deck operator+=(const Deck& d);
    };
}

#endif
