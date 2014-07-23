#include <stdio.h>

#define NSymbols	1<<MAXBIT
#define MAXLEAF     1<<MAXBIT
#define MAXBIT      8
#define MAXVALUE  10000
#define MAXNODE    MAXLEAF*2-1


typedef struct
{
    int bit[MAXBIT];
    int start;
} HCodeType;        /* ����ṹ�� */
typedef struct
{
    int weight;
    int parent;
    int lchild;
    int rchild;
} HNodeType;        /* ���ṹ�� */

int freq[NSymbols];
int w[NSymbols];
int sym[NSymbols];

/* ����һ�Ź������� */
void HuffmanTree (HNodeType HuffNode[MAXNODE],  int n)
{
    /* 
    i��j�� ѭ��������m1��m2���������������ͬ������������СȨֵ����Ȩֵ��
        x1��x2���������������ͬ������������СȨֵ����������е���š�
    */
    int i, j, m1, m2, x1, x2;
    /* ��ʼ����Ź����������� HuffNode[] �еĽ�� */
    for (i=0; i<2*n-1; i++)
    {
        HuffNode[i].weight = 0;
        HuffNode[i].parent =-1;
        HuffNode[i].lchild =-1;
        HuffNode[i].lchild =-1;
    } /* end for */

    /* ���� n ��Ҷ�ӽ���Ȩֵ */
    for (i=0; i<n; i++)
    {
        HuffNode[i].weight = w[i];
    } /* end for */

    /* ѭ������ Huffman �� */
    for (i=0; i<n-1; i++)
    {
        m1=m2=MAXVALUE;     /* m1��m2�д�������޸�����ҽ��Ȩֵ��С��������� */
        x1=x2=0;
        /* �ҳ����н����Ȩֵ��С���޸�����������㣬���ϲ�֮Ϊһ�Ŷ����� */
        for (j=0; j<n+i; j++)
        {
            if (HuffNode[j].weight < m1 && HuffNode[j].parent==-1)
            {
                m2=m1;
                x2=x1;
                m1=HuffNode[j].weight;
                x1=j;
            }
            else if (HuffNode[j].weight < m2 && HuffNode[j].parent==-1)
            {
                m2=HuffNode[j].weight;
                x2=j;
            }
        } /* end for */
        /* �����ҵ��������ӽ�� x1��x2 �ĸ������Ϣ */
        HuffNode[x1].parent  = n+i;
        HuffNode[x2].parent  = n+i;
        HuffNode[n+i].weight = HuffNode[x1].weight + HuffNode[x2].weight;
        HuffNode[n+i].lchild = x1;
        HuffNode[n+i].rchild = x2;
    } /* end for */
} /* end HuffmanTree */

int main(void)
{
    HNodeType HuffNode[MAXNODE];            /* ����һ�����ṹ������ */
    HCodeType HuffCode[MAXLEAF],  cd;       /* ����һ������ṹ�����飬 ͬʱ����һ����ʱ���������������ʱ����Ϣ */
    int i, j, c, p, n=0;

    char temc;
    FILE* fp = fopen("in.txt", "r");
    //statistic character frequency
    while(~fscanf(fp, "%c", &temc))
        freq[temc]++;
    fclose(fp);
    for (i=0; i<NSymbols; ++i)
    {
        if (freq[i])
        {
            w[n] = freq[i];
            sym[n] = i;
            n++;
        }
    }

    HuffmanTree (HuffNode, n);

    for (i=0; i < n; i++)
    {
        cd.start = n-1;
        c = i;
        p = HuffNode[c].parent;
        while (p != -1)   /* �������� */
        {
            if (HuffNode[p].lchild == c)
                cd.bit[cd.start] = 0;
            else
                cd.bit[cd.start] = 1;
            cd.start--;        /* �����ĵ�һλ */
            c=p;
            p=HuffNode[c].parent;    /* ������һѭ������ */
        } /* end while */

        /* ���������ÿ��Ҷ���Ĺ���������ͱ������ʼλ */
        for (j=cd.start+1; j<n; j++)
        {
            HuffCode[i].bit[j] = cd.bit[j];
        }
        HuffCode[i].start = cd.start;
    } /* end for */

    /* ����ѱ���õ����д��ڱ���Ĺ��������� */
    for (i=0; i<n; i++)
    {
        printf ("%c 's Huffman code is: ", sym[i]);
        for (j=HuffCode[i].start+1; j < n; j++)
        {
            printf ("%d", HuffCode[i].bit[j]);
        }
        printf ("\n");
    }
	system("pause");
    return 0;
}
