// used 10.6 zybooks for help

#ifndef CARD_H
#define CARD_H
#include <stdbool.h>

typedef struct card_struct {
    int value;  // number on card
    char action[15];    // what the card does
    int isProtected; // set to 0 for no protection, when protection is on it, place the value of the card # on other card
    // this way if player switches the card, we can place protect card into discard
} card;

// must include function names
void printCurrDeck (card deck[], int size);

void shuffleDeck(card deck[]);

void printPlayerHand (card hand[]);

void printFaceUpRow(card faceUpRow[]);

void highLowSort(card hand[], int size);

int drawCards(char player[], card hand[], card deck[], int *deckIndex);

void placeCardInHand (int replaceCard, card playerHand[], card faceUpRow[], int drawnCard, card deck[], card discardPile[]);

void addToDiscard(card deckOfCards[], card discardPile[], int replaceCard);
  
int checkFaceUpRowAvailSpots(card faceUpRow[]); 
 
bool checkWin(card playerHand[]);
  
void chooseAction(card playersTurn[], char playerTurnName[], card otherPlayerHand[], char otherPlayerName[], card faceUpRow[], card deckOfCards[], int *deckIndex, card discardPile[]); 
  
bool discardDuplicates(card faceUpRow[], card discardPile[], card deckOfCards[]);

 // card action functions
void swapAdjacent(card playerHand[], char playerName[], card deckOfCards[], card discardPile[]);
void shift2Right(card playerHand[], char playerName[], card deckOfCards[], card discardPile[]);
void shift2Left(card playerHand[], char playerName[], card deckOfCards[], card discardPile[]);
void swapSkip1Card(card playerHand[], char playerName[], card deckOfCards[], card discardPile[]);
void protectCard(card playerHand[], char playerName[], int protectValNum);
void removeLeft(card p1hand[], char p1name[], card p2hand[], char p2name[], card faceUpRow[], card deckOfCards[], int *deckIndex);
void removeRight(card p1hand[], char p1name[], card p2hand[], char p2name[], card faceUpRow[], card deckOfCards[], int *deckIndex);
void removeMiddle(card p1hand[], char p1name[], card p2hand[], char p2name[], card faceUpRow[], card deckOfCards[], int *deckIndex);

#endif