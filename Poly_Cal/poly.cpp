#include <QString>
#include <iostream>
#include <cmath>
class pair
{
    public:
        double c;
        int e;
        pair* next;
        pair()
        {
            next = NULL;
            c = 0;
            e = 0;
        }
};

class Poly
{
    private:
        int len;
        pair* head;

    public:
        Poly();
        Poly(QString str);
        void insert(double c, int e);

        QString compute(QString& num) const;
        QString transform() const;
        Poly diff() const;
        QString print() const;

        friend Poly operator +(const Poly& p1,const Poly& p2);
        friend Poly operator -(const Poly& p1,const Poly& p2);
        friend Poly operator *(const Poly& p1,const Poly& p2);
};

Poly::Poly()
{
    head = new pair;
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
    head = new pair;
    int l = 0, r = 0, temp2 = 0;
    double temp1 = 0;
    while(r < str.length())
    {
        bool mark = true;
        while(str[r].isDigit() || str[r] == '.' || mark && (str[r] == '+' || str[r] == '-') && r < str.length())
        {
            mark = false;
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
            mark = true;
            continue;
        }
        mark = true;
        while(str[r].isDigit() || mark && (str[r] == '+' || str[r] == '-') && r < str.length())
        {
            if (!mark)
            if (str[r] == '+'||str[r] == '-')
                break;
            mark = false;
            r++;
        }
        temp2 = str.mid(l,r-l).toInt();
        this->insert(temp1, temp2);
        l = r;
    }
}

void Poly::insert(double c, int e)
{
    pair* p = head;
    while(p->next)
	{
        if(p->next->e == e)
		{
            c = c + p->next -> c;
            if(c == 0)
			{
                p->next = p->next->next;
                delete p->next;
                len --;
                return;
			}
			else
			{
                p->next->c = c;
                return;
			}
		}
        if(p->next->e < e)
		{
            pair* q = new pair;
            q->e = e;
            q->c = c;
            q->next = p->next;
            p->next = q;
            len ++;
            return;
		}
        p = p->next;
	}

    pair* q = new pair;
    q->e = e;
    q->c = c;
    q->next = p->next;
    p->next = q;
    len ++;
    return;
}

QString Poly::compute(QString &num) const
{
    double x = num.toDouble(),result = 0;
    pair *cur = this->head->next;
    while(cur)
    {
        result += cur->c * pow(x,cur->e);
        cur = cur->next;
    }
    QString temp;
    return temp.setNum(result);
}

QString Poly::transform() const
{
    QString str;
    pair* p = head->next;
    if(p==NULL){return QString("0");}
    if (p->c != 0 && p->e != 0)
    {
        QString temp;
        if (p->c == -1)
            str = str + '-';
        else if (p->c != 1)
            str = temp.setNum(p->c);
        str = str + 'x';
        if (p->e != 1)
        {
            str = str + '^';
            str = str + QString::number(p->e, 10);
        }
    }
    else if(p->c != 0 && p->e == 0)
    {
        QString temp;
        str = temp.setNum(p->c);
    }
    p = p->next;
	while(p)
	{
        if (p->c >= 0)
            str = str + '+';
        QString temp;
        if (p->e == 0)    str = str + temp.setNum(p->c);
        else
        {
            if (p->c == -1)
                str = str + '-';
            if (p->c != 1 && p->c != -1)
                str = str + temp.setNum(p->c);
            if (p->e != 0)
            {
                str = str + 'x';
                if (p->e != 1)
                    str = str + '^' + QString::number(p->e, 10);
            }
        }
        p = p->next;
	}
    return str;
}

QString Poly::print() const
{
    QString str;
    str = str + QString::number(len,10);
    pair *cur = this->head;
    while(cur->next)
    {
        cur = cur->next;
        str = str + ',';
        str = str + QString::number(int(cur->c),10) + ',';
        str = str + QString::number(cur->e,10);
    }
    return str;
}

Poly Poly::diff() const
{
    Poly tem;
    pair *cur = this->head;
    while(cur->next)
    {
        cur = cur->next;
        if (cur->e != 0)
            tem.insert(cur->c * cur->e,cur->e - 1);
    }
    return tem;
}

Poly operator +(const Poly& P1,const Poly& P2)
{

    pair* p1 = P1.head->next;
    pair* p2 = P2.head->next;
    Poly p;
    while(p1 || p2)
	{
        if(p1 == NULL)
		{
            p.insert(p2->c,p2->e);
            p2 = p2->next;
		}
        else if(p2 == NULL)
		{
            p.insert(p1->c,p1->e);
            p1 = p1->next;
		}
        else if(p1->e > p2->e)
		{
            p.insert(p1->c,p1->e);
            p1 = p1->next;
		}
        else if(p1->e < p2->e)
		{
            p.insert(p2->c,p2->e);
            p2 = p2->next;
		}
        else
        {
            if(p1->e == p2->e && (p1->c + p2->c != 0))
                p.insert(p1->c + p2->c,p1->e);
            p1 = p1->next;
            p2 = p2->next;
        }
	}
    return p;
}

Poly operator -(const Poly& P1,const Poly& P2)
{

    pair* p1 = P1.head->next ;
    pair* p2 = P2.head->next ;
    Poly p;
    while(p1 || p2)
	{
        if(p1 == NULL)
		{
            p.insert(-(p2->c),p2->e);
            p2 = p2->next;
		}
        else if(p2 == NULL)
		{
            p.insert(p1->c,p1->e);
            p1 = p1->next;
		}
        else if(p1->e > p2->e)
		{
            p.insert(p1->c,p1->e);
            p1 = p1->next;
		}
        else if(p1->e < p2->e)
		{
            p.insert(-(p2->c),p2->e);
            p2 = p2->next;
		}
        else
        {

            if(p1->e == p2->e && (p1->c - p2->c) != 0)
                p.insert(p1->c - p2->c,p1->e);
            p1 = p1->next;
            p2 = p2->next;
        }
	}
    return p;
}

Poly operator *(const Poly& P1,const Poly& P2)
{
    Poly *store = new Poly[P1.len];
    pair *cur1 = P1.head, *cur2 = P2.head;
    int i = 0;
    while(cur1->next)
    {
        cur1 = cur1->next;
        {
            cur2 = P2.head;
            while(cur2->next)
            {
                cur2 = cur2->next;
                store[i].insert(cur1->c * cur2->c,cur1->e + cur2->e);
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
