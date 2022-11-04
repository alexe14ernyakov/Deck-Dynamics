#include "Deck.h"
#include "gtest/gtest.h"

void menu();
void action(Deck::Deck& d, int action);
int Testing();

int main() {
    //d.print(std::cout);
    //d.sort();
    //d.print(std::cout);

    /*Deck::Deck d(1);
    Deck::Card c(Deck::KING, Deck::SPADES);

    Deck::Deck r = c + d;
    r.print(std::cout);*/

    Deck::Deck d(Deck::Card(Deck::JACK, Deck::SPADES));
    d = d;
    d.print(std::cout);

    /*std::cout << "How do you want to set your deck?" << std::endl;
    std::cout << "1. Create empty deck" << std::endl;
    std::cout << "2. By amount of cards(random)" << std::endl;
    std::cout << "3. By first card" << std::endl;
    std::cout << "4. Test the program" << std::endl << ">";
    std::cout << "" << std::endl;

    Deck::Deck d;
    int c;
    std::cin >> c;
    switch (c) {
        case 1:{
            break;
        }
        case 2:{
            int n;
            std::cout << "Enter number of cards" << std::endl << ">";
            std::cin >> n;
            try{
                d = Deck::Deck(n);
            }
            catch(std::exception& ex){
                std::cout << ex.what();
                return 0;
            }
            break;
        }
        case 3:{
            std::string card_rang, card_suit;
            std::cout << "Enter rang and suit of the first card" << std::endl;
            std::cin >> card_rang >> card_suit;
            try {
                d = Deck::Deck( Deck::Card(Deck::transfer_rang(card_rang), Deck::transfer_suit(card_suit)));
            }
            catch(std::exception& ex){
                std::cout << ex.what();
            }
            break;
        }
        case 4:{
            Testing();
            break;
        }
        default:{
            std::cout << "Invalid way of setting deck...";
            return 0;
        }
    }

    int a = 1;
    do{
        menu();
        std::cin >> a;
        action(d, a);
    } while(a != 0);*/
    return 0;
}

void menu(){
    std::cout << "What do you want to do?" << std::endl;
    std::cout << "0. Exit program" << std::endl;
    std::cout << "1. Add random card" << std::endl;
    std::cout << "2. Add card" << std::endl;
    std::cout << "3. Delete random card" << std::endl;
    std::cout << "4. Get card info by number" << std::endl;
    std::cout << "5. Add some cards" << std::endl;
    std::cout << "6. Sort your deck" << std::endl;
    std::cout << "7. Get the deck with one suit" << std::endl;
    std::cout << "8. See your deck" << std::endl << ">";
}

void action(Deck::Deck& d, int action){
    switch (action) {
        case 0:{
            break;
        }
        case 1:{
            try{
                ++d;
            }
            catch(std::exception& ex){
                std::cout << ex.what();
            }
            break;
        }
        case 2:{
            std::string card_rang, card_suit;
            std::cout << "Enter rang and suit of card" << std::endl;
            std::cin >> card_rang >> card_suit;
            try{
                d.add_card( Deck::Card(Deck::transfer_rang(card_rang), Deck::transfer_suit(card_suit)));
            }
            catch(std::exception& ex){
                std::cout << ex.what() << std::endl;
            }
            break;
        }
        case 3:{
            try{
                --d;
            }
            catch(std::exception& ex){
                std::cout << ex.what();
            }
            break;
        }
        case 4:{
            int n;
            std::cout << "Enter number of the card" << std::endl << ">";
            std::cin >> n;
            try{
                std::cout << "Card:\t";
                d.get_card(n).print(std::cout);
            }
            catch(std::exception& ex){
                std::cout << ex.what() << std::endl;
            }
            break;
        }
        case 5:{
            std::cout << "Enter number of cards and than their ranges and suits";
            try {
                d.input(std::cin);
            }
            catch(std::exception& ex){
                std::cout << ex.what() << std::endl;
            }
            break;
        }
        case 6:{
            d.sort();
            break;
        }
        case 7:{
            std::string card_suit;
            std::cout << "Choose your suit" << std::endl;
            std::cin >> card_suit;
            try {
                d = d.given_suit_deck(Deck::transfer_suit(card_suit));
            }
            catch(std::exception& ex){
                std::cout << ex.what() << std::endl;
            }
            break;
        }
        case 8:{
            d.print(std::cout);
            break;
        }
        default:{
            std::cout << "Unknown action..." << std::endl;
            break;
        }

    }
}

