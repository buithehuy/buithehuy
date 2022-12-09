/* game tictactoe
1.AI engine
    + state representation : vector<vector<char>> 3x3
    + checking if game is end
    + detect winner if game end
    + render (text screen)
    + valid moves
        - detect current player
        - calculate valid move
    + calculate state score
        - final state score
        - note final state score
    + caclculate best move
2.User interface
    + asking X or O
    + input move cardinate from 0
    + response if illegal move
    + response game result when end
    + print machine's move
*/
#include <iostream>
#include<vector>
using namespace std;

const int SIZE = 3;
// state representation
typedef vector<vector<char> > GameState;

// function IsEnd (checking if game is end)
// input : GameState 
// output : true if end game else false
bool IsEnd(GameState game)
{
    for(int i = 0 ; i < 3 ; i++){
        // check cols 
        if(game[i][0] == game[i][1] && game[i][0] == game [i][2] && game[i][0] != '.') return true;
        // check rows
        if(game[0][i] == game[1][i] && game[0][i] == game [2][i] && game[0][i] != '.') return true;
        

    }
    // check diagonals
        if(game[0][0] == game[1][1] && game[0][0] == game[2][2] && game[0][0] != '.') return true;
        if(game[0][2] == game[1][1] && game[0][2] == game[2][0] && game[0][2] != '.') return true;
    // check full board
    for(int i = 0 ; i < 3 ; i++){
        for(int j = 0 ; j < 3 ; j++){
            if(game[i][j] ==  '.') return false;
        }

    }
    return true;
}
// function checkWinner : detect winner if game end
// input:GameState
// ouput: 1 if winner is X , -1 if winner is O , 0 if draw
int checkWinner(GameState game){
    for(int i = 0 ; i < 3 ; i++){
        // check cols 
        if(game[i][0] == game[i][1] && game[i][0] == game [i][2] && game[i][0] != '.' ) return  game[i][0] == 'X' ? 1 : -1 ;
        // check rows
        if(game[0][i] == game[1][i] && game[0][i] == game [2][i] && game[0][i] != '.' ) return game[0][i] == 'X'  ? 1 : -1 ;
        

    }
    // check diagonals
        if(game[0][0] == game[1][1] && game[0][0] == game[2][2] ) return game[0][0] == 'X' ? 1 : -1 ;
        if(game[0][2] == game[1][1] && game[0][2] == game[2][0] ) return game[0][2] =='X' ? 1 : -1;
    
    return 0;
}
// function renderGame : render (text screen)
// input : StateGame
// output: A board Game current
void renderGame(GameState game){
    for(int i = 0 ; i < 3 ; i++){
        for(int j = 0 ; j < 3 ; j++){
            cout << "|  " << game[i][j] << "  ";
        }
        cout << "|" << endl << "|-----|-----|-----|" << endl;
    }
    cout << endl;
}
// valid moves
        // function NextPlayer : detect current player
        // input : GameState 
        // ouput : next player
char NextPlayer(GameState game ){
    int ceelempty = 0 ;
    for(int i = 0 ; i < 3 ; i++){
        for(int j = 0 ; j < 3 ; j++){
            if(game[i][j] == '.' ) ceelempty++;
        }
    }
    return (ceelempty % 2 == 1) ? 'X' : 'O' ;
}

    // funtion copy : copy nextState 
    // input : GameState , place play( i , j) , char
    // ouput : nextState
GameState copy(GameState game,int i , int j ,char player){
    GameState nw_State = GameState(3, vector<char>(3, ' '));;
    for(int i = 0 ; i < 3 ; i++ ){
        for(int j = 0 ; j < 3 ; j++){
            nw_State[i][j] = game[i][j];
        }
    }
    nw_State[i][j] = player;
    return nw_State;
}

        // function NexStates : calculate valid move
        // input : GameState
        // ouput : nextStates of Game
vector<GameState> NextStates(GameState game){
    char player = NextPlayer(game);
    vector<GameState> states ;
    for(int i = 0 ; i < 3 ; i++){
        for(int j = 0 ; j < 3 ; j++){
            if(game[i][j] == '.'){
                GameState nw_State = copy(game,i,j,player); // copy nextState 
                states.push_back(nw_State);
            }
            
        }

    }
    return states;
}
// + calculate state score
    // Function GetScoreFinalGame : get final state score
    // input : GameState
    // output : score of final Game ( 1 is X win , -1 is O win , 0 is draw)

int GetScoreFinalGame(GameState game ){
    // check rows
    for (int i = 0; i < SIZE; i++)
        if (game[i][0] == game[i][1] && game[i][0] == game[i][2] && game[i][0] != ' ') 
            return game[i][0] == 'X' ? 1 : -1;
    // check cols
    for (int i = 0; i < SIZE; i++)
        if (game[0][i] == game[1][i] && game[0][i] == game[2][i] && game[0][i] != ' ')
            return game[0][i] == 'X' ? 1 : -1;
    if (game[0][0] == game[1][1] && game[0][0] == game[2][2] && game[0][0] != ' ')
        return game[0][0] == 'X' ? 1 : -1;
    if (game[0][2] == game[1][1] && game[0][2] == game[2][0] && game[0][2] != ' ')
        return game[0][2] == 'X' ? 1 : -1;;
    return 0;
}
    
    // function getScore caclculate best move
    // input : GameState
    // output : best Sore and best State

pair<int , GameState> getScore(GameState game){
    if(IsEnd(game)){
        return make_pair(GetScoreFinalGame(game),game);
    }
    char player = NextPlayer(game);
    vector<GameState> States = NextStates(game);
    int bestScore = - 10 ;
    GameState bestState;
    for(GameState st : States){
        pair<int,GameState> p = getScore(st);
        int score = p.first;
        if(player == 'X'){
            if(bestScore < score || bestScore == -10){
            bestScore = score ;
            bestState = st;
            }
        }else{
            if(bestScore > score || bestScore == -10){
                bestScore = score;
                bestState = st;
            }
        }
    }
    return make_pair(bestScore,bestState);
}

pair<int, int> getComputerPlay(GameState s)
{
    pair<int, GameState> p = getScore(s);
    int score = p.first;
    GameState newState = p.second;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (newState[i][j] != s[i][j]) return make_pair(i, j);
        }
    }
    return make_pair(-1, -1);
}
int main(){
GameState s = GameState(3, vector<char>(3, '.'));
    char humanPlayer = ' ', currentPlayer = 'X';
    cout << "Choose your player (X or O): ";
    cin >> humanPlayer;
    cout << "You are " << humanPlayer << " player" << endl;

    renderGame(s);
    while (true) {
        int i = -1, j = -1; 
        if (humanPlayer == currentPlayer) {
        while(true){
                cout << "Enter your play: ";
                cin >> i >> j;
                if(s[i][j] != '.'){
                    cout << "Play again"<< endl ;
                }
                else {cout << "You play (" << i << ", " << j << ")"<<endl;
                break;
                }
            }
            // TODO check legal move
        } else {
            pair<int, int> move = getComputerPlay(s);
            i = move.first;
            j = move.second;
            cout << "computer play (" << i << ", " << j << ")" << endl;
        }
        s = copy(s,i, j, currentPlayer);
        renderGame(s);

        currentPlayer = currentPlayer == 'X' ? 'O' : 'X';
        if (IsEnd(s)) {
            int score = GetScoreFinalGame(s);
            if (score > 0) {
                cout << "X won" << endl; 
            } else if (score < 0) {
                cout << "X lost" << endl; 
            } else {
                cout << "A draw" << endl; 
            }
            break;
        }
    }
}