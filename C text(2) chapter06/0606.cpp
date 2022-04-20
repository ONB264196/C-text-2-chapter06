#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<time.h>

int mday[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
int dayofweek(int year, int month, int day) {
	if (month == 1 || month == 2) {
		year--;
		month += 12;
	}
	return (year + year / 4 - year / 100 + year / 400 + (13 * month + 8) / 5 + day) % 7;
}
int is_leap(int year) {
	return year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
}
int monthdays(int year, int month) {
	if (month-- != 2) {
		return mday[month];
	}
	return mday[month] + is_leap(year);
}

void make_calender2(int y, int m, char s[7][22], int n) {
	int k = 0;
	int wd = dayofweek(y, m, 1);
	int neighborflag = 0;
	int mdays = monthdays(y, m);
	char tmp[4] = { 0 };



	sprintf_s(s[0], 22, "%10d / %02d      ", y, m);

	for (k = 1; k < 7; k++) {
		s[k][0] = '\0';
	}

	k = 1;
	sprintf_s(s[k], 22, "%*s", 3 * wd, "");

	for (int i = 1; i <= mdays; i++) {
		sprintf_s(tmp, 4, "%3d", i);
		strcat_s(s[k], 22, tmp);
		if (++wd % 7 == 0) {
			k++;
		}
	}

	if (wd % 7 == 0) {
		k--;
	}
	else {
		if (n != 3) {
			for (wd %= 7; wd < 7; wd++) {
				strcat_s(s[k], 22, "   ");
			}
		}
	}
	while (++k < 7) {
		sprintf_s(s[k], 22, "%21s", "");
	}
}
void print2(char sbuf[3][7][22], int n, int numweek) {
	int i = 0;
	for (i = 0; i < n; i++) {
		printf("%s   ", sbuf[i][0]);
	}
	putchar('\n');
	for (i = 0; i < n; i++) {
		printf(" 日 月 火 水 木 金 土   ");
	}
	putchar('\n');

	for (i = 0; i < n; i++) {
		printf("----------------------  ");
	}
	putchar('\n');

	if (numweek <= 0) {
		for (i = 1; i < 7; i++) {
			for (int j = 0; j < n; j++) {
				printf("%s   ", sbuf[j][i]);
			}
			putchar('\n');
		}
	}
	else {
		for (i = 1; i < 6; i++) {
			for (int j = 0; j < n; j++) {
				printf("%s   ", sbuf[j][i]);
			}
			putchar('\n');
		}
	}
	putchar('\n');
}
int check_numweek(int y, int m) {
	int wd = 0;
	int flag = 0;
	int numday = 0;

	for (int i = 0; i < 3; i++) {
		wd = dayofweek(y, m, 1);
		numday = mday[m - 1];
		switch (numday) {
		case 28: flag++; break;
		case 30: if (wd <= 5) flag++; break;
		case 31: if (wd <= 4) flag++; break;
		}
		m++;
		if (m == 13) {
			m = 1;
			y++;
		}
	}

	if (flag == 3) return 1;
	else return 0;
}
void put_calenders3(int y1, int m1, int y2, int m2) {
	int y = y1;
	int m = m1;
	int n = 0;
	char sbuf[3][7][22]{ 0 };
	int numweek = 0;

	while (y <= y2) {
		//左端の月で各三か月の週数を調べる
		if (n == 0) {
			numweek = check_numweek(y, m);
		}
		if (y == y2 && m > m2) break;
		make_calender2(y, m, sbuf[n++], n);
		if (n == 3) {
			print2(sbuf, n, numweek);
			n = 0;
			numweek = 0;
		}
		m++;
		if (m == 13 && y < y2) {
			y++;
			m = 1;
		}
	}
	if (n) {
		print2(sbuf, n, numweek);
	}
}
int strncmpx(const char* s1, const char* s2, size_t n) {
	while (n && toupper(*s1) && toupper(*s2)) {
		if (toupper(*s1) != toupper(*s2)) {
			return (unsigned char)*s1 - (unsigned char)*s2;
		}
		s1++;
		s2++;
		n--;
	}
	if (!n) return 0;
	if (*s1) return 1;
	return -1;
}
int get_month(char* s) {
	int m = 0;
	const char* month[] = { "", "January", "Febuary", "March", "April",
							"May", "June", "July", "August", "Septmber",
							"October", "November", "December" };

	m = atoi(s);
	if (m >= 1 && m <= 12) {
		return m;
	}

	for (int i = 1; i <= 12; i++) {
		if (strncmpx(month[i], s, 3) == 0) {
			return i;
		}
	}

	return -1;
}

int main(int argc, char* argv[]) {
	int y1 = 0, m1 = 0;
	int y2 = 0, m2 = 0;
	time_t t = time(NULL);
	struct tm local {};
	localtime_s(&local, &t);

	y1 = local.tm_year + 1900;
	m1 = local.tm_mon + 1;

	if (argc >= 2) {
		m1 = get_month(argv[1]);
		if (m1 < 0 || m1 > 12) {
			fprintf_s(stderr, "月の値が不正です。\n");
			return 1;
		}
	}
	if (argc >= 3) {
		y1 = atoi(argv[2]);
		if (y1 < 0) {
			fprintf_s(stderr, "年の値が不正です。\n");
			return 1;
		}
	}

	y2 = y1;
	m2 = m1;
	for (int i = 0; i < 2; i++) {
		m2++;
		if (m2 == 13) {
			y2++;
			m2 = 1;
		}
	}


	put_calenders3(y1, m1, y2, m2);

	return 0;
}
