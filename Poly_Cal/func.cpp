#include <QString>
#include <iostream>
#include <cmath>
class term
{
    public:
        double coef;
        int exp;
        term* pNext;
        term()
        {
            pNext = NULL;
            coef = 0;
            exp = 0;
        }
};

class Poly
{
    public:
        int len;
        term* head;
        Poly();
        Poly(QString str);
        double insert(double coef, int exp);

        QString compute(QString& num);
        QString transform();
        Poly diff();
        QString print();

        friend Poly operator +(const Poly& p1,const Poly& p2);
        friend Poly operator -(const Poly& p1,const Poly& p2);
        friend Poly operator *(const Poly& p1,const Poly& p2);
};

Poly::Poly()
{
    head = new term;
    len = 0;
}

Poly::Poly(QString str)
{
    if(str[0] == 'x')   str = '1' + str;
    int i = 0,le = str.length();
    for (int j = 0;j < le;j ++)
    {
        if (str[j] == 'x' && !str[j - 1].isDigit())
        {
            str.insert(j,'1');
            le ++;
        }
    }

    len = 0;
    head = new term;
    int l = 0, r = 0, temp2 = 0;
    double temp1 = 0;
    while(r < str.length())
    {
        bool g = true;
        while(str[r].isDigit() || str[r] == '.' || g && (str[r] == '+' || str[r] == '-') && r < str.length())
        {
            g = false;
            r++;
        }
        temp1 = str.mid(l,r-l).toDouble();
        if (str[r] == 'x')
        {
            r += 2;
            l = r;
        }
        else
        {
            l = r;
            this->insert(temp1, 0);
            g = true;
            continue;
        }
        g = true;
        while(str[r].isDigit()||g&&(str[r] == '+'||str[r] == '-')&&r<str.length())
        {
            if (!g)
            if (str[r] == '+'||str[r] == '-')
                break;
            g = false;
            r++;
        }
        temp2 = str.mid(l,r-l).toInt();
        this->insert (temp1, temp2);
        l = r;
    }
}

double Poly::insert(double coef, int exp)
{
	term* p = head;
    while(p -> pNext)
	{
        if(p -> pNext -> exp == exp)
		{
			coef = coef + p -> pNext -> coef;
            if(coef == 0)
			{
				p -> pNext = p -> pNext -> pNext;
				delete p -> pNext;
                len --;
				return 0;
			}
			else
			{
				p -> pNext -> coef = coef;
				return coef;
			}
		}
        if(p -> pNext -> exp < exp)
		{
			term* q = new term;
			q -> exp = exp;
			q -> coef = coef;
			q -> pNext = p -> pNext;
			p -> pNext = q;
            len ++;
			return coef;
		}
		p = p -> pNext;
	}

	term* q = new term;
	q -> exp = exp;
	q -> coef = coef;
	q -> pNext = p -> pNext;
	p -> pNext = q;
    len ++;
	return coef;
}

QString Poly::compute(QString &num)
{
    double x = num.toDouble(),result = 0;
    term *cur = this->head->pNext;
    while(cur)
    {
        result += cur->coef * pow(x,cur->exp);
        cur = cur->pNext;
    }
    QString temp;
    return temp.setNum(result);
}

QString Poly::transform()
{
    QString str;
	term* p = head -> pNext;
    if(p==NULL){return QString("0");}
    if (p->coef != 0 && p->exp !=0 )
    {
        QString temp;
        if (p->coef == -1)
            str = str + '-';
        else if (p->coef != 1)
            str = temp.setNum(p -> coef);
        str = str + 'x';
        if (p->exp != 1)
        {
            str = str + '^';
            str = str + QString::number(p -> exp, 10);
        }
    }
    else if(p->coef!=0 && p->exp==0)
    {
        QString temp;
        str = temp.setNum(p -> coef);
    }
    p = p -> pNext;
	while(p)
	{
        if (p->coef >= 0)
            str = str + '+';
        QString temp;
        if (p->exp == 0)    str = str + temp.setNum(p->coef);
        else
        {
            if (p->coef == -1)
                str = str + '-';
            if (p->coef != 1 && p->coef != -1)
                str = str + temp.setNum(p -> coef);
            if (p->exp != 0)
            {
                str = str + 'x';
                if (p->exp != 1)
                    str = str + '^' + QString::number(p -> exp, 10);
            }
        }
		p = p -> pNext;
	}
    return str;
}

