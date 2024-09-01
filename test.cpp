#include "Date.h"

int main()
{
	Date d0;
	d0.Print();

	Date d1(2024, 8, 1);
	d1.Print();

	Date d2(d1);
	d2.Print();

	Date d3(1999, 8, 35);  //�Ƿ����ڣ�ǰ�����һЩ���
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

	//ע���Ƿ�Ҫ����һ������������������������Ƿ�������Ķ���������
	Date d5 = d1 + 520;
	d5.Print();
	d1.Print();  //d1����

	Date d6 = d1 += 520;
	d6.Print();
	d1.Print();  //d1���d6һ����

	Date d7 = d1 - 10;
	d7.Print();
	d1.Print();  //d1����

	Date d8 = d1 -= 10;
	d8.Print();
	d1.Print();  //d1���d7һ����

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
