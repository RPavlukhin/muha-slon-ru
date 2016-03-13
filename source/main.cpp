#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <algorithm>
#include <iterator>
#include <list>
#include <queue>
#include <fstream>

#include "branch.h"
#include "wordrouter.h"


using namespace std;

int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "rus");

   if (argc!=4) {
        std::wcerr << "������ �������� ���������! ������ ���������: [��� ���������] [���� � �������] [������ �����] [��������� �����]" << endl;
        return EXIT_FAILURE;
    }    

    set <string> dict;
    ifstream dictfile;

    // ��������� ���� �� ��������
    dictfile.open (argv[1], std::ios::in);
    if(!dictfile) {
        std::wcerr<<"������ ��� �������� �����"<< dictfile <<endl;
        return EXIT_FAILURE;
    }

    string tmp;
    while (!dictfile.eof())
        {
         std::getline(dictfile,tmp);
         //��������� � �������
         if (!tmp.empty()) dict.insert(tmp);
        }
    dictfile.close();

    // ��������� �� ������� �������� ������ � ��������� �����
    string startword = argv[2];
    string finword = argv[3];

	//���������, ���������� �� ����� �����
	if (startword.length()!=finword.length()) 
	{
        wcerr << "����� ��������� �����!" << endl;
		return EXIT_FAILURE;
	}

	// ���������, ���� �� ��������� � �������� ����� � �������
	if (dict.find(startword)==dict.end()) {
        wcerr << "������� ����� ��� � �������!" << endl;
		return EXIT_FAILURE;
	}
	if (dict.find(finword)==dict.end()) 
	{
        wcerr << "������� ����� ��� � �������!" << endl;
		return EXIT_FAILURE;
	}


    WordRouter wr(dict);
   // ������ �������
   std::list <string> route;
   int res = wr.CreateRoute(startword,finword,route);
   

    // ������� ��� �� �����
   for (auto it = route.begin(); it !=route.end(); ++it)
    {
        cout << *it << endl;
    }
	
   if (route.empty()) wcout << "� ������� �� ������� ���������� ������� ����� �������"<<endl;

    return res;
}

