#pragma once
#include<iostream>
#include<string>
#include <queue>
#include <unordered_map>
#include<fstream>
#include<ctime>
using namespace std;
// node của cây
struct Node
{
	char ch;
	int freq;
	Node* left, * right;
};
// so sánh đối tượng để đặt vào heap
struct comp
{
	bool operator()(Node* l, Node* r)
	{
		// ưu tiên mục đối tượng có tần suất thấp nhất.
		return l->freq > r->freq;
	}
};
// hàm tạo một node mới
Node* getNode(char ch, int freq, Node* left, Node* right);
// đi qua cây Huffman và lưu trữ mã trong bản đồ
void encode(Node* root, string str,unordered_map<char, string>& huffmanCode);
// duyệt qua cây huffman và giải mã chuỗi đã được mã hóa
void decode(Node* root, int& index, string str, string& x);
// ma hoa moi 8 bit thanh 1 ky tu trong ma ascii
char mahoa(string x);
//chuyen ky tu trong ma ascii thanh 1 chuoi gom 8 bit
void giaima(char c, string& x);
//xây dựng cây huffman và giải mã văn bản đưa vào
//void buildHuffmanTree(string text,string& str,Node* &root);
// nen file: chuyen cac ky tu ve ma nhi phan theo ma tren cay huffman sau do dua ve dang ky tu trong bang ma ascii
void xulyfile(string text);