int Testing(){
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}


TEST(DeckTest, TransferTest1){
    EXPECT_EQ(Deck::transfer_rang("KING"), 13);
}

TEST(DeckTest, TransferTest2){
    EXPECT_EQ(Deck::transfer_rang("7"), 7);
}

TEST(DeckTest, TransferTest3){
    EXPECT_EQ(Deck::transfer_suit("HEARTS"), 3);
}

TEST(DeckTest, TransferTest4){
    EXPECT_EQ(Deck::transfer_suit("DIAMONDS"), 5);
}

TEST(DeckTest, TransferTest5){
    EXPECT_EQ(Deck::transfer_rang("zxc"), 0);
}

TEST(DeckTest, TransferTest6){
    EXPECT_EQ(Deck::transfer_suit("zxc"), 0);
}

TEST(DeckTest, RetransferTest1){
    EXPECT_EQ(Deck::retransfer_rang(11), "JACK");
}

TEST(DeckTest, RetransferTest2){
    EXPECT_EQ(Deck::retransfer_rang(0), "UNKNOWN");
}

TEST(DeckTest, CardConstructorTest1){
    Deck::Card c;
    EXPECT_EQ(c.rang, 0);
}

TEST(DeckTest, CardConstructorTest2){
    Deck::Card c;
    EXPECT_EQ(c.suit, 0);
}

TEST(DeckTest, CardConstructorTest3){
    Deck::Card c(3, 2);
    EXPECT_EQ(c.rang, 3);
}

TEST(DeckTest, CardConstructorTest4){
    Deck::Card c(11, 5);
    EXPECT_EQ(c.suit, 5);
}

TEST(DeckTest, PrintTest1) {
    Deck::Deck d(Deck::Card(11, 6));
    std::ostringstream o;
    d.print(o);
    ASSERT_STREQ(o.str().c_str(), "[1]:\tJACK \x06\n");
}

TEST(DeckTest, GenerateTest1){
    Deck::Deck d(1);
    EXPECT_NEAR(d.get_card(1).rang, 7, 6);
}

TEST(DeckTest, GenerateTest2){
    Deck::Deck d(1);
    EXPECT_NEAR(d.get_card(1).suit, 4.5, 1.5);
}

TEST(DeckTest, ConstructorTest1) {
    Deck::Deck d;
    EXPECT_EQ(d.get_amount(), 0);
}

TEST(DeckTest, ConstructorTest2) {
    Deck::Deck d(20);
    EXPECT_EQ(d.get_amount(), 20);
}

TEST(DeckTest, ConstructorTest3) {
    ASSERT_ANY_THROW(Deck::Deck d(-3));
}

TEST(DeckTest, ConstructorTest4) {
    Deck::Deck d(Deck::Card(6, 4));
    EXPECT_EQ(d.get_amount(), 1);
}

TEST(DeckTest, ConstructorTest5) {
    Deck::Deck d(Deck::Card(6, 4));
    EXPECT_EQ(d.get_card(1).rang, 6);
}

TEST(DeckTest, ConstructorTest6) {
    Deck::Deck d(Deck::Card(6, 4));
    EXPECT_EQ(d.get_card(1).suit, 4);
}

TEST(DeckTest, ConstructorTest7) {
    Deck::Deck p(10);
    Deck::Deck d(p);
    EXPECT_EQ(p.get_amount(), 10);
}

TEST(DeckTest, GetRangTest1) {
    Deck::Card c(10, 4);
    Deck::Deck d(c);
    EXPECT_EQ(d.get_rang(1), 10);
}

TEST(DeckTest, GetSuitTest1) {
    Deck::Card c(10, 4);
    Deck::Deck d(c);
    EXPECT_EQ(d.get_suit(1), 4);
}

