# define  _CRT_SECURE_NO_WARNINGS 1
# include "Date.h"

//��ȡһ���µľ�������
int Date::GetMonthDay(int year, int month) const
{
	static int monthDays[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };

	//�����2�¾ͷ���29
	if (month == 2 && ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0))
	{
		return 29;
	}

	return monthDays[month];
}

Date::Date(int year, int month, int day)
{
	if (year >= 0 && month >= 1 && month <= 12 && day >= 1 && day <= GetMonthDay(year, month))
	{
		_year = year;
		_month = month;
		_day = day;
	}
	else
	{
		cout << "�Ƿ�����" << endl;
	}
}

//Date d2(d1)
Date::Date(const Date& d)
{
	_year = d._year;
	_month = d._month;
	_day = d._day;
}

//d4 = d1
Date& Date::operator=(const Date& d)
{
	if (this != &d)  //��ֹ�Լ����Լ���ֵ�����(��d4 = d4)
	{
		_year = d._year;
		_month = d._month;
		_day = d._day;
	}

	return *this;  //*this���������棬�����������ڣ�����ǰ���������&(���÷��ؿ��Լ���һ�ο�������)
}

//d1 < d2  ->   d1.operator<(&d1, d2)
bool Date::operator<(const Date& d) const //bool operator<(Date* this, const Date& d)
{
	if (_year < d._year)
	{
		return true;
	}
	else if (_year == d._year && _month < d._month)
	{
		return true;
	}
	else if (_year == d._year && _month == d._month && _day < d._day)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//d1 == d2  ->   d1.operator==(&d1, d2)
bool Date::operator==(const Date& d) const //bool operator==(Date* this, const Date& d)
{
	return _year == d._year && _month == d._month && _day == d._day;
}

//d1 <= d2  ->  d1 < d2 || d1 == d2
bool Date::operator<=(const Date& d) const
{
	return *this < d || *this == d;  //*********�����������ʵ��***********
}

//d1 > d2  ->   !(d1 <= d2)
bool Date::operator>(const Date& d) const
{
	return!(*this <= d);  //*********�����������ʵ��***********
}

//d1 >= d2  ->   !(d1 < d2)
bool Date::operator>=(const Date& d) const
{
	return!(*this < d);  //*********�����������ʵ��***********
}

//d1 != d2  ->   !(d1 == d2)
bool Date::operator!=(const Date& d) const
{
	return!(*this == d);  //*********�����������ʵ��***********
}

//d1 + 10   d1 + 100  ...d1�����
Date Date::operator+(int day) const //���صĻ���һ������
{
	Date ret(*this);  //��d1��������һ��ret
	ret += day;   //*********�����������ʵ��***********

	//ret._day += day;
	//while (ret._day > GetMonthDay(ret._year, ret._month))
	//{
	//	//������ڵ��������Ϸ�������Ҫ���½�λ
	//	ret._day -= GetMonthDay(ret._year, ret._month);
	//	ret._month++;

	//	if (ret._month == 13)
	//	{
	//		ret._year++;
	//		ret._month = 1;
	//	}
	//}

	return ret;  //retΪ��ʱ���󣬳���������Ͳ����ˣ��ʲ��ü�����&
}

//d1 += 10   d1 += 100  ...d1���
Date& Date::operator+=(int day)
{
	if (day < 0)
	{
		return *this -= -day;
	}

	_day += day;
	while (_day > GetMonthDay(_year, _month))
	{
		_day -= GetMonthDay(_year, _month);
		++_month;

		if (_month == 13)
		{
			++_year;
			_month = 1;
		}
	}

	return *this;  //*this���������棬�����������ڣ�����ǰ���������&(���÷��ؿ��Լ���һ�ο�������)
}

//d1 - 10   d1 - 100  ...d1�����
Date Date::operator-(int day) const //���صĻ���һ������
{
	Date ret(*this);  //��d1��������һ��ret
	ret -= day;   //*********�����������ʵ��***********

	/*ret._day -= day;
	while (ret._day <= 0)
	{
		--ret._month;
		if (ret._month == 0)
		{
			--ret._year;
			ret._month = 12;
		}

		ret._day += GetMonthDay(ret._year, ret._month);
	}*/

	return ret;  //retΪ��ʱ���󣬳���������Ͳ����ˣ��ʲ��ü�����&
}

//d1 -= 10   d1 -= 100  ...d1���
Date& Date::operator-=(int day)
{
	if (day < 0)
	{
		return *this += -day;
	}

	_day -= day;
	while (_day <= 0)
	{
		--_month;
		if (_month == 0)
		{
			--_year;
			_month = 12;
		}

		_day += GetMonthDay(_year, _month);
	}

	return *this;  //*this���������棬�����������ڣ�����ǰ���������&(���÷��ؿ��Լ���һ�ο�������)
}

//++d1(���ص��Ǽ��Ժ��ֵ)
Date& Date::operator++()  //d1.operator++(&d1)
{
	*this += 1;  //����+=

	return *this;  //*this���������棬�����������ڣ�����ǰ���������&(���÷��ؿ��Լ���һ�ο�������)
}

//d1++(���ص��Ǽ���ǰ��ֵ)
Date Date::operator++(int)  //��������ͬ��Ϊ�˹��ɺ������أ����˸����õ��β�  //d1.operator++(&d1,0)
{
	Date tmp(*this);
	*this += 1;

	return tmp;  //tmpΪ��ʱ���󣬳���������Ͳ����ˣ��ʲ��ü�����&
}

//--d1(���ص��Ǽ��Ժ��ֵ)
Date& Date::operator--()  //d1.operator--(&d1)
{
	*this -= 1;  //����-=

	return *this;  //*this���������棬�����������ڣ�����ǰ���������&(���÷��ؿ��Լ���һ�ο�������)
}

//d1--(���ص��Ǽ���ǰ��ֵ)
Date Date::operator--(int)  //��������ͬ��Ϊ�˹��ɺ������أ����˸����õ��β�  //d1.operator--(&d1,0)
{
	Date tmp(*this);
	*this -= 1;   //����-=

	return tmp;  //tmpΪ��ʱ���󣬳���������Ͳ����ˣ��ʲ��ü�����&
}

//d1-d2
int Date::operator-(const Date& d) const
{
	//���跨
	int flag = 1;
	Date max = *this;  //��������
	Date min = d;
	if (*this < d)
	{
		max = d;  //operator=
		min = *this;
		flag = -1;
	}

	int n = 0;
	while (min != max)
	{
		++min;
		++n;
	}

	return n * flag;  //С����Ϊ�������СΪ��
}

void Date::Print() const
{
	cout << _year << "-" << _month << "-" << _day << endl;
}