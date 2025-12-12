/*
    Bryn Neal
    ECE 175 
    Final Project 
    A Game of Trains
    Due Date: 4/30/24

    Online GDB used to create project
    
    For extra credit:
    1.) Prompt the user for the player's name
    2.) Created a discard pile which refills draw pile after the draw pile is empty and player wins
    3.) Added graphics to game
    
*/


#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#define HAND 7

// struct in card.h file
#include "card.h"

int main()
{
    // variables
    char deckType;
    card deckOfCards[84];
    int deckIndex = 0;
    char oscillatingName[100]; // switches which name is output 
    char playerMove; // 'd' is draw, 'a' is action
    
    bool winner = false;
    int count = 0; // when count is even, p1 turn
    // when count is odd, p2 turn
    
    int z = 0;
    int replaceCard;
    int drawnCard;      // card player choose to put into hand
    char emptyText[100] = "EMPTY";
    
    // player 1 hand
    card player1[HAND];
    char p1name[100];
    
    // player 2 hand
    card player2[HAND];
    char p2name[100];
    int p2drawCard1;
    int p2drawCard2;
    int discardedCard;
    int cardPlayerKeeps;
    
    //center face up card row array
    card faceUpRow[8];

    // populate face up card row array
     for (int i = 0; i < 8; i++) {
    faceUpRow[i].value = 0;
    strcpy(faceUpRow[i].action, emptyText);
    faceUpRow[i].isProtected = 0;
   }
    
    //discard pile
    card discardPile[84];
   
    
    //populate discardPile
   for (int i = 0; i < 84; i++) {
    discardPile[i].value = 0;
    strcpy(discardPile[i].action, emptyText);
    discardPile[i].isProtected = 0;
   }
   
   
    printf(" _______  _______  _______  _______    _______  _______   _________ _______  _______ _________ _        _______ \n");
    printf("(  ____ \\(  ___  )(       )(  ____ \\  (  ___  )(  ____ \\  \\__   __/(  ____ )(  ___  )\\__   __/( (    /|(  ____ \\\n");
    printf("| (    \\/| (   ) || () () || (    \\/  | (   ) || (    \\/     ) (   | (    )|| (   ) |   ) (   |  \\  ( || (    \\/\n");
    printf("| |      | (___) || || || || (__      | |   | || (__         | |   | (____)|| (___) |   | |   |   \\ | || (_____ \n");
    printf("| | ____ |  ___  || |(_)| ||  __)     | |   | ||  __)        | |   |     __)|  ___  |   | |   | (\\ \\) |(_____  )\n");
    printf("| | \\_  )| (   ) || |   | || (        | |   | || (           | |   | (\\ (   | (   ) |   | |   | | \\   |      ) |\n");
    printf("| (___) || )   ( || )   ( || (____/\\  | (___) || )           | |   | ) \\ \\__| )   ( |___) (___| )  \\  |/\\____) |\n");
    printf("(_______)|/     \\||/     \\|(_______/  (_______)|/            )_(   |/   \\__/|/     \\|\\_______/|/    )_)\\_______)\n");
    printf("                                                                                                                \n");

   
    // prompt the user to either load in a file to preset the deck of cards or shuffle them for a regular game
    printf("Use premade deck or shuffle deck?\n");
    printf("Enter 'p' for premade deck or 's' for shuffled deck:\n");
    scanf(" %c", &deckType);
  
    // gets what type of deck user wants to use
    while (deckType != 'p' && deckType != 'P' && deckType != 's' && deckType != 'S') {
        printf("Not a valid input.\n");
        printf("Enter 'p' for premade deck or 's' for shuffled deck: ");
        scanf(" %c", &deckType);
    }
    
    // get sampleDeck into array
       // open file
        FILE *sampleDeck = fopen("sampledeck.txt", "r");
        
        // check if file opens successfully
        if (sampleDeck == NULL) {
            printf("Error opening file\n");
            return -1;
        }
        
        // place sample deck into deck of cards array
        while(!feof(sampleDeck)) {
            fscanf(sampleDeck,"%d %s", &deckOfCards[z].value, deckOfCards[z].action);
            deckOfCards[z].isProtected = 0;
             z++;
        }
        
        // close file
        fclose(sampleDeck);
    
    // shuffle deck if user enters 's'
     if (deckType == 's' || deckType == 'S') {
        shuffleDeck(deckOfCards);
    } 
    
    // deal seven cards to each player
     for (int i = 0; i < 7; i++) {
         player1[i] = deckOfCards[i*2];
         player2[i] = deckOfCards[i*2+1];
     }
     // move card to index 14 because 0-13 have been given to player
     deckIndex = deckIndex + 14;
  
    // get player 1 name
    printf("\nEnter player 1 name: ");
    scanf("%s", p1name);
    
    // get player 2 name
    printf("\nEnter player 2 name: ");
    scanf("%s", p2name);

    // player 1 turn
    drawnCard = drawCards(p1name, player1, deckOfCards, &deckIndex);
    
    // sort each player's hand highest to lowest
    printf("\nThis is %s's hand: ", p1name);
    highLowSort(player1, HAND);
    printPlayerHand(player1);
    
    printf("%s: What card value # do you want to replace? ", p1name);
    scanf("%d", &replaceCard);
    
    placeCardInHand(replaceCard, player1, faceUpRow, drawnCard, deckOfCards, discardPile);
    printf("\n");
    printf("New hand: \n");
    printPlayerHand(player1);
 
    // player 2 turn
    printf("\nThis is %s's hand: ", p2name);
    highLowSort(player2, HAND);
    printPlayerHand(player2);
    
    // he draws two cards
    p2drawCard1 = drawCards(p2name, player2, deckOfCards, &deckIndex);
    p2drawCard2 = drawCards(p2name, player2, deckOfCards, &deckIndex);
    
    // draws two cards and discards one to discard pile
    printf("What card value # do you want to place into your train? The other card will be discarded.\n");
    scanf("%d", &cardPlayerKeeps);
    printf("\n");
    
    // check if player actually enters number of drawn card
    while (cardPlayerKeeps != p2drawCard1 && cardPlayerKeeps != p2drawCard2) {
    printf("Invalid card value. Please enter %d or %d: ", p2drawCard1, p2drawCard2);
    scanf("%d", &cardPlayerKeeps);
    printf("\n");
    }
    
    // sets which card the player is going to keep to the correct drawn card
    // card not chosen will become discarded
    if (cardPlayerKeeps == p2drawCard1) {
        drawnCard = p2drawCard1;
        discardedCard = p2drawCard2;
    } else if (cardPlayerKeeps == p2drawCard2) {
        drawnCard = p2drawCard2;
        discardedCard = p2drawCard1;
    } 
    
    printf("What card do you want to replace?\n");
    scanf("%d", &replaceCard);
    printf("\n");
    

    placeCardInHand(replaceCard, player2, faceUpRow, drawnCard, deckOfCards, discardPile);
    
    printf("New hand: \n");
    printPlayerHand(player2);
    printf("\n");
    
    // card that player didn't choose goes into discard pile
    addToDiscard(deckOfCards, discardPile, discardedCard);
   
    //Player 1 goes. They can either draw from deckOfCards or from faceUpRow
    // Player 2 goes. Same choices
    // Continue until someones card are in ascending order
    
    // Use while loop until someone wins
    while(!winner) {
        
        // switches whos name is outupt each time
        if(count % 2 == 0) {
        strcpy(oscillatingName, p1name);
        } else {
            strcpy(oscillatingName, p2name);
        }
        
        printf("%s: Do you want to draw a card or choose an action card from the face up pile?\n\n", oscillatingName);
        
        if (strcmp(oscillatingName, p1name) == 0) {
             printf("This is your current hand: ");
            printPlayerHand(player1);
        } else if (strcmp(oscillatingName, p2name) == 0) {
            printf("This is your current hand: ");
            printPlayerHand(player2);
        }
        
       
        printf("This is what the face up pile looks like:\n");
        printFaceUpRow(faceUpRow);
        
        printf("\nEnter 'd' for draw or 'a' to use action card: ");
        getchar();
        scanf("%c", &playerMove);
        printf("\n");
        
        // make sure player chooses 'd' or 'a'
        while (playerMove != 'd' && playerMove != 'a' && playerMove != 'D' && playerMove != 'A') {
        printf("Not a valid input.\n");
        printf("Enter 'd' for draw or 'a' to use action card: ");
        getchar();
        scanf("%c", &playerMove);
        printf("\n");
        }
        
        // if player draws card
        if (playerMove == 'd') {
            
            // player 1 turn
             if (strcmp(oscillatingName, p1name) == 0) {
            printf("Current Hand: ");
            printPlayerHand(player1);
                 
            drawnCard = drawCards(oscillatingName, player1, deckOfCards, &deckIndex);
              printf("%s: What card value # do you want to replace?\n", p1name);
              scanf("%d", &replaceCard);
        
            placeCardInHand(replaceCard, player1, faceUpRow, drawnCard, deckOfCards, discardPile);
            
            printf("\n%s's new hand: \n", p1name);
            printPlayerHand(player1);
            printf("\n");
        } 
        // player 2 turn
        else if (strcmp(oscillatingName, p2name) == 0) {
            printf("Current Hand: ");
            printPlayerHand(player2);
                 
            drawnCard = drawCards(oscillatingName, player2, deckOfCards, &deckIndex);
              printf("%s: What card value # do you want to replace?\n", p2name);
              scanf("%d", &replaceCard);
        
            placeCardInHand(replaceCard, player2, faceUpRow, drawnCard, deckOfCards, discardPile);
            
            printf("\n%s's new hand: \n", p2name);
            printPlayerHand(player2);
            printf("\n");
          }
        } 
        // if player chooses to do an action
        else if (playerMove == 'a') {
            // player 1 turn
             if (strcmp(oscillatingName, p1name) == 0) {
                  chooseAction(player1, p1name, player2, p2name, faceUpRow, deckOfCards, &deckIndex, discardPile);
                  printf("%s's new hand: \n", p1name);
                  printPlayerHand(player1);
                  printf("\n");
       
                  
             } 
             // player 2 turn
             else if (strcmp(oscillatingName, p2name) == 0) {
                 chooseAction(player2, p2name, player1, p1name, faceUpRow, deckOfCards, &deckIndex, discardPile);
                 printf("%s's new hand: \n", p2name);
                 printPlayerHand(player2);
                 printf("\n");
             }
          
        }
    
        
        // check who wins
        if (checkWin(player1)) {
    printf("  _______      ___      .___  ___.  _______      ______   ____    ____  _______ .______      \n");
    printf(" /  _____|    /   \\     |   \\/   | |   ____|    /  __  \\  \\   \\  /   / |   ____||   _  \\     \n");
    printf("|  |  __     /  ^  \\    |  \\  /  | |  |__      |  |  |  |  \\   \\/   /  |  |__   |  |_)  |    \n");
    printf("|  | |_ |   /  /_\\  \\   |  |\\/|  | |   __|     |  |  |  |   \\      /   |   __|  |      /     \n");
    printf("|  |__| |  /  _____  \\  |  |  |  | |  |____    |  `--'  |    \\    /    |  |____ |  |\\  \\----.\n");
    printf(" \\______| /__/     \\__\\ |__|  |__| |_______|    \\______/      \\__/     |_______|| _| `._____|\n");
    
        
        printf("\n\n%s has won the game!", p1name);
        winner = true;
        return 0;
         }
    
        if (checkWin(player2)) {
    printf("  _______      ___      .___  ___.  _______      ______   ____    ____  _______ .______      \n");
    printf(" /  _____|    /   \\     |   \\/   | |   ____|    /  __  \\  \\   \\  /   / |   ____||   _  \\     \n");
    printf("|  |  __     /  ^  \\    |  \\  /  | |  |__      |  |  |  |  \\   \\/   /  |  |__   |  |_)  |    \n");
    printf("|  | |_ |   /  /_\\  \\   |  |\\/|  | |   __|     |  |  |  |   \\      /   |   __|  |      /     \n");
    printf("|  |__| |  /  _____  \\  |  |  |  | |  |____    |  `--'  |    \\    /    |  |____ |  |\\  \\----.\n");
    printf(" \\______| /__/     \\__\\ |__|  |__| |_______|    \\______/      \\__/     |_______|| _| `._____|\n");
       
        
        printf("\n\n%s has won the game!", p2name);
        winner = true;
        
        
        
        return 0;
        }
        
        // check if there are duplicates in faceUpRow
        // do this while it is true, because there could be multiple duplicates
        while (discardDuplicates(faceUpRow, discardPile, deckOfCards)) {
            printf("Discard Pile had duplicates, so we removed both cards\n");
        } 
    
    // switches who's turn it is    
    count++;
    
    // put discard pile back into deckOfCards when it runs out 
    if (deckIndex == 84) {
        deckIndex = 0;  // set deck index back to zero
        
        
        for (int i = 0; i < 84; i++) {
            deckOfCards[i] = discardPile[i];
            // reset discard pile to empty
            discardPile[i].value = 0;
            discardPile[i].isProtected = 0;
            strcpy(discardPile[i].action, "EMPTY");
        }
        
        // shuffles cards 
         shuffleDeck(deckOfCards);
    }

    }
    
    return 0;
}
