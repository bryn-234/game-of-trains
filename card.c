#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "card.h"
#include <stdbool.h>
#include <string.h>
 
// functions and their actual implementation


// print out current deck of cards
void printCurrDeck (card deck[], int size)
{
  for (int i = 0; i < size; i++)
	{
	  printf ("%d %s %d", deck[i].value, deck[i].action, deck[i].isProtected);
	  printf ("\n");
	}
}

// shuffle
// based off of Fisher-Yates algorithm
void shuffleDeck(card deck[]) {
    card temp; 
    srand(time(NULL)); // seed the random number generator
    
    for (int i = 83; i > 0; i--) {
        int j = rand() % (i+1); // generate a random index between 0 and 1
        
        // swap deck[i] and deck[j]
         temp = deck[i];
         deck[i] = deck[j];
         deck[j] = temp;
    }
}

// print players' hand
void printPlayerHand (card hand[]) {
    for (int i = 0; i < 6; i++) {
        printf("%d, ", hand[i].value);
    }
    printf("%d\n", hand[6].value);
}

// print faceUpRow not including empty spots
void printFaceUpRow(card faceUpRow[]) {
    for (int i = 0; i < 8; i++) {
         if (faceUpRow[i].value != 0) {
    printf(" .-------.       ");
         }
    }
    printf("\n");
    
     for (int i = 0; i < 8; i++) {
         if (faceUpRow[i].value != 0) {
    printf(" |        |      ");
         }
    }
     printf("\n");
    
    
    for (int i = 0; i < 8; i++) {
        if (faceUpRow[i].value != 0) {
        printf(" |  #%-2d   |      ", faceUpRow[i].value);
        }
    }
     printf("\n");
    
    for (int i = 0; i < 8; i++) {
         if (faceUpRow[i].value != 0) {
    printf(" |        |      ");
         }
    }
    printf("\n");
    
    for (int i = 0; i < 8; i++) {
         if (faceUpRow[i].value != 0) {
    printf(" |        |      ");
         }
    }
    printf("\n");
    
    for (int i = 0; i < 8; i++) {
         if (faceUpRow[i].value != 0) {
    printf(" '------- '      ");
         }
    }
    printf("\n");
    
    for (int i = 0; i < 8; i++) {
        if (strcmp(faceUpRow[i].action, "EMPTY") != 0) {
        printf("%-18s", faceUpRow[i].action);
        }
    }
    printf("\n");
    
    
    }
    

// sort hand from highest to lowest
//Code adapted from zybooks section 8.7.1
void highLowSort(card hand[], int size) {
   int i;
   int j;
   card temp;      // Temporary variable for swap
   
   for (i = 1; i < size; ++i) {
      j = i;
      // Insert hand[i] into sorted part
      // stopping once hand[i] in correct position
      while (j > 0 && hand[j].value > hand[j - 1].value) {
         
         // Swap hand[j] and hand[j - 1]
         temp = hand[j];
         hand[j] = hand[j - 1];
         hand[j - 1] = temp;
         --j;
      }
   }
}

// player draws cards
int drawCards(char player[], card hand[], card deck[], int *deckIndex) {
    int cardVal;
    
    // this is for when deck of cards runs out and it switches to discard pile
        while (deck[(*deckIndex)].value == 0) {
            (*deckIndex)++;
        }
    
        cardVal = deck[*deckIndex].value;
        (*deckIndex)++;
        
    printf("\n%s has drawn card #%d\n", player, cardVal);
    printf(" .-------.");
    printf("\n");
    printf(" |        |");
    printf("\n");
    printf(" |        |");
    printf("\n");
    printf(" |   %-2d   |", cardVal);
    printf("\n");
    printf(" |        |");
    printf("\n");
    printf(" |        |");
    printf("\n");
    printf(" '------- '");
    printf("\n");
    
      return cardVal;
}

