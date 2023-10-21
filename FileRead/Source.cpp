#include<iostream>
#include<Windows.h>
#include<string>
#include<fstream>
#include<sstream>

#pragma warning(disable: 4018)

using namespace std;

string filepath_format(string p) { //������� �������������� ���������� ���� � �����
	string result;

	for (int i = 0; i < p.size(); i++) {
		if (p[i] == static_cast<char>(92)) {
			result = result + p[i] + p[i];
		}
		else {
			result = result + p[i];
		}
	}

	return result;
}

string filename_cut(string p) { //������� ��� �������� ����� �� ���� � �����
	string fname;

	for (int i = p.size() - 1; i >= 0; i--) {
		if (p[i] == static_cast<char>(92)) break;
		else {
			fname = p[i] + fname;
		}
	}

	return fname;
}

string fileex_cut(string p) { //������� ��� ��������� ���������� �����
	string exion;

	for (int i = p.size() - 1; i >= 0; i--) {
		exion = p[i] + exion;
		if (p[i] == '.') break;
	}

	return exion;
}

string fileToString(string p) { //�������, ����������� ����� ����� � ������
	ifstream input(p, ios::binary);
	input.seekg(0);
	if (input) {
		ostringstream out;
		out << input.rdbuf();

		input.close();
		return out.str();
	}
	else {
		input.close();
		return "";
	}
}

struct filestruct { //��������� �����, ��� ������� � ��������� ���������
	string path;
	string fpath;
	string name;
	string expression;
};

int main() {
	setlocale(LC_CTYPE, "rus");
	SetConsoleCP(1251); //����� ��������� �������� ��������
	SetConsoleOutputCP(1251); //����� ��������� ��������� ��������

	ifstream fin;
	ofstream fout;
	filestruct file;
	string content;

	string valid_exions[5] = { //���������� ������ � ������� ����������� ����� �������� � �������
		".txt", ".log", ".cpp", ".py", ".bat"
	};

	cout << "Input path: ";
	getline(cin, file.path);

	file.fpath = filepath_format(file.path);
	file.name = filename_cut(file.path);
	file.expression = fileex_cut(file.name);

	fout.open(file.name, ios::binary);

	content = fileToString(file.fpath);

	int valid_exions_len = sizeof(valid_exions) / sizeof(valid_exions[0]);
	for (int i = 0; i < valid_exions_len; i++) {
		if (file.expression == valid_exions[i]) {
			cout << content << endl;
			break;
		}
	}

	fout << content;

	fin.open(file.fpath);
	if (!fin) {
		cout << "������: ���������� ������� ����!" << endl;
		return 2;
	}

	fin.seekg(0, ios_base::end);
	cout << endl << "������� " << fin.tellg() << " ���� �� ����� " << file.name << endl;

	fout.close();
	system("pause");
	return 1;
}