goal([0,0,0]).
en([A,B,_]):-
    A>B,
    B>0.
en([A,B,_]):-
    B<3,
    B>A.

f10([A,B,1],[C,B,0]):-
    A>=1,
    C is A-1.
f20([A,B,1],[C,B,0]):-
    A>=2,
    C is A-2.
f11([A,B,1],[C,D,0]):-
    A>0,
    B>0,
    C is A-1,
    D is B-1.
f01([A,B,1],[A,D,0]):-
    B>=1,
    D is B-1.
f02([A,B,1],[A,D,0]):-
    B>=2,
    D is B-2.
b10([A,B,0],[C,B,1]):-
    A<3,
    C is A+1.
b20([A,B,0],[C,B,1]):-
    A<2,
    C is A+2.
b11([A,B,0],[C,D,1]):-
    A<3,
    B<3,
    C is A+1,
    D is B+1.
b01([A,B,0],[A,D,1]):-
    B<3,
    D is B+1.
b02([A,B,0],[A,D,1]):-
    B=<1,
    D is B+2.

ts(A,B):- f10(A,B),\+ en(B).
ts(A,B):- f20(A,B),\+ en(B).
ts(A,B):- f11(A,B),\+ en(B).
ts(A,B):- f01(A,B),\+ en(B).
ts(A,B):- f02(A,B),\+ en(B).
ts(A,B):- b10(A,B),\+ en(B).
ts(A,B):- b20(A,B),\+ en(B).
ts(A,B):- b11(A,B),\+ en(B).
ts(A,B):- b01(A,B),\+ en(B).
ts(A,B):- b02(A,B),\+ en(B).

dfs(A,P,[A|P]):- goal(A).
dfs(A,P,Path):- ts(A,B),A\=B,\+ member(B,P),dfs(B,[A|P],Path).