// place card in hand, including it's action
// also puts replaced card into the faceup row
    void placeCardInHand (int replaceCard, card playerHand[], card faceUpRow[], int drawnCard, card deck[], card discardPile[]) {
        int index = 0;
        int checkIfThere = 0;
        
         for (int i = 0; i < 84; i++) {
            if (drawnCard == deck[i].value) {
                index = i;
                break;
            }
        }
        
      // continues looping if player enters invalid number
        while (checkIfThere == 0) {
        for (int i = 0; i < 7; i++) {
            if (playerHand[i].value == replaceCard) {
          
          // if card has protection on it, places the protect card in discard because card is being replaced
          // resets protection on card to 0
            if (playerHand[i].isProtected != 0) {
                addToDiscard(deck, discardPile, playerHand[i].isProtected);
                playerHand[i].isProtected = 0;
            }
        
            faceUpRow[checkFaceUpRowAvailSpots(faceUpRow)] = playerHand[i];
         
            
            // we want drawn card to have the attribute as well
            playerHand[i] = deck[index];
              
               checkIfThere++;
            }
            
        }
        if (checkIfThere == 0) {
            printf("Card number is not in your hand. Please input a valid number.\n");
            printf("What card value # do you want to replace? ");
            scanf("%d", &replaceCard);
            }
        }
    
    }


// function that adds card to discard pile
    void addToDiscard(card deckOfCards[], card discardPile[], int replaceCard) {
        int k = 0;
        int index = 0;
        
       
            while(discardPile[k].value != 0) {
                k++;
            }
        
        for (int i = 0; i < 84; i++) {
            if (deckOfCards[i].value == replaceCard) {
            index = i;
            discardPile[k] = deckOfCards[index];
            break;
            }
        }
    }

// checks which spots are free in faceUpRow and gives an index of where you can put card
    int checkFaceUpRowAvailSpots(card faceUpRow[]) {
        int i = 0;
        while (faceUpRow[i].value != 0) {
            i++;
        }
        
        return i;
    }

    // check if player has won game
    // cards will be sorted low to high
    bool checkWin(card playerHand[]) {
       for (int i = 0; i < 6; i++) {
           if (playerHand[i].value > playerHand[i+1].value) {
               return false;
           }
       }
       return true;
    }
 
// allows user to choose which action card they want to take
    void chooseAction(card playersTurn[], char playerTurnName[], card otherPlayerHand[], char otherPlayerName[], card faceUpRow[], card deckOfCards[], int *deckIndex, card discardPile[]) {
        int actionNumber;
        int actionIndex;
        int protectValNum; // this is the value of the # on the protect card
        int checkIfThere = 0;
        
        printf("Which action card would you like to use?\n");
        printf("Enter the card value # displayed on the face up card of the action you want to play\n");
        printf("Enter number: ");
        scanf("%d", &actionNumber);
        
        
        // continues looping if player enters invalid number
        while (checkIfThere == 0) {
        for (int i = 0; i < 8; i++) {
            if (faceUpRow[i].value == actionNumber) {
               actionIndex = i;
               checkIfThere++;
            }
        }
        
        if (checkIfThere == 0) {
        printf("Invalid number selection. Please pick the card value # displayed on the face up action card you want to play.\n");
        printf("Enter number: ");
        scanf("%d", &actionNumber);
        }
        }
        
        printf("\n");
        
        // we are gonna put p1 first if player 1 is going, and then p2 if player 2 is going
        
        if (strcmp(faceUpRow[actionIndex].action, "swapAdjacent") == 0) {
            swapAdjacent(playersTurn, playerTurnName, deckOfCards, discardPile);
        } else if (strcmp(faceUpRow[actionIndex].action, "shift2Right") == 0) {
            shift2Right(playersTurn, playerTurnName, deckOfCards, discardPile);
        } else if (strcmp(faceUpRow[actionIndex].action, "shift2Left") == 0) {
            shift2Left(playersTurn, playerTurnName, deckOfCards, discardPile);
        } else if (strcmp(faceUpRow[actionIndex].action, "swapSkip1Card") == 0) {
            swapSkip1Card(playersTurn, playerTurnName, deckOfCards, discardPile);
        } else if (strcmp(faceUpRow[actionIndex].action, "protect") == 0) {
            protectValNum = faceUpRow[actionIndex].value;
            protectCard(playersTurn, playerTurnName, protectValNum);
        } else if (strcmp(faceUpRow[actionIndex].action, "removeLeft") == 0) {
            removeLeft(playersTurn, playerTurnName, otherPlayerHand, otherPlayerName, faceUpRow, deckOfCards, deckIndex);
        } else if (strcmp(faceUpRow[actionIndex].action, "removeRight") == 0) {
            removeRight(playersTurn, playerTurnName, otherPlayerHand, otherPlayerName, faceUpRow, deckOfCards, deckIndex);
        } else if (strcmp(faceUpRow[actionIndex].action, "removeMiddle") == 0) {
        removeMiddle(playersTurn, playerTurnName, otherPlayerHand, otherPlayerName, faceUpRow, deckOfCards, deckIndex);    
        }
       
       
        // discard card afterwards, unless it is a protect because it will be in another players hand
       if (strcmp(faceUpRow[actionIndex].action, "protect") != 0) {
            addToDiscard(deckOfCards, discardPile, faceUpRow[actionIndex].value);
       }
  
    // set face up row card to 0 and empty because it has been played
    faceUpRow[actionIndex].value = 0;
    strcpy(faceUpRow[actionIndex].action, "EMPTY");
    faceUpRow[actionIndex].isProtected = 0;
    }
    
