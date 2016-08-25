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

## Devotion
Devotion is defined by 2 metrics, available devotion and total devotion. Devotion increases by 1 every time a card from that element is played. For example, a fire element card being summoned or cast increases total devotion to fire by 1. When a player casts or summons a card, all devotion to other elements decreases by 1 while the devotion element of the card casted or summoned increases by 1. When a conflict happens between devotion of elements, the element being summoned or cast increases by 1, however the other devotion will decrease by the cost of the card being cast (See table below for all conflicts between devotions.) All cards contain devotion costs. Unless stated otherwise, the only way to have a card enter play is by paying its devotion cost. Paying a devotion cost decreases total available devotion by the cost specified on the card.

## Card Types
* Souls
  * Souls have attack and health properties. 
  * A soul may only be summoned by paying its devotion cost, or by other card effect. 
  * Souls participate in combat. 
  * A soul may only leave the battlefield as a result of combat or card effect.
  * On the turn a soul is summoned it cannot attack a player, only opposing souls.
  * Souls may possess 0 or more 1 word effects (i.e. introduce, rush.) 

 * Swifts
  * To cast swifts, players must pay the devotion cost. 
  * Swifts may only be played on your turn and may not be cast while there is an effect waiting to resolve on the stack 
  * When cast, a swift’s effect enters the stack. 
  * When a swift has resolved, it is sent to the graveyard.

* Constants
  * Constants may only be cast by paying the devotion cost labeled on the card. 
  * As a constant enters the battlefield it enters the stack. 
  * Constants have 2 kinds of effects. 
   * Continuous effects (i.e. All water souls gain +1/+1)
   * Continuous effects do not enter the stack
   * Trigger effects (i.e. Once per turn give a water soul +1/+1)
   * Trigger effects do enter the stack.  

## One Word Effects
* Rush
  * The turn a creature enters the battlefield, they may attack players as well as souls.
* Overwhelm
  * During combat between an attacking soul with higher attack strength than the defending soul’s health, inflict the difference as damage to your opponent.
* Introduce
  * Triggers an effect specified on the card when a soul enters the battlefield. This can be from anywhere.
* Downfall
  * Triggers an effect when a soul dies.
* Soulwalk
  * Souls with soulwalk may attack a player directly. They are still unable to attack a player the turn they are summoned unless they have rush.
* Flurry
  * Souls with flurry may attack X number of times per turn. For example a soul with Flurry 3 may declare 3 attacks in a single turn.
* High-Tide
  * This cost may be paid for a card if the card is drawn and played before any other card. For example if a player draws a 4 cost card with a high-tide of 3, if they cast that card before any other card they may pay the high-tide cost instead.
* Stasis
  * Souls with stasis cannot attack or be destroyed for the duration of their stasis. A stasis lasts X turns. When the player who cast the stasis card’s turn starts, it counts towards this number. Souls in stasis do not prevent other souls from attacking a player directly. 
* Sequence
  * Cards may be played with a sequence cost if there was another card played previously during that turn. The only cards that count towards a sequence cost are ones that the player controls who is trying to cast a card for its sequence cost.
* Burst
  * Burst is an alternate cost a player may pay when casting or summoning a card. When the card is casted or summoned the player who casted or summoned the card lose devotion equal to half of the burst cost. 
* Recursion
  * When a player casts a card with recursion, that cards owner vanquishes souls until the total devotion of souls vanquished is greater than or equal to the devotion cost of the card with recursion.
* Heavenborn
  * When a player casts a card with heavenborn return souls from that players battlefield back to the deck equal to or greater than the cost of the card with heavenborn.

## Combat
*	Souls cannot attack enemy player(s) unless they control no souls or because of card effect.
*	A soul declaring an attack on another soul, deals damage to the target soul equal to the attacking soul’s attack.
*	The defending soul deals damage equal to its attack to the attacking soul’s health.
*	A soul that takes damage greater than its health, is destroyed.
*	A soul that takes damage will retain damage unless otherwise stated (For ex. Give a soul +N health)
