class Solution {
public:
    bool canAliceWin(int n) {
        int stones = 10;
        bool aliceTurn = true;
        while (n >= stones) {
            n -= stones;
            stones--;
            aliceTurn = !aliceTurn;
        }
        // The player whose turn it is cannot move, so they lose
        // Alice wins if it's Bob's turn when someone can't move
        return !aliceTurn;
    }
};