# Whisperer
A fun fast paced card game that takes inspiration from Yu-gi-oh, Magic: The Gathering, and Hearthstone. 

## Terms
You'll see the following terms throughout the code and the cards
* Stack 
  * Abstract location in which all card effects resolve, last in first out.
* Field
  * Overall playing field. Other fields are contained here. 
* Banished
  * Cards "removed" from the game. When a card is entering this field it is "Vanquished"
* Graveyard
  * When a card is destroyed, it enters the graveyard unless otherwise specified.
* Deck
  * Containment field of all the cards a player has immediate non effect access to. 40 cards.
* Hand
  * Any Card that is drawn enters the hand. Maximum hand size is 8. If a player draws a card and the yhave 8 or more cards in hand, send that card to the graveyard.
