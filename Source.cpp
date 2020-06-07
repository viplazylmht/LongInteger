#include <stdio.h>
#include <iostream>
#include <sstream>
#include "QInt.h"
#include "RWFile.h"

using namespace std;

void Menu();

int main(int argc, char **argv)
{
	if (argc == 3)
	{
		// read instruction from command line
		char *input = argv[1];
		char *output = argv[2];

		RWFile rw(input, output);

		rw.Start();
		rw.WriteFile();

		return 0;
	}

	Menu();

	return 0;
}

void Menu()
{
	try
	{
		int k = 0;
		while (1)
		{
			system("cls");
			cout << "\n---------------MENU--------------";
			cout << "\n1. Chuyen tu he BIN qua DEC va HEX";
			cout << "\n2. Chuyen doi tu he DEC qua he BIN va HEX";
			cout << "\n3. Chuyen doi tu he HEX qua he BIN va DEC";
			cout << "\n4. Phep +";
			cout << "\n5. Phep -";
			cout << "\n6. Phep *";
			cout << "\n7. Phep /";
			cout << "\n8. Phep &";
			cout << "\n9. Phep |";
			cout << "\n10. Phep ^";
			cout << "\n11. Phep ~";
			cout << "\n12. Phep <<";
			cout << "\n13. Phep >>";
			cout << "\n14. Phep SAR";
			cout << "\n15. Phep ROL";
			cout << "\n16. Phep ROR";
			cout << "\n0. Thoat!";

			cout << "\n\nBan chon gi? : ";
			cin >> k;

			switch (k)
			{
			case 1:
			{
				string s;
				cout << "\nNhap chuoi nhi phan : ";
				cin >> s;
				QInt test1(s, BIN);
				cout << test1.toString();
				system("pause");
			}
			break;
			case 2:
			{
				string s;
				cout << "\nNhap chuoi thap phan : ";
				cin >> s;
				QInt test1(s, DEC);
				cout << test1.toString();
				system("pause");
			}
			break;
			case 3:
			{
				string s;
				cout << "\nNhap chuoi thap luc phan : ";
				cin >> s;
				QInt test1(s, HEX);
				cout << test1.toString();
				system("pause");
			}
			break;
			case 4:
			{
				while (1)
				{
					system("cls");
					cout << "\n1. Phep + 2 so nhi phan\n";
					cout << "\n2. Phep + 2 so thap phan\n";
					cout << "\n3. Phep + 2 so thap luc phan\n";
					cout << "\n0. Thoat \n";
					int lc;
					cout << "Nhap lua chon : ";
					cin >> lc;
					switch (lc)
					{
					case 1:
					{
						string s1, s2;
						cout << "\nNhap chuoi nhi phan so 1 : ";
						cin >> s1;
						QInt test1(s1, BIN);
						cout << "\nNhap chuoi nhi phan so 2 : ";
						cin >> s2;
						QInt test2(s2, BIN);
						cout << "\nKet qua phep cong(+))\n";
						cout << (test1 + test2).toString();
						system("pause");
					}
					break;
					case 2:
					{
						string s1, s2;
						cout << "\nNhap chuoi thap phan so 1 : ";
						cin >> s1;
						QInt test1(s1, DEC);
						cout << "\nNhap chuoi thap phan so 2 : ";
						cin >> s2;
						QInt test2(s2, DEC);
						cout << "\nKet qua phep cong(+))\n";
						cout << (test1 + test2).toString();
						system("pause");
					}
					break;
					case 3:
					{
						string s1, s2;
						cout << "\nNhap chuoi thap luc phan so 1 : ";
						cin >> s1;
						QInt test1(s1, HEX);
						cout << "\nNhap chuoi thap luc phan so 2 : ";
						cin >> s2;
						QInt test2(s2, HEX);
						cout << "\nKet qua phep cong(+))\n";
						cout << (test1 + test2).toString();
						system("pause");
					}
					break;
					case 0:
					{
						break;
					}
					break;
					default:
						break;
					}
					if (lc == 0)
						break;
				}
			}
			break;
			case 5:
			{
				while (1)
				{
					system("cls");
					cout << "\n1. Phep - 2 so nhi phan\n";
					cout << "\n2. Phep - 2 so thap phan\n";
					cout << "\n3. Phep - 2 so thap luc phan\n";
					cout << "\n0. Thoat \n";
					int lc;
					cout << "Nhap lua chon : ";
					cin >> lc;
					switch (lc)
					{
					case 1:
					{
						string s1, s2;
						cout << "\nNhap chuoi nhi phan so 1 : ";
						cin >> s1;
						QInt test1(s1, BIN);
						cout << "\nNhap chuoi nhi phan so 2 : ";
						cin >> s2;
						QInt test2(s2, BIN);
						cout << "\nKet qua phep tru(-))\n";
						cout << (test1 - test2).toString();
						system("pause");
					}
					break;
					case 2:
					{
						string s1, s2;
						cout << "\nNhap chuoi thap phan so 1 : ";
						cin >> s1;
						QInt test1(s1, DEC);
						cout << "\nNhap chuoi thap phan so 2 : ";
						cin >> s2;
						QInt test2(s2, DEC);
						cout << "\nKet qua phep tru(-))\n";
						cout << (test1 - test2).toString();
						system("pause");
					}
					break;
					case 3:
					{
						string s1, s2;
						cout << "\nNhap chuoi thap luc phan so 1 : ";
						cin >> s1;
						QInt test1(s1, HEX);
						cout << "\nNhap chuoi thap luc phan so 2 : ";
						cin >> s2;
						QInt test2(s2, HEX);
						cout << "\nKet qua phep tru(-))\n";
						cout << (test1 - test2).toString();
						system("pause");
					}
					break;
					case 0:
					{
						break;
					}
					break;
					default:
						break;
					}
					if (lc == 0)
						break;
				}
			}
			break;

			case 6:
			{
				while (1)
				{
					system("cls");
					cout << "\n1. Phep * 2 so nhi phan\n";
					cout << "\n2. Phep * 2 so thap phan\n";
					cout << "\n3. Phep * 2 so thap luc phan\n";
					cout << "\n0. Thoat \n";
					int lc;
					cout << "Nhap lua chon : ";
					cin >> lc;
					switch (lc)
					{
					case 1:
					{
						string s1, s2;
						cout << "\nNhap chuoi nhi phan so 1 : ";
						cin >> s1;
						QInt test1(s1, BIN);
						cout << "\nNhap chuoi nhi phan so 2 : ";
						cin >> s2;
						QInt test2(s2, BIN);
						cout << "\nKet qua phep nhan(*)\n";
						cout << (test1 * test2).toString();
						system("pause");
					}
					break;
					case 2:
					{
						string s1, s2;
						cout << "\nNhap chuoi thap phan so 1 : ";
						cin >> s1;
						QInt test1(s1, DEC);
						cout << "\nNhap chuoi thap phan so 2 : ";
						cin >> s2;
						QInt test2(s2, DEC);
						cout << "\nKet qua phep nhan(*))\n";
						cout << (test1 * test2).toString();
						system("pause");
					}
					break;
					case 3:
					{
						string s1, s2;
						cout << "\nNhap chuoi thap luc phan so 1 : ";
						cin >> s1;
						QInt test1(s1, HEX);
						cout << "\nNhap chuoi thap luc phan so 2 : ";
						cin >> s2;
						QInt test2(s2, HEX);
						cout << "\nKet qua phep nhan(*)\n";
						cout << (test1 * test2).toString();
						system("pause");
					}
					break;
					case 0:
					{
						break;
					}
					break;
					default:
						break;
					}
					if (lc == 0)
						break;
				}
			}
			break;
			case 7:
			{
				while (1)
				{
					system("cls");
					cout << "\n1. Phep / 2 so nhi phan\n";
					cout << "\n2. Phep / 2 so thap phan\n";
					cout << "\n3. Phep / 2 so thap luc phan\n";
					cout << "\n0. Thoat \n";
					int lc;
					cout << "Nhap lua chon : ";
					cin >> lc;
					switch (lc)
					{
					case 1:
					{
						string s1, s2;
						cout << "\nNhap chuoi nhi phan so 1 : ";
						cin >> s1;
						QInt test1(s1, BIN);
						cout << "\nNhap chuoi nhi phan so 2 : ";
						cin >> s2;
						QInt test2(s2, BIN);
						cout << "\nKet qua phep chia(/))\n";
						cout << (test1 / test2).toString();
						system("pause");
					}
					break;
					case 2:
					{
						string s1, s2;
						cout << "\nNhap chuoi thap phan so 1 : ";
						cin >> s1;
						QInt test1(s1, DEC);
						cout << "\nNhap chuoi thap phan so 2 : ";
						cin >> s2;
						QInt test2(s2, DEC);
						cout << "\nKet qua phep chia(/))\n";
						cout << (test1 / test2).toString();
						system("pause");
					}
					break;
					case 3:
					{
						string s1, s2;
						cout << "\nNhap chuoi thap luc phan so 1 : ";
						cin >> s1;
						QInt test1(s1, HEX);
						cout << "\nNhap chuoi thap luc phan so 2 : ";
						cin >> s2;
						QInt test2(s2, HEX);
						cout << "\nKet qua phep chia(/))\n";
						cout << (test1 / test2).toString();
						system("pause");
					}
					break;
					case 0:
					{
						break;
					}
					break;
					default:
						break;
					}
					if (lc == 0)
						break;
				}
			}
			break;
			case 8:
			{
				while (1)
				{
					system("cls");
					cout << "\n1. Phep & 2 so nhi phan\n";
					cout << "\n2. Phep & 2 so thap phan\n";
					cout << "\n3. Phep & 2 so thap luc phan\n";
					cout << "\n0. Thoat \n";
					int lc;
					cout << "Nhap lua chon : ";
					cin >> lc;
					switch (lc)
					{
					case 1:
					{
						string s1, s2;
						cout << "\nNhap chuoi nhi phan so 1 : ";
						cin >> s1;
						QInt test1(s1, BIN);
						cout << "\nNhap chuoi nhi phan so 2 : ";
						cin >> s2;
						QInt test2(s2, BIN);
						cout << "\nKet qua phep &\n";
						QInt k = (test1 & test2);
						cout << k.toString();
						system("pause");
					}
					break;
					case 2:
					{
						string s1, s2;
						cout << "\nNhap chuoi thap phan so 1 : ";
						cin >> s1;
						QInt test1(s1, DEC);
						cout << "\nNhap chuoi thap phan so 2 : ";
						cin >> s2;
						QInt test2(s2, DEC);
						cout << "\nKet qua phep &\n";
						QInt k = (test1 & test2);
						cout << k.toString();
						system("pause");
					}
					break;
					case 3:
					{
						string s1, s2;
						cout << "\nNhap chuoi thap luc phan so 1 : ";
						cin >> s1;
						QInt test1(s1, HEX);
						cout << "\nNhap chuoi thap luc phan so 2 : ";
						cin >> s2;
						QInt test2(s2, HEX);
						cout << "\nKet qua phep &\n";
						QInt k = (test1 & test2);
						cout << k.toString();
						system("pause");
					}
					break;
					case 0:
					{
						break;
					}
					break;
					default:
						break;
					}
					if (lc == 0)
						break;
				}
			}
			break;
			case 9:
			{
				while (1)
				{
					system("cls");
					cout << "\n1. Phep | 2 so nhi phan\n";
					cout << "\n2. Phep | 2 so thap phan\n";
					cout << "\n3. Phep | 2 so thap luc phan\n";
					cout << "\n0. Thoat \n";
					int lc;
					cout << "Nhap lua chon : ";
					cin >> lc;
					switch (lc)
					{
					case 1:
					{
						string s1, s2;
						cout << "\nNhap chuoi nhi phan so 1 : ";
						cin >> s1;
						QInt test1(s1, BIN);
						cout << "\nNhap chuoi nhi phan so 2 : ";
						cin >> s2;
						QInt test2(s2, BIN);
						cout << "\nKet qua phep |\n";
						QInt k = (test1 | test2);
						cout << k.toString();
						system("pause");
					}
					break;
					case 2:
					{
						string s1, s2;
						cout << "\nNhap chuoi thap phan so 1 : ";
						cin >> s1;
						QInt test1(s1, DEC);
						cout << "\nNhap chuoi thap phan so 2 : ";
						cin >> s2;
						QInt test2(s2, DEC);
						cout << "\nKet qua phep |\n";
						QInt k = (test1 | test2);
						cout << k.toString();
						system("pause");
					}
					break;
					case 3:
					{
						string s1, s2;
						cout << "\nNhap chuoi thap luc phan so 1 : ";
						cin >> s1;
						QInt test1(s1, HEX);
						cout << "\nNhap chuoi thap luc phan so 2 : ";
						cin >> s2;
						QInt test2(s2, HEX);
						cout << "\nKet qua phep |\n";
						QInt k = (test1 | test2);
						cout << k.toString();
						system("pause");
					}
					break;
					case 0:
					{
						break;
					}
					break;
					default:
						break;
					}
					if (lc == 0)
						break;
				}
			}
			break;
			case 10:
			{
				while (1)
				{
					system("cls");
					cout << "\n1. Phep ^ 2 so nhi phan\n";
					cout << "\n2. Phep ^ 2 so thap phan\n";
					cout << "\n3. Phep ^ 2 so thap luc phan\n";
					cout << "\n0. Thoat \n";
					int lc;
					cout << "Nhap lua chon : ";
					cin >> lc;
					switch (lc)
					{
					case 1:
					{
						string s1, s2;
						cout << "\nNhap chuoi nhi phan so 1 : ";
						cin >> s1;
						QInt test1(s1, BIN);
						cout << "\nNhap chuoi nhi phan so 2 : ";
						cin >> s2;
						QInt test2(s2, BIN);
						cout << "\nKet qua phep ^\n";
						cout << (test1 ^ test2).toString();
						system("pause");
					}
					break;
					case 2:
					{
						string s1, s2;
						cout << "\nNhap chuoi thap phan so 1 : ";
						cin >> s1;
						QInt test1(s1, DEC);
						cout << "\nNhap chuoi thap phan so 2 : ";
						cin >> s2;
						QInt test2(s2, DEC);
						cout << "\nKet qua phep ^\n";
						cout << (test1 ^ test2).toString();
						system("pause");
					}
					break;
					case 3:
					{
						string s1, s2;
						cout << "\nNhap chuoi thap luc phan so 1 : ";
						cin >> s1;
						QInt test1(s1, HEX);
						cout << "\nNhap chuoi thap luc phan so 2 : ";
						cin >> s2;
						QInt test2(s2, HEX);
						cout << "\nKet qua phep ^\n";
						cout << (test1 ^ test2).toString();
						system("pause");
					}
					break;
					case 0:
					{
						break;
					}
					break;
					default:
						break;
					}
					if (lc == 0)
						break;
				}
			}
			break;
			case 11:
			{
				while (1)
				{
					system("cls");
					cout << "\n1. Phep ~ so nhi phan\n";
					cout << "\n2. Phep ~ so thap phan\n";
					cout << "\n3. Phep ~ so thap luc phan\n";
					cout << "\n0. Thoat \n";
					int lc;
					cout << "Nhap lua chon : ";
					cin >> lc;
					switch (lc)
					{
					case 1:
					{
						string s1;
						cout << "\nNhap chuoi nhi phan : ";
						cin >> s1;
						QInt test1(s1, BIN);
						cout << "\nKet qua phep ~\n";
						cout << (~test1).toString();
						system("pause");
					}
					break;
					case 2:
					{
						string s1;
						cout << "\nNhap chuoi thap phan : ";
						cin >> s1;
						QInt test1(s1, DEC);
						cout << "\nKet qua phep ~\n";
						cout << (~test1).toString();
						system("pause");
					}
					break;
					case 3:
					{
						string s1;
						cout << "\nNhap chuoi thap luc phan : ";
						cin >> s1;
						QInt test1(s1, HEX);
						cout << "\nKet qua phep ~\n";
						cout << (~test1).toString();
						system("pause");
					}
					break;
					case 0:
					{
						break;
					}
					break;
					default:
						break;
					}
					if (lc == 0)
						break;
				}
			}
			break;
			case 12:
			{
				while (1)
				{
					system("cls");
					cout << "\n1. Phep << so nhi phan\n";
					cout << "\n2. Phep << so thap phan\n";
					cout << "\n3. Phep << so thap luc phan\n";
					cout << "\n0. Thoat \n";
					int lc;
					cout << "Nhap lua chon : ";
					cin >> lc;
					switch (lc)
					{
					case 1:
					{
						string s1;
						cout << "\nNhap chuoi nhi phan : ";
						cin >> s1;
						QInt test1(s1, BIN);
						int bit;
						cout << "\nNhap so bit can dich : ";
						cin >> bit;
						cout << "\nKet qua phep <<(SHL)\n";
						QInt k = (test1 << bit);
						cout << k.toString();
						system("pause");
					}
					break;
					case 2:
					{
						string s1;
						cout << "\nNhap chuoi thap phan : ";
						cin >> s1;
						QInt test1(s1, DEC);
						int bit;
						cout << "\nNhap so bit can dich : ";
						cin >> bit;
						cout << "\nKet qua phep <<(SHL)\n";
						QInt k = (test1 << bit);
						cout << k.toString();
						system("pause");
					}
					break;
					case 3:
					{
						string s1;
						cout << "\nNhap chuoi thap luc phan : ";
						cin >> s1;
						QInt test1(s1, HEX);
						int bit;
						cout << "\nNhap so bit can dich : ";
						cin >> bit;
						cout << "\nKet qua phep <<(SHL)\n";
						QInt k = (test1 << bit);
						cout << k.toString();
						system("pause");
					}
					break;
					case 0:
					{
						break;
					}
					break;
					default:
						break;
					}
					if (lc == 0)
						break;
				}
			}
			break;
			case 13:
			{

				while (1)
				{
					system("cls");
					cout << "\n1. Phep >> so nhi phan\n";
					cout << "\n2. Phep >> so thap phan\n";
					cout << "\n3. Phep >> so thap luc phan\n";
					cout << "\n0. Thoat \n";
					int lc;
					cout << "Nhap lua chon : ";
					cin >> lc;
					switch (lc)
					{
					case 1:
					{
						string s1;
						cout << "\nNhap chuoi nhi phan : ";
						cin >> s1;
						QInt test1(s1, BIN);
						int bit;
						cout << "\nNhap so bit can dich : ";
						cin >> bit;
						cout << "\nKet qua phep >>(SHR)\n";
						QInt k = test1 >> bit;
						cout << k.toString();
						system("pause");
					}
					break;
					case 2:
					{
						string s1;
						cout << "\nNhap chuoi thap phan : ";
						cin >> s1;
						QInt test1(s1, DEC);
						int bit;
						cout << "\nNhap so bit can dich : ";
						cin >> bit;
						cout << "\nKet qua phep >>(SHR)\n";
						QInt k = test1 >> bit;
						cout << k.toString();
						system("pause");
					}
					break;
					case 3:
					{
						string s1;
						cout << "\nNhap chuoi thap luc phan : ";
						cin >> s1;
						QInt test1(s1, HEX);
						int bit;
						cout << "\nNhap so bit can dich : ";
						cin >> bit;
						cout << "\nKet qua phep >>(SHR)\n";
						QInt k = (test1 >> bit);
						cout << k.toString();
						system("pause");
					}
					break;
					case 0:
					{
						break;
					}
					break;
					default:
						break;
					}
					if (lc == 0)
						break;
				}
			}
			break;
			case 14:
			{

				while (1)
				{
					system("cls");
					cout << "\n1. Phep SAR so nhi phan\n";
					cout << "\n2. Phep SAR so thap phan\n";
					cout << "\n3. Phep SAR so thap luc phan\n";
					cout << "\n0. Thoat \n";
					int lc;
					cout << "Nhap lua chon : ";
					cin >> lc;
					switch (lc)
					{
					case 1:
					{
						string s1;
						cout << "\nNhap chuoi nhi phan : ";
						cin >> s1;
						QInt test1(s1, BIN);
						int bit;
						cout << "\nNhap so bit can dich : ";
						cin >> bit;
						cout << "\nKet qua phep SAR\n";
						test1.SAR(bit);
						cout << test1.toString();
						system("pause");
					}
					break;
					case 2:
					{
						string s1;
						cout << "\nNhap chuoi thap phan : ";
						cin >> s1;
						QInt test1(s1, DEC);
						int bit;
						cout << "\nNhap so bit can dich : ";
						cin >> bit;
						cout << "\nKet qua phep SAR\n";
						test1.SAR(bit);
						cout << test1.toString();
						system("pause");
					}
					break;
					case 3:
					{
						string s1;
						cout << "\nNhap chuoi thap luc phan : ";
						cin >> s1;
						QInt test1(s1, HEX);
						int bit;
						cout << "\nNhap so bit can dich : ";
						cin >> bit;
						cout << "\nKet qua phep SAR\n";
						test1.SAR(bit);
						cout << test1.toString();
						system("pause");
					}
					break;
					case 0:
					{
						break;
					}
					break;
					default:
						break;
					}
					if (lc == 0)
						break;
				}
			}
			break;
			case 15:
			{

				while (1)
				{
					system("cls");
					cout << "\n1. Phep ROL so nhi phan\n";
					cout << "\n2. Phep ROL so thap phan\n";
					cout << "\n3. Phep ROL so thap luc phan\n";
					cout << "\n0. Thoat \n";
					int lc;
					cout << "Nhap lua chon : ";
					cin >> lc;
					switch (lc)
					{
					case 1:
					{
						string s1;
						cout << "\nNhap chuoi nhi phan : ";
						cin >> s1;
						QInt test1(s1, BIN);
						cout << "\nKet qua phep ROL\n";
						test1.ROL();
						cout << test1.toString();
						system("pause");
					}
					break;
					case 2:
					{
						string s1;
						cout << "\nNhap chuoi thap phan : ";
						cin >> s1;
						QInt test1(s1, DEC);
						cout << "\nKet qua phep ROL\n";
						test1.ROL();
						cout << test1.toString();
						system("pause");
					}
					break;
					case 3:
					{
						string s1;
						cout << "\nNhap chuoi thap luc phan : ";
						cin >> s1;
						QInt test1(s1, HEX);
						cout << "\nKet qua phep ROL\n";
						test1.ROL();
						cout << test1.toString();
						system("pause");
					}
					break;
					case 0:
					{
						break;
					}
					break;
					default:
						break;
					}
					if (lc == 0)
						break;
				}
			}
			break;
			case 16:
			{

				while (1)
				{
					system("cls");
					cout << "\n1. Phep ROR so nhi phan\n";
					cout << "\n2. Phep ROR so thap phan\n";
					cout << "\n3. Phep ROR so thap luc phan\n";
					cout << "\n0. Thoat \n";
					int lc;
					cout << "Nhap lua chon : ";
					cin >> lc;
					switch (lc)
					{
					case 1:
					{
						string s1;
						cout << "\nNhap chuoi nhi phan : ";
						cin >> s1;
						QInt test1(s1, BIN);
						cout << "\nKet qua phep ROR\n";
						test1.ROR();
						cout << test1.toString();
						system("pause");
					}
					break;
					case 2:
					{
						string s1;
						cout << "\nNhap chuoi thap phan : ";
						cin >> s1;
						QInt test1(s1, DEC);
						cout << "\nKet qua phep ROR\n";
						test1.ROR();
						cout << test1.toString();
						system("pause");
					}
					break;
					case 3:
					{
						string s1;
						cout << "\nNhap chuoi thap luc phan : ";
						cin >> s1;
						QInt test1(s1, HEX);
						cout << "\nKet qua phep ROR\n";
						test1.ROR();
						cout << test1.toString();
						system("pause");
					}
					break;
					case 0:
					{
						break;
					}
					break;
					default:
						break;
					}
					if (lc == 0)
						break;
				}
			}
			break;
			case 0:
			{
				break;
			}
			break;
			default:
				break;
			}
			if (k == 0)
				break;
		}
	}
	catch (const char *msg)
	{
		cout << "ERROR EXIT: " << msg << endl;
	}
}