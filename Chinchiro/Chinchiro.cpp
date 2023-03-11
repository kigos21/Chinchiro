#include <iostream>
#include <time.h>
#include <string>
using namespace std;

struct Roll
{
	string type; // Snake Eyes, Triples, Pairs ,etc
	int rank; // Higher is better. Snake Eyes has higher ranking than Triples
	int val; // The value of the roll for Triples and Pairs (eg. 6-4-4 value is 6)
	int dice[3]; // The actual value rolled for each die
};

int wager(int money)
{
    int bet = 0;
    do
    {
        // while invalid bet, continue to ask
        cout << "=== PLACE YOUR BET ===" << endl;
        cout << "Perica Balance: " << money << endl;
        cout << "Minimum Bet: 100" << endl << endl;
        cout << "Enter amount of bet: ";
        cin >> bet;

        if (bet > money || bet < 100)
        {
            system("cls");
            continue;
        }

        system("cls");
        return bet;

    } while (bet > money || bet < 100);
}

Roll sort(Roll r)
{
    // sort the items in r.dice
    int temp;
    for (int x = 0; x < 2; x++)
        for (int y = x + 1; y < 3; y++)
            if (r.dice[x] > r.dice[y])
            {
                temp = r.dice[x];
                r.dice[x] = r.dice[y];
                r.dice[y] = temp;
            }

    return r;
}

Roll rollDice()
{
    // initialize the values of r.dice
    Roll r;
    r.dice[0] = rand() % 6 + 1;
    r.dice[1] = rand() % 6 + 1;
    r.dice[2] = rand() % 6 + 1;
    return sort(r);
}

bool rollHasVal(Roll r)
{
    return (r.val != 0);
}

void printRoll(Roll r)
{
    if (r.type == "Pisser")
        cout << r.type << endl;
    else
    {
        cout << r.type << ": " << r.dice[0] << " " << r.dice[1] << " " << r.dice[2] << " ";
        if (rollHasVal(r))
            cout << "(" << r.val << ")";
        cout << endl;
    }
}

Roll rollUntilValid()
{
    // continue to roll until a valid roll
    // or a pisser or bust occured
    Roll r;
    int tries = 3;

    while (tries != 0)
    {
        if ((rand() % 100 + 1) <= 5)
        {
            r.type = "Pisser";
            r.rank = 0;
            r.val = 0;
            printRoll(r);
            system("pause && cls");
            break;
        }

        r = rollDice();

        if (r.dice[0] == 1 && r.dice[1] == 1 && r.dice[2] == 1)
        {
            r.type = "Snake Eyes";
            r.rank = 5;
            r.val = 0;
        }

        else if (r.dice[0] == r.dice[1] && r.dice[1] == r.dice[2])
        {
            r.type = "Triples";
            r.rank = 3;
            r.val = r.dice[0];
        }

        // sorted the array at ascending manner for these conditions 
        else if (r.dice[0] == 4 && r.dice[1] == 5 && r.dice[2] == 6)
        {
            r.type = "4-5-6";
            r.rank = 2;
            r.val = 0;
        }

        else if (r.dice[0] == r.dice[1])
        {
            r.type = "Pairs";
            r.rank = 1;
            r.val = r.dice[2];
        }

        else if (r.dice[1] == r.dice[2])
        {
            r.type = "Pairs";
            r.rank = 1;
            r.val = r.dice[0];
        }

        else if (r.dice[0] == 1 && r.dice[1] == 2 && r.dice[2] == 3)
        {
            r.type = "1-2-3";
            r.rank = 0;
            r.val = 0;
        }

        else
        {
            r.type = "Bust";
            r.rank = 0;
            r.val = 0;
        }

        tries -= 1;
        printRoll(r);

        // if bust, continue to roll until tries = 0
        if (r.type == "Bust")
        {
            cout << "Tries left: " << tries << endl;
            system("pause");
            cout << endl;
            
            if (tries != 0)
                continue;
        }

        // if the program reached this, r.type is not bust; no need to re-roll
        system("pause && cls");
        break;
    }

    return r;
}

int payout(Roll oht, Roll kai, int bet)
{
    if (oht.rank == 0 && kai.rank == 0)
    {
        if (kai.type == "Pisser")
            bet = 0;
    }

    else if (oht.rank > kai.rank)
    {
        if (kai.type == "1-2-3")
            bet = (bet * 2) * -1;
        else
            bet *= -1;
    }

    else if (oht.rank < kai.rank)
        bet *= kai.rank;

    else if (oht.rank == kai.rank)
    {
        if (oht.val > kai.val)
            bet *= -1;
        else if (oht.val < kai.val)
            bet *= kai.rank;
        else
            bet = 0;
    }

    return bet;
}

void evaluateEnding(int money)
{
    if (money >= 500000)
        cout << "Congratulations! You're the best gambler!";
    else if (money >= 90000)
        cout << "Wow, you're a good one!";
    else if (money < 90000 && money > 0)
        cout << "Meh, could have done better.";
    else if (money == 0)
        cout << "You're just so bad!";
    else
        cout << "Congratulations, you're the WORST!";

    cout << endl << endl;
}

int main()
{
    srand(time(0));

    int round = 1;
    int money = 90000;

    int bet;
    int tries = 0;
    Roll oht;
    Roll kai;
    int temp;

    while (round <= 10)
    {
        if (money < 100)
        {
            cout << "Perica: " << money << endl << endl;
            cout << "You don't have enough to pay for your loss or living expenses." << endl;
            cout << "    \"Luck diff...\" -Ohtsuki" << endl;
            system("pause && cls");
            break;
        }
        cout << "ROUND " << round << " out of 10" << endl;
        cout << "Perica: " << money << endl;
        system("pause && cls");

        bet = wager(money);
        
        cout << "Ohtsuki rolls..." << endl;
        system("pause");
        cout << endl;
        oht = rollUntilValid();
        
        if (oht.type != "Pisser")
        {
            cout << "Kaiji rolls..." << endl;
            system("pause");
            cout << endl;
            kai = rollUntilValid();
        }
        else
        {
            cout << "Ohtsuki automatically loses." << endl;
            cout << "Kaiji wins " << bet << " Perica!" << endl;
            money += bet;
            round += 1;
            system("pause && cls");
            continue;
        }

        cout << "OHTSUKI:" << endl;
        cout << "==================================" << endl;
        printRoll(oht);
        cout << endl;

        cout << "KAIJI:" << endl;
        cout << "==================================" << endl;
        printRoll(kai);
        cout << endl;
        
        system("pause");

        temp = money; // initial value
        money += payout(oht, kai, bet); // final value

        cout << endl << endl << endl;
        cout << "========== R E S U L T ===========" << endl;

        if (temp < money)
            cout << "Kaiji wins " << money - temp << " Perica!" << endl << endl;
        else if (temp > money)
            cout << "Kaiji lost " << temp - money << " Perica." << endl << endl;
        else
            cout << "Round Draw!" << endl << endl;

        round += 1;
        system("pause && cls");
    }

    cout << "=== PERICA: " << money << " ===" << endl << endl;
    evaluateEnding(money);

	system("pause");
	return 0;
}