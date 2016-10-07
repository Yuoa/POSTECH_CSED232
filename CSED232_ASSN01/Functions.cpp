﻿#include "Products.h"
#include <fstream>

using std::endl;
using std::cin;
using std::ifstream;
using std::ofstream;
using std::ios;

void dispAllProducts(SnackList*, DrinkList*, IceList*, OtherList*);
void procSale(SnackList*, DrinkList*, IceList*, OtherList*);
void procStock(SnackList*, DrinkList*, IceList*, OtherList*);
int* dispSearch(SnackList*, DrinkList*, IceList*, OtherList*, bool);
void procModify(SnackList*, DrinkList*, IceList*, OtherList*);
void procRemove(SnackList*, DrinkList*, IceList*, OtherList*);
void dispRecord();

bool dispMenu(SnackList* Snacks, DrinkList* Drinks, IceList* Ices, OtherList* Others) {

	static bool sync = 0;

	cls();

	con.csSize(42, 18);

	if (sync) {

		con.boxOpen();
		con.boxLine("잘못된 입력입니다.");
		con.boxClose();

	}

	sync = false;

	con.boxOpen();
	con.boxLineCenter("[MENU]");
	con.boxLine();
	con.boxLine("0: 전체 상품정보 출력");
	con.boxLine("1: 판매");
	con.boxLine("2: 입고");
	con.boxLine("3: 상품검색");
	con.boxLine("4: 상품정보 수정");
	con.boxLine("5: 상품정보 삭제");
	con.boxLine("6: 판매이력 출력");
	con.boxLine("7 : 종료");
	con.boxClose();

	int input;

	cout << " 메뉴 선택: ";

	cin >> input;

	switch (input) {

	case 0:
		dispAllProducts(Snacks, Drinks, Ices, Others);
		break;
	case 1:
		procSale(Snacks, Drinks, Ices, Others);
		break;
	case 2:
		procStock(Snacks, Drinks, Ices, Others);
		break;
	case 3:
		dispSearch(Snacks, Drinks, Ices, Others, false);
		break;
	case 4:
		procModify(Snacks, Drinks, Ices, Others);
		break;
	case 5:
		procRemove(Snacks, Drinks, Ices, Others);
		break;
	case 6:
		dispRecord();
		break;
	case 7:
		return false;
		break;
	default:
		sync = true;
		break;
	}
	
	return true;

};

void dispAllProducts(SnackList* Snacks, DrinkList* Drinks, IceList* Ices, OtherList* Others) {

	cls();

	con.csSize(140, 45);

	Snacks->dispAllProducts();

	if (Snacks->getAmounts() > 15) {

		con.boxOpen();
		con.boxLine("총 " + to_string(Snacks->getAmounts() + Drinks->getAmounts() + Ices->getAmounts() + Others->getAmounts()) + "개의 상품이 검색되었습니다.");
		con.boxClose();

		con.csPause();

		cls();

	}

	Drinks->dispAllProducts();

	if (Drinks->getAmounts() > 15) {

		con.boxOpen();
		con.boxLine("총 " + to_string(Snacks->getAmounts() + Drinks->getAmounts() + Ices->getAmounts() + Others->getAmounts()) + "개의 상품이 검색되었습니다.");
		con.boxClose();

		con.csPause();

		cls();

	}

	Ices->dispAllProducts();

	if (Ices->getAmounts() > 15) {

		con.boxOpen();
		con.boxLine("총 " + to_string(Snacks->getAmounts() + Drinks->getAmounts() + Ices->getAmounts() + Others->getAmounts()) + "개의 상품이 검색되었습니다.");
		con.boxClose();

		con.csPause();

		cls();

	}

	Others->dispAllProducts();

	con.boxOpen();
	con.boxLine("총 " + to_string(Snacks->getAmounts() + Drinks->getAmounts() + Ices->getAmounts() + Others->getAmounts()) + "개의 상품이 검색되었습니다.");
	con.boxClose();

	con.csPause();

}

