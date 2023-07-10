#include <bits/stdc++.h>
typedef long long ll;
#define nl "\n"
#define mod 1000000007
#define ye cout<<"YES"<<nl
#define no cout<<"NO"<<nl
#define inp(n) cin>>n
#define FC ios_base::sync_with_stdio(false);cin.tie(NULL);
#define forl(i,n) for(ll i=0;i<n;i++)
#define _inp(arr,n) for(ll i=0;i<n;i++)cin>>arr[i]
#define _print(arr,n) for(ll i=0;i<n;i++)cout<<arr[i]<<" "
#define all(a) a.begin(),a.end()
#define pb push_back 
#define setall(arr,n,p) for(ll i=0;i<n;i++)arr[i]=p;

using namespace std;

void printSudoku(int arr[9][9]){
    cout << "--------------------------" << endl;

    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            cout << arr[i][j] <<" " ;
        }
        cout << endl;
    }

    cout << "--------------------------" << endl;

}

bool check2 (int arr[9][9]){
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            if(arr[i][j]==0)return true;
        }
    }
    return false;
}

bool check(vector<vector<int>>&boardc){
    vector<int>hsh1(10,0);
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            hsh1[boardc[i][j]]++;
        }
        for(int k=1;k<=9;k++){
            if(hsh1[k]>1)return true;
            hsh1[k]=0;
        }
        // hsh1.clear();
    }

    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            hsh1[boardc[j][i]]++;
        }
        for(int k=1;k<=9;k++){
            if(hsh1[k]>1)return true;
            hsh1[k]=0;
        }
        // hsh1.clear();
    }
    
    return false;
}

bool canPlace(int arr[9][9], int row, int col, int num){
    if(arr[row][col]!=0) return false;
    int gridy= (row/3) * 3, gridx= (col/3) * 3;

    for(int i=0;i<9;i++){
        if(arr[i][col]==num) return false;
        if(arr[row][i]==num) return false;
        if(arr[gridy+i/3][gridx+i%3]==num) return false;
    }
    return true;
    
}

std::vector<int> findPlaceables(int arr[9][9] , int row, int col){
     vector<int> cps;
     for(int i=1;i<=9;i++){
         if(canPlace(arr, row, col, i)){
             cps.push_back(i);
         }
     }
     return cps;
}

void copyArr(int arr[9][9], int arrcpy[9][9]){
     for(int i=0;i<9;i++){
         for(int j=0;j<9;j++){
             arrcpy[i][j]=arr[i][j];
         }
     }
}
void nextCell(int arr[9][9], int row, int col, int& nrow, int& ncol){
    //int index=9*9;
    for(int i= row*9+col+1;i<81;i++){
        if(arr[i/9][i%9]==0){
            nrow=i/9;
            ncol=i%9;
            break;
        }
    }
}

bool solveSudoku(int arr[9][9], int row, int col){
    //system("cls");
    //printSudoku(arr);
    if(row>8) return true;
    if(arr[row][col]!=0){
        int nextRow, nextCol;
        nextCell(arr,row,col, nextRow, nextCol);
        return solveSudoku(arr, nextRow, nextCol);
            
    }

    std::vector<int> placeables= findPlaceables(arr, row, col);
    if(placeables.size()==0) return false;

    for(int i=0;i< placeables.size();i++){
        int n= placeables[i];
        int arrcpy[9][9];
        copyArr(arr, arrcpy);

        int nextRow, nextCol;
        arrcpy[row][col]=n;
        nextCell(arrcpy,row,col, nextRow, nextCol);
        if(solveSudoku(arrcpy, nextRow, nextCol)){
            copyArr(arrcpy, arr);
            return true;
        }
    }
    return false;

} 

int main(int argc, char** argv){

    int board[9][9];
    vector<vector<int>>boardcopy(9,vector<int>(9,0));
    bool flag=false;
    cout << " Give Sudoku to solve:" << endl;
    cout << " Rules for input :- " << endl;
    cout << "   1) Enter 9 rows , each row must contain 9 space separated integers 0<=n<=9 " << endl;
    cout << "   2) Empty Cells should contain number 0 " << endl;
    cout << "   3) No row or column should contain one number more than once " << endl;
    cout << "--------------------------" << endl;
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            cin >> board[i][j];
            boardcopy[i][j]=board[i][j];
            if(board[i][j]>9 || board[i][j]<0)flag=true;
        }
    }

    if(flag || check(boardcopy)){
        cout << "--------------------------" << endl;
        cout<<"INVALID INPUT"<<endl; 
    }

    else{
        solveSudoku(board, 0, 0);
        if(check2(board)){
            cout << "--------------------------" << endl;
            cout<<"NO CORRECT SOLUTION EXISTS"<<endl; 
        }
        else{
            cout << "--------------------------" << endl;
            cout << "Solved Sudoku is:" << endl;
            printSudoku(board);
        }
    }

    system("pause");
    return 0;
}