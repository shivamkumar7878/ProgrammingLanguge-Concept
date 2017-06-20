/* Activity 3 (original) */

weather0(precipitation) :-
	weather0(raining);
	weather0(snowing).
weather0(snowing) :-
	weather0(freezing),
	weather0(precipitation).
weather0(raining) :-
	weather0(not(freezing)),
	weather0(precipitation).
weather0(snowing).


/* Activity 3 (modified) */

weather1(precipitation) :- weather1(raining).
weather1(precipitation) :- weather1(snowing).
weather1(snowing).
weather1(snowing) :-
	weather1(freezing),
	weather1(precipitation).
weather1(freezing) :-
	weather1(snowing).
weather1(raining) :-
	weather1(not(freezing)),
	weather1(precipitation).


/* Activity 4 */

mammal(horse).
arms(horse,0).
arms(X,2) :- mammal(X), legs(X,2).
arms(X,0) :- mammal(X), legs(X,4).
legs(X,4) :- mammal(X), arms(X,0).
legs(X,2) :- mammal(X), arms(X,2).


/* Activity 5 */

parent(bill, jill).
parent(bill, sarah).
parent(jill, sam).
parent(jill, ana).
parent(sarah, jan).
parent(sarah, smith).
grandparent(A,C) :- parent(A,X), parent(X,C).
sibling(A,B) :- parent(X,A), parent(X,B), not(A=B).
cousin(A,B) :- parent(X,A), parent(Y,B), sibling(X,Y), not(A=B).


/* Activity 6 */

gcd(U, 0, U).
gcd(U, V, W) :- not(V=0), Z is (U mod V), gcd(V,Z,W).

/* Activity 7 */

lastItem([X], X).
lastItem([_|T], Y) :- lastItem(T, Y).
