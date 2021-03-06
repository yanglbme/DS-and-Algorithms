/*
题目描述

给出一个数据序列，建立二叉排序树，并实现删除功能

对二叉排序树进行中序遍历，可以得到有序的数据序列

输入

第一行输入t，表示有t个数据序列

第二行输入n，表示首个序列包含n个数据

第三行输入n个数据，都是自然数且互不相同，数据之间用空格隔开

第四行输入m，表示要删除m个数据

从第五行起，输入m行，每行一个要删除的数据，都是自然数

以此类推输入下一个示例

输出

第一行输出有序的数据序列，对二叉排序树进行中序遍历可以得到

从第二行起，输出删除第m个数据后的有序序列，输出m行

以此类推输出下一个示例的结果

样例输入

1
6
22 33 55 66 11 44
3
66
22
77
样例输出

11 22 33 44 55 66 
11 22 33 44 55 
11 33 44 55 
11 33 44 55 
提示

当删除数据不在序列中，那么删除操作等于不执行，所以输出序列不变化
*/
#include <iostream>
using namespace std;

#define OK 1
#define ERROR 0

class TreeNode
{
  public:
    int data;
    TreeNode *LeftChild;
    TreeNode *RightChild;
    TreeNode()
    {
        LeftChild = NULL;
        RightChild = NULL;
        data = 0;
    }
};

class Tree
{
  public:
    TreeNode *Root;
    bool Find;
    int times;
    void CreateBinary(int *a, int size)
    {
        if (size == 0)
            return;
        Root = NULL;
        TreeNode *t;
        int length = 0;
        t = new TreeNode();
        t->data = a[length];
        Root = t;
        for (; ++length < size;)
        {
            t = new TreeNode();
            t->data = a[length];
            InsertElem(Root, t);
        } //for
    }     //CreateBinary

    void InsertElem(TreeNode *F, TreeNode *t)
    {
        if (F->data < t->data)
        {
            if (F->RightChild)
            {
                InsertElem(F->RightChild, t);
            } //if
            else
                F->RightChild = t;
        } //if
        else
        {
            if (F->LeftChild)
                InsertElem(F->LeftChild, t);
            else
                F->LeftChild = t;
        } //else
    }     //InsertElem

    void Searchfordata(TreeNode *t, int data)
    {
        if (Find && t)
        {
            times++;
            if (t->data == data)
            {
                Find = false;
            }
            else if (t->data > data)
            {
                Searchfordata(t->LeftChild, data);
            }
            else
            {
                Searchfordata(t->RightChild, data);
            }
        }
    }

    void Delete(TreeNode *&p)
    {
        TreeNode *q;
        if (!p->RightChild)
        {
            q = p;
            p = p->LeftChild;
            delete q;
        }
        else if (!p->LeftChild)
        {
            q = p;
            p = p->RightChild;
            delete q;
        }
        else
        {
            q = p;
            TreeNode *s;
            s = p->LeftChild;
            while (s->RightChild)
            {
                q = s;
                s = s->RightChild;
            }
            p->data = s->data;
            if (q != p)
                q->RightChild = s->LeftChild;
            else
                q->LeftChild = s->LeftChild;
            delete s;
        }
    }

    void delete_data(TreeNode *&t, int data)
    {
        if (Find && t)
        {
            if (t->data == data)
            {
                Find = false;
                Delete(t);
            }
            else if (t->data > data)
            {
                delete_data(t->LeftChild, data);
            }
            else
            {
                delete_data(t->RightChild, data);
            }
        }
    } //delete_data

    void delete_data(int data)
    {
        Find = true;
        delete_data(Root, data);
    }

    int Searchfordata(int data)
    {
        Find = true;
        times = 0;
        Searchfordata(Root, data);
        if (Find)
            return -1;
        else
            return times;
    }

    void InOrder()
    {
        InOrder(Root);
    }

    void InOrder(TreeNode *t)
    {
        if (t)
        {
            InOrder(t->LeftChild);
            cout << t->data << " ";
            InOrder(t->RightChild);
        } //if
    }     //InSearch
};

int main()
{
    int t, n, i, num, N;
    Tree T;
    cin >> t;
    while (t--)
    {
        cin >> n;
        int *a = new int[n];
        for (i = -1; ++i < n;)
        {
            cin >> a[i];
        } //for
        T.CreateBinary(a, n);
        T.InOrder();
        cout << endl;
        cin >> num;
        while (num--)
        {
            cin >> N;
            T.delete_data(N);
            T.InOrder();
            cout << endl;
        } //while
    }     //while
    return 0;
}