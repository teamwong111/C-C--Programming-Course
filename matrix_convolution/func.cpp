#include <iostream>
#include <conio.h>
#include <opencv2/opencv.hpp>
#include<queue>
using namespace cv;
using namespace std;
//使用到的数组,idx为找最大连通子图，进行广度优先搜索使用的数组
int a[258 * 258] = { 0 }, b[256 * 256] = { 0 }, c[256 * 256] = { 0 }, idx[30010] = { 0 };
struct three //对三通道读取的结构体
{
	int blu;
	int gree;
	int re;
}d[30010],e[30010];
struct place //找最大连通子图，进行广度优先搜索使用的结构体
{
	int x;
	int y;
	int num;
}f[256 * 256];
queue<int> q, p;//找最大连通子图，进行广度优先搜索使用的队列
void menu()//菜单
{
	cout << "*********************************************************" << endl;
	cout << " *      1 矩阵加法      2 矩阵数乘      3 矩阵转置      *" << endl;
	cout << " *      4 矩阵乘法      5 Hadamard乘积  6 矩阵卷积      *" << endl;
	cout << " *      7 卷积应用      8 OTSU算法      9 保留区域      *" << endl;
	cout << " *      0 退出系统	                                     *" << endl;
	cout << "*********************************************************" << endl;
	cout << "选择菜单项<0~9>:" << endl;
	return;
}
void matriplus()//矩阵加法
{
	int m, n;
	cout << "请输入两个矩阵的行和列数：" << endl;
	cin >> m >> n;
	cout << "请输入矩阵a：" << endl;
	for (int i = 0; i < n * m; i++)
		cin >> a[i];
	cout << "请输入矩阵b：" << endl;
	for (int i = 0; i < n * m; i++)
	{
		cin >> b[i];
		a[i] += b[i];
	}
	cout << "结果为：";
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
void nummulti()//矩阵数乘
{
	int x, m, n;
	cout << "请输入矩阵的行和列数以及矩阵要乘的数：" << endl;
	cin >> m >> n>> x;
	cout << "请输入矩阵：" << endl;
	for (int i = 0; i < n * m; i++)
	{
		cin >> a[i];
		a[i] *= x;
	}
	cout << "结果为：";
	for (int i = 0; i < n * m; i++)
	{
		if (i % n == 0)
			cout << endl;
		cout << a[i] << " ";
	}
	memset(a, 0, sizeof(a)); 
	return;
}
void matritrans()//矩阵转置
{
	int m, n;
	cout << "请输入矩阵的行和列数：" << endl;
	cin >> m >> n;
	cout << "请输入矩阵：" << endl;
	for (int i = 0; i < n * m; i++)
	{
		cin >> a[i];
		int j = i / n;
		int k = i % n;
		b[j + k * m] = a[i];
	}
	cout << "结果为：";
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
void matrimulti()//矩阵乘法
{
	int m, n, p, q;
	cout << "请输入第一个和第二个矩阵的行和列数：" << endl;
	cin >> m >> n >> p >> q;
	if (n != p)
	{
		cout << "两矩阵不能进行乘法" << endl;
		return;
	}
	cout << "请输入矩阵a：" << endl;
	for (int i = 0; i < n * m; i++)
		cin >> a[i];
	cout << "请输入矩阵b：" << endl;
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
	cout << "结果为：";
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
void hadamulti()//矩阵Hadamard乘积
{
	int m, n;
	cout << "请输入两个矩阵的行和列数：" << endl;
	cin >> m >> n;
	cout << "请输入矩阵a：" << endl;
	for (int i = 0; i < n * m; i++)
		cin >> a[i];
	cout << "请输入矩阵b：" << endl;
	for (int i = 0; i < n * m; i++)
	{
		cin >> b[i];
		a[i] *= b[i];
	}
	cout << "结果为：";
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
void conv(int sel)//矩阵卷积（用于第6和第7个功能）
{
	int n, m = 0, p = 0, q;
	int d[9] = { 0 };
	switch (sel)//选择卷积核
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
		cout << "输入错误" << endl;
		return;
	}
	}
	if (sel == 0)//这是第6个功能
	{
		cout << "请输入矩阵的阶数：" << endl;
		cin >> n;
		cout << "请输入矩阵：" << endl;
		for (int i = n + 3; i < n * n + 3 * n + 1; i++)//加Padding
		{
			if (i % (n + 2) == 0 || i % (n + 2) == n + 1)
				continue;
			else
				cin >> a[i];
		}
	}
	else
	{
		n = 256;//这是第7个功能
	}
	for (int i = 0; i < n * (n + 2); i++)//进行卷积
	{
		if (i % (n + 2) == n || i % (n + 2) == n + 1)
			continue;
		else
		{
			int k[9] = { 0 };//存放9个点的结果
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
			for (int l = 0; l < 9; l++)//把9个点加起来
				c[p] += k[l];
			if(sel!=0)//区分第6个功能和第7个功能
				c[p] /= 9;
			if (c[p] < 0&&sel!=0)//判断unisigned char类型是否越界
				c[p] = 0;
			p++;
		}
	}
	if (sel == 0)
	{
		cout << "结果为：" << endl;
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
void demo()//卷积应用
{
	int sel;
	Mat image = imread("./resources/1.jpg", 0);//单通道读取
	for (int i = 0; i < 256; i++)
		for (int j = 0; j < 256; j++)
		{
			b[i * 256 + j] = image.at<uchar>(j, i);//矩阵转数组
		}
	int l = 0;
	for (int i = 256 + 3; i < 256 * 256 + 3 * 256 + 1; i++)//加Padding
	{
		if (i % (256 + 2) == 0 || i % (256 + 2) == 256 + 1)
			continue;
		else
		{
			a[i] = b[l];
			++l;
		}
	}
	cout << "请输入核的代号" << endl;
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
	imshow("卷积结果", result);
	waitKey(0);
	return;
}
int myotsu(Mat& images,int what)//寻找阈值
{
	int th=0;
	const int Scale = 256;	//单通道总灰度256级
	int count[Scale] = { 0 };
	int sum = images.cols * images.rows;
	float Pro[Scale] = { 0 };//每个灰度值所占总像素比例
	float w0, w1, v0, v1, u0, u1, deltaTmp, deltaMax = 0;
	if (what == 0)
	{
		for (int i = 0; i < images.cols; i++)
		{
			for (int j = 0; j < images.rows; j++)
			{
				count[images.at<uchar>(j, i)]++;//统计每个灰度级中像素的个数  
			}
		}
	}
	else
	{
		for (int i = 0; i < images.cols; i++)
		{
			for (int j = 0; j < images.rows; j++)
			{
				count[d[j * images.cols + i].blu]++;//统计每个灰度级中像素的个数  
			}
		}
	}
	for (int i = 0; i < Scale; i++)
	{
		Pro[i] = count[i] * 1.0 / sum;//计算每个灰度级的像素数目占整幅图像的比例  
	}

	for (int i = 0; i < Scale; i++)//测试哪一个的类间方差最大
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
		deltaTmp = (float)(w0 * w1 * pow((u0 - u1), 2)); //方差公式
		if (deltaTmp > deltaMax)
		{
			deltaMax = deltaTmp;
			th = i;
		}
	}
	return th;
}
void otsu()//OTSU算法
{
	Mat image = imread("./resources/1.jpg", 0);
	int th=myotsu(image,0);//得阈值
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
void bfs(int i, int j, int cnt, int& size, Mat image)//广度优先搜索找所有白色连通域
{
	if (i < 0 || i >= image.rows || j < 0 || j >= image.cols)
		return;  //出界
	else if (idx[i*image.cols + j] > 0 || d[i * image.cols + j].blu ==0)
		return;  //为0或者已经访问过
	else
	{
		size++;
		q.push(i);
		q.push(j);
		idx[i * image.cols + j] = cnt;
		return;
	}
}
void bfs_ex(int i, int j, int cnt, int& size, Mat image)//广度优先搜索找所有白色连通域
{
	size++;//连通域大小
	q.push(i);
	q.push(j);
	idx[i * image.cols + j] = cnt;//已经访问过
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
void bfs_1(int i, int j, Mat image,int what)//广度优先搜索调整最大白色连通域值为1
{
	if (i < 0 || i >= image.rows || j < 0 || j >= image.cols)
		return;  //出界
	else if (idx[i * image.cols + j] > 0 || (what == 0 && d[i * image.cols + j].blu == 0) || (what == 1 && d[i * image.cols + j].gree == 0) || (what == 2 && d[i * image.cols + j].re == 0))
		return;  //不是255或者已经访问过
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
void bfs_1_ex(int i, int j, Mat image,int what)//广度优先搜索调整最大白色连通域值为1
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
void retain(Mat image,int n)//保留目标区域
{
	int cnt = 0;//记录白色连通域多少
	int size = 0;//记录白色连通域大小
	Mat ima = image;
	for (int i = 0; i < image.rows; i++)
		for (int j = 0; j < image.cols; j++)
		{
			Vec3b pixel = image.at<Vec3b>(i, j);//将三通道三层取出
			d[i * image.cols + j].blu = pixel[0];
			d[i * image.cols + j].gree = pixel[1];
			d[i * image.cols + j].re = pixel[2];
			e[i * image.cols + j].blu = pixel[0];
			e[i * image.cols + j].gree = pixel[1];
			e[i * image.cols + j].re = pixel[2];
		}
	int th = myotsu(image, 1);//找到阈值
	if (n == 2)//处理阈值
		th -= 37;
	for (int i = 0; i < image.rows; i++)//二值化处理
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
	for (int i = 0; i < image.rows; i++)//进行广度优先搜索找所有白色（255）连通域
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
	for (int i = 1; i <= cnt; i++)//对找到的连通域按大小排序
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
	int p = f[cnt].x;//最大连通域的位置
	int q = f[cnt].y;
	memset(idx, 0, sizeof(idx));
	bfs_1_ex(p, q, image, 0);//处理blue层最大连通域，使值为1
	for(int i=0;i<image.rows;i++)//其余小白色连通域变为背景
		for (int j = 0; j < image.cols; j++)
		{
			if (idx[i * image.cols + j] == 0&& d[i * image.cols + j].blu!=0)
			{
				d[i * image.cols + j].blu = 0;
			}
		}
	memset(idx, 0, sizeof(idx));
	bfs_1_ex(p, q, image, 1);//处理green层
	for (int i = 0; i < image.rows; i++)
		for (int j = 0; j < image.cols; j++)
		{
			if (idx[i * image.cols + j] == 0&& d[i * image.cols + j].gree != 0)
				d[i * image.cols + j].gree = 0;
		}
	memset(idx, 0, sizeof(idx));
	bfs_1_ex(p, q, image, 2);
	for (int i = 0; i < image.rows; i++)//处理red层
		for (int j = 0; j < image.cols; j++)
		{
			if (idx[i * image.cols + j] == 0&& d[i * image.cols + j].re!= 0)
				d[i * image.cols + j].re = 0;
		}
	if (n == 3)//对于图多角星形进行高亮处理
	{
		for (int i = 0; i < image.rows * image.cols; i++)
		{
			e[i].blu += 100;
			e[i].gree += 100;
			e[i].re += 100;
		}
	}
	for (int i = 0; i < image.rows * image.cols; i++)//利用Hadamard乘积得到目标区域，并使背景变黑
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
	imshow("结果", ima);
	waitKey(0);
	ima = Mat(256, 256, CV_8U, Scalar::all(0));
	return;
}
void retain_ex()//保留目标区域
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