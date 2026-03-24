#include<ctime>
#include <iostream>
#include<string>
#include<cctype>
#include <cmath>
#include<cstdlib>
#include <time.h>
#include<iomanip>
#include<vector>
#include<fstream>


using namespace std;
const string ClientsFileName = "ClientsAtM.txt";

void LoginATM();
void ShowATMMainMenue();

enum enATMOption { QuickWithdraw = 1, NormalWithdraw = 2, Deposit = 3, CheckBalance = 4, Logout = 5 };
enum enQuickWithdrawOptin { Zwanzig = 1, Funfzig = 2, Hundart = 3, zweiHundart = 4, vierHundart = 5, seachHundart = 6, achtHundart = 7, Tausend = 8, Exist = 9 };

struct sClient
{
	string AccountNumber;
	string PIN;
	int AccountBalance;

};

sClient CurrentClient;

vector<string> SplitString(string S1, string Delim)
{

	vector<string> vString;

	short pos = 0;
	string sWord; // define a string variable  

	// use find() function to get the position of the delimiters  
	while ((pos = S1.find(Delim)) != std::string::npos)
	{
		sWord = S1.substr(0, pos); // store the word   
		if (sWord != "")
		{
			vString.push_back(sWord);
		}

		S1.erase(0, pos + Delim.length());  /* erase() until positon and move to next word. */
	}

	if (S1 != "")
	{
		vString.push_back(S1); // it adds last word of the string.
	}

	return vString;

}

sClient ConvertLinetoRecord(string Line, string Seperator = "#//#")
{

	sClient Client;
	vector<string> vClientData;

	vClientData = SplitString(Line, Seperator);

	Client.AccountNumber = vClientData[0];
	Client.PIN = vClientData[1];
	Client.AccountBalance = stod(vClientData[2]);//cast string to double


	return Client;

}

string ConvertRecordToLine(sClient Client, string Seperator = "#//#")
{

	string stClientRecord = "";

	stClientRecord += Client.AccountNumber + Seperator;
	stClientRecord += Client.PIN + Seperator;
	stClientRecord += to_string(Client.AccountBalance);

	return stClientRecord;

}

vector <sClient> LoadCleintsDataFromFile(string FileName)
{

	vector <sClient> vClients;

	fstream MyFile;
	MyFile.open(FileName, ios::in);//read Mode

	if (MyFile.is_open())
	{

		string Line;
		sClient Client;

		while (getline(MyFile, Line))
		{

			Client = ConvertLinetoRecord(Line);

			vClients.push_back(Client);
		}

		MyFile.close();

	}

	return vClients;

}

vector <sClient> SaveCleintsDataToFile(string FileName, vector <sClient> vClients)
{

	fstream MyFile;
	MyFile.open(FileName, ios::out);//overwrite

	string DataLine;

	if (MyFile.is_open())
	{

		for (sClient C : vClients)
		{

			DataLine = ConvertRecordToLine(C);
			MyFile << DataLine << endl;

		}

		MyFile.close();

	}

	return vClients;

}

void AddDataLineToFile(string FileName, string  stDataLine)
{
	fstream MyFile;
	MyFile.open(FileName, ios::out | ios::app);

	if (MyFile.is_open())
	{

		MyFile << stDataLine << endl;

		MyFile.close();
	}

}

bool DepositBalanceToClientByAccountNumber(string AccountNumber, double Amount, vector <sClient> & vClients)
{


	char Answer = 'n';


	cout << "\n\nAre you sure you want perfrom this transaction? y/n ? ";
	cin >> Answer;
	if (Answer == 'y' || Answer == 'Y')
	{

		for (sClient& C : vClients)
		{
			if (C.AccountNumber == AccountNumber)
			{
				C.AccountBalance += Amount;
				SaveCleintsDataToFile(ClientsFileName, vClients);
				cout << "\n\nDone Successfully. New balance is: " << C.AccountBalance;

				return true;
			}

		}


		return false;
	}

}

string ReadClientAccountNumber()
{
	string AccountNumber = "";

	cout << "\nPlease enter AccountNumber? ";
	cin >> AccountNumber;
	return AccountNumber;

}

short ReadClientChoose()
{
	short Choose = 0;

	cout << "\nChoose what do you want to do? [1 to 5]? ";
	(cin >> Choose);

	return Choose;
}

short ReadClientChooseWithdraw()
{
	short Choose = 0;

	cout << "\nChoose what to withdraw from[1] to [9] ?  ";
	cin >> Choose;

	return Choose;
}

int CalculateQuickWithdraw(enQuickWithdrawOptin Option)
{
	int FinalBalance = 0;

	switch (Option)
	{
	case Zwanzig:
		FinalBalance = 20;
		break;
	case Funfzig:
		FinalBalance = 50;
		break;
	case Hundart:
		FinalBalance = 100;
		break;
	case zweiHundart:
		FinalBalance = 200;
		break;
	case vierHundart:
		FinalBalance = 400;
		break;
	case seachHundart:
		FinalBalance = 600;
		break;
	case achtHundart:
		FinalBalance = 800;
		break;
	case Tausend:
		FinalBalance = 1000;
		break;
	}

	return FinalBalance;

}

void ShowClientBalance()
{
	vector < sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);

	for (sClient& C : vClients)
	{
		if (CurrentClient.AccountNumber == C.AccountNumber)
		{
			cout << "\nYour Balance is:"
				<< C.AccountBalance << "\n\n";
		}
	}

}

