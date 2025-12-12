# Game of Trains (C)

## Overview
Game of Trains is a **terminal-based, two-player strategy card game**
implemented in **C**. Players build a “train” of numbered cards and use
action cards to rearrange their own train or disrupt their opponent’s.
The goal is to be the first player whose cards are in ascending order.

This project was developed as a comprehensive C programming assignment
and demonstrates structured program design, custom data modeling, and
state-based game logic.

---

## Core Features
- Two-player, turn-based gameplay
- Custom card actions that manipulate player hands
- Discard pile that refills the deck when exhausted
- ASCII-based card graphics for terminal display
- Deterministic or randomized deck loading

---

## Data Structures & Design
- A custom `card` struct represents game entities, storing card value,
  action type, and protection state.
- Fixed-size arrays of cards are used to model the deck, player hands,
  face-up action row, and discard pile.
- Game flow is controlled by a loop-driven **state machine** that manages
  player turns, actions, and win conditions.
- Core algorithms include:
  - Fisher–Yates shuffle for deck randomization
  - Insertion sort for ordering player hands
  - Linear search for card lookup and state transitions

---

## How to Play (Quick Start)

### Setup
1. Compile the program:
   ```bash
   gcc main.c card.c -o game_of_trains
2. Run the game:
   ./game_of_trains
3. Choose whether to use a premade deck or a shuffled deck
4. Enter both player names

## Gameplay
- Each player starts with a **hand of 7 cards**, representing their train.
- On each turn, a player may:
  - **Draw a card** from the deck and replace a card in their train, or
  - **Play an action card** from the face-up action row.
- Action cards allow players to:
  - Swap or shift cards within their own train
  - Remove or affect cards in an opponent’s train
  - Protect specific cards from being modified
- Used action cards are moved to the discard pile and replaced with new
  cards from the deck.

Gameplay alternates between players until a winning condition is met.

## Winning
A player wins the game when their train (hand of cards) is in strictly
ascending order from left to right at the end of their turn

## Repository Structure
- main.c          Main game loop and state management
- card.c          Card logic, actions, and helper functions
- card.h          Card struct definition and function declarations
- sampledeck.txt  Preset deck used for deterministic gameplay

## Official Rules
Game of Trains is based on the commercially available card game.
The official rules can be found here:

🔗 https://www.ultraboardgames.com/game-of-trains/game-rules.php

This implementation follows the core mechanics of the original game,
with adaptations made for terminal-based gameplay. The official game can be played with up to 4 players, however, this version was created for only 2 players.




