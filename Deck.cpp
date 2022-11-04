#include "Deck.h"

namespace Deck{
    int transfer_rang(std::string rang_str){
        if(rang_str == "ACE") return ACE;
        if(rang_str == "2") return 2;
        if(rang_str == "3") return 3;
        if(rang_str == "4") return 4;
        if(rang_str == "5") return 5;
        if(rang_str == "6") return 6;
        if(rang_str == "7") return 7;
        if(rang_str == "8") return 8;
        if(rang_str == "9") return 9;
        if(rang_str == "10") return 10;
        if(rang_str == "JACK") return JACK;
        if(rang_str == "QUEEN") return QUEEN;
        if(rang_str == "KING") return KING;
        return 0;
    }

    int transfer_suit(std::string suit_str){
        if(suit_str == "CLUBS") return CLUBS;
        if(suit_str == "DIAMONDS") return DIAMONDS;
        if(suit_str == "HEARTS") return HEARTS;
        if(suit_str == "SPADES") return SPADES;
        return 0;
    }

    std::string retransfer_rang(int r){
        switch (r) {
            case 0: return "UNKNOWN";
            case ACE: return "ACE";
            case 2: return "2";
            case 3: return "3";
            case 4: return "4";
            case 5: return "5";
            case 6: return "6";
            case 7: return "7";
            case 8: return "8";
            case 9: return "9";
            case 10: return "10";
            case JACK: return "JACK";
            case QUEEN: return "QUEEN";
            case KING: return "KING";
            default: return "UNKNOWN";
        }
    }

    Card::Card() {
        rang = 0;
        suit = 0;
    }

    Card::Card(int r, int s) {
        rang = r;
        suit = s;
    }

    void Card::print(std::ostream& stream) const {
        stream << retransfer_rang(rang) << " " << (char)suit << std::endl;
    }

    int Deck::generate_rang() const {
        return rand() % 13 + 1;
    }

    int Deck::generate_suit() const {
        return rand() % 4 + 3;
    }

    bool Deck::repeat_check(int r, int s) const {
        for(int i = 0; i < amount; i++){
            if(cards[i].rang == r && cards[i].suit == s)
                return true;
        }
        return false;
    }

    Deck::Deck() {
        amount = 0;
        cards = nullptr;
    }

    Deck::Deck(int n) {
        if(n < 0 || n > 52)
            throw std::out_of_range("Invalid value of cards amount...");

        amount = n;
        try {
            cards = new Card[n];
        }
        catch(std::bad_alloc& ba){
            std::cout << ba.what();
            delete[] cards;
            cards = nullptr;
            throw ba;
        }

        int r, s;
        for(int i = 0; i < n; i++) {
            do {
                r = generate_rang();
                s = generate_suit();
            } while (repeat_check(r, s));
            cards[i].rang = r;
            cards[i].suit = s;
        }
    }

    Deck::Deck(Card c) {
        amount = 1;
        try {
            cards = new Card;
        }
        catch(std::bad_alloc& ba){
            std::cout << ba.what();
            delete[] cards;
            cards = nullptr;
            throw ba;
        }
        *cards = c;
    }

    Deck::Deck(const Deck &d) {
        amount = d.amount;
        try {
            cards = new Card[amount];
            std::memcpy(cards, d.cards, sizeof(Card) * amount);
        }
        catch(std::bad_alloc& ba){
            std::cout << ba.what();
            delete[] cards;
            cards = nullptr;
            throw ba;
        }
    }

    Deck::Deck(Deck && d) {
        amount = d.amount;
        cards = d.cards;

        d.amount = 0;
        d.cards = nullptr;
    }

    Deck::~Deck() {
        delete[] cards;
    }

    int Deck::get_amount() const {
        return amount;
    }

    int Deck::get_rang(int n) const{
        return cards[n - 1].rang;
    }

    int Deck::get_suit(int n) const{
        return cards[n - 1].suit;
    }