void endPOS(SnackList* Snacks, DrinkList* Drinks, IceList* Ices, OtherList* Others) {

	con.csSize(80, 24);

	ofstream Products("product.txt", std::ios::trunc);

	deb("POS Shut down process started.");

	Products << "-SNACK-" << endl;

	for (Snack* aSnack = Snacks->getHead(); aSnack != NULL; aSnack = aSnack->getNext())
		Products << aSnack->getID() << " " + aSnack->getName() + " " << aSnack->getStock() << " " << aSnack->getPrimeCost() << " " << aSnack->getMargin() << " " << aSnack->getSailCost() << " " << aSnack->getManufacturer() << endl;

	for (; Snacks->getHead() != NULL; Snacks->Delete(Snacks->getHead()));

	deb("Snacks Deleted.");

	Products << "-DRINK-" << endl;

	for (Drink* aSnack = Drinks->getHead(); aSnack != NULL; aSnack = aSnack->getNext())
		Products << aSnack->getID() << " " + aSnack->getName() + " " << aSnack->getStock() << " " << aSnack->getPrimeCost() << " " << aSnack->getMargin() << " " << aSnack->getSailCost() << " " << aSnack->getManufacturer() << endl;

	for (; Drinks->getHead() != NULL; Drinks->Delete(Drinks->getHead()));

	deb("Drinks Deleted.");

	Products << "-ICE-" << endl;

	for (Ice* aSnack = Ices->getHead(); aSnack != NULL; aSnack = aSnack->getNext())
		Products << aSnack->getID() << " " + aSnack->getName() + " " << aSnack->getStock() << " " << aSnack->getPrimeCost() << " " << aSnack->getMargin() << " " << aSnack->getSailCost() << " " << aSnack->getManufacturer() << endl;

	for (; Ices->getHead() != NULL; Ices->Delete(Ices->getHead()));

	deb("Ices Deleted.");

	Products << "-OTHER-" << endl;

	for (Other* aSnack = Others->getHead(); aSnack != NULL; aSnack = aSnack->getNext())
		Products << aSnack->getID() << " " + aSnack->getName() + " " << aSnack->getStock() << " " << aSnack->getPrimeCost() << " " << aSnack->getMargin() << " " << aSnack->getSailCost() << " " << aSnack->getManufacturer() << endl;

	for (; Others->getHead() != NULL; Others->Delete(Others->getHead()));

	deb("Others Deleted.");

	delete Snacks, Drinks, Ices, Others;

	if (_Kano::isDev)
		con.csPause();

	con.csSize(20, 3);

	color(BLACK, CYAN);

	cout << endl;

	con.printSpaceCenter("Thank You.");
	
	cout << endl;

	con.csDelay(2);

	color(DEFAULTBACK, DEFAULTFONT);

	cls();

}

Other* makeProd(int id, string name, int stock, int pCost, float margin, int sCost, string man) {

	return new Other(id, name, stock, pCost, margin, sCost, man);

}

