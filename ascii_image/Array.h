#include<string.h>
class Array {
public:
    Array()//构造函数
    {
        index = 0;
        memset(shape, 0, sizeof(shape));
        axisNum = 0;
        nowAxis = 0;
        ischild = true;
        data = nullptr;
    }
    ~Array()//析构函数
    {
        if (!ischild)
        {
            delete data;
            data = nullptr;
        }
    }
    template<typename ...Args>
    Array(Args... args) //构造函数
    {
        // 获取参数包大小并转换为数组
        auto num = sizeof...(args);
        int list[100] = { args... };

        ischild = false;
        axisNum = num;
        nowAxis = 0;
        index = 0;
        //为每一维度的长度赋值
        memset(shape, 0, sizeof(shape));
        for (int i = 0; i <= axisNum; i++)
            shape[i] = 1;

        for (int i = 0; i < axisNum; i++)
            shape[0] *= list[i];

        for (int i = 1; i < axisNum; i++)
        {
            shape[i] = shape[i - 1] / list[i - 1];
        }
        data = new int[shape[0]];
    }
    template<typename ...Args>
    void reshape(Args... args)
    {
        // 获取参数包大小并转换为数组
        auto num = sizeof...(args);
        int list[100] = { args... };

        axisNum = num;
        nowAxis = 0;
        index = 0;
        //调整每一维度长度
        memset(shape, 0, sizeof(shape));
        for (int i = 0; i <= axisNum; i++)
            shape[i] = 1;

        for (int i = 0; i < axisNum; i++)
            shape[0] *= list[i];

        for (int i = 1; i < axisNum; i++)
        {
            shape[i] = shape[i - 1] / list[i - 1];
        }
    }
    int* get_content()
    {
        return data;
    }
    Array operator[](int _index)//重载[]
    {
        // 在这里修改子矩阵的nowAxis的值以及其他有必要的值，以返回一个子矩阵
        Array child;
        child.ischild = true;
        child.axisNum = axisNum - 1;
        child.nowAxis = nowAxis + 1;
        memcpy(child.shape, shape, 16);
        child.index = child.shape[child.nowAxis] * _index;

        if (child.axisNum == 0)
            child.data = data;
        else
            child.data = data + child.index;

        return child;
    }
    Array& operator=(int data)
    {
        this->data[index] = data;
        return *this;
    }
    operator int()
    {
        return data[index];
    }
    Array operator+(Array& b)//矩阵加法
    {
        Array c;
        c.index = 0;
        c.axisNum = axisNum;
        c.nowAxis = nowAxis;
        c.ischild = true;
        for (int i = 0; i <= axisNum; i++)
        {
            c.shape[i] = shape[i];
        }
        c.data = new int[c.shape[0]];
        for (int i = 0; i < c.shape[0]; i++)
        {
            c.data[i] = data[i] + b.data[i];
        }
        return c;
    }
    Array operator+(int b)//矩阵加法
    {
        Array c;
        c.index = 0;
        c.axisNum = axisNum;
        c.nowAxis = nowAxis;
        c.ischild = true;
        for (int i = 0; i <= axisNum; i++)
        {
            c.shape[i] = shape[i];
        }
        c.data = new int[c.shape[0]];
        for (int i = 0; i < c.shape[0]; i++)
        {
            c.data[i] = data[i] + b;
        }
        return c;
    }
    Array operator-(Array& b)//矩阵减法
    {
        Array c;
        c.index = 0;
        c.axisNum = axisNum;
        c.nowAxis = nowAxis;
        c.ischild = true;
        for (int i = 0; i <= axisNum; i++)
        {
            c.shape[i] = shape[i];
        }
        c.data = new int[c.shape[0]];
        for (int i = 0; i < c.shape[0]; i++)
        {
            c.data[i] = data[i] - b.data[i];
        }
        return c;
    }
    Array operator-(int b)//矩阵减法
    {
        Array c;
        c.index = 0;
        c.axisNum = axisNum;
        c.nowAxis = nowAxis;
        c.ischild = true;
        for (int i = 0; i <= axisNum; i++)
        {
            c.shape[i] = shape[i];
        }
        c.data = new int[c.shape[0]];
        for (int i = 0; i < c.shape[0]; i++)
        {
            c.data[i] = data[i] - b;
        }
        return c;
    }
    Array operator*(Array& b)//矩阵点乘
    {
        Array c;
        c.index = 0;
        c.axisNum = axisNum;
        c.nowAxis = nowAxis;
        c.ischild = true;
        for (int i = 0; i <= axisNum; i++)
        {
            c.shape[i] = shape[i];
        }
        c.data = new int[c.shape[0]];
        for (int i = 0; i < c.shape[0]; i++)
        {
            c.data[i] = data[i] * b.data[i];
        }
        return c;
    }
    Array operator*(int b)//矩阵点乘
    {
        Array c;
        c.index = 0;
        c.axisNum = axisNum;
        c.nowAxis = nowAxis;
        c.ischild = true;
        for (int i = 0; i <= axisNum; i++)
        {
            c.shape[i] = shape[i];
        }
        c.data = new int[c.shape[0]];
        for (int i = 0; i < c.shape[0]; i++)
        {
            c.data[i] = data[i] * b;
        }
        return c;
    }
    Array operator/(Array& b)//矩阵点除
    {
        Array c;
        c.index = 0;
        c.axisNum = axisNum;
        c.nowAxis = nowAxis;
        c.ischild = true;
        for (int i = 0; i <= axisNum; i++)
        {
            c.shape[i] = shape[i];
        }
        c.data = new int[c.shape[0]];
        for (int i = 0; i < c.shape[0]; i++)
        {
            c.data[i] = data[i] / b.data[i];
        }
        return c;
    }
    Array operator/(int b)//矩阵点除
    {
        Array c;
        c.index = 0;
        c.axisNum = axisNum;
        c.nowAxis = nowAxis;
        c.ischild = true;
        for (int i = 0; i <= axisNum; i++)
        {
            c.shape[i] = shape[i];
        }
        c.data = new int[c.shape[0]];
        for (int i = 0; i < c.shape[0]; i++)
        {
            c.data[i] = data[i] / b;
        }
        return c;
    }

    int* data; //底层一维数组
    int index; //data的下标
    int shape[16];//存储每一维的长度
    int axisNum; //总维数
    int nowAxis; //当前维数
    bool ischild; //判断是否是子矩阵决定是否析构
};