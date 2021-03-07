#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<fstream>
#include<iostream>
#include<ctime>
#include <string> 
#include<cstring>
using namespace std;
#define CLOCKS_PER_SEC ((clock_t)1000)
#define window_length 4100//滑动窗口长
#define cache 650//缓冲区长
#define max_length 10400000//原文件大小
struct CODE //lz77编码的结构体
{
    int off, len;
    char c;
};
string tocode;//用于压缩输出
CODE zip_file[max_length] = { 0,0,0 };
char ori_file[max_length] = { 0 };//读入的字符串
char decode_file[max_length] = { 0 };//解压后的字符串

void origin_file_in(char* s)  //从文件读入字符串
{
    ifstream fin(s, ios::binary);
    if (!fin)
    {
        cerr << "Can not open the input file!" << endl;
        exit(-1);
    }
    fin.read(ori_file, max_length);
    fin.close();
}

int match(char* s, int sn, char* t, int& longest)//字符串的匹配
{
    //找到最长的匹配字符串
    int i = 0, j = 0, match = 0, offset = 0;
    longest = 0;
    for (int k = 0; k < sn; k++)
    {
        i = k;
        j = 0;
        match = 0;
        while (i < sn && j < cache)//逐个匹配
        {
            if (s[i] != t[j])
                break;
            match++;
            i++;
            j++;
        }
        if (match > longest)
        {
            offset = k;
            longest = match;
        }
    }
    return offset;
}

void code()//编码
{
    int maxoff = 0;
    int maxlen = 0;
    int all_length = strlen(ori_file), window_end = 0, i = 1, offset = 0, len = 0;
    if (all_length > 0)//对字符串第一个字符进行编码输出
    {
        tocode += "0 0 ";
        tocode += ori_file[0];
        tocode += ' ';
    }
    for (; i < all_length; i++)
    {
        if (i < window_length)//更新窗口右边界
            window_end = i;
        else
            window_end = window_length;
        offset = match(ori_file + i - window_end, window_end, ori_file + i, len);//匹配结果返回
        if (len == 0)
            tocode += '0';
        else
            tocode += to_string(window_end - offset);
        tocode += ' ';
        tocode += to_string(len);
        tocode += ' ';
        tocode += ori_file[i + len];
        tocode += ' ';
        i = i + len;
    }
}

void zip_file_out(char* s)  //将压缩的字符串输出到文件
{
    ofstream fout(s);
    if (!fout)
    {
        cerr << "Can not open the output file!" << endl;
        exit(-1);
    }
    fout << tocode;
    fout.close();
}

void decode(char* s)//解压
{
    ifstream fin(s);
    if (!fin)
    {
        cerr << "Can not open the input file!" << endl;
        exit(-1);
    }
    int co = 0;
    while (!fin.eof())
    {
        fin >> zip_file[co].off >> zip_file[co].len;
        fin.get();
        fin.get(zip_file[co].c);
        co++;
    }
    fin.close();
    int count = 0;
    int i = 0, j = 0;
    //解码
    for (; i < co; ++i)
    {
        if (zip_file[i].len == 0)//正常赋值
        {
            decode_file[count] = zip_file[i].c;
            ++count;
        }
        else//偏移赋值
        {
            for (j = 0; j < zip_file[i].len; ++j)
            {
                decode_file[count + j] = decode_file[count - zip_file[i].off + j];
            }
            decode_file[count + j] = zip_file[i].c;
            count = count + zip_file[i].len + 1;
        }
    }
}

void decode_file_out(char* s)//将解码输出到文件中
{
    ofstream fout(s);
    if (!fout)
    {
        cerr << "Can not open the output file!" << endl;
        exit(-1);
    }
    fout << decode_file;
    fout.close();
}

int main(int argc, char* argv[])
{
    cout << "Zipper 0.001! Author: root" << endl;
    cout << "可选择压缩或解压" << endl;
    if (argc != 4) {
        cerr << "Please make sure the number of parameters is correct." << endl;
        return -1;
    }

    if (strcmp(argv[3], "zip")&& strcmp(argv[3], "unzip")) {
        cerr << "Unknown parameter!\nCommand list:\nzip\nunzip" << endl;
        return -1;
    }
    if (!strcmp(argv[3], "zip"))
    {
        clock_t starttime, finishtime;//记录时间
        double  duration;
        starttime = clock();
        origin_file_in(argv[1]);
        code();
        zip_file_out(argv[2]);
        finishtime = clock();
        duration = ((double)finishtime - (double)starttime) / CLOCKS_PER_SEC;
        cout << "压缩用时：" << duration << "s" << endl;
    }
    else if (!strcmp(argv[3], "unzip"))
    {
        clock_t starttime, finishtime;//记录时间
        double  duration;
        starttime = clock();
        decode(argv[1]);
        decode_file_out(argv[2]);
        finishtime = clock();
        duration = ((double)finishtime - (double)starttime) / CLOCKS_PER_SEC;
        cout << "解压用时：" << duration << "s" << endl;
    }
    return 0;
}
