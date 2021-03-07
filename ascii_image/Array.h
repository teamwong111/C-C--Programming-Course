#include<string.h>
class Array {
public:
    Array()//���캯��
    {
        index = 0;
        memset(shape, 0, sizeof(shape));
        axisNum = 0;
        nowAxis = 0;
        ischild = true;
        data = nullptr;
    }
    ~Array()//��������
    {
        if (!ischild)
        {
            delete data;
            data = nullptr;
        }
    }
    template<typename ...Args>
    Array(Args... args) //���캯��
    {
        // ��ȡ��������С��ת��Ϊ����
        auto num = sizeof...(args);
        int list[100] = { args... };

        ischild = false;
        axisNum = num;
        nowAxis = 0;
        index = 0;
        //Ϊÿһά�ȵĳ��ȸ�ֵ
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
        // ��ȡ��������С��ת��Ϊ����
        auto num = sizeof...(args);
        int list[100] = { args... };

        axisNum = num;
        nowAxis = 0;
        index = 0;
        //����ÿһά�ȳ���
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
    Array operator[](int _index)//����[]
    {
        // �������޸��Ӿ����nowAxis��ֵ�Լ������б�Ҫ��ֵ���Է���һ���Ӿ���
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
    Array operator+(Array& b)//����ӷ�
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
    Array operator+(int b)//����ӷ�
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
    Array operator-(Array& b)//�������
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
    Array operator-(int b)//�������
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
    Array operator*(Array& b)//������
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
    Array operator*(int b)//������
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
    Array operator/(Array& b)//������
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
    Array operator/(int b)//������
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

    int* data; //�ײ�һά����
    int index; //data���±�
    int shape[16];//�洢ÿһά�ĳ���
    int axisNum; //��ά��
    int nowAxis; //��ǰά��
    bool ischild; //�ж��Ƿ����Ӿ�������Ƿ�����
};