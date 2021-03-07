#pragma comment(lib, "winmm.lib")
#include"all.h"
#include"PicReader.h"
#include"FastPrinter.h"
using namespace std;
BYTE mydata[512][512][4];//��Array������ݾ������ת��mydata������Array�๹�졢����Ƶ������������
char asciistrength[] = { 'M','N','H','Q','$','O','C','?','7','>','!',':','-',';','.' };//���Ҷȷ�Ϊ15��
void get_video()
{
    clock_t CLOCKS_PER_1000SEC = ((clock_t)1);//����ʱ������ת��
    const int SIZE = 160 * 45;//�̶���С��������������Ƶ����Ҫ�ı�
    //const int SIZE = 320 * 90;
    BYTE* frontColorBuffer = new BYTE[SIZE * 3];
    BYTE* backColorBuffer = new BYTE[SIZE * 3];
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            frontColorBuffer[i * 3 + j] = 0;
            backColorBuffer[i * 3 + j] = 255;
        }
    }
    FastPrinter printer(160, 45, 5);
    //FastPrinter printer(320, 90, 5);
    PlaySoundA("resource1\\1.wav", NULL, SND_FILENAME | SND_ASYNC);//��Ƶ����
    //PlaySoundA("resource2\\2.wav", NULL, SND_FILENAME | SND_ASYNC);
    clock_t start = clock();//��ʼʱ��
    clock_t now;
    for (int z = 1; z <= 661; z++)//ע�⻻��ƵҪ����661Ϊ501
    {
        if (z == 1)
            Sleep(700);
        string c = "resource1\\\\file\\\\";
        //string c = "resource2\\\\file\\\\";
        c += to_string(z);
        c += ".txt";
        ifstream fin(c, ios::binary);
        char* dataBuffer = new char[SIZE];
        fin.read(dataBuffer, SIZE);//�ļ���ȡ
        printer.cleanSrceen();
        printer.setData(dataBuffer, frontColorBuffer, backColorBuffer);
        printer.draw(true);
        now = clock();//��ȡ��ǰʱ��
        //ȷ��Sleepʱ��
        double sleeptime = double(start +double(700)+ 1000 * double(z) / 24 - now / CLOCKS_PER_1000SEC);
        if (sleeptime < 0)
            sleeptime = 10;
        Sleep((DWORD)sleeptime);
        delete[] dataBuffer;
    }
    delete[] frontColorBuffer;
    delete[] backColorBuffer;
    getchar();
    //�ָ������С
    CONSOLE_FONT_INFOEX cfi;
    cfi.cbSize = sizeof(cfi);
    GetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
    cfi.dwFontSize.X = 0;
    cfi.dwFontSize.Y = 16;
    SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
}
void get_txt()
{
    const int SIZE = 160 * 45;//��С�̶���������ڶ�����Ƶ����Ҫ������ע�͵�
    //const int SIZE = 320 * 90;
    PicReader imread;
    UINT x, y;
    BYTE* frontColorBuffer = new BYTE[SIZE * 3];
    BYTE* backColorBuffer = new BYTE[SIZE * 3];
    //JPGתTXT
    for (int z = 1; z <= 661; z++)//ע�⻻��ƵҪ����661Ϊ501
    {
        Array data;
        //�γ��ַ�������Ϊ�ļ�·��
        string a = "resource1\\\\pic\\\\(";
        string c = "resource1\\\\file\\\\";
        //string a = "resource2\\\\pic\\\\(";
        //string c = "resource2\\\\file\\\\";
        a += to_string(z);
        a += ").jpg";
        char b[25];
        memset(b, 0, sizeof(b));
        for (int i = 0; i < a.size(); i++)
        {
            b[i] = a[i];
        }
        c += to_string(z);
        c += ".txt";

        imread.readPic(b);
        imread.getData(data, x, y);
        data.ischild = false;//ʹ��data������
        //ѹ��
        for (UINT k = 0; k < y; k += 4)
        {
            for (UINT l = 0; l < x; l += 2)
            {
                int sumr = 0;
                int sumg = 0;
                int sumb = 0;
                int suma = 0;
                for (int i = 0; i < 4; i++)
                {
                    for (int j = 0; j < 2; j++)
                    {
                        sumr += data[k + i][l + j][0];
                        sumg += data[k + i][l + j][1];
                        sumb += data[k + i][l + j][2];
                        suma += data[k + i][l + j][3];
                    }
                }
                mydata[k / 4][l / 2][0] = sumr / 8;
                mydata[k / 4][l / 2][1] = sumg / 8;
                mydata[k / 4][l / 2][2] = sumb / 8;
                mydata[k / 4][l / 2][3] = suma / 8;
            }
        }
        //ת�Ҷ�
        char* dataBuffer = new char[SIZE];
        char asciistrength[] = { 'M','N','H','Q','$','O','C','?','7','>','!',':','-',';','.' };
        for (UINT i = 0; i < y / 4; i++)
        {
            for (UINT j = 0; j < x / 2; j++)
            {
                BYTE graydata = (mydata[i][j][0] * 299 + mydata[i][j][1] * 587 + mydata[i][j][2] * 114 + 500) / 1000;
                BYTE asciiindex = graydata / 18;
                dataBuffer[(i * x / 2 + j)] = asciistrength[asciiindex];
            }
        }

        //txtд���ļ�
        ofstream fout(c, ios::binary);
        if (!fout)
        {
            cerr << "Can not open the output file!" << endl;
            exit(-1);
        }
        fout.write((char*)&dataBuffer[0], SIZE);
        fout.close();
        delete[] dataBuffer;
        dataBuffer = nullptr;
    }
    delete[] frontColorBuffer;
    delete[] backColorBuffer;
    cout << "תtxt����\n";
    getchar();
}
void Video_output()
{
    cout << "����1����JPG�ļ�ת��Ϊ�ַ����飬������txt�ļ�(��ǰ����Դ�ļ�������txt�ļ�)\n";
    cout << "����2����ȡtxt�ļ����õ��ַ�����Ƶ\n";
    int n;
    cin >> n;
    if (n == 1)
    {
        get_txt();
    }
    else if (n == 2)
    {
        get_video();
    }
    else
    {
        cout << "������󣬷������˵�\n";
        getchar();
        return;
    }
}
void Pic_output()
{
    PicReader imread;

    //ͼƬ
    imread.readPic("classic_picture\\airplane.jpg"); //512*512
    //imread.readPic("classic_picture\\baboon.jpg"); //512*512
    //imread.readPic("classic_picture\\barbara.jpg"); //720*580
    //imread.readPic("classic_picture\\cameraman.jpg");//256*256
    //imread.readPic("classic_picture\\compa.png"); //385*184
    //imread.readPic("classic_picture\\goldhill.jpg"); //720*576
    //imread.readPic("classic_picture\\lena.jpg"); //400*400
    //imread.readPic("classic_picture\\lena1.jpg"); //70*70
    //imread.readPic("classic_picture\\milkdrop.jpg");//512*512
    //imread.readPic("classic_picture\\peppers.jpg"); //512*512
    //imread.readPic("classic_picture\\woman.jpg"); //512*512
     
    UINT x, y;
    Array data;
    imread.getData(data, x, y);//��ȡdata��x��y
    data.ischild = false;//ʹ��data��������
    int SIZEX, SIZEY, compressX, compressY;//x���ȣ�y���ȣ�xѹ������yѹ����
    if (x <= 200 && y <= 200)//С��200*200��ѹ��
    {
        compressX = compressY = 1;
    }
    else//��x����ȡ2��y����ȡ4��2*4С�飬��Ϊѹ�����ݵ�һ��С�����ѹ��
    {
        compressX = 2;
        compressY = 4;
    }
    SIZEX = x / compressX;
    SIZEY = y / compressY;
    int SIZE = SIZEX * SIZEY;//SIZEΪѹ������������
    int x1 = SIZEX * compressX;//x��������ȡż��
    int y1 = SIZEY * compressY;//y��������ȡ4�ı���
    //ѹ��
    for (int k = 0; k < y1; k += compressY)
    {
        for (int l = 0; l < x1; l += compressX)
        {
            int sumr = 0;
            int sumg = 0;
            int sumb = 0;
            int suma = 0;
            for (int i = 0; i < compressY; i++)
            {
                for (int j = 0; j < compressX; j++)
                {
                    sumr += data[k + i][l + j][0];
                    sumg += data[k + i][l + j][1];
                    sumb += data[k + i][l + j][2];
                    suma += data[k + i][l + j][3];
                }
            }
            mydata[k / compressY][l / compressX][0] = sumr / 8;
            mydata[k / compressY][l / compressX][1] = sumg / 8;
            mydata[k / compressY][l / compressX][2] = sumb / 8;
            mydata[k / compressY][l / compressX][3] = suma / 8;
        }
    }
    //�����ѹ������x�������ݳ�2������ͼƬ����
    if (compressX == 1 && compressY == 1)
        SIZE *= 2;
    char* dataBuffer = new char[SIZE];
    BYTE* frontColorBuffer = new BYTE[(size_t)SIZE * 3];
    BYTE* backColorBuffer = new BYTE[(size_t)SIZE * 3];
    //תΪ�Ҷ�����
    for (int i = 0; i < SIZEY; i++)
    {
        for (int j = 0; j < SIZEX; j++)
        {
            BYTE graydata = (mydata[i][j][0] * 299 + mydata[i][j][1] * 587 + mydata[i][j][2] * 114 + 500) / 1000;
            BYTE asciiindex = graydata / 18;
            if (compressX == 1 && compressY == 1)
            {
                int pos = 2 * (i * SIZEX + j);
                if (pos < SIZE)
                {
                    dataBuffer[pos] = asciistrength[asciiindex];
                    dataBuffer[pos + 1] = asciistrength[asciiindex];
                }
            }
            else
            {
                int pos = i * SIZEX + j;
                if (pos < SIZE)
                    dataBuffer[pos] = asciistrength[asciiindex];
            }
        }
    }
    //ǰ��ɫ����ɫ��ֵ
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            frontColorBuffer[i * 3 + j] = 0;
            backColorBuffer[i * 3 + j] = 255;
        }
    }
    //����ַ���
    if (compressX == 1 && compressY == 1)
    {
        SIZEX *= 2;
        FastPrinter printer(SIZEX, SIZEY, 5);
        printer.setData(dataBuffer, frontColorBuffer, backColorBuffer);
        printer.draw(true);
        getchar();
        getchar();
        //�ָ������С
        CONSOLE_FONT_INFOEX cfi;
        cfi.cbSize = sizeof(cfi);
        GetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
        cfi.dwFontSize.X = 0;
        cfi.dwFontSize.Y = 16;
        SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
    }
    else
    {
        FastPrinter printer(SIZEX, SIZEY, 5);
        printer.setData(dataBuffer, frontColorBuffer, backColorBuffer);
        printer.draw(true);
        getchar();
        getchar();
        //�ָ������С
        CONSOLE_FONT_INFOEX cfi;
        cfi.cbSize = sizeof(cfi);
        GetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
        cfi.dwFontSize.X = 0;
        cfi.dwFontSize.Y = 16;
        SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
    }
    
    delete[] dataBuffer;
    delete[] frontColorBuffer;
    delete[] backColorBuffer;

    return;
}