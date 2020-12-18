#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <string>
#include <Windows.h>
#include <fstream>
#include <cstdlib>
#include <time.h>
#include <sstream>

#define getch() _getch()
using namespace std;

//COORDINATES FUNCTION
void gotoXY(int x, int y) {
	COORD pos;
	pos.X = x - 1;
	pos.Y = y - 1;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
//GUI
void loginmenu() {

}
void mainmenu() {

}
void catalogmenu() {

}
void productmenu() {

}
//---------------------------------------------------------------------------------
//----------------------------TOWAR------------------------------------------------
//---------------------------------------------------------------------------------
class merch {
protected:
	int ID, maxID, sztuk, pagenr, i, artshown;
	string nazwa, opis, fakecena, fakesztuk;
	long double cena;

public:
	//set
	void setID(int i); //ID = n (musi policzyć ile linii jest dotychczas w pliku i przypisać ostatni numer ID)
	void setSztuk(int n); // sztuk = n
	void setNazwa(string name); //nazwa = name
	void setOpis(string desc); // opis = desc
	void setCena(float price); //cena = price
	void save();// done
	//reszta (możliwe przeniesienie tych funkcji do klasy client
	int getMaxID(); //?
	void setcurrentartykul(int i); //do sprawdzenia przy tworzeniu metody wyszukiwania
	void showartykul(); //done
	void nextartykul(); //done
	void previousartykul(); //done //dodać if (numer < 1) numer = 1; !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	void showpage(); //done
	void nextpage(); //done
	void prevpage(); //done
	void resetpagenr(); //done
	void removeChangeItem(bool choice); //done
	void swapfiles(); //done
	void wyszukajartykul();
};
//MERCH METHODS ------------------------------------------------------------------------------------------
//SETTERS
void merch::setID(int i) {
	ID = i;
}
void merch::setSztuk(int n) { // sztuk = n
	sztuk = n;
}
void merch::setNazwa(string name) { //nazwa = name
	nazwa = name;
}
void merch::setOpis(string desc) { // opis = desc
	opis = desc;
}
void merch::setCena(float price) { //cena = price
	cena = price;
}
//WRITE APPENDING INFO TO THE FILE
void merch::save() { 
	fstream artykuly;
	artykuly.open("artykuly.txt", fstream::app);
	artykuly << nazwa << "\n"
		<< cena << "\n"
		<< sztuk << "\n";
	artykuly.close();
}
//SET THE ID OF THE CURRENT CHOSEN PRODUCT ON THE PAGE
void merch::setcurrentartykul(int i) {
	ID = (pagenr * 9) - (9 - i);
	setID(ID);
	//może if (bool_szukanie==true) { ID = co innego} dla wyszukiwania
}
//SHOW PRODUCT
void merch::showartykul() { 
	int a;
	ifstream artykuly;
	artykuly.open("artykuly.txt");
	for (a = 0; a < ID; a++) {
		getline(artykuly, nazwa);
		getline(artykuly, fakecena);
		getline(artykuly, fakesztuk);
	};
	if (nazwa != "") {
		cout << "Nazwa: " << nazwa << endl
			<< "Cena: " << fakecena << endl
			<< "Sztuk: " << fakesztuk << endl;
	}
	artykuly.close();
}
//NEXT PRODUCT
void merch::nextartykul() { 
	ID++;
}
//SHOW PREVIOUS PRODUCT
void merch::previousartykul() { 
	ID--;
}
//SHOW CATALOG PAGE
void merch::showpage() { 

	i = 1;
	int j, l, num = 1, intcena, intsztuk;
	string art;
	ifstream artykuly;
	if (pagenr < num) pagenr = num;
	artshown = pagenr * 9;
	artykuly.open("artykuly.txt");
	do {
		if (num == pagenr) break;
		if (num != pagenr) {
			for (j = 0; j < 9; j++) {
				getline(artykuly, nazwa);
				getline(artykuly, fakecena);
				getline(artykuly, fakesztuk);
				i++;
			};
		}
		num++;
	} while (num != pagenr);

	for (int a = 0; a < 9; a++) {
		getline(artykuly, nazwa);
		if (nazwa == "") break;
		getline(artykuly, fakecena);
		stringstream intcena(fakecena);
		intcena >> cena;
		getline(artykuly, fakesztuk);
		stringstream intsztuk(fakesztuk);
		intsztuk >> sztuk;
		ID = i;
		cout << a + 1 << ". "
			<< ID << " "
			<< nazwa << " "
			<< cena << " "
			<< sztuk << "\n";
		i++;
	}
	artykuly.close();
}
//NEXT PAGE
void merch::nextpage() { 
	pagenr++;
}
//PREVIOUSPAGE
void merch::prevpage() { 
	pagenr--;
}
//RESET PAGE NUMBER
void merch::resetpagenr() { 
	pagenr = 1;
}
//REMOVE OR CHANGE PRODUCT DATA
void merch::removeChangeItem(bool choice) { //choice=false dla usuwania //choice=true dla zmiany
	//otworz pliki
	ifstream artykuly("artykuly.txt");
	ofstream artykulytemp("artykulytemp.txt");
	string tempnazwa, tempcena, tempsztuk;
	//spisz artykuly
	int count=1;
	bool pusto = 0;
	while (!pusto) {
		getline(artykuly, nazwa);
		if (nazwa == "") break;
		else {
			getline(artykuly, fakecena);
			getline(artykuly, fakesztuk);
		}
		if (count != ID) { //wpisywanie jeśli nie do usunięcia
			artykulytemp << nazwa << "\n"
				<< fakecena << "\n"
				<< fakesztuk << "\n";
		}
		else if (count == ID && choice == true) { //zmiana danych
			getline(cin, tempnazwa);
			if (tempnazwa == "") artykulytemp << nazwa << "\n";
			else artykulytemp << tempnazwa << "\n";
			cin.clear();
			getline(cin, tempcena);
			if (tempcena == "") artykulytemp << fakecena << "\n";
			else artykulytemp << tempcena << "\n";
			cin.clear();
			getline(cin, tempsztuk);
			if (tempsztuk == "") artykulytemp << fakesztuk << "\n";
			else artykulytemp << tempsztuk << "\n";
		}
		count++;
	}
	artykuly.close();
	artykulytemp.close();
}
//SWAP ORIGINAL AND NEW FILE
void merch::swapfiles() { 
	int result;

	char oldname[] = "artykulytemp.txt";
	char newname[] = "artykuly.txt";
	remove(newname);
	do {
		result = rename(oldname, newname);
	} while (result == 0);
}
//---------------------------------------------------------------------------------
//----------------------------KLIENT-----------------------------------------------
//---------------------------------------------------------------------------------
class client {
protected:
	string login;
	string haslo;
	string pesel;
	int wiek;
	string numerkonta;
	//long long int numerkonta;

public:
	void stworzpliki(); //done
	bool logowanie(string login, string has); //done
	void rejestracja(string log, string has, string pes); //done
	bool sprawdzdostepnoscLogin(string log); //done
	bool sprawdzdostepnoscPesel(string pes); //done
	bool sprawdzdlugoscPeselu(string pes); //done
	void zmienhaslo(string haslo, string nowehaslo);//idk jak (może skopiować cały plik i przepisać ze zmienioną jedną linijką)
	void pokazinformacje(string login); //done
	//string getLogin();
	//string getHaslo();
	//string getPesel();
	void utworzkoszykklienta();
	void nowykoszyk();
	void dodajdokoszyka();
	void pokazkoszyk();
	void usunzkoszyka();
	float policzkoszyk();
};

//TWORZENIE PLIKÓW KLIENTA
void client::stworzpliki() {
	bool good();
	fstream loginy("loginy.txt"),
		hasla("hasla.txt"),
		pesele("pesele.txt"),
		numerkoszyka("numerkoszyka.txt"),
		artykuly("artykuly.txt");
	do {
		if (loginy.good() == true) continue;
		else ofstream loginy("loginy.txt");
		if (hasla.good() == true) continue;
		else ofstream hasla("hasla.txt");
		if (pesele.good() == true) continue;
		else ofstream pesele("pesele.txt");
		if (numerkoszyka.good() == true) continue;
		else ofstream numerkoszyka("numerkoszyka.txt");
		if (artykuly.good() == true) continue;
		else ofstream artykuly("artykuly.txt");
	} while (loginy.good() != true &&
		hasla.good() != true &&
		pesele.good() != true &&
		numerkoszyka.good() != true &&
		artykuly.good() != true);
	loginy.close();
	hasla.close();
	pesele.close();
	numerkoszyka.close();
	artykuly.close();
}

//LOGOWANIE ZE SPRAWDZENIEM
bool client::logowanie(string login, string has) {
	ifstream loginy, hasla, pesele;
	string linialogin, liniahaslo;
	bool x, y;
	int i = 0;

	loginy.open("loginy.txt");
	while (getline(loginy, linialogin)) {
		x = login.compare(linialogin);
		i++;
		if (x == 0) break;
		if (linialogin == "") return false;
	};
	loginy.close();
	if (x != 0) return false;
	else {
		hasla.open("hasla.txt");
		pesele.open("pesele.txt");
		for (int j = 0; j < i; j++) {
			getline(hasla, haslo);
			getline(pesele, pesel);
		};
		y = has.compare(haslo);
		if (y == 0) {
			return true;
		}
		else return false;
	};
	hasla.close();
	pesele.close();
}

//REJESTRACJA
void client::rejestracja(string log, string has, string pes) {
	ofstream loginy, hasla, pesele;
	cin.ignore();

	loginy.open("loginy.txt", fstream::app);
	loginy << log << "\n";
	loginy.close();

	hasla.open("hasla.txt", fstream::app);
	hasla << has << "\n";
	hasla.close();

	pesele.open("pesele.txt", fstream::app);
	pesele << pes << "\n";
	pesele.close();
}
//SPRAWDZANIE DOSTĘPNOŚCI LOGINU
bool client::sprawdzdostepnoscLogin(string log) {
	ifstream loginy;
	string login;
	bool x;
	loginy.open("loginy.txt");
	while (getline(loginy, login)) {
		x = log.compare(login);
		if (x == 0) return false;
		if (login == "") return true;
	}
	loginy.close();
	return true;
}
//SPRAWDZANIE DOSTĘPNOŚCI PESELU
bool client::sprawdzdostepnoscPesel(string pes) {
	ifstream pesele;
	string pesel;
	bool x;
	pesele.open("pesele.txt");
	while (getline(pesele, pesel)) {
		x = pes.compare(pesel);
		if (x == 0) return false;
		if (pesel == "") return true;
	}
	pesele.close();
	return true;
}
//SPRAWDZANIE DLUGOSCI PESELU
bool client::sprawdzdlugoscPeselu(string pes) {
	if (pes.size() != 11) return false;
	else return true;
}
//POKAŻ DANE KONTA
void client::pokazinformacje(string login) {
	cout << "Login: " << login << endl;
	cout << "Hasło: " << haslo << endl;
	cout << "Pesel: " << pesel << endl;
}
/*
string client::getLogin() {
	return login;
}

string client::getHaslo() {
	return haslo;
}

string client::getPesel() {
	return pesel;
}
*/
//-------------------------------------------------------------------------------------------------
//-------------------------------------MAIN--------------------------------------------------------
//-------------------------------------------------------------------------------------------------
int main() {
	setlocale(LC_CTYPE, "Polish");
	SetConsoleTitleA("Sklep internetowy OSKI BOSKI");
	ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);

	srand(time(NULL));
	client dane;
	merch towar;
	string login, haslo, pesel;
	bool logowanie, quit = false, powrot = false, powrot2 = false, returnmainpage, returnkatalog, test,
		choice;
	int getchar, c;
	dane.stworzpliki();

	while (!quit) {
		system("cls");
		cout << "---------------SKLEP-------------" << endl << endl;
		cout << "1.Zaloguj sie" << endl;
		cout << "2.Zarejestruj sie" << endl;
		cout << "ESC.Wyjdz" << endl;
		getchar = getch();
		switch (getchar) {
			//LOGOWANIE DONE
		case '1': {
			system("cls");
			cout << "Login: ";
			getline(cin, login);
			cout << "Haslo: ";
			getline(cin, haslo);
			logowanie = dane.logowanie(login, haslo);
			if (logowanie == false) {
				cout << "Bledne dane logowania" << endl;
				cout << "Naciśnij dowolny przycisk by wrócić do ekranu logowania." << endl;
				getchar = getch();
			}
			else if (logowanie == true) {
				cout << "Udane logowanie" << endl;
				Sleep(300);
				powrot = false;
				while (!powrot) {
					system("cls");
					cout << "---------------SKLEP-------------" << endl << endl;
					cout << "1. KATALOG" << endl;
					cout << "2. DODAJ ARTYKUL" << endl;
					cout << "C. Wyloguj" << endl;
					cout << "Z. Zmień hasło." << endl;
					cout << "P. Pokaż informacje" << endl;
					cout << "ESC. Wyjdź" << endl;
					towar.resetpagenr();
					getchar = getch();
					switch (getchar) {
						//katalog (listing artykułów)
					case '1': {
						returnmainpage = false;
						while (!returnmainpage) {
							system("cls");
							cout << "---------------SKLEP-------------" << endl << endl;
							towar.showpage();
							cout << "p-poprzednia strona" << endl
								<< "n-następna strona" << endl
								<< "ESC-powrót do głównej strony" << endl;
							getchar = getch();
							c = 0;
							switch (getchar) {
								//wybór 
								case '1': c = 1; break;
								case '2': c = 2; break;
								case '3': c = 3; break;
								case '4': c = 4; break;
								case '5': c = 5; break;
								case '6': c = 6; break;
								case '7': c = 7; break;
								case '8': c = 8; break;
								case '9': c = 9; break;

								//poprzednia strona
								case 112: {
									towar.prevpage();
									break;
								}
								//nastepna strona
								case 110: {
									towar.nextpage();
									break;
								}
								//wyjście do strony głównej
								case 27: {
									returnmainpage = true;
									break;
								}
							}

							if (c < 10 && c>0) {
								returnkatalog = false;
								towar.setcurrentartykul(c);
								while (!returnkatalog) {
									system("cls");
									towar.showartykul();
									cout << "p-poprzedni artykul" << endl
										<< "n-następny artykul" << endl
										<< "d-usuń artykuł" << endl
										<< "z-zmień dane" << endl
										<< "ESC-powrót do katalogu" << endl;
									//opcje artykułu
									getchar = getch();
									switch (getchar) {
										case 27: { //wyjscie
											returnkatalog = true;
											break;
										}
										case 112: { //poprzedni artykul
											towar.previousartykul();
											break;
										}
										case 110: { //nastepny artykul
											towar.nextartykul();
											break;
										}
										case 100: { //usuń artykuł
											choice = false;
											towar.removeChangeItem(choice);
											towar.swapfiles();
											returnkatalog = true;
											break;
										}
										case 122: { //zmien dane
											choice = true;
											towar.removeChangeItem(choice);
											towar.swapfiles();
											returnkatalog = true;
											break;
										}
									}
								}
							}
						}
						break;
					}
					//dodawanie artykułu do bazy
					case '2': {
						system("cls");
						cout << "---------------SKLEP-------------" << endl << endl;
						cout << "DODAJ ARTYKUŁ: " << endl;
						string a;
						float b;
						int c;
						cout << "Nazwa: ";
						cin >> a;
						towar.setNazwa(a);
						cout << "Cena: ";
						cin >> b;
						towar.setCena(b);
						cout << "Sztuk: ";
						cin >> c;
						towar.setSztuk(c);
						towar.save();
						cin.clear();
						cin.ignore();
						break;
					}
					//cofnij do ekranu logowania DONE
					case 99: {
						cout << "Czy na pewno? (T/N)" << endl;
						getchar = getch();
						if (getchar == 116) powrot = true;
						cin.clear();
						break;
					};
					//zmień hasło
					case 122: {
						cout << "Zmień hasło." << endl;
						break;
					};
					//pokaż informacje o koncie
					case 112: {
						system("cls");
						dane.pokazinformacje(login);
						cout << "Naciśnij dowolny przycisk by wrócić." << endl;
						getchar = getch();
						break;
					}
					//powrót
					case 27: {
						powrot = true;
						quit = true;
						break;
					};
					};
				};
			};
			break;
		}
		//REJESTRACJA DONE
		case '2': {
			powrot = false;
			powrot2 = false;
			while (!powrot2) {
				while (!powrot) {
					system("cls");
					cout << "ZAREJESTRUJ SIE" << endl;
					cout << "Login: ";
					getline(cin, login);
					test = dane.sprawdzdostepnoscLogin(login);
					if (test == false) {
						cout << "Login zajęty." << endl;
						Sleep(300);
					}
					else {
						cout << "Haslo: ";
						getline(cin, haslo);
						cout << "Pesel: ";
						getline(cin, pesel);
						test = dane.sprawdzdlugoscPeselu(pesel);
						if (test == false) {
							cout << "Pesel nieprawidłowy." << endl;
							Sleep(500);
						}
						else {
							test = dane.sprawdzdostepnoscPesel(pesel);
							if (test == false) {
								cout << "Pesel zajęty." << endl;
								Sleep(500);
							}
							else {
								dane.rejestracja(login, haslo, pesel);
								Sleep(300);
								system("cls");
								cout << "ZAREJESTROWANO" << endl;
							}
						}
					}
					powrot = true;
					powrot2 = true;
				};
			};
			cout << "Naciśnij dowolny przycisk by wrócić do ekranu logowania." << endl;
			getchar = getch();
			break;
		};
		//WYJŚCIE DONE
		case 27: {
			quit = true;
			break;
		};
		}
	}
	return 0;
}