// discard duplicate action cards in face up row
    bool discardDuplicates(card faceUpRow[], card discardPile[], card deckOfCards[]) {
         for (int i = 0; i < 8; i++) {
        for (int j = i + 1; j < 8; j++) {
            if ((strcmp(faceUpRow[i].action, faceUpRow[j].action) == 0) && (strcmp(faceUpRow[i].action, "EMPTY") != 0) && (strcmp(faceUpRow[j].action, "EMPTY") != 0)) {
             
             // we want to discard both action cards
             addToDiscard(deckOfCards, discardPile, faceUpRow[i].value);
             addToDiscard(deckOfCards, discardPile, faceUpRow[j].value);
             
             // get rid of both cards from faceUpRow
             faceUpRow[i].value = 0;
             strcpy(faceUpRow[i].action, "EMPTY");
             faceUpRow[i].isProtected = 0;
             faceUpRow[j].value = 0;
             strcpy(faceUpRow[j].action, "EMPTY");
             faceUpRow[j].isProtected = 0;
            return true; // Duplicate found 
            }
        }
    }
    return false; // No duplicates found
    
    }


// CARD ACTIONS

// swaps adjacent cards
    void swapAdjacent(card playerHand[], char playerName[], card deckOfCards[], card discardPile[]) {
        card temp[1];
        
        int leftCardSwap;
        
        printf("%s: ", playerName);
        printf("What adjacent cards do you want to swap?\n");
        printf("Enter number based on position from left to right. For example, the leftmost card is card 1 and the rightmost card is card 7.\n");
        printf("Enter the number of the card on the left that you want to swap. For example, if you want to swap the first and second cards in your row, enter 1.");
        printf("\nNumber (1-6): ");
        scanf("%d", &leftCardSwap);
        
        while (leftCardSwap > 6 || leftCardSwap < 1) {
            printf("Invalid number selection. Please pick a number 1-6:\n");
            scanf("%d", &leftCardSwap);
        }
        
        printf("\n");

        // this gets index of where card is located in the hand
        leftCardSwap--;
        
       temp[0] = playerHand[leftCardSwap];
       playerHand[leftCardSwap] = playerHand[leftCardSwap + 1];
       playerHand[leftCardSwap + 1] = temp[0];
       
     
       //sets card protection back to 0 because player will have voluntarily got rid of protection
       // place protectCard in discard
       if (playerHand[leftCardSwap].isProtected != 0) {
           addToDiscard(deckOfCards, discardPile, playerHand[leftCardSwap].isProtected);
            playerHand[leftCardSwap].isProtected = 0;
       }
       
        if (playerHand[leftCardSwap+1].isProtected != 0) {
           addToDiscard(deckOfCards, discardPile, playerHand[leftCardSwap+1].isProtected);
            playerHand[leftCardSwap+1].isProtected = 0;
       }
    
    }
    
    // shifts card 2 spots to the right
    void shift2Right(card playerHand[], char playerName[], card deckOfCards[], card discardPile[]) {
        int shiftedCard;
        
        card temp[1];
        
        printf("%s: ", playerName);
        printf("What card do you want to shift two spaces to the right? You cannot choose one of the two rightmost cards\n");
        printf("Enter number based on position from left to right. For example, the leftmost card is card 1\n");
        printf("Number (1-5): ");
        scanf("%d", &shiftedCard);
        
        while (shiftedCard > 5 || shiftedCard < 1) {
            printf("Invalid number selection. Please pick a number 1-5:\n");
            scanf("%d", &shiftedCard);
        }
        printf("\n");

        // gets index of where card is located in the hand
        shiftedCard--;
        
        temp[0] = playerHand[shiftedCard]; 
        
        
        
        for (int i = 0; i < 2; i++) {
            playerHand[shiftedCard + i] = playerHand[shiftedCard + i + 1];
        }
        
        playerHand[shiftedCard + 2] = temp[0];
        
         //sets card protection back to 0 because player will have voluntarily got rid of protection
           if (playerHand[shiftedCard].isProtected != 0) {
           addToDiscard(deckOfCards, discardPile, playerHand[shiftedCard].isProtected);
            playerHand[shiftedCard].isProtected = 0;
       }
       
        if (playerHand[shiftedCard+1].isProtected != 0) {
           addToDiscard(deckOfCards, discardPile, playerHand[shiftedCard+1].isProtected);
            playerHand[shiftedCard+1].isProtected = 0;
       }
         if (playerHand[shiftedCard+2].isProtected != 0) {
           addToDiscard(deckOfCards, discardPile, playerHand[shiftedCard+2].isProtected);
            playerHand[shiftedCard+2].isProtected = 0;
       }
      
        
    }
    
    // shifts card 2 spots to the left
     void shift2Left(card playerHand[], char playerName[], card deckOfCards[], card discardPile[]) {
        int shiftedCard;
        
        card temp[1];
        
        printf("%s: ", playerName);
        printf("What card do you want to shift two spaces to the left? You cannot choose one of the two leftmost cards\n");
        printf("Enter number based on position from left to right. For example, the leftmost card is card 1\n");
        printf("Number (3-7): ");
        scanf("%d", &shiftedCard);
        
        while (shiftedCard > 7 || shiftedCard < 3) {
            printf("Invalid number selection. Please pick a number 3-7:\n");
            scanf("%d", &shiftedCard);
        }
        printf("\n");
        
        // gets index of where card is located in the hand
        shiftedCard--;
        
        temp[0] = playerHand[shiftedCard]; 
    
        for (int i = 0; i < 2; i++) {
            playerHand[shiftedCard - i] = playerHand[shiftedCard - i - 1];
        }
        
        playerHand[shiftedCard - 2] = temp[0];
        
          //sets card protection back to 0 because player will have voluntarily got rid of protection
           if (playerHand[shiftedCard].isProtected != 0) {
           addToDiscard(deckOfCards, discardPile, playerHand[shiftedCard].isProtected);
            playerHand[shiftedCard].isProtected = 0;
       }
       
        if (playerHand[shiftedCard-1].isProtected != 0) {
           addToDiscard(deckOfCards, discardPile, playerHand[shiftedCard-1].isProtected);
            playerHand[shiftedCard-1].isProtected = 0;
       }
         if (playerHand[shiftedCard-2].isProtected != 0) {
           addToDiscard(deckOfCards, discardPile, playerHand[shiftedCard-2].isProtected);
            playerHand[shiftedCard-2].isProtected = 0;
       }
    }
    
    // swaps 2 cards that have one card in between them
    void swapSkip1Card(card playerHand[], char playerName[], card deckOfCards[], card discardPile[]) {
        int cardPos1;
        int cardPos2;
        
        card temp[1];
    
        
        printf("%s: ", playerName);
        printf("What two cards do you want to swap? There can only be one card in between them.\n");
        printf("Enter number based on position from left to right. For example, the leftmost card is card 1\n");
        printf("Enter the value # of the cards with a space in between them.\n");
        printf("For example, if you want to switch your first and third card, enter '1 3'\n");
        printf("Enter 2 numbers (between 1 and 7): ");
        scanf("%d %d", &cardPos1, &cardPos2);
        
        while (cardPos1 < 1 || cardPos1 > 7 || cardPos2 < 1 || cardPos2 > 7) {
            printf("Invalid number selection.\n");
            printf("Enter 2 numbers (between 1 and 7): ");
            scanf("%d %d", &cardPos1, &cardPos2);
        }
        
        
        while (abs(cardPos2 - cardPos1) != 2) {
            printf("Numbers entered have more than 1 number between them. Please enter your numbers again: "); 
                scanf("%d %d", &cardPos1, &cardPos2);
        }
        
        printf("\n");
        
         cardPos1--;
        cardPos2--;
        
        temp[0] = playerHand[cardPos1];
        playerHand[cardPos1] = playerHand[cardPos2];
        playerHand[cardPos2] = temp[0];
        
          //sets card protection back to 0 because player will have voluntarily got rid of protection
          if (playerHand[cardPos1].isProtected != 0) {
              addToDiscard(deckOfCards, discardPile, playerHand[cardPos1].isProtected);
              playerHand[cardPos1].isProtected = 0;
          }
          
          if (playerHand[cardPos2].isProtected != 0) {
              addToDiscard(deckOfCards, discardPile, playerHand[cardPos2].isProtected);
              playerHand[cardPos2].isProtected = 0;
          }
    }
    
    // Protection
    void protectCard(card playerHand[], char playerName[], int protectValNum) {
        int choice;
        
        printf("%s: ", playerName);
        printf("What card do you want to protect?\n");
        printf("\n1. Leftmost\n2. Middle\n3. Rightmost\n");
        scanf("%d", &choice);
        
        while(choice > 4 || choice < 1) {
           printf("Invalid number selection. Please pick a number 1-3:\n"); 
           scanf("%d", &choice);
        }
        
       printf("\n");
        
        if (choice == 1) {
            playerHand[0].isProtected = protectValNum;
        } else if (choice == 2) {
            playerHand[3].isProtected = protectValNum;
        } else if (choice == 3) {
            playerHand[6].isProtected = protectValNum;
        }
        
    }
    
   
    // Removes leftmost card from all players' hands
    void removeLeft(card p1hand[], char p1name[], card p2hand[], char p2name[], card faceUpRow[], card deckOfCards[], int *deckIndex) {
        int drawnCard;
        int index;
        
        // if p1 hand is not protected (isProtected will be 0), complete action
       if (p1hand[0].isProtected == 0) {
            
        // p1 is the person who is playing the ACTIONS, so they draw first
        
         // p1 essentially draws a card from deck of cards and puts it in left spots
        drawnCard = drawCards(p1name, p1hand, deckOfCards, deckIndex); // --> this returns an INT
        
         for (int i = 0; i < 84; i++) {
            if (drawnCard == deckOfCards[i].value) {
                index = i;
                break;
            }
        }
        
        // puts leftmost card from p1hand into faceUpRow
        faceUpRow[checkFaceUpRowAvailSpots(faceUpRow)] = p1hand[0];
        // makes leftmost card equal to the card that was just drawn
        p1hand[0] = deckOfCards[index];
        
         printf("\n%s's hand after removeLeft action\n", p1name);
        printPlayerHand (p1hand);
        
        } else if (p1hand[0].isProtected != 0) {
            printf("%s's deck did not change\n", p1name);
            printPlayerHand (p1hand);
        }
        
         // Now, p2 turn
        // check if p2 hand is protected
        if (p2hand[0].isProtected == 0) {
             
        drawnCard = drawCards(p2name, p2hand, deckOfCards, deckIndex);
        
        for (int i = 0; i < 84; i++) {
            if (drawnCard == deckOfCards[i].value) {
                index = i;
                break;
            }
        }
        
        // puts leftmost card from p2hand into faceUpRow
        faceUpRow[checkFaceUpRowAvailSpots(faceUpRow)] = p2hand[0];
        // makes leftmost card equal to the card that was just drawn
        p2hand[0] = deckOfCards[index];
        
        printf("\n%s's hand after removeLeft action\n", p2name);
        printPlayerHand (p2hand);
        
        } else if (p2hand[0].isProtected != 0) {
             printf("%s's deck did not change\n", p2name);
            printPlayerHand (p2hand);
        }
        
        printf("\n");
    }
        
    // Removes rightmost card from all players' hands
    void removeRight(card p1hand[], char p1name[], card p2hand[], char p2name[], card faceUpRow[], card deckOfCards[], int *deckIndex) {
        int drawnCard;
        int index;
        
        // if p1 hand is not protected, complete action
       if (p1hand[6].isProtected == 0) {
            
        // p1 is the person who is playing the ACTIONS, so they draw first
        
         // p1 essentially draws a card from deck of cards and puts it in left spots
        drawnCard = drawCards(p1name, p1hand, deckOfCards, deckIndex); // --> this returns an INT
        
         for (int i = 0; i < 84; i++) {
            if (drawnCard == deckOfCards[i].value) {
                index = i;
                break;
            }
        }
        
        // puts rightmost card from p1hand into faceUpRow
        faceUpRow[checkFaceUpRowAvailSpots(faceUpRow)] = p1hand[6];
        // makes rightmost card equal to the card that was just drawn
        p1hand[6] = deckOfCards[index];
        
         printf("\n%s's hand after removeRight action\n", p1name);
        printPlayerHand (p1hand);
        
        } else if (p1hand[6].isProtected != 0) {
            printf("%s's deck did not change\n", p1name);
            printPlayerHand (p1hand);
        }
        
         // Now, p2 turn
        // check if p2 hand is protected
        if (p2hand[6].isProtected == 0) {
             
        drawnCard = drawCards(p2name, p2hand, deckOfCards, deckIndex);
        
        for (int i = 0; i < 84; i++) {
            if (drawnCard == deckOfCards[i].value) {
                index = i;
                break;
            }
        }
        
        // puts rightmost card from p2hand into faceUpRow
        faceUpRow[checkFaceUpRowAvailSpots(faceUpRow)] = p2hand[6];
        // makes rightmost card equal to the card that was just drawn
        p2hand[6] = deckOfCards[index];
        
        printf("\n%s's hand after removeRight action\n", p2name);
        printPlayerHand (p2hand);
        } else if (p2hand[6].isProtected != 0) {
            printf("%s's deck did not change\n", p2name);
            printPlayerHand (p2hand);
        }
    
        printf("\n");
    }
        
        
    // Removes middle card    
      void removeMiddle(card p1hand[], char p1name[], card p2hand[], char p2name[], card faceUpRow[], card deckOfCards[], int *deckIndex) {
        int drawnCard;
        int index;
        
        // if p1 hand is not protected, complete action
       if (p1hand[3].isProtected == 0) {
            
        // p1 is the person who is playing the ACTIONS, so they draw first
        
         // p1 essentially draws a card from deck of cards and puts it in left spots
        drawnCard = drawCards(p1name, p1hand, deckOfCards, deckIndex); 
        
         for (int i = 0; i < 84; i++) {
            if (drawnCard == deckOfCards[i].value) {
                index = i;
                break;
            }
        }
        
        // puts leftmost card from p1hand into faceUpRow
        faceUpRow[checkFaceUpRowAvailSpots(faceUpRow)] = p1hand[3];
        // makes leftmost card equal to the card that was just drawn
        p1hand[3] = deckOfCards[index];
        
        printf("\n%s's hand after removeMiddle action\n", p1name);
        printPlayerHand (p1hand);
        } else if (p1hand[3].isProtected != 0) {
            printf("%s's deck did not change\n", p1name);
            printPlayerHand (p1hand);
        }
        
         // Now, p2 turn
        // check if p2 hand is protected
        if (p2hand[3].isProtected == 0) {
             
        drawnCard = drawCards(p2name, p2hand, deckOfCards, deckIndex);
        
        for (int i = 0; i < 84; i++) {
            if (drawnCard == deckOfCards[i].value) {
                index = i;
                break;
            }
        }
        
        // puts leftmost card from p2hand into faceUpRow
        faceUpRow[checkFaceUpRowAvailSpots(faceUpRow)] = p2hand[3];
        // makes leftmost card equal to the card that was just drawn
        p2hand[3] = deckOfCards[index];
        printf("\n%s's hand after removeMiddle action\n", p2name);
        printPlayerHand (p2hand);
        
        } else if (p2hand[3].isProtected != 0) {
            printf("%s's deck did not change\n", p2name);
            printPlayerHand (p2hand);
        }
      
        printf("\n");
        
    }
        

