#include "Date.h"

int main()
{
	Date d0;
	d0.Print();

	Date d1(2024, 8, 1);
	d1.Print();

	Date d2(d1);
	d2.Print();

	Date d3(1999, 8, 35);  //非法日期，前面得做一些检查
	//d3.Print();

	Date d4;
	d4 = d1;
	d4.Print();

	cout << (d1 < d2) << endl;
	cout << (d1 > d2) << endl;
	cout << (d1 == d2) << endl;
	cout << (d1 != d2) << endl;
	cout << (d1 <= d2) << endl;
	cout << (d1 >= d2) << endl;

	//注：是否要重载一个运算符，看的是这个运算符是否对这个类的对象有意义
	Date d5 = d1 + 520;
	d5.Print();
	d1.Print();  //d1不变

	Date d6 = d1 += 520;
	d6.Print();
	d1.Print();  //d1变成d6一样的

	Date d7 = d1 - 10;
	d7.Print();
	d1.Print();  //d1不变

	Date d8 = d1 -= 10;
	d8.Print();
	d1.Print();  //d1变成d7一样的

	d1++;
	d1.Print();

	++d1;
	d1.Print();

	d1--;
	d1.Print();

	--d1;
	d1.Print();

	Date d9(1999, 8, 3);
	Date d10(2024, 8, 2);

	cout << (d9 - d10) << endl;

	return 0;
}
