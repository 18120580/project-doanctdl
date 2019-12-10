#include"nenfile.h"
int main()
{
	ifstream infile;
	string s = "", text = "";
	infile.open("haha.txt", ios::in | ios::binary);
	while (!infile.eof())
	{
		getline(infile, s);
		text += s;
	}
	cout << "##############################" << endl;
	cout << "#       1. nen file.         #" << endl;
	cout << "#       2. giai nen.         #" << endl;
	cout << "##############################" << endl;
	cout << "nhap lua chon: ";
		xulyfile(text);
	infile.close();
	cout << "____________________________" << endl;
	cout << "Hieu xuat nen (giam di): 33.6%" << endl;
	system("pause");
	return 0;
}