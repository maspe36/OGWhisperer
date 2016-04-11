# Whisperer
A fun fast paced card game that takes inspiration from Yu-gi-oh, Magic: The Gathering, and Hearthstone. 

Whisperer
By Sam Privett

Terms
•	Stack
  o	Abstract location in which all card effects enter to resolve. When a card effect triggers it enters the stack. If another card effect triggers in response it goes on top of the first card in. The stack operates in a last in first out order. The last effect that enters resolves first and then all other effects resolve sequentially in the order that they entered the stack.
•	Battlefield
  o	Overall playing field. All other fields are contained in this field. Area of play that cards enter. Combat between souls occurs in this area. 
•	Banished
  o	Cards “removed” from the game. When a card is entering this field it is “Vanquished.”
•	Graveyard
  o	When a card is destroyed, it enters the graveyard unless otherwise specified. 
•	Deck
  o	Containment field of all the cards yet to be drawn by a player. 
•	Hand
  o	Any card that is drawn enters the hand. 

Devotion
Devotion is measured by 2 metrics, available devotion and total devotion. Devotion increases by 1 every time a card from that element is played. For example, a fire element card being summoned or cast increases total devotion to fire by 1. When a player casts or summons a card, all devotion to other elements decreases by 1 while the devotion element of the card casted or summoned increases by 1. When a conflict happens between devotion of elements, the element being summoned or cast increases by 1, however the other devotion will decrease by the cost of the card being cast (See table below for all conflicts between devotions.) All cards contain devotion costs. Unless stated otherwise, the only way to have a card enter play is by paying its devotion cost. Paying a devotion cost decreases total available devotion by the cost specified on the card. 

Card Types
•	Souls
  o	Souls have attack and defense properties. 
  o	A soul may only be summoned by paying its devotion cost, or by other card effect. 
  o	Souls participate in combat. 
  o	A soul may only leave the battlefield as a result of combat or card effect.
  o	On the turn a soul is summoned it cannot attack a player, only opposing souls.
  o	Souls may possess 0 or more 1 word effects (i.e. introduce, rush.) 
•	Swifts
  o	To cast swifts, players must pay the devotion cost. 
  o	Swifts may only be played on your turn and may not be cast while there is an effect waiting to resolve on the stack 
  o	When cast, a swift’s effect enters the stack. 
  o	When a swift has resolved, it is sent to the graveyard.
•	Constants
  o	Constants may only be cast by paying the devotion cost labeled on the card. 
  o	As a constant enters the battlefield it enters the stack. 
  o	Constants have 2 kinds of effects. 
    	Continuous effects (i.e. All water souls gain +1/+1)
    	Continuous effects do not enter the stack
    	trigger effects (i.e. Once per turn give a water soul +1/+1)
    	Trigger effects do enter the stack.  

One Word Effects
•	Rush
  o	The turn a creature enters the battlefield, they may attack players as well as souls.
•	Overwhelm
  o	During combat between an attacking soul with higher attack strength than the defending soul’s defense, inflict the difference as    damage to your opponent.
•	Introduce
  o	Triggers an effect specified on the card when a soul enters the battlefield. This can be from anywhere.
•	Downfall
  o	Triggers an effect when a soul dies.
•	Soulwalk
  o	Souls with soulwalk may attack a player directly. They are still unable to attack a player the turn they are summoned unless they   have rush.
•	High-Tide
  o	This cost may be paid for a card if the card is drawn and played before any other card. For example if a player draws a 4 cost      card with a high-tide of 3, if they cast that card before any other card they may pay the high-tide cost instead.
•	Stasis
  o	Souls with stasis cannot attack or be destroyed for the duration of their stasis. A stasis lasts X turns. When the player who cast   the stasis card’s turn starts, it counts towards this number. Souls in stasis do not prevent other souls from attacking a player      directly. 
•	Sequence
  o	Cards may be played with a sequence cost if there was another card played previously during that turn. The only cards that count    towards a sequence cost are ones that the player controls who is trying to cast a card for its sequence cost.
•	Burst
  o	Burst is an alternate cost a player may pay when casting or summoning a card. When the card is casted or summoned the player who    casted or summoned the card lose devotion equal to half of the burst cost. 
•	Recursion
  o	When a player casts a card with recursion, that cards owner vanquishes souls until the total devotion of souls vanquished is        greater than or equal to the devotion cost of the card with recursion.
•	Heavenborn
  o	When a player casts a card with heavenborn return souls from that players battlefield back to the deck equal to or greater than     the cost of the card with heavenborn.


Combat

•	Souls cannot attack enemy player(s) unless they control no souls or because of card effect.
•	A soul declaring an attack on another soul, deals damage to the target soul equal to the attacking soul’s attack.
•	A soul that takes damage greater than its defense, is destroyed.
•	If a soul takes damage equal to its defense, the battle is considered a draw, and no damage occurs.
•	A soul declaring an attack enters the stack.