    void Deck::add_card() {
        if(amount > 51)
            throw std::out_of_range("The deck is full...");

        int r, s;
        do {
            r = generate_rang();
            s = generate_suit();
        } while (repeat_check(r, s));

        try {
            Card *ptr = new Card[amount + 1];
            std::memcpy(ptr, cards, amount * sizeof(Card));
            ptr[amount] = Card(r, s);
            delete[] cards;
            cards = ptr;
            amount++;
        }
        catch(std::bad_alloc& ba){
            std::cout << ba.what();
            delete[] cards;
            cards = nullptr;
            throw ba;
        }
    }

    void Deck::add_card(Card c) {
        if(repeat_check(c.rang, c.suit))
            throw std::logic_error("There is such card in deck...");

        if(amount > 51)
            throw std::out_of_range("The deck is full...");
        try {
            Card *ptr = new Card[amount + 1];
            std::memcpy(ptr, cards, amount * sizeof(Card));
            ptr[amount] = c;
            delete[] cards;
            cards = ptr;
            amount++;
        }
        catch(std::bad_alloc& ba){
            std::cout << ba.what();
            delete[] cards;
            cards = nullptr;
            throw ba;
        }
    }

    Card Deck::get_card(int n) const{
        if(n > amount || n <= 0)
            throw std::out_of_range("There is no such card...");
        return cards[n - 1];
    }

    void Deck::input(std::istream &stream) {
        int n;
        stream >> n;

        if(amount + n > 52)
            throw std::out_of_range("You want to add too many cards...");

        int r, s;
        std::string rang_str, suit_str;
        for(int i = 0; i < n; i++){
            stream >> rang_str >> suit_str;
            r = transfer_rang(rang_str);
            s = transfer_suit(suit_str);
            add_card( Card(r, s) );
        }
    }

    void Deck::print(std::ostream& stream) const{
        for(int i = 0; i < amount; i++){
            stream << "[" << i+1 << "]:\t";
            get_card(i + 1).print(stream);
        }
    }

    bool cmp(const Card& a, const Card& b){
        /*if(a.suit > b.suit)
            return true;
        else{
            if(a.rang < b.rang)
                return true;
            else
                return false;
        }*/
        return a.suit > b.suit;
    }

    void Deck::sort() {
        std::sort(cards, cards + amount, cmp);
    }

    Deck Deck::given_suit_deck(int s) const {
        Deck res;
        for(int i = 0; i < amount; i++){
            if(cards[i].suit == s)
                res.add_card(cards[i]);
        }
        return res;
    }

    Deck &Deck::operator=(const Deck &other) noexcept {
        if(this == &other)
            return *this;
        if (cards != nullptr)
            delete[] cards;
        amount = other.amount;
        cards = new Card[amount];
        for(size_t i = 0; i < amount; ++i){
            cards[i].suit = other.cards[i].suit;
            cards[i].rang= other.cards[i].rang;
        }
        return *this;
    }

    Deck &Deck::operator=(Deck &&d) noexcept {
        if(this == &d)
            return *this;
        if (cards != nullptr)
            delete[] cards;
        cards = d.cards;
        amount = d.amount;

        d.amount = 0;
        d.cards = nullptr;
        return *this;
    }

    const Card &Deck::operator[](int n) const {
        if(n < 0 || n > amount - 1)
            throw std::logic_error("There is no such card in the deck...");

        return cards[n];
    }

    const Deck Deck::operator++(int i) {
        if(amount == 52)
            throw std::logic_error("Deck is full");

        Deck res(*this);
        int r, s;
        do{
            r = generate_rang();
            s = generate_suit();
        } while(repeat_check(r, s));

        try {
            Card *ptr = new Card[amount + 1];
            std::memcpy(ptr, cards, amount * sizeof(Card));
            ptr[amount] = Card(r, s);
            delete[] cards;
            cards = ptr;
            cards[amount].rang = r;
            cards[amount].suit = s;
            amount++;
        }
        catch(std::bad_alloc& ba){
            std::cout << ba.what();
            delete[] cards;
            cards = nullptr;
            throw ba;
        }

        return res;
    }