int* dispSearch(SnackList* Snacks, DrinkList* Drinks, IceList* Ices, OtherList* Others, bool Mode) {

	if (!Mode) {

		cls();
		con.csSize(140, 30);

	}
	else
		con.setCS(140, 30);

	int Temp = 0, sort = 0;
	static int retVal[2] = {-1, -1};

	string TempStr;

	Snack* aSnack;
	Drink* aDrink;
	Ice* anIce;
	Other *aProd, *targetProd;
	SnackList* sSnacks = new SnackList;
	DrinkList* sDrinks = new DrinkList;
	IceList* sIces = new IceList;
	OtherList *sOthers = new OtherList;

	con.boxOpen();
	con.boxLineCenter("[상품 검색]");
	con.boxLine();
	con.boxLine("검색 기준을 선택하세요.");
	con.boxClose();
	con.boxOpen();
	con.boxLineCenter((Mode) ? "1. Prod. ID    2. Name" : "1. Prod. ID    2. Name    3. Manufacturer");
	con.boxClose();
	
	cout << " 검색 기준: ";
	cin >> Temp;

	cout << endl;

	if (Temp == 1) {

		cout << " 찾을 상품의 ID: ";
		cin >> Temp;

		if ((aSnack = Snacks->getProdByID(Temp)) && aSnack->getID() == Temp) {

			deb("It\'s a Snack!");

			targetProd = makeProd(aSnack->getID(), aSnack->getName(), aSnack->getStock(), aSnack->getPrimeCost(), aSnack->getMargin(), aSnack->getSailCost(), aSnack->getManufacturer());

			sort = 2;

		}
		else if ((aDrink = Drinks->getProdByID(Temp)) && aDrink->getID() == Temp) {

			deb("It\'s a Drink!");

			targetProd = makeProd(aDrink->getID(), aDrink->getName(), aDrink->getStock(), aDrink->getPrimeCost(), aDrink->getMargin(), aDrink->getSailCost(), aDrink->getManufacturer());

			sort = 3;

		}
		else if ((anIce = Ices->getProdByID(Temp)) && anIce->getID() == Temp) {

			deb("It\'s an Ice!");

			targetProd = makeProd(anIce->getID(), anIce->getName(), anIce->getStock(), anIce->getPrimeCost(), anIce->getMargin(), anIce->getSailCost(), anIce->getManufacturer());

			sort = 4;

		}
		else if ((aProd = Others->getProdByID(Temp)) && aProd->getID() == Temp) {

			deb("It\'s a Product!");

			sort = 5;

			targetProd = aProd;

		}

		if (Mode)
			cls();

		con.boxOpen();
		con.boxLineCenter("[검색 결과]");
		con.boxLine();
		
		if (sort) {

			con.boxLine("총 1개의 상품이 검색되었습니다.");
			con.boxLine();
			printf("│");
			con.printSpace("Prod. ID", 12);
			con.printSpace("Name", 32);
			con.printSpace("Stocks", 16); //60
			con.printSpace("Prime Cost", 15);
			con.printSpace("Margin(%%)", 21);
			con.printSpace("Sail Cost", 15); //110
			con.printSpace("Manufacturer", 26);
			printf("│\n");
			con.boxLine();
			printf("│");
			con.printSpace(to_string(targetProd->getID()), 12);
			con.printSpace(targetProd->getName(), 32);
			con.printSpace(to_string(targetProd->getStock()), 16);
			con.printSpace(to_string(targetProd->getPrimeCost()), 15);
			con.printSpace(to_string((int)(targetProd->getMargin() * 100)), 20);
			con.printSpace(to_string(targetProd->getSailCost()), 15);
			con.printSpace(targetProd->getManufacturer(), 26);
			printf("│\n");

			retVal[0] = targetProd->getID();
			retVal[1] = sort;

			if (sort != 5)
				delete targetProd;

		}
		else
			con.boxLine("해당 상품(들)을 찾을 수 없습니다.");	

		con.boxClose();

	}
	else if (Temp == 2) {

		cout << " 찾을 제품의 이름: ";
		cin >> TempStr;

		if ((aSnack = Snacks->getProdByName(TempStr)) && aSnack->getName() == TempStr) {

			deb("It\'s a Snack!");

			targetProd = makeProd(aSnack->getID(), aSnack->getName(), aSnack->getStock(), aSnack->getPrimeCost(), aSnack->getMargin(), aSnack->getSailCost(), aSnack->getManufacturer());

			sort = 2;

		}
		else if ((aDrink = Drinks->getProdByName(TempStr)) && aDrink->getName() == TempStr) {

			deb("It\'s a Drink!");

			targetProd = makeProd(aDrink->getID(), aDrink->getName(), aDrink->getStock(), aDrink->getPrimeCost(), aDrink->getMargin(), aDrink->getSailCost(), aDrink->getManufacturer());

			sort = 3;

		}
		else if ((anIce = Ices->getProdByName(TempStr)) && anIce->getName() == TempStr) {

			deb("It\'s an Ice!");

			targetProd = makeProd(anIce->getID(), anIce->getName(), anIce->getStock(), anIce->getPrimeCost(), anIce->getMargin(), anIce->getSailCost(), anIce->getManufacturer());

			sort = 4;

		}
		else if ((aProd = Others->getProdByName(TempStr)) && aProd->getName() == TempStr) {

			deb("It\'s a Product!");

			sort = 5;

			targetProd = aProd;

		}

		if (Mode)
			cls();

		con.boxOpen();
		con.boxLineCenter("[검색 결과]");
		con.boxLine();

		if (sort) {

			con.boxLine("총 1개의 상품이 검색되었습니다.");
			con.boxLine();
			printf("│");
			con.printSpace("Prod. ID", 12);
			con.printSpace("Name", 32);
			con.printSpace("Stocks", 16); //60
			con.printSpace("Prime Cost", 15);
			con.printSpace("Margin(%%)", 21);
			con.printSpace("Sail Cost", 15); //110
			con.printSpace("Manufacturer", 26);
			printf("│\n");
			con.boxLine();
			printf("│");
			con.printSpace(to_string(targetProd->getID()), 12);
			con.printSpace(targetProd->getName(), 32);
			con.printSpace(to_string(targetProd->getStock()), 16);
			con.printSpace(to_string(targetProd->getPrimeCost()), 15);
			con.printSpace(to_string((int)(targetProd->getMargin() * 100)), 20);
			con.printSpace(to_string(targetProd->getSailCost()), 15);
			con.printSpace(targetProd->getManufacturer(), 26);
			printf("│\n");

			retVal[0] = targetProd->getID();
			retVal[1] = sort;

			if (sort != 5)
				delete targetProd;

		}
		else
			con.boxLine("해당 상품(들)을 찾을 수 없습니다.");

		con.boxClose();

	}
	else if (Temp == 3 && !Mode) {

		cout << " 찾을 제품들의 제조사: ";
		cin >> TempStr;

		sSnacks = Snacks->getProdsByManufacturer(sSnacks, TempStr);
		sDrinks = Drinks->getProdsByManufacturer(sDrinks, TempStr);
		sIces = Ices->getProdsByManufacturer(sIces, TempStr);
		sOthers = Others->getProdsByManufacturer(sOthers, TempStr);

		con.boxOpen();
		con.boxLineCenter("[검색 결과]");
		con.boxLine();

		if (sSnacks->getAmounts() + sDrinks->getAmounts() + sIces->getAmounts() + sOthers->getAmounts()) {

			con.boxLine("총 " + to_string(sSnacks->getAmounts() + sDrinks->getAmounts() + sIces->getAmounts() + sOthers->getAmounts()) + "개의 상품이 검색되었습니다.");
			con.boxLine();
			printf("│");
			con.printSpace("Prod. ID", 12);
			con.printSpace("Name", 32);
			con.printSpace("Stocks", 16); //60
			con.printSpace("Prime Cost", 15);
			con.printSpace("Margin(%%)", 21);
			con.printSpace("Sail Cost", 15); //110
			con.printSpace("Manufacturer", 26);
			printf("│\n");
			con.boxLine();

			for (Snack* Queue = sSnacks->getHead(); Queue != NULL; Queue = Queue->getNext()) {

				printf("│");
				con.printSpace(to_string(Queue->getID()), 12);
				con.printSpace(Queue->getName(), 32);
				con.printSpace(to_string(Queue->getStock()), 16); //60
				con.printSpace(to_string(Queue->getPrimeCost()), 15);
				con.printSpace(to_string((int)(Queue->getMargin() * 100)), 20);
				con.printSpace(to_string(Queue->getSailCost()), 15); //110
				con.printSpace(Queue->getManufacturer(), 26);
				printf("│\n");

			}

			for (Drink* Queue = sDrinks->getHead(); Queue != NULL; Queue = Queue->getNext()) {

				printf("│");
				con.printSpace(to_string(Queue->getID()), 12);
				con.printSpace(Queue->getName(), 32);
				con.printSpace(to_string(Queue->getStock()), 16); //60
				con.printSpace(to_string(Queue->getPrimeCost()), 15);
				con.printSpace(to_string((int)(Queue->getMargin() * 100)), 20);
				con.printSpace(to_string(Queue->getSailCost()), 15); //110
				con.printSpace(Queue->getManufacturer(), 26);
				printf("│\n");

			}

			for (Ice* Queue = sIces->getHead(); Queue != NULL; Queue = Queue->getNext()) {

				printf("│");
				con.printSpace(to_string(Queue->getID()), 12);
				con.printSpace(Queue->getName(), 32);
				con.printSpace(to_string(Queue->getStock()), 16); //60
				con.printSpace(to_string(Queue->getPrimeCost()), 15);
				con.printSpace(to_string((int)(Queue->getMargin() * 100)), 20);
				con.printSpace(to_string(Queue->getSailCost()), 15); //110
				con.printSpace(Queue->getManufacturer(), 26);
				printf("│\n");

			}

			for (Other* Queue = sOthers->getHead(); Queue != NULL; Queue = Queue->getNext()) {

				printf("│");
				con.printSpace(to_string(Queue->getID()), 12);
				con.printSpace(Queue->getName(), 32);
				con.printSpace(to_string(Queue->getStock()), 16); //60
				con.printSpace(to_string(Queue->getPrimeCost()), 15);
				con.printSpace(to_string((int)(Queue->getMargin() * 100)), 20);
				con.printSpace(to_string(Queue->getSailCost()), 15); //110
				con.printSpace(Queue->getManufacturer(), 26);
				printf("│\n");

			}

		}
		else
			con.boxLine("해당 상품(들)을 찾을 수 없습니다.");

		con.boxClose();

	}
	else {

		con.boxOpen();
		con.boxLineCenter("[오류]");
		con.boxLine();
		con.boxLine("잘못된 값을 입력하셨습니다.");
		con.boxClose();

	}

	for (; sSnacks->getHead() != NULL; sSnacks->Delete(sSnacks->getHead()));
	for (; sDrinks->getHead() != NULL; sDrinks->Delete(sDrinks->getHead()));
	for (; sIces->getHead() != NULL; sIces->Delete(sIces->getHead()));
	for (; sOthers->getHead() != NULL; sOthers->Delete(sOthers->getHead()));

	delete sSnacks, sDrinks, sIces, sOthers;

	if (!Mode || !Temp || retVal[0] == -1)
		con.csPause();

	return retVal;

}

void dispRecord() {

	ifstream Records("sell_info.txt");

	con.csSize(100, 45);

	int count = 0;
	char Temp[1024];

	con.boxOpen();
	con.boxLineCenter("[판매 이력]");
	con.boxClose();
	con.boxOpen();

	for (Records.getline(Temp, 1024); !Records.eof(); Records.getline(Temp, 1024)) {

		con.boxLine(Temp);

		if ((count++) % 35 == 34) {

			con.boxLine();
			con.boxLine("계속 보시려면 아무 키나 누르세요.");
			con.boxClose();
			con.csPause();

			cls();

			con.boxOpen();
			con.boxLineCenter("[판매 이력]");
			con.boxClose();
			con.boxOpen();

		}

	}

	con.boxClose();

	con.csPause();

}
