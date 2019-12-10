#include"nenfile.h"
Node* getNode(char ch, int freq, Node* left, Node* right)
{
	Node* node = new Node();

	node->ch = ch;
	node->freq = freq;
	node->left = left;
	node->right = right;

	return node;
}
// ####################################################
void encode(Node* root, string str,
	unordered_map<char, string>& huffmanCode)
{
	if (root == nullptr)
		return;

	// khi tìm thấy một node lá
	if (!root->left && !root->right) {
		huffmanCode[root->ch] = str;
	}

	encode(root->left, str + "0", huffmanCode);
	encode(root->right, str + "1", huffmanCode);
}
//###################################################
void decode(Node* root, int& index, string str, string& x)
{
	if (root == nullptr) {
		return;
	}
	//khi tìm thấy một node lá
	if (!root->left && !root->right)
	{
		x += root->ch;
		//cout << root->ch;
		return;
	}

	index++;

	if (str[index] == '0')
		decode(root->left, index, str, x);
	else
		decode(root->right, index, str, x);
}
//###################################################
char mahoa(string x)
{
	char ch;
	int tem = 0;
	for (int i = 0; i < x.length(); i++)
	{
		tem = tem + (_int64(x[i]) - '0') * pow(2, 7 - i);
	}
	ch = tem;
	return ch;
}
//####################################################
void giaima(char c, string& x)
{
	int n = _int64(c);
	if (n < 0) n += 256;
	//cout << "n = " << n << " " << c << endl;
	while (n > 0)
	{
		x.push_back(n % 2 + 48);
		n = n / 2;
	}
	while (x.length() < 8)
	{
		x.push_back(48);
	}
	reverse(x.begin(), x.end());
}
//###################################################
void xulyfile(string text)
{
	// đếm tần suất xuất hiện của đối tượng và lưu trữ nó trong bản đồ
	unordered_map<char, int> freq;
	for (char ch : text) {
		freq[ch]++;
	}

	//tạo một hàng đợi ưu tiên để lưu trữ trực tiếp node của cây huffman
	priority_queue<Node*, vector<Node*>, comp> pq;

	// tạo mỗi node lá cho một ký tự và thêm nó vào hàng đợi ưu tiên
	for (auto pair : freq) {
		pq.push(getNode(pair.first, pair.second, nullptr, nullptr));
	}

	// làm đến khi chỉ còn 1 node trong hàng đợi
	while (pq.size() != 1)
	{
		//xóa nút có độ ưu tiên cao nhất ( có tần xuất thấp nhất) trong hàng đợi
		Node* left = pq.top(); pq.pop();
		Node* right = pq.top();	pq.pop();

		// tạo một node nội bộ với 2 node con và có tần số bằng tổng 2 node và thêm node mới vào hàng đợi ưu tiên
		int sum = left->freq + right->freq;
		pq.push(getNode('\0', sum, left, right));
	}

	// lưu trữ con trỏ đến cây huffman
	Node* root = pq.top();

	// đi qua cây huffman lưu trữ mã trong bản đồ và in chúng
	unordered_map<char, string> huffmanCode;
	encode(root, "", huffmanCode);
	/*cout << "ma huffman la :\n" << endl;
	for (auto pair : huffmanCode) {
		cout << pair.first << " " << pair.second << endl;

	}*/
	string str = "";
	for (char ch : text) {
		str += huffmanCode[ch];
	}
	int lc;
	cin >> lc;
	if (lc == 1)
	{
		clock_t start = clock();
		fstream outfile;
		outfile.open("filedanen.dat", ios::out);
		//cout << "\nchuoi duoc ma hoa la :\n" << str << endl;
		string s = "";
		int i = 0;
		while (i < str.length())
		{
			s = str.substr(i, 8);
			//cout << "\ns=" << s << endl;
			outfile << mahoa(s);
			i = i + 8;
		}
		clock_t end = clock();
		cout << "thoi gian nen: " << float(end-start)/60 <<"s"<< endl;
		outfile.close();
	}
	else
	{
		clock_t bd = clock();
		string  str1 = "", str2 = "", str3 = "";
		string tem;
		fstream ifile;
		ifile.open("filedanen.dat", ios::in | ios::binary);
		while (!ifile.eof())
		{
			tem = "";
			getline(ifile, tem);
			str1 += tem;
		}

			//cout << "\n chuoi doc ra:" << str1 << endl;
			for (int i = 0; i < str1.length(); i++)
			{
				tem = "";
				giaima(str1[i], tem);
				str2 += tem;
			}
			str3 = str2.substr(0, str.length());
			//cout << "\nstr3= " << str3 << endl;

			tem = "";
			str1 = "";
			str2 = "";
			int index = -1;
			while (index < (int)str.size() - 2)
			{
				decode(root, index, str, tem);
			}
			clock_t kt = clock();
			//cout << "\ntem=" << tem << endl;
			ofstream f1;
			f1.open("giainen", ios::out);
			f1 << tem;
			cout << "thoi gian giai nen: " << float(kt - bd) / 60 << "s" << endl;
			f1.close();
			ifile.close();
			f1.close();
	}
}