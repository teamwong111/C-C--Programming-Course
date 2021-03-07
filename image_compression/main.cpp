#define _CRT_SECURE_NO_WARNINGS
#include"PicReader.h"
#include<cmath>
#include<fstream>
#include<iostream>
using namespace std;
//DCT����
double quotient[64] =
{
    0.353553, 0.353553, 0.353553, 0.353553, 0.353553, 0.353553, 0.353553, 0.353553,
    0.490393, 0.415735, 0.277785, 0.0975452, -0.0975451, -0.277785, -0.415735, -0.490393,
    0.46194, 0.191342, -0.191342, -0.46194, -0.46194, -0.191342, 0.191342, 0.46194,
    0.415735, -0.0975451, -0.490393, -0.277785, 0.277785, 0.490393, 0.0975453, -0.415735,
    0.353553, -0.353553, -0.353553, 0.353553, 0.353554, -0.353553, -0.353554, 0.353553,
    0.277785, -0.490393, 0.097545, 0.415735, -0.415735, -0.0975454, 0.490393, -0.277785,
    0.191342, -0.46194, 0.46194, -0.191342, -0.191342, 0.46194, -0.46194, 0.191341,
    0.0975452, -0.277785, 0.415735, -0.490393, 0.490393, -0.415735, 0.277785, -0.0975447
};  
//DCTת�þ���
double quotientT[64] = 
{
    0.353553, 0.490393, 0.46194, 0.415735, 0.353553, 0.277785, 0.191342, 0.0975452,
    0.353553, 0.415735, 0.191342, -0.0975451, -0.353553, -0.490393, -0.46194, -0.277785,
    0.353553, 0.277785, -0.191342, -0.490393, -0.353553, 0.097545, 0.46194, 0.415735,
    0.353553, 0.0975452, -0.46194, -0.277785, 0.353553, 0.415735, -0.191342, -0.490393,
    0.353553, -0.0975451, -0.46194, 0.277785, 0.353554, -0.415735, -0.191342, 0.490393,
    0.353553, -0.277785, -0.191342, 0.490393, -0.353553, -0.0975454, 0.46194, -0.415735,
    0.353553, -0.415735, 0.191342, 0.0975453, -0.353554, 0.490393, -0.46194, 0.277785,
    0.353553, -0.490393, 0.46194, -0.415735, 0.353553, -0.277785, 0.191341, -0.0975447
};
//��׼����������
const unsigned char standard_YTable[64] =
{
    16,  11,  10,  16,  24,  40,  51,  61,
    12,  12,  14,  19,  26,  58,  60,  55,
    14,  13,  16,  24,  40,  57,  69,  56,
    14,  17,  22,  29,  51,  87,  80,  62,
    18,  22,  37,  56,  68, 109, 103,  77,
    24,  35,  55,  64,  81, 104, 113,  92,
    49,  64,  78,  87, 103, 121, 120, 101,
    72,  92,  95,  98, 112, 100, 103,  99
};
//��׼ɫ��������
const unsigned char standard_CbCrTable[64] =
{
    17,  18,  24,  47,  99,  99,  99,  99,
    18,  21,  26,  66,  99,  99,  99,  99,
    24,  26,  56,  99,  99,  99,  99,  99,
    47,  66,  99,  99,  99,  99,  99,  99,
    99,  99,  99,  99,  99,  99,  99,  99,
    99,  99,  99,  99,  99,  99,  99,  99,
    99,  99,  99,  99,  99,  99,  99,  99,
    99,  99,  99,  99,  99,  99,  99,  99
};
//Z�����б�
const char zigzag[64] =
{
    0, 1, 5, 6,14,15,27,28,
    2, 4, 7,13,16,26,29,42,
    3, 8,12,17,25,30,41,43,
    9,11,18,24,31,40,44,53,
    10,19,23,32,39,45,52,54,
    20,22,33,38,46,51,55,60,
    21,34,37,47,50,56,59,61,
    35,36,48,49,57,58,62,63
};
//����ֱ��huffman�����
const char standard_Y_DC_Code[] = { 0, 0, 7, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0 };
const unsigned char standard_Y_DC_Value[] = { 4, 5, 3, 2, 6, 1, 0, 7, 8, 9, 10, 11 };
//���Ƚ���huffman�����
const char standard_Y_AC_Code[] = { 0, 2, 1, 3, 3, 2, 4, 3, 5, 5, 4, 4, 0, 0, 1, 0x7d };
const unsigned char standard_Y_AC_Value[] =
{
    0x01, 0x02, 0x03, 0x00, 0x04, 0x11, 0x05, 0x12,
    0x21, 0x31, 0x41, 0x06, 0x13, 0x51, 0x61, 0x07,
    0x22, 0x71, 0x14, 0x32, 0x81, 0x91, 0xa1, 0x08,
    0x23, 0x42, 0xb1, 0xc1, 0x15, 0x52, 0xd1, 0xf0,
    0x24, 0x33, 0x62, 0x72, 0x82, 0x09, 0x0a, 0x16,
    0x17, 0x18, 0x19, 0x1a, 0x25, 0x26, 0x27, 0x28,
    0x29, 0x2a, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39,
    0x3a, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49,
    0x4a, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59,
    0x5a, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69,
    0x6a, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79,
    0x7a, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89,
    0x8a, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97, 0x98,
    0x99, 0x9a, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7,
    0xa8, 0xa9, 0xaa, 0xb2, 0xb3, 0xb4, 0xb5, 0xb6,
    0xb7, 0xb8, 0xb9, 0xba, 0xc2, 0xc3, 0xc4, 0xc5,
    0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xd2, 0xd3, 0xd4,
    0xd5, 0xd6, 0xd7, 0xd8, 0xd9, 0xda, 0xe1, 0xe2,
    0xe3, 0xe4, 0xe5, 0xe6, 0xe7, 0xe8, 0xe9, 0xea,
    0xf1, 0xf2, 0xf3, 0xf4, 0xf5, 0xf6, 0xf7, 0xf8,
    0xf9, 0xfa
};
//ɫ��ֱ��huffman�����
const char standard_CbCr_DC_Code[] = { 0, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0 };
const unsigned char standard_CbCr_DC_Value[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };
//ɫ�Ƚ���huffman�����
const char standard_CbCr_AC_Code[] = { 0, 2, 1, 2, 4, 4, 3, 4, 7, 5, 4, 4, 0, 1, 2, 0x77 };
const unsigned char standard_CbCr_AC_Value[] =
{
    0x00, 0x01, 0x02, 0x03, 0x11, 0x04, 0x05, 0x21,
    0x31, 0x06, 0x12, 0x41, 0x51, 0x07, 0x61, 0x71,
    0x13, 0x22, 0x32, 0x81, 0x08, 0x14, 0x42, 0x91,
    0xa1, 0xb1, 0xc1, 0x09, 0x23, 0x33, 0x52, 0xf0,
    0x15, 0x62, 0x72, 0xd1, 0x0a, 0x16, 0x24, 0x34,
    0xe1, 0x25, 0xf1, 0x17, 0x18, 0x19, 0x1a, 0x26,
    0x27, 0x28, 0x29, 0x2a, 0x35, 0x36, 0x37, 0x38,
    0x39, 0x3a, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48,
    0x49, 0x4a, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58,
    0x59, 0x5a, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68,
    0x69, 0x6a, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78,
    0x79, 0x7a, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87,
    0x88, 0x89, 0x8a, 0x92, 0x93, 0x94, 0x95, 0x96,
    0x97, 0x98, 0x99, 0x9a, 0xa2, 0xa3, 0xa4, 0xa5,
    0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xb2, 0xb3, 0xb4,
    0xb5, 0xb6, 0xb7, 0xb8, 0xb9, 0xba, 0xc2, 0xc3,
    0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xd2,
    0xd3, 0xd4, 0xd5, 0xd6, 0xd7, 0xd8, 0xd9, 0xda,
    0xe2, 0xe3, 0xe4, 0xe5, 0xe6, 0xe7, 0xe8, 0xe9,
    0xea, 0xf2, 0xf3, 0xf4, 0xf5, 0xf6, 0xf7, 0xf8,
    0xf9, 0xfa
};
//�������λ
unsigned short highest[] = { 1,2,4,8,16,32,64,128,256,512,1024,2048,4096,8192,16384,32768 };
//��ʽhuffman�����Ӧ���Ⱥ�ֵ
struct Huff 
{
    int length;
    int value;
};
//��
class Jpgcreator
{
private:
    BYTE *data;//��������� 
    UINT x;//���ݾ���
    UINT y;//�����
    unsigned char YTable[64];//������
    unsigned char CbCrTable[64];
    Huff Y_DC_Table[12];//huffman�����
    Huff Y_AC_Table[256];
    Huff CbCr_DC_Table[12];
    Huff CbCr_AC_Table[256];
public:
    void jpgcreate();//�ܴ�������
    Jpgcreator(char[]);
    ~Jpgcreator();
private:
    void init();//��ʼ��
    void initquality(int);//�������ʼ��
    void inithuffman();//huffman������ʼ��
    void converthuffman(const char[], const unsigned char[], Huff[]);//ת�������
    void towrite(const char*, int, ofstream&);//д���ļ�
    void write_one_byte(unsigned char, ofstream&);//дһ��byte
    void write_two_byte(unsigned short, ofstream&);//д����byte
    void write_header(ofstream&);//д���ļ�ͷ
    void matrixmultiply(double[], double[], double[]);//DCT�任
    void compress(double[], short[], unsigned char[]);//����+Z��
    Huff getcode(int);//��ȡ����
    void huffmancoding(int&, int&, short[], const Huff[], const Huff[], Huff[]);//huffman����
    void write_huff(int, int&, int&, const Huff[], ofstream&);//������д���ļ�
};
//���캯��
Jpgcreator::Jpgcreator(char file[])
{
    PicReader imread;
    imread.readPic(file);
    imread.getData(data, x, y);
    memset(YTable, 0, sizeof(YTable));
    memset(CbCrTable, 0, sizeof(CbCrTable));
    memset(Y_DC_Table, 0, sizeof(Y_DC_Table));
    memset(Y_AC_Table, 0, sizeof(Y_AC_Table));
    memset(CbCr_DC_Table, 0, sizeof(CbCr_DC_Table));
    memset(CbCr_AC_Table, 0, sizeof(CbCr_AC_Table));
}
//��������
Jpgcreator::~Jpgcreator()
{
    delete[] data;
    data = nullptr;
}
//�������ʼ��
void Jpgcreator::initquality(int ratio)
{
    for (int i = 0; i < 64; i++)
    {
        int temp = (int)(standard_YTable[i] * ratio / 100);
        if (temp <= 0) 
            temp = 1;
        YTable[i] = (unsigned char)temp;

        temp = (int)(standard_CbCrTable[i] * ratio / 100);
        if (temp <= 0) 	
            temp = 1;
        CbCrTable[i] = (unsigned char)temp;
    }
}
//ת�������
void Jpgcreator::converthuffman(const char Code[], const unsigned char Value[], Huff Table[])
{
    int pos = 0;
    int value = 0;
    for (int i = 0; i < 16; i++)
    {
        for (int j = 0; j < Code[i]; j++)
        {
            Table[Value[pos]].value = value;
            Table[Value[pos]].length = i + 1;
            pos++;
            value++;
        }
        value <<= 1;
    }
}
//huffman������ʼ��
void Jpgcreator::inithuffman()
{
    converthuffman(standard_Y_DC_Code, standard_Y_DC_Value, Y_DC_Table);//��׼��ת��Ϊʵ�ʱ����

    converthuffman(standard_Y_AC_Code, standard_Y_AC_Value, Y_AC_Table);

    converthuffman(standard_CbCr_DC_Code, standard_CbCr_DC_Value, CbCr_DC_Table);

    converthuffman(standard_CbCr_AC_Code, standard_CbCr_AC_Value, CbCr_AC_Table);
}
//��ʼ��
void Jpgcreator::init()
{
    cout << "ע�⣺ѹ����Խ��ѹ���ļ�ԽС�����ᵼ��ͼƬ�����½�\n";
    cout << "������ѹ����(����1~100֮��)��\n";
    int ratio;
    cin >> ratio;
    initquality(ratio);
    inithuffman();
}
//д���ļ�
void Jpgcreator::towrite(const char* p, int size, ofstream& fout)
{   
    fout.write(p, size);
}
//дһ��byte
void Jpgcreator::write_one_byte(unsigned char value, ofstream& fout)
{
    towrite((char*)&value, 1, fout);
}
//д����byte
void Jpgcreator::write_two_byte(unsigned short value, ofstream& fout)
{
    unsigned short value1 = ((value >> 8) & 0xFF) | ((value & 0xFF) << 8);//�ߵ�λת��
    towrite((char*)&value1, 2, fout);
}
//д���ļ�ͷ
void Jpgcreator::write_header(ofstream& fout)
{
    //SOI
    write_two_byte(0xFFD8, fout);//ͼ��ʼ
    //APPO
    write_two_byte(0xFFE0, fout);//Ӧ�ó��������0	
    write_two_byte(16, fout);//����	
    towrite("JFIF", 5, fout);//��ʶ��		
    write_one_byte(1, fout);//�汾��		
    write_one_byte(1, fout);		
    write_one_byte(0, fout);//�ܶȵ�λ		
    write_two_byte(1, fout);//�����ܶ�		
    write_two_byte(1, fout);		
    write_one_byte(0, fout);//������Ŀ		
    write_one_byte(0, fout);			
    //DQT
    write_two_byte(0xFFDB, fout);//����������		
    write_two_byte(132, fout);//����			
    write_one_byte(0, fout);//������ID	                 			
    towrite((char*)YTable, 64, fout);//����
    write_one_byte(1, fout);//ID			
    towrite((char*)CbCrTable, 64, fout);//ɫ��
    //SOFO
    write_two_byte(0xFFC0, fout);//֡ͼ��ʼ			
    write_two_byte(17, fout);//���� 				
    write_one_byte(8, fout);//����				
    write_two_byte(y & 0xFFFF, fout);//�߶�  	
    write_two_byte(x & 0xFFFF, fout);//���	
    write_one_byte(3, fout);//������  				
    write_one_byte(1, fout);//��ɫ������Ϣ1				
    write_one_byte(0x11, fout);				
    write_one_byte(0, fout);				
    write_one_byte(2, fout);//��ɫ������Ϣ2				
    write_one_byte(0x11, fout);				
    write_one_byte(1, fout);				
    write_one_byte(3, fout);//��ɫ������Ϣ3				
    write_one_byte(0x11, fout);			
    write_one_byte(1, fout);				
    //DHT
    write_two_byte(0xFFC4, fout);//�����������		
    write_two_byte(0x01A2, fout);//����  		
    write_one_byte(0, fout);//��ID
    towrite(standard_Y_DC_Code, sizeof(standard_Y_DC_Code), fout);//��ͬλ������������	
    towrite((char*)standard_Y_DC_Value, sizeof(standard_Y_DC_Value), fout);//�������ݣ���ͬ��
    write_one_byte(0x10, fout);			
    towrite(standard_Y_AC_Code, sizeof(standard_Y_AC_Code), fout);
    towrite((char*)standard_Y_AC_Value, sizeof(standard_Y_AC_Value), fout);
    write_one_byte(0x01, fout);			
    towrite(standard_CbCr_DC_Code, sizeof(standard_CbCr_DC_Code), fout);
    towrite((char*)standard_CbCr_DC_Value, sizeof(standard_CbCr_DC_Value), fout);
    write_one_byte(0x11, fout);		
    towrite(standard_CbCr_AC_Code, sizeof(standard_CbCr_AC_Code), fout);
    towrite((char*)standard_CbCr_AC_Value, sizeof(standard_CbCr_AC_Value), fout);
    //SOS
    write_two_byte(0xFFDA, fout);//ɨ�迪ʼ		
    write_two_byte(12, fout);//����			
    write_one_byte(3, fout);//������			
    write_one_byte(1, fout);//��ɫ������Ϣ1			
    write_one_byte(0, fout);			                             
    write_one_byte(2, fout);//��ɫ������Ϣ2		
    write_one_byte(0x11, fout);			
    write_one_byte(3, fout);//��ɫ������Ϣ3			
    write_one_byte(0x11, fout);			
    write_one_byte(0, fout);//ѹ��ͼ������			
    write_one_byte(0x3F, fout);			
    write_one_byte(0, fout);			
}
//DCT�任
void Jpgcreator::matrixmultiply(double A[], double B[], double result[])
{
    //����˷�
    double t = 0;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            t = 0;
            for (int k = 0; k < 8; k++)
                t += A[i*8+k] * B[k*8+j];
            result[i*8+j] = t;
        }
    }
}
//����+Z��
void Jpgcreator::compress(double raw_data[], short final_data[], unsigned char table[])
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            double temp = raw_data[i * 8 + j] / table[zigzag[i * 8 + j]];
            final_data[zigzag[i * 8 + j]] = (short)(temp);
        }
    }
}
//��ȡ����
Huff Jpgcreator::getcode(int value)
{
    Huff temp;
    int length = 0;
    int value_fabs = (value > 0) ? value : -value;
    for (length = 0; value_fabs; value_fabs >>= 1)//��ȡ����
        length++;
    temp.value = value > 0 ? value : ((1 << length) + value - 1);//��ȡֵ
    temp.length = length;
    return temp;
};
//RLE+huffman����
void Jpgcreator::huffmancoding(int& form, int& Length, short data[], const Huff DC[], const Huff AC[], Huff Out[])
{
    Huff EOB = AC[0x00];//������Ϊ��
    Huff SIXTEEN_ZEROS = AC[0xF0];//����16��
    int length = 0;//��ʼ������
    int last = 63;//AC����������λ

    int diff = (int)(data[0] - form);//DC������ֵ
    form = data[0];//�ı�ǰֵ
    if (diff == 0)//��ֵΪ0
        Out[length++] = DC[0];
    else//��ֵ��Ϊ0
    {
        Huff a = getcode(diff);
        Out[length++] = DC[a.length];
        Out[length++] = a;
    }

    while ((last > 0) && (data[last] == 0))//��ȡ������λ
        last--;
    for (int i = 1; i <= last; )
    {
        int start = i;
        while ((data[i] == 0) && (i <= last))//��ȡ������ĸ��� 
            i++;
        int zeronum = i - start;
        if (zeronum >= 16)//����������������16
        {
            for (int j = 1; j <= zeronum / 16; j++)
                Out[length++] = SIXTEEN_ZEROS;
            zeronum = zeronum % 16;
        }
        Huff a = getcode(data[i]);
        Out[length++] = AC[(zeronum << 4) | a.length];
        Out[length++] = a;
        i++;
    }

    if (last != 63)//������λ�Ƿ񵽽���֮��
        Out[length++] = EOB;
    Length = length;
}
//������д���ļ�
void Jpgcreator::write_huff(int Length, int& byte, int& bytepos, const Huff data[], ofstream& fout)
{
    for (int i = 0; i < Length; i++)
    {
        int value = data[i].value;
        int length = data[i].length - 1;
        while (length >= 0)
        {
            if ((value & highest[length]) != 0)//���λ
                byte = byte | highest[bytepos];//�γ�һ��byte������
            length--;
            bytepos--;
            if (bytepos < 0)
            {
                write_one_byte((unsigned char)(byte), fout);//д���ļ�
                if (byte == 0xFF)                  
                    write_one_byte((unsigned char)(0x00), fout);//Ϊ�˱���ʶ��Ϊ��ʶ��                
                bytepos = 7;//��λ
                byte = 0;
            }
        }
    }
}
//�ܴ�������
void Jpgcreator::jpgcreate()
{
    init();//��ʼ��
    ofstream fout("lena.jpg", ios::binary | ios::out);//������ļ�
    if (!fout.is_open())
    {
        cout << "illegal";
        exit(-1);
    }
    write_header(fout);//д�ļ�ͷ

    int formY = 0, formCb = 0, formCr = 0;//DC����ǰֵ
    int byte = 0, bytepos = 7;//Ҫд���byte
    Huff Out[128];//huffman����Ľ��
    int Length;//�������
    double Y[64], Cb[64], Cr[64], tmp[64];
    short ydata[64], cbdata[64], crdata[64];
    for (unsigned int k = 0; k < x; k += 8)
    {
        for (unsigned int l = 0; l < y; l += 8)
        {
            for (int i = 0; i < 8; i++)
            {
                int t = (i + k) * y * 4 + l * 4;
                for (int j = 0; j < 8; j++)
                {
                    double R = data[t++];
                    double G = data[t++];
                    double B = data[t++];
                    t++;
                    Y[i * 8 + j] = (0.299f * R + 0.587f * G + 0.114f * B - 128);
                    Cb[i * 8 + j] = (-0.1687f * R - 0.3313f * G + 0.5f * B);
                    Cr[i * 8 + j] = (0.5f * R - 0.4187f * G - 0.0813f * B);
                }
            }
            //Y�Ĵ���
            matrixmultiply(quotient, Y, tmp);//DCT�任
            matrixmultiply(tmp, quotientT, Y);
            compress(Y, ydata, YTable);//����+Z��
            huffmancoding(formY, Length, ydata, Y_DC_Table, Y_AC_Table, Out);//Huffman����
            write_huff(Length, byte, bytepos, Out, fout);//����д���ļ�
            //Cb�Ĵ���ͬ�ϣ�
            matrixmultiply(quotient, Cb, tmp);
            matrixmultiply(tmp, quotientT, Cb);
            compress(Cb, cbdata, CbCrTable);
            huffmancoding(formCb, Length, cbdata, CbCr_DC_Table, CbCr_AC_Table, Out);
            write_huff(Length, byte, bytepos, Out, fout);
            //Cr�Ĵ���ͬ�ϣ�
            matrixmultiply(quotient, Cr, tmp);
            matrixmultiply(tmp, quotientT, Cr);
            compress(Cr, crdata, CbCrTable);
            huffmancoding(formCr, Length, crdata, CbCr_DC_Table, CbCr_AC_Table, Out);
            write_huff(Length, byte, bytepos, Out, fout);
        }
    }
    write_two_byte(0xFFD9, fout);//����
    fout.close();
}
//������
int main(int argc, char* argv[])
{
    if (argc != 3) 
    {
        cerr << "��ȷ����������Ŀ��ȷ" << endl;
        return -1;
    }

    if (!strcmp(argv[1], "-compress"))//ѹ��
    {
        Jpgcreator lena(argv[2]);
        lena.jpgcreate();//ǰ���ܴ�������
    }
    
    else if (!strcmp(argv[1], "-read"))//��ȡ
    {
        PicReader imread;
        imread.readPic(argv[2]);
        BYTE* Data = nullptr;
        UINT X, Y;
        imread.getData(Data, X, Y);
        imread.showPic(Data, X, Y);
        delete[] Data;
        Data = nullptr;
    }
    return 0;
}