    const Deck& Deck::operator++() {
        if(amount == 52)
            throw std::logic_error("Deck is full");

        int r, s;
        do{
            r = generate_rang();
            s = generate_suit();
        } while(repeat_check(r, s));

        try {
            Card *ptr = new Card[amount + 1];
            std::memcpy(ptr, cards, amount * sizeof(Card));
            ptr[amount] = Card(r, s);
            delete[] cards;
            cards = ptr;
            cards[amount].rang = r;
            cards[amount].suit = s;
            amount++;
        }
        catch(std::bad_alloc& ba){
            std::cout << ba.what();
            delete[] cards;
            cards = nullptr;
            throw ba;
        }

        return *this;
    }

    const Deck Deck::operator--(int i) {
        if(amount == 0)
            throw std::logic_error("There are no cards in deck");

        Deck res(*this);

        int n = rand() % amount;
        cards[n].rang = cards[amount - 1].rang;
        cards[n].suit = cards[amount - 1].suit;

        try {
            Card *ptr = new Card[amount - 1];
            std::memcpy(ptr, cards, (amount - 1) * sizeof(Card));
            delete[] cards;
            cards = ptr;
        }
        catch(std::bad_alloc& ba){
            std::cout << ba.what();
            delete[] cards;
            cards = nullptr;
            throw ba;
        }

        amount--;

        return res;
    }

    const Deck& Deck::operator--() {
        if(amount == 0)
            throw std::logic_error("There are no cards in deck");

        int n = rand() % amount;
        cards[n].rang = cards[amount - 1].rang;
        cards[n].suit = cards[amount - 1].suit;

        try {
            Card *ptr = new Card[amount - 1];
            std::memcpy(ptr, cards, (amount - 1) * sizeof(Card));
            delete[] cards;
            cards = ptr;
        }
        catch(std::bad_alloc& ba){
            std::cout << ba.what();
            delete[] cards;
            cards = nullptr;
            throw ba;
        }
        amount--;

        return *this;
    }

    /*Deck Deck::operator+(const Card& c) {
        if(amount == 52)
            throw std::out_of_range("Deck is full...");

        if(repeat_check(c.rang, c.suit))
            throw std::logic_error("There is such card in the deck...");

        Deck res;
        try {
            Card *ptr = new Card[amount + 1];
            std::memcpy(ptr, cards, amount * sizeof(Card));
            res.cards = ptr;

        }
        catch(std::bad_alloc& ba){
            std::cout << ba.what();
            delete[] cards;
            cards = nullptr;
            throw ba;
        }
        res.cards[amount].rang = c.rang;
        res.cards[amount].suit = c.suit;
        res.amount = amount + 1;

        return res;
    }

    Deck Deck::operator+(const Deck& d) {
        Deck res;
        try {
            Card *ptr = new Card[amount];
            std::memcpy(ptr, cards, amount * sizeof(Card));
            res.cards = ptr;
            res.amount = amount;
        }
        catch(std::bad_alloc& ba){
            std::cout << ba.what();
            delete[] cards;
            cards = nullptr;
            throw ba;
        }

        for(int i = 0; i < d.amount; i++){
            if(!repeat_check(d.cards[i].rang, d.cards[i].suit))
                res.add_card(d.cards[i]);
        }

        return res;
    } */

    const Deck operator+(const Deck& first, const Deck& second){
        Deck res;
        try {
            Card *ptr = new Card[first.amount];
            std::memcpy(ptr, first.cards, first.amount * sizeof(Card));
            res.cards = ptr;
            res.amount = first.amount;
        }
        catch(std::bad_alloc& ba){
            std::cout << ba.what();
            delete[] first.cards;
            res.cards = nullptr;
            throw ba;
        }

        for(int i = 0; i < second.amount; i++){
            if(!first.repeat_check(second.cards[i].rang, second.cards[i].suit))
                res.add_card(second.cards[i]);
        }

        return res;
    }

    Deck Deck::operator+=(const Deck &d) {
        for(int i = 0; i < d.amount; i++){
            if(!repeat_check(d.cards[i].rang, d.cards[i].suit))
                add_card(d.cards[i]);
        }

        return *this;
    }
}
