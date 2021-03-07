#include <iostream>
#include <conio.h>
#include <opencv2/opencv.hpp>
#include<queue>
using namespace cv;
using namespace std;
//ʹ�õ�������,idxΪ�������ͨ��ͼ�����й����������ʹ�õ�����
int a[258 * 258] = { 0 }, b[256 * 256] = { 0 }, c[256 * 256] = { 0 }, idx[30010] = { 0 };
struct three //����ͨ����ȡ�Ľṹ��
{
	int blu;
	int gree;
	int re;
}d[30010],e[30010];
struct place //�������ͨ��ͼ�����й����������ʹ�õĽṹ��
{
	int x;
	int y;
	int num;
}f[256 * 256];
queue<int> q, p;//�������ͨ��ͼ�����й����������ʹ�õĶ���
void menu()//�˵�
{
	cout << "*********************************************************" << endl;
	cout << " *      1 ����ӷ�      2 ��������      3 ����ת��      *" << endl;
	cout << " *      4 ����˷�      5 Hadamard�˻�  6 ������      *" << endl;
	cout << " *      7 ���Ӧ��      8 OTSU�㷨      9 ��������      *" << endl;
	cout << " *      0 �˳�ϵͳ	                                     *" << endl;
	cout << "*********************************************************" << endl;
	cout << "ѡ��˵���<0~9>:" << endl;
	return;
}
void matriplus()//����ӷ�
{
	int m, n;
	cout << "����������������к�������" << endl;
	cin >> m >> n;
	cout << "���������a��" << endl;
	for (int i = 0; i < n * m; i++)
		cin >> a[i];
	cout << "���������b��" << endl;
	for (int i = 0; i < n * m; i++)
	{
		cin >> b[i];
		a[i] += b[i];
	}
	cout << "���Ϊ��";
	for (int i = 0; i < n * m; i++)
	{
		if (i % n == 0)
			cout << endl;
		cout << a[i] << " ";
	}
	memset(a, 0, sizeof(a));
	memset(b, 0, sizeof(b));
	return;
}
void nummulti()//��������
{
	int x, m, n;
	cout << "�����������к������Լ�����Ҫ�˵�����" << endl;
	cin >> m >> n>> x;
	cout << "���������" << endl;
	for (int i = 0; i < n * m; i++)
	{
		cin >> a[i];
		a[i] *= x;
	}
	cout << "���Ϊ��";
	for (int i = 0; i < n * m; i++)
	{
		if (i % n == 0)
			cout << endl;
		cout << a[i] << " ";
	}
	memset(a, 0, sizeof(a)); 
	return;
}
void matritrans()//����ת��
{
	int m, n;
	cout << "�����������к�������" << endl;
	cin >> m >> n;
	cout << "���������" << endl;
	for (int i = 0; i < n * m; i++)
	{
		cin >> a[i];
		int j = i / n;
		int k = i % n;
		b[j + k * m] = a[i];
	}
	cout << "���Ϊ��";
	for (int i = 0; i < n * m; i++)
	{
		if (i % m == 0)
			cout << endl;
		cout << b[i] << " ";
	}
	memset(a, 0, sizeof(a));
	memset(b, 0, sizeof(b));
	return;
}
void matrimulti()//����˷�
{
	int m, n, p, q;
	cout << "�������һ���͵ڶ���������к�������" << endl;
	cin >> m >> n >> p >> q;
	if (n != p)
	{
		cout << "�������ܽ��г˷�" << endl;
		return;
	}
	cout << "���������a��" << endl;
	for (int i = 0; i < n * m; i++)
		cin >> a[i];
	cout << "���������b��" << endl;
	for (int i = 0; i < p * q; i++)
		cin >> b[i];
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < q; j++)
		{
			for (int k = 0; k < n; k++)
				c[i * q + j] += a[i * n + k] * b[k * q + j];
		}
	}
	cout << "���Ϊ��";
	for (int i = 0; i < m * q; i++)
	{
		if (i % q == 0)
			cout << endl;
		cout << c[i] << " ";
	}
	memset(a, 0, sizeof(a));
	memset(b, 0, sizeof(b));
	memset(c, 0, sizeof(c));
	return;
}
void hadamulti()//����Hadamard�˻�
{
	int m, n;
	cout << "����������������к�������" << endl;
	cin >> m >> n;
	cout << "���������a��" << endl;
	for (int i = 0; i < n * m; i++)
		cin >> a[i];
	cout << "���������b��" << endl;
	for (int i = 0; i < n * m; i++)
	{
		cin >> b[i];
		a[i] *= b[i];
	}
	cout << "���Ϊ��";
	for (int i = 0; i < n * m; i++)
	{
		if (i % n == 0)
			cout << endl;
		cout << a[i] << " ";
	}
	memset(a, 0, sizeof(a));
	memset(b, 0, sizeof(b));
	return;
}
void conv(int sel)//�����������ڵ�6�͵�7�����ܣ�
{
	int n, m = 0, p = 0, q;
	int d[9] = { 0 };
	switch (sel)//ѡ������
	{
	case 0:
	{
		for (int i = 0; i < 9; i++)
		{
			if (i % 3 == 0)
				d[i] = -1;
			else if (i % 3 == 2)
				d[i] = 1;
		}
		break;
	}
	case 1:
	{
		for (int i = 0; i < 9; i++)
		{
			d[i] = 1;
		}
		break;
	}
	case 2:
	{
		d[0] = 1; d[1] = 2; d[2] = 1; d[3] = 0; d[4] = 0; d[5] = 0; d[6] = -1; d[7] = -2; d[8] = -1;
		break;
	}
	case 3:
	{
		d[0] = -1; d[1] = 0; d[2] = 1; d[3] = -2; d[4] = 0; d[5] = 2; d[6] = -1; d[7] = 0; d[8] = 1;
		break;
	}
	case 4:
	{
		for (int i = 0; i < 9; i++)
		{
			if (i == 4)
				d[i] = 9;
			else
				d[i] = -1;
		}
		break;
	}
	case 5:
	{
		d[0] = -1; d[1] = -1; d[2] = 0; d[3] = -1; d[4] = 0; d[5] = 1; d[6] = 0; d[7] = 1; d[8] = 1;
		break;
	}
	case 6:
	{
		d[0] = 1; d[1] = 2; d[2] = 1; d[3] = 2; d[4] = 4; d[5] = 2; d[6] = 1; d[7] = 2; d[8] = 1;
		break;
	}
	default:
	{
		cout << "�������" << endl;
		return;
	}
	}
	if (sel == 0)//���ǵ�6������
	{
		cout << "���������Ľ�����" << endl;
		cin >> n;
		cout << "���������" << endl;
		for (int i = n + 3; i < n * n + 3 * n + 1; i++)//��Padding
		{
			if (i % (n + 2) == 0 || i % (n + 2) == n + 1)
				continue;
			else
				cin >> a[i];
		}
	}
	else
	{
		n = 256;//���ǵ�7������
	}
	for (int i = 0; i < n * (n + 2); i++)//���о��
	{
		if (i % (n + 2) == n || i % (n + 2) == n + 1)
			continue;
		else
		{
			int k[9] = { 0 };//���9����Ľ��
			m = 0;
			q = 0;
			for (int j = i; j < i + 2 * n + 7; j++)
			{
				if (j % (n + 2) == i % (n + 2))
				{
					k[m] = a[j] * d[q % 9];
					m++;
					q++;
				}
				else if (j % (n + 2) == (i + 1) % (n + 2))
				{
					k[m] = a[j] * d[q % 9];
					m++;
					q++;
				}
				else if (j % (n + 2) == (i + 2) % (n + 2))
				{
					k[m] = a[j] * d[q % 9];
					m++;
					q++;
				}
			}
			for (int l = 0; l < 9; l++)//��9���������
				c[p] += k[l];
			if(sel!=0)//���ֵ�6�����ܺ͵�7������
				c[p] /= 9;
			if (c[p] < 0&&sel!=0)//�ж�unisigned char�����Ƿ�Խ��
				c[p] = 0;
			p++;
		}
	}
	if (sel == 0)
	{
		cout << "���Ϊ��" << endl;
		for (int i = 0; i < n * n; i++)
		{
			if (i % n == 0)
				cout << endl;
			cout << c[i] << " ";
		}
		memset(a, 0, sizeof(a));
		memset(c, 0, sizeof(c));
		return;
	}
	return;
}
void demo()//���Ӧ��
{
	int sel;
	Mat image = imread("./resources/1.jpg", 0);//��ͨ����ȡ
	for (int i = 0; i < 256; i++)
		for (int j = 0; j < 256; j++)
		{
			b[i * 256 + j] = image.at<uchar>(j, i);//����ת����
		}
	int l = 0;
	for (int i = 256 + 3; i < 256 * 256 + 3 * 256 + 1; i++)//��Padding
	{
		if (i % (256 + 2) == 0 || i % (256 + 2) == 256 + 1)
			continue;
		else
		{
			a[i] = b[l];
			++l;
		}
	}
	cout << "������˵Ĵ���" << endl;
	cin >> sel;
	conv(sel);
	Mat result = Mat(256, 256, CV_8U, Scalar::all(0));
	for (int i = 0; i < 256; i++)
		for (int j = 0; j < 256; j++)
		{
			result.at<uchar>(j, i) = (unsigned char)c[i * 256 + j];
		}
	memset(a, 0, sizeof(a));
	memset(b, 0, sizeof(b));
	memset(c, 0, sizeof(c));
	imshow("������", result);
	waitKey(0);
	return;
}
int myotsu(Mat& images,int what)//Ѱ����ֵ
{
	int th=0;
	const int Scale = 256;	//��ͨ���ܻҶ�256��
	int count[Scale] = { 0 };
	int sum = images.cols * images.rows;
	float Pro[Scale] = { 0 };//ÿ���Ҷ�ֵ��ռ�����ر���
	float w0, w1, v0, v1, u0, u1, deltaTmp, deltaMax = 0;
	if (what == 0)
	{
		for (int i = 0; i < images.cols; i++)
		{
			for (int j = 0; j < images.rows; j++)
			{
				count[images.at<uchar>(j, i)]++;//ͳ��ÿ���Ҷȼ������صĸ���  
			}
		}
	}
	else
	{
		for (int i = 0; i < images.cols; i++)
		{
			for (int j = 0; j < images.rows; j++)
			{
				count[d[j * images.cols + i].blu]++;//ͳ��ÿ���Ҷȼ������صĸ���  
			}
		}
	}
	for (int i = 0; i < Scale; i++)
	{
		Pro[i] = count[i] * 1.0 / sum;//����ÿ���Ҷȼ���������Ŀռ����ͼ��ı���  
	}

	for (int i = 0; i < Scale; i++)//������һ������䷽�����
	{
		w0 = w1 = v0 = v1 = u0 = u1 = deltaTmp = 0;
		for (int j = 0; j < Scale; j++)
		{
			if (j <= i)
			{
				w0 += Pro[j];
				v0 += j * Pro[j];
			}
			else
			{
				w1 += Pro[j];
				v1 += j * Pro[j];
			}
		}
		u0 = v0 / w0;
		u1 = v1 / w1;
		deltaTmp = (float)(w0 * w1 * pow((u0 - u1), 2)); //���ʽ
		if (deltaTmp > deltaMax)
		{
			deltaMax = deltaTmp;
			th = i;
		}
	}
	return th;
}
void otsu()//OTSU�㷨
{
	Mat image = imread("./resources/1.jpg", 0);
	int th=myotsu(image,0);//����ֵ
	for (int i = 0; i < image.rows; i++)
		for (int j = 0; j < image.cols; j++)
		{
			if (image.at<uchar>(i, j) > th)
			{
				image.at<uchar>(i, j) = 255;
			}
			else
			{
				image.at<uchar>(i, j) = 0;
			}
		}
	imshow("OTSU", image);
	waitKey(0);
	return;
}
void bfs(int i, int j, int cnt, int& size, Mat image)//����������������а�ɫ��ͨ��
{
	if (i < 0 || i >= image.rows || j < 0 || j >= image.cols)
		return;  //����
	else if (idx[i*image.cols + j] > 0 || d[i * image.cols + j].blu ==0)
		return;  //Ϊ0�����Ѿ����ʹ�
	else
	{
		size++;
		q.push(i);
		q.push(j);
		idx[i * image.cols + j] = cnt;
		return;
	}
}
void bfs_ex(int i, int j, int cnt, int& size, Mat image)//����������������а�ɫ��ͨ��
{
	size++;//��ͨ���С
	q.push(i);
	q.push(j);
	idx[i * image.cols + j] = cnt;//�Ѿ����ʹ�
	while (!q.empty())
	{
		int k = q.front();
		q.pop();
		int l = q.front();
		q.pop();
		bfs(k - 1, l, cnt, size, image);
		bfs(k + 1, l, cnt, size, image);
		bfs(k, l - 1, cnt, size, image);
		bfs(k, l + 1, cnt, size, image);
	}
}
void bfs_1(int i, int j, Mat image,int what)//�������������������ɫ��ͨ��ֵΪ1
{
	if (i < 0 || i >= image.rows || j < 0 || j >= image.cols)
		return;  //����
	else if (idx[i * image.cols + j] > 0 || (what == 0 && d[i * image.cols + j].blu == 0) || (what == 1 && d[i * image.cols + j].gree == 0) || (what == 2 && d[i * image.cols + j].re == 0))
		return;  //����255�����Ѿ����ʹ�
	else
	{
		idx[i * image.cols + j] = 1;
		p.push(i);
		p.push(j);
		if(what==0)
			d[i * image.cols + j].blu = 1;
		else if (what == 1)
			d[i * image.cols + j].gree = 1;
		else if (what == 2)
			d[i * image.cols + j].re = 1;
		return;
	}
}
void bfs_1_ex(int i, int j, Mat image,int what)//�������������������ɫ��ͨ��ֵΪ1
{
	if (what == 0)
		d[i * image.cols + j].blu = 1;
	else if(what==1)
		d[i * image.cols + j].gree = 1;
	else if (what == 2)
		d[i * image.cols + j].re = 1;
	idx[i * image.cols + j] = 1;
	p.push(i);
	p.push(j);
	while (!p.empty())
	{
		int k = p.front();
		p.pop();
		int l = p.front();
		p.pop();
		bfs_1(k - 1, l, image,what);
		bfs_1(k + 1, l, image,what);
		bfs_1(k, l - 1, image,what);
		bfs_1(k, l + 1, image,what);
	}
}
void retain(Mat image,int n)//����Ŀ������
{
	int cnt = 0;//��¼��ɫ��ͨ�����
	int size = 0;//��¼��ɫ��ͨ���С
	Mat ima = image;
	for (int i = 0; i < image.rows; i++)
		for (int j = 0; j < image.cols; j++)
		{
			Vec3b pixel = image.at<Vec3b>(i, j);//����ͨ������ȡ��
			d[i * image.cols + j].blu = pixel[0];
			d[i * image.cols + j].gree = pixel[1];
			d[i * image.cols + j].re = pixel[2];
			e[i * image.cols + j].blu = pixel[0];
			e[i * image.cols + j].gree = pixel[1];
			e[i * image.cols + j].re = pixel[2];
		}
	int th = myotsu(image, 1);//�ҵ���ֵ
	if (n == 2)//������ֵ
		th -= 37;
	for (int i = 0; i < image.rows; i++)//��ֵ������
		for (int j = 0; j < image.cols; j++)
		{
			if (d[i * image.cols + j].blu > th)
			{
				d[i * image.cols + j].blu = 255;
			}
			else
			{
				d[i * image.cols + j].blu = 0;
			}
			if (d[i * image.cols + j].gree > th)
			{
				d[i * image.cols + j].gree = 255;
			}
			else
			{
				d[i * image.cols + j].gree = 0;
			}
			if (d[i * image.cols + j].re > th)
			{
				d[i * image.cols + j].re = 255;
			}
			else
			{
				d[i * image.cols + j].re = 0;
			}
		}
	for (int i = 0; i < image.rows; i++)//���й���������������а�ɫ��255����ͨ��
		for (int j = 0; j < image.cols; j++)
		{
			if (d[i * image.cols + j].blu == 255 && idx[i * image.cols + j] == 0)
			{
				size = 0;
				bfs_ex(i, j, ++cnt, size, image);
				f[cnt].num = size;
				f[cnt].x = i;
				f[cnt].y = j;
			}
		}
	for (int i = 1; i <= cnt; i++)//���ҵ�����ͨ�򰴴�С����
	{
		place t;
		for (int j = i; j <= cnt; j++)
		{
			if (f[i].num > f[j].num)
			{
				t = f[i];
				f[i] = f[j];
				f[j] = t;
			}
		}
	}
	int p = f[cnt].x;//�����ͨ���λ��
	int q = f[cnt].y;
	memset(idx, 0, sizeof(idx));
	bfs_1_ex(p, q, image, 0);//����blue�������ͨ��ʹֵΪ1
	for(int i=0;i<image.rows;i++)//����С��ɫ��ͨ���Ϊ����
		for (int j = 0; j < image.cols; j++)
		{
			if (idx[i * image.cols + j] == 0&& d[i * image.cols + j].blu!=0)
			{
				d[i * image.cols + j].blu = 0;
			}
		}
	memset(idx, 0, sizeof(idx));
	bfs_1_ex(p, q, image, 1);//����green��
	for (int i = 0; i < image.rows; i++)
		for (int j = 0; j < image.cols; j++)
		{
			if (idx[i * image.cols + j] == 0&& d[i * image.cols + j].gree != 0)
				d[i * image.cols + j].gree = 0;
		}
	memset(idx, 0, sizeof(idx));
	bfs_1_ex(p, q, image, 2);
	for (int i = 0; i < image.rows; i++)//����red��
		for (int j = 0; j < image.cols; j++)
		{
			if (idx[i * image.cols + j] == 0&& d[i * image.cols + j].re!= 0)
				d[i * image.cols + j].re = 0;
		}
	if (n == 3)//����ͼ������ν��и�������
	{
		for (int i = 0; i < image.rows * image.cols; i++)
		{
			e[i].blu += 100;
			e[i].gree += 100;
			e[i].re += 100;
		}
	}
	for (int i = 0; i < image.rows * image.cols; i++)//����Hadamard�˻��õ�Ŀ�����򣬲�ʹ�������
	{
		e[i].blu = e[i].blu*d[i].blu;
		e[i].gree *= d[i].gree;
		e[i].re *= d[i].re;
	}
	for (int i = 0; i < image.rows; i++)
		for (int j = 0; j < image.cols; j++)
		{
			Vec3b pixel;
			pixel[0] = (unsigned char)e[i * image.cols + j].blu;//Blue            
			pixel[1] = (unsigned char)e[i * image.cols + j].gree;//Green            
			pixel[2] = (unsigned char)e[i * image.cols + j].re;//Red             
			ima.at<Vec3b>(i, j) = pixel;
		}
	memset(d, 0, sizeof(d));
	memset(e, 0, sizeof(e));
	memset(idx, 0, sizeof(idx));
	memset(f, 0, sizeof(f));
	imshow("���", ima);
	waitKey(0);
	ima = Mat(256, 256, CV_8U, Scalar::all(0));
	return;
}
void retain_ex()//����Ŀ������
{
	Mat im_2 = imread("./resources/2.jpg", 1);
	Mat im_3 = imread("./resources/3.jpg", 1);
	Mat im_4 = imread("./resources/4.jpg", 1);
	Mat im_5 = imread("./resources/5.jpg", 1);
	retain(im_2, 2);
	retain(im_3, 3);
	retain(im_4, 4);
	retain(im_5, 5);
	return;
}