void ScreenQuickWithdraw()
{
	cout << "=====================================";
	cout << "\n\tQuick Withdraw";
	cout << "\n=====================================";

	cout << "\n\t[1] 20 \t\t[2] 50"
		<< "\n\t[3] 100 \t[4] 200"
		<< "\n\t[5] 400 \t[6] 600"
		<< "\n\t[7] 800 \t[8] 1000"
		<< "\n\t[9] Exit";
	cout << "\n=====================================\n";
	ShowClientBalance();

}

void ScreenNormalWithdraw()
{
	vector<sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
	int Amount = 0;
	char Answer = 'y';
	bool OperationCurrect = false;

	cout << "=====================================";
	cout << "\n\tNormal Withdraw";
	cout << "\n=====================================\n";



	do
	{
		cout << "\nEnter An Amount multiple of 5`s ? ";
		cin >> Amount;

		if (Amount % 5 == 0)
			OperationCurrect = true;

	} while (!OperationCurrect);

	for (sClient& C : vClients)
	{
		if (C.AccountNumber == CurrentClient.AccountNumber)
		{
			while (Amount > C.AccountBalance)
			{
				cout << "\nAmount Exceeds the balance, you can withdraw up to : " << C.AccountBalance << endl;
				cout << "Please enter another amount? ";
				cin >> Amount;

			}
		}
	}

	DepositBalanceToClientByAccountNumber(CurrentClient.AccountNumber, (Amount * -1), vClients);

}

void ScreenBalance()
{
	cout << "=====================================";
	cout << "\n\tCheck Balance Screen";
	cout << "\n=====================================";

}

void ShowScreenBalance()
{
	vector<sClient> vClient = LoadCleintsDataFromFile(ClientsFileName);
	ScreenBalance();
	ShowClientBalance();
}

void ShowScreenQuickWithdraw()
{
	vector<sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
	ScreenQuickWithdraw();
	short Choose = ReadClientChooseWithdraw();

	char Answer = 'y';
	int Amount = 0;

	if (Choose == 9)
	{
		return;
	}

	Amount = CalculateQuickWithdraw((enQuickWithdrawOptin)Choose);

	for (sClient& C : vClients)
	{
		if (C.AccountNumber == CurrentClient.AccountNumber)
		{
			while (Amount > C.AccountBalance)
			{
				cout << "\nAmount Exceeds the balance, you can withdraw up to : " << C.AccountBalance << endl;
				cout << "Please enter another amount? ";
				cin >> Amount;

			}
		}
	}

	DepositBalanceToClientByAccountNumber(CurrentClient.AccountNumber, (Amount * -1), vClients);


}

void ScreenDepositBalance()
{
	vector<sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);

	cout << "=====================================";
	cout << "\n\tDeposit Screen";
	cout << "\n=====================================\n";

	double Amount = 0;
	cout << "\nPlease enter deposit amount? ";
	cin >> Amount;

	DepositBalanceToClientByAccountNumber(CurrentClient.AccountNumber, Amount, vClients);

}

void GoBacktoATMMainMenue()
{
	cout << "\n\nPresss any key to go back to Main Manue...";
	system("pause>0");

	ShowATMMainMenue();
}

void PerformancATMMainMenue(enATMOption Option)
{
	switch (Option)
	{
	case QuickWithdraw:
	{
		system("cls");
		ShowScreenQuickWithdraw();
		GoBacktoATMMainMenue();
		break;
	}
	case NormalWithdraw:
	{
		system("cls");
		ScreenNormalWithdraw();
		GoBacktoATMMainMenue();
		break;
	}
	case Deposit:
		system("cls");
		ScreenDepositBalance();
		GoBacktoATMMainMenue();
		break;
	case CheckBalance:
	{
		system("cls");
		ShowScreenBalance();
		GoBacktoATMMainMenue();
		break;
	}
	case Logout:
	{
		LoginATM();
		GoBacktoATMMainMenue();
		break;
	}
	}
}

void ShowATMMainMenue()
{
	system("cls");
	cout << "=======================================";
	cout << "\n\tATM Main Menue Screen";
	cout << "\n=======================================";

	cout << "\n\t[1] Quick Withdraw.";
	cout << "\n\t[2] Normal Withdraw.";
	cout << "\n\t[3] Deposit.";
	cout << "\n\t[4] Check Balance.";
	cout << "\n\t[5] Logout.";
	cout << "\n=======================================";
	PerformancATMMainMenue((enATMOption)ReadClientChoose());

}


bool FindClinetByAccountNumber(string AccountNumber, string PIN, sClient & CurrentClient)
{
	vector<sClient> vClient = LoadCleintsDataFromFile(ClientsFileName);

	for (sClient& C : vClient)
	{
		if (C.AccountNumber == AccountNumber && C.PIN == PIN)
		{
			CurrentClient = C;
			return true;
		}
	}
	return false;
}

bool LoadDataClient(string AccountNumber, string PIN)
{

	if (FindClinetByAccountNumber(AccountNumber, PIN, CurrentClient))
		return true;
	else
		return false;
}

void LogInScreen()
{
	system("cls");
	cout << "\n===========================================\n";
	cout << "\t\tLogin Screem";
	cout << "\n===========================================\n";

}

void LoginATM()
{
	bool NotFind = false;

	string AccountNumber, PIN;

	do
	{
		LogInScreen();

		if (NotFind)
		{
			cout << "Invalid Account NUmber/PIN\n";
		}

		cout << "\nEnter Account Name?";
		getline(cin >> ws, AccountNumber);

		cout << "Enter PIN?";
		getline(cin >> ws, PIN);

		NotFind = !LoadDataClient(AccountNumber, PIN);

	} while (NotFind);

	ShowATMMainMenue();
}

int main()

{
	LoginATM();

	system("pause>0");

	return 0;
}