// Text Tournament Fighter.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "Text tournament fighter.h.h"

using namespace std;

void setupPlayerStats(string &name, int &str, int &def, int &armor, int &skill, int &wins);
void savePlayerStats(string name, int str, int def, int armor, int skill, int wins);

int main() {

	random_device rd;
	uniform_int_distribution<int> d6(1, 6);

	//Player 1 stats
	string player1Name;
	int player1Str;
	int player1Def;
	int player1Armor;
	int player1Skill;
	int player1Wins;

	//Player 2 stats
	string player2Name;
	int player2Str;
	int player2Def;
	int player2Armor;
	int player2Skill;
	int player2Wins;

	cout << "Setup Player 1" << endl;
	setupPlayerStats(player1Name, player1Str, player1Def, player1Armor, player1Skill, player1Wins);

	cout << "Setup Player 2" << endl;
	setupPlayerStats(player2Name, player2Str, player2Def, player2Armor, player2Skill, player2Wins);

	int player1Health = 20;
	int player2Health = 20;
	int turns = 0;

	cout << player1Name << " - " << player1Wins << " Wins" << endl;
	cout << " - vs. - " << endl;
	cout << player2Name << " - " << player2Wins << " Wins" << endl;

	cout << "FIGHT!";
	//Fight loop

	while (player1Health > 0 && player2Health > 0 && turns < 100) {
		int attackRoll;
		int damageRoll;

		//Attack P1 > P2
		attackRoll = player1Skill + d6(rd);
		if (attackRoll >= 3 + player2Def) {
			//Attack hits!
			cout << player1Name << " hits" << "." << endl;
			damageRoll = player1Str + d6(rd) - player2Armor;
			if (damageRoll > 0) {
				player2Health -= damageRoll;
				cout << player2Name << " takes " << damageRoll << " damage ." << endl;
			}
			else {
				cout << player2Name << "'s armor blocks the hit." << endl;
			}
		}
		else {
			cout << player1Name << " missed." << endl;
		}

		attackRoll = player2Skill + d6(rd);
		if (attackRoll >= 3 + player2Def) {
			//Attack hits!
			cout << player2Name << " hits" << "." << endl;
			damageRoll = player2Str + d6(rd) - player1Armor;
			if (damageRoll > 0) {
				player1Health -= damageRoll;
				cout << player1Name << " takes " << damageRoll << " damage ." << endl;
			}
			else {
				cout << player1Name << "'s armor blocks the hit." << endl;
			}
		}
		else {
			cout << player2Name << " missed." << endl;
		}

		cout << player1Name << " HP: " << player1Health << endl;
		cout << player2Name << " HP: " << player2Health << endl;
		turns++;
	}

	if (player1Health <= 0 && player2Health <=0) {
		cout << "This match is a draw!" << endl;
	}

	else if (player1Health > 0) {
		cout << player1Name << " wins!" << endl;
		player1Wins++;
	}
	else {
		cout << player2Name << " wins!" << endl;
		player2Wins++;
	}

	// Save records to a file:
	savePlayerStats(player1Name, player1Str, player1Def, player1Armor, player1Skill, player1Wins);
	savePlayerStats(player2Name, player2Str, player2Def, player2Armor, player2Skill, player2Wins);

	return 0;
}

void setupPlayerStats(string &name, int &str, int &def, int&armor, int&skill, int&wins){

	fstream file;
	cout << "Name: ";
	cin >> name;

	//if a name is not chosen
	if (name == "") {
		name = "Rookie";
	}

	string filename = name + ".txt";

	file.open(filename, ios::in);
	if (file.is_open()) {
		//File already exists, read data from the file
		cout << "File found,loading from the file" << endl;

		file >> str;
		file >> def;
		file >> armor;
		file >> skill;
		file >> wins;
	}
	else {
		//File doesn't exist, have user fill it in
		bool accepted = false;
		while (!accepted) {
			int points = 20;

			cout << points << " points left." << endl;
			cout << "Player Str: ";
			cin >> str;
			points -= str;

			cout << points << " points left." << endl;
			cout << "Player Def: ";
			cin >> def;
			points -= def;

			cout << points << " points left." << endl;
			cout << "Player Armor: ";
			cin >> armor;
			points -= armor;

			cout << points << " points left." << endl;
			cout << "Player Skill: ";
			cin >> skill;
			points -= skill;

			wins = 0;

			if (points >= 0) {
				accepted = true;

			}

			else {

				cout << "You used too many points!" << endl;
			}

		}
		
	}
}


void savePlayerStats(string name, int str, int def, int armor, int skill, int wins) {

	fstream file;
	string filename = name + ".txt";

	file.open(filename, ios::out);


	file << str << endl;
	file << def << endl;
	file << armor << endl;
	file << skill << endl;
	file << wins << endl;

	file.close();

    return ;
}

