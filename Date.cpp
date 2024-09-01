# define  _CRT_SECURE_NO_WARNINGS 1
# include "Date.h"

//获取一个月的具体天数
int Date::GetMonthDay(int year, int month) const
{
	static int monthDays[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };

	//闰年的2月就返回29
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
		cout << "非法日期" << endl;
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
	if (this != &d)  //防止自己给自己赋值的情况(如d4 = d4)
	{
		_year = d._year;
		_month = d._month;
		_day = d._day;
	}

	return *this;  //*this不在这里面，出了作用域还在，故在前面加了引用&(引用返回可以减少一次拷贝步骤)
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
	return *this < d || *this == d;  //*********复用上面的来实现***********
}

//d1 > d2  ->   !(d1 <= d2)
bool Date::operator>(const Date& d) const
{
	return!(*this <= d);  //*********复用上面的来实现***********
}

//d1 >= d2  ->   !(d1 < d2)
bool Date::operator>=(const Date& d) const
{
	return!(*this < d);  //*********复用上面的来实现***********
}

//d1 != d2  ->   !(d1 == d2)
bool Date::operator!=(const Date& d) const
{
	return!(*this == d);  //*********复用上面的来实现***********
}

//d1 + 10   d1 + 100  ...d1不会变
Date Date::operator+(int day) const //返回的还是一个日期
{
	Date ret(*this);  //用d1拷贝构造一个ret
	ret += day;   //*********复用下面的来实现***********

	//ret._day += day;
	//while (ret._day > GetMonthDay(ret._year, ret._month))
	//{
	//	//如果日期的天数不合法，就需要往月进位
	//	ret._day -= GetMonthDay(ret._year, ret._month);
	//	ret._month++;

	//	if (ret._month == 13)
	//	{
	//		ret._year++;
	//		ret._month = 1;
	//	}
	//}

	return ret;  //ret为临时对象，出了作用域就不在了，故不用加引用&
}

//d1 += 10   d1 += 100  ...d1会变
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

	return *this;  //*this不在这里面，出了作用域还在，故在前面加了引用&(引用返回可以减少一次拷贝步骤)
}

//d1 - 10   d1 - 100  ...d1不会变
Date Date::operator-(int day) const //返回的还是一个日期
{
	Date ret(*this);  //用d1拷贝构造一个ret
	ret -= day;   //*********复用下面的来实现***********

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

	return ret;  //ret为临时对象，出了作用域就不在了，故不用加引用&
}

//d1 -= 10   d1 -= 100  ...d1会变
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

	return *this;  //*this不在这里面，出了作用域还在，故在前面加了引用&(引用返回可以减少一次拷贝步骤)
}

//++d1(返回的是加以后的值)
Date& Date::operator++()  //d1.operator++(&d1)
{
	*this += 1;  //复用+=

	return *this;  //*this不在这里面，出了作用域还在，故在前面加了引用&(引用返回可以减少一次拷贝步骤)
}

//d1++(返回的是加以前的值)
Date Date::operator++(int)  //函数名相同，为了构成函数重载，加了个无用的形参  //d1.operator++(&d1,0)
{
	Date tmp(*this);
	*this += 1;

	return tmp;  //tmp为临时对象，出了作用域就不在了，故不用加引用&
}

//--d1(返回的是减以后的值)
Date& Date::operator--()  //d1.operator--(&d1)
{
	*this -= 1;  //复用-=

	return *this;  //*this不在这里面，出了作用域还在，故在前面加了引用&(引用返回可以减少一次拷贝步骤)
}

//d1--(返回的是减以前的值)
Date Date::operator--(int)  //函数名相同，为了构成函数重载，加了个无用的形参  //d1.operator--(&d1,0)
{
	Date tmp(*this);
	*this -= 1;   //复用-=

	return tmp;  //tmp为临时对象，出了作用域就不在了，故不用加引用&
}

//d1-d2
int Date::operator-(const Date& d) const
{
	//假设法
	int flag = 1;
	Date max = *this;  //拷贝构造
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

	return n * flag;  //小减大为负，大减小为正
}

void Date::Print() const
{
	cout << _year << "-" << _month << "-" << _day << endl;
}