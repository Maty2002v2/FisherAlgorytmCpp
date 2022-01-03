#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

/*
1 wie¿a
2 koñ
3 goniec
4 król
5 dama

parzyste pola czarne
nieparzyste bai³e
*/
class FischerChessboard {
	private:
		vector<int>chessboard;
		int blackBishopPosition;
		int whiteBishopPosition;
		int kingPosition;
		int firstRookPosition;
		int secoundRookPosition;
		int queenPosition;
		
		void drawChessboard();
		void drawBishop();
		void drawKing();
		void drawRook();
		void drawQueen();
		void drawKNight();
		int countAvailablePlaces();
		
	public:
		FischerChessboard();
		void init();
		void clear();
		void schowChessboard();
};

FischerChessboard::FischerChessboard() {
	this->init();
	this->drawChessboard();
}

void FischerChessboard::init() {
	for (int i = 0; i < 8; i++) {
		chessboard.push_back(0);
	};
}

void FischerChessboard::clear() {
	for (int i = 0; i < 8; i++) {
		chessboard[i] = 0;
	};
}

void FischerChessboard::schowChessboard() {
	for (int i = 0; i < 8; i++) {
		cout<<chessboard[i]<<", ";
	};
}

void FischerChessboard::drawChessboard() {
	this->drawBishop();
	this->drawKing();
	this->drawRook();
	this->drawQueen();
	this->drawKNight();
}

void FischerChessboard::drawBishop() {
	int blacBishop, blacBishopPosition, whiteBishop, whiteBishopPosition;
	
	blacBishop = 3;
	whiteBishop = 3;
	
	blacBishopPosition = rand()%7;
	whiteBishopPosition = rand()%7;
	
	while (
		blacBishopPosition == whiteBishopPosition || 
		whiteBishopPosition % 2 == 0 ||
		blacBishopPosition % 2 == 1 ||
		whiteBishopPosition == 0
	) {
		blacBishopPosition = rand()%7;
		whiteBishopPosition = rand()%7;
	};
	
	this->chessboard[blacBishopPosition] = blacBishop;
	this->chessboard[whiteBishopPosition] = whiteBishop;
	
	this->blackBishopPosition = blacBishopPosition;
	this->whiteBishopPosition = whiteBishopPosition;
}

void FischerChessboard::drawKing() {
	int kingPosition, king, startRange, endRange;
	
	startRange = 1;
	endRange = 6;
	king = 4;
	
	if (this->blackBishopPosition == 0) {
		startRange = 2;
	}
	
	if (this->whiteBishopPosition == 7) {
		endRange = 5;
	}
	
	kingPosition = startRange + rand()%endRange;
	
	while (
		kingPosition == this->blackBishopPosition || 
		kingPosition == this->whiteBishopPosition ||
		kingPosition == 0 ||
		kingPosition == 7
	) {
		kingPosition = 1 + rand()%7;
	}
	
	this->chessboard[kingPosition] = king;
	this->kingPosition = kingPosition;
}

void FischerChessboard::drawRook() {
	int firstRook, firstRookPosition, secoundRook, secoundRookPosiiton, leftAttitude, rightAttitude;
	string direction = "left";
	
	firstRookPosition = -1;
	secoundRookPosiiton = -1;
	leftAttitude = 0;
	rightAttitude = 0;
	firstRook = 1;
	secoundRook = 1;
	
	for (int i = 0; i < this->chessboard.size(); i++) {
		if (this->chessboard[i] == 4) {
			direction = "right";
		} else {
			if (direction == "left") {
				if (this->chessboard[i] == 0) {
					leftAttitude++;
				}
			} else {
				if (this->chessboard[i] == 0) {
					rightAttitude++;
				}	
			}	
		}
	}
	
	if (leftAttitude == 1) {
		vector<int>freePlace;
		int drawnNumberLeft;
		bool flag = false;
		
		for (int i = 0; i < this->chessboard.size(); i++) {
			if (this->chessboard[i] == 0) {
				firstRookPosition = i;
				this->chessboard[firstRookPosition] = firstRook;
				break;
			}
		}
		
		for (int i = 0; i < this->chessboard.size(); i++) {
			if (this->chessboard[i] == 4) {
				flag = true;
			}
			
			if (flag) {
				if (this->chessboard[i] == 0) {
					freePlace.push_back(i);
				}
			}
		}
		
		secoundRookPosiiton = freePlace[rand()%freePlace.size()];
	} else if (rightAttitude == 1) {
		vector<int>freePlace;
		int drawnNumberLeft;
		
		for (int i = 7; 1 >= 0; i--) {
			if (this->chessboard[i] == 0) {
				secoundRookPosiiton = i;
				this->chessboard[secoundRookPosiiton] = secoundRook;
				break;
			}
		}
		
		for (int i = 0; i < this->chessboard.size(); i++) {
			if (this->chessboard[i] == 4) {
				break;
			}
			
			if (this->chessboard[i] == 0) {
				freePlace.push_back(i);
			}
		}
		
		firstRookPosition = freePlace[rand()%freePlace.size()];
	} else {
		int drawnNumberLeft = 1 + rand()%leftAttitude;
		int drawnNumberRight = 1 + rand()%rightAttitude;
		vector<int>freePlace;
		
		for (int i = 0; i < this->chessboard.size(); i++) {	
			if (this->chessboard[i] == 0) {
				freePlace.push_back(i);
			}
		}
		firstRookPosition = freePlace[drawnNumberLeft - 1];
		secoundRookPosiiton = freePlace[leftAttitude + drawnNumberRight - 1];
	}
	this->chessboard[firstRookPosition] = firstRook;
	this->chessboard[secoundRookPosiiton] = secoundRook;
	
	this->firstRookPosition = firstRookPosition;
	this->secoundRookPosition = secoundRookPosition;
}

void FischerChessboard::drawQueen() {
	vector<int>freePlaceIndex;
	int queen, queenPosition;
	
	queen = 5;
	
	for (int i = 0; i < this->chessboard.size(); i++) {	
		if (this->chessboard[i] == 0) {
			freePlaceIndex.push_back(i);
		}	
	}
	
	queenPosition = freePlaceIndex[rand()%freePlaceIndex.size()];
	
	this->chessboard[queenPosition] = queen;
	this->queenPosition = queenPosition;
}

void FischerChessboard::drawKNight() {
	for (int i = 0; i < this->chessboard.size(); i++) {
		if (this->chessboard[i] == 0) {
			this->chessboard[i] = 2;
		}
	}
}

int FischerChessboard::countAvailablePlaces() {
	int freePlaces = 0;
	
	for (int i = 0; i < this->chessboard.size(); i++) {
		if (this->chessboard[i] == 0) {
			freePlaces++;
		}
	}
	
	return freePlaces;
}

int main(int argc, char** argv) {
	srand(time(NULL));
	
	FischerChessboard chessboard;
	chessboard.schowChessboard();
	return 0;
}