TEST(DeckTest, AddCardTest1) {
    Deck::Deck d(11);
    d.add_card();
    EXPECT_EQ(d.get_amount(), 12);
}

TEST(DeckTest, AddCardTest2) {
    Deck::Deck d(52);
    ASSERT_ANY_THROW(d.add_card());
}

TEST(DeckTest, AddCardTest3) {
    Deck::Deck d(Deck::Card(3, 3));
    ASSERT_ANY_THROW(d.add_card(Deck::Card(3, 3)));
}

TEST(DeckTest, AddCardTest4) {
    Deck::Deck d(52);
    ASSERT_ANY_THROW(d.add_card(Deck::Card(4, 4)));
}

TEST(DeckTest, AddCardTest5) {
    Deck::Deck d(Deck::Card(3, 3));
    d.add_card(Deck::Card(4, 4));
    EXPECT_EQ(d.get_amount(), 2);
}

TEST(DeckTest, GetCardTest1) {
    Deck::Deck d(10);
    ASSERT_ANY_THROW(d.get_card(11));
}

TEST(DeckTest, GetCardTest2) {
    Deck::Deck d(4);
    EXPECT_EQ(d.get_card(3).rang != 0, 1);
}

TEST(DeckTest, PrintDeckTest1) {
    Deck::Deck d;
    d.add_card(Deck::Card(4, 4));
    d.add_card(Deck::Card(11, 3));
    std::ostringstream o;
    d.print(o);
    ASSERT_STREQ(o.str().c_str(), "[1]:\t4 \x04\n[2]:\tJACK \x03\n");
}

TEST(DeckTest, GivenSuitTest1){
    Deck::Deck d(52);
    Deck::Deck r;
    r = d.given_suit_deck(5);
    EXPECT_EQ(r.get_amount(), 13);
}

TEST(DeckTest, BracketsTest1){
    Deck::Deck d(52);
    Deck::Card c;
    ASSERT_NO_THROW(c = d[4]);
}

TEST(DeckTest, BracketsTest2){
    Deck::Deck d(10);
    Deck::Card c;
    ASSERT_ANY_THROW(c = d[11]);
}

TEST(DeckTest, PlusPlusTest1){
    Deck::Deck d(10);
    d++;
    EXPECT_EQ(d.get_amount(), 11);
}

TEST(DeckTest, PlusPlusTest2){
    Deck::Deck d(10);
    ++d;
    EXPECT_EQ(d.get_amount(), 11);
}

TEST(DeckTest, PlusPlusTest3){
    Deck::Deck d(52);
    ASSERT_ANY_THROW(d++);
}

TEST(DeckTest, PlusPlusTest4){
    Deck::Deck d(52);
    ASSERT_ANY_THROW(++d);
}

TEST(DeckTest, MinusMinusTest1){
    Deck::Deck d(15);
    d--;
    EXPECT_EQ(d.get_amount(), 14);
}

TEST(DeckTest, MinusMinusTest2){
    Deck::Deck d(15);
    --d;
    EXPECT_EQ(d.get_amount(), 14);
}

TEST(DeckTest, MinusMinusTest3){
    Deck::Deck d;
    ASSERT_ANY_THROW(d--);
}

TEST(DeckTest, MinusMinusTest4){
    Deck::Deck d;
    ASSERT_ANY_THROW(--d);
}

TEST(DeckTest, PlusTest1){
    Deck::Deck d;
    Deck::Card c(4, 4);
    EXPECT_EQ( (d + c).get_amount(), 1);
}

TEST(DeckTest, PlusTest2){
    Deck::Deck c(40);
    Deck::Deck d(40);
    EXPECT_EQ( (c + d).get_amount() <= 52, 1);
}

TEST(DeckTest, PlusEqTest1){
    Deck::Deck d;
    d += Deck::Card(5, 5);
    EXPECT_EQ( d.get_amount(), 1);
}

TEST(DeckTest, PlusEqTest2){
    Deck::Deck d(30);
    d += Deck::Deck(30);
    EXPECT_EQ( d.get_amount() <= 52, 1);
}