QString Poly::print()
{
    QString str;
    str = str + QString::number(len,10);
    term *cur = this->head;
    while(cur->pNext)
    {
        cur = cur->pNext;
        str = str + ',';
        str = str + QString::number(int(cur->coef),10) + ',';
        str = str + QString::number(cur->exp,10);
    }
    return str;
}

Poly Poly::diff()
{
    Poly tem;
    term *cur = this->head;
    while(cur->pNext)
    {
        cur = cur->pNext;
        if (cur->exp != 0)
            tem.insert(cur->coef * cur->exp,cur->exp - 1);
    }
    return tem;
}

Poly operator +(const Poly& P1,const Poly& P2)
{

	term* p1 = P1.head -> pNext;
	term* p2 = P2.head -> pNext;
    Poly p;
    while(p1 || p2)
	{
        if(p1 == NULL)
		{
            p.insert(p2 -> coef,p2 -> exp);
			p2 = p2 -> pNext;
		}
        else if(p2 == NULL)
		{
            p.insert(p1 -> coef,p1 -> exp);
			p1 = p1 -> pNext;
		}
        else if(p1 -> exp > p2 -> exp)
		{
            p.insert(p1 -> coef,p1 -> exp);
            p1 = p1 -> pNext;
		}
        else if(p1 -> exp < p2 -> exp)
		{
            p.insert(p2 -> coef,p2 -> exp);
            p2 = p2 -> pNext;
		}
        else
        {
            if(p1 -> exp == p2 -> exp && (p1->coef + p2->coef != 0))
                p.insert(p1 -> coef + p2 -> coef,p1 -> exp);
            p1 = p1 -> pNext;
            p2 = p2 -> pNext;
        }
	}
    return p;
}

Poly operator -(const Poly& P1,const Poly& P2)
{

	term* p1 = P1.head->pNext ;
	term* p2 = P2.head->pNext ;
    Poly p;
    while(p1 || p2)
	{
        if(p1 == NULL)
		{
            p.insert(-(p2 -> coef),p2 -> exp);
			p2 = p2 -> pNext;
		}
        else if(p2 == NULL)
		{
            p.insert(p1 -> coef,p1 -> exp);
			p1 = p1 -> pNext;
		}
        else if(p1 -> exp > p2 -> exp)
		{
            p.insert(p1 -> coef,p1 -> exp);
            p1 = p1 -> pNext;
		}
        else if(p1 -> exp < p2 -> exp)
		{
            p.insert(-(p2 -> coef),p2 -> exp);
            p2 = p2 -> pNext;
		}
        else
        {

            if(p1 -> exp == p2 -> exp && (p1->coef - p2->coef) != 0)
                p.insert(p1 -> coef - p2 -> coef,p1 -> exp);
            p1 = p1 -> pNext;
            p2 = p2 -> pNext;
        }
	}
    return p;
}

Poly operator *(const Poly& P1,const Poly& P2)
{
    Poly *store = new Poly[P1.len];
    term *cur1 = P1.head, *cur2 = P2.head;
    int i = 0;
    while(cur1->pNext)
    {
        cur1 = cur1->pNext;
        {
            cur2 = P2.head;
            while(cur2->pNext)
            {
                cur2 = cur2->pNext;
                store[i].insert(cur1->coef * cur2->coef,cur1->exp + cur2->exp);
            }
            i ++;
        }
    }
    Poly tem;
    for (i = 0;i < P1.len;i ++)
        tem = tem + store[i];
    delete [] store;
    return tem;
}
