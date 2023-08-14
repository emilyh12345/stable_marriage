#include <iostream>
using namespace std;

void nextWomen(int q[], int &c); 
void nextMan(int q[], int &c);
void backtrack(int q[], int &c);
void print(int q[], int c);
bool isStable(int q[], int c); 

bool isStable(int q[], int c){
    	for (int i = 0; i < c; i++){ //for loop to make sure the women isnt already married
        	if (q[i] == q[c]) return false;
    	}
    	int mp[3][3]={ //mens preferance tables, 0 is highest rating and 2 is the lowest rating
        	{0,2,1}, //man 0 
        	{0,2,1}, //man 1
        	{1,2,0}}; //man 2 
    	int wp[3][3]={ //womens preferance tables
        	{2,1,0}, //women 0
        	{0,1,2}, //women 1
        	{2,0,1}}; //women 2
    	int nm=c; //initialize new man to column number 
    	for(int pm=0; pm<nm; pm++){ //for loop to check if each pairing is stable 
        	int pw=q[pm]; //initialize previous women to be who previous man is pairing with
        	int newWomen=q[nm]; //initialize new women to be who new man is paired with 
        	if (mp[pm][newWomen]<mp[pm][pw] && wp[newWomen][pm]<wp[newWomen][nm]) return false; // check if previous man prefers new women over previous women(current partner) and the new women prefers him (previous man) over her current partner (new man) then its unstable
        	if (mp[nm][pw]<mp[nm][newWomen] && wp[pw][nm]<wp[pw][pm]) return false; //check if new man prefers previous women over his current partner and the previous women prefers the new man over his current partner then its unstable
    	}
    	return true; //if all tests passed then return true
}

void nextMan(int q[], int &c) { //function to go to check next man
	c++; //increment man since to check for his stable pairing
    	if (c == 3) {
		print (q,c); //if at man 3, we have a solution so print it
	}else{
		nextWomen(q, c); //otherwise check next women since haven't found a solution yet
	}
}

void nextWomen(int q[], int &c) {
	q[c]++; //increment the # women up to to check if thats a stable pairing
	if (q[c] == 3) { //if up to women 3 then backtrack since tried all women and those pairings didn't work
        	q[c]=-1; //reset to women -1 so can later increment to 0
        	backtrack(q,c); 
    	}
	if (isStable(q, c)) nextMan(q,c); //if the pairing is stable(passes all tests) increment man to check for next mans stable pairing  
    	nextWomen(q,c); //if the pairing isn't stable then increment the women to test if that is a stable pairing
}

void backtrack(int q[], int &c) {
	c--; //decrease column to go to previous man 
    	if (c == -1) exit(1); //if get to nonexistent column -1 terminate since weve found all stable pairings
	nextWomen(q, c); //otherwise try next women since haven't found all stable pairings
}

void print(int q[], int c){
	static int sol = 0; 
    	cout << "Solution #" << ++sol << ":\n";
    	cout << "man 0 matches with women " << q[0] << ", man 1 matches with women " << q[1] << ", man 2 matches with women " << q[2] << endl; //print stable pairings
    	backtrack(q,c);
}

int main() {
    	int q[3] = {-1, -1, -1}, c = -1; //initalize array and column(man) to store -1s so that we can increment to begin at 0 later
	nextMan(q, c); 
    	return 0;
}
