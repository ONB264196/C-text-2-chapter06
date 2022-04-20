#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<time.h>
#define _0607


int mday[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
int mday_leap[12] = { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
void put_date(const struct tm* timer) {
	const char* wday_name[] = { "日", "月", "火", "水", "木", "金", "土" };

	printf("%4d年%02d月%02d日(%s)%02d時%02d分%02d秒",
			timer->tm_year + 1900,
			timer->tm_mon + 1,
			timer->tm_mday,
			wday_name[timer->tm_wday],
			timer->tm_hour,
			timer->tm_min,
			timer->tm_sec
		);
}
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
void put_calender(int y, int m) {
	int wd = dayofweek(y, m, 1);
	int mdays = monthdays(y, m);

	printf(" 日 月 火 水 木 金 土 \n");
	printf("----------------------\n");

	printf("%*s", 3 * wd, "");

	for (int i = 1; i <= mdays; i++) {
		printf("%3d", i);
		if (++wd % 7 == 0) {
			putchar('\n');
		}
	}
	if (wd % 7 != 0) {
		putchar('\n');
	}
}
void make_calender(int y, int m, char s[7][22]) {
	int k = 0;
	int wd = dayofweek(y, m, 1);
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
		for (wd %= 7; wd < 7; wd++) {
			strcat_s(s[k], 22, "   ");
		}
	}
	while (++k < 7) {
		sprintf_s(s[k], 22, "%21s", "");
	}
}
void print(char sbuf[4][7][22], int n) {
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

	for (i = 1; i < 7; i++) {
		for (int j = 0; j < n; j++) {
			printf("%s   ", sbuf[j][i]);
		}
		putchar('\n');
	}
	putchar('\n');
}
void put_calenders(int y1, int m1, int y2, int m2) {
	int y = y1;
	int m = m1;
	int n = 0;
	char sbuf[4][7][22] { 0 };

	while (y <= y2) {
		if (y == y2 && m > m2) break;
		make_calender(y, m, sbuf[n++]);
		if (n == 4) {
			print(sbuf, n);
			n = 0;
		}
		m++;
		if (m == 13 && y < y2) {
			y++;
			m = 1;
		}
	}
	if (n) {
		print(sbuf, n);
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



//6-1
void disp_JST(void) {
	time_t current = time(NULL);
	struct tm timer;
	localtime_s(&timer, &current);

	printf("現在の日付・時刻(JST)は");
	put_date(&timer);
	printf("です。\n");
}
//6-2
void disp_UTC(void) {
	time_t current = time(NULL);
	struct tm timer;
	gmtime_s(&timer, &current);

	printf("現在の日付・時刻(UTC)は");
	put_date(&timer);
	printf("です。\n");
}
//6-3
void disp_asctime(void) {
	time_t current = time(NULL);
	struct tm timer;
	char str[32] = { 0 };

	localtime_s(&timer, &current);
	asctime_s(str, 32, &timer);

	printf("現在の日付・時刻 : %s", str);
}
//6-5
void disp_ctime(void) {
	time_t current = time(NULL);
	char str[32];

	ctime_s(str, 32, &current);

	printf("現在の日付・時刻 : %s", str);
	
}
//6-7
void calculation(void) {
	int a = 0, b = 0, c = 0, d = 0;
	int x = 0;
	time_t start = 0, end = 0;

	srand((unsigned)time(NULL));

	a = rand() % 100;
	b = rand() % 100;
	c = rand() % 100;
	d = rand() % 100;

	printf("%d + %d + %d + %dは何ですか : ", a, b, c, d);

	start = time(NULL);

	while (1) {
		scanf_s("%d", &x);
		if (x == a + b + c + d) {
			break;
		}
		printf("\a違いますよ!!\n再入力してください : ");
	}

	end = time(NULL);

	printf("%.0f秒かかりました\n", difftime(end, start));
}
//6-10
void disp_mktime(void) {
	int y = 0, m = 0, d, w;
	const char* ws[] = { "日", "月", "火", "水", "木", "金", "土" };

	printf("曜日を求めます。\n");
	printf("年 : "); scanf_s("%d", &y);
	printf("月 : "); scanf_s("%d", &m);
	printf("日 : "); scanf_s("%d", &d);

	w = dayofweek(y, m, d);

	if (w != -1) {
		printf("それは%s曜日です\n", ws[w]);
	}
	else {
		printf("求められませんでした。\n");
	}
}
//6-11
void disp_calender(void) {
	int y = 0, m = 0;

	printf("カレンダーを表示します。\n");
	printf("年 : "); scanf_s("%d", &y);
	printf("月 : "); scanf_s("%d", &m);

	putchar('\n');

	put_calender(y, m);
}
//6-12
void disp_calenders(void) {
	int y1 = 0, m1 = 0, y2 = 0, m2 = 0;

	printf("カレンダーを表示します。\n");

	printf("開始年月を入力してください。\n");
	printf("年 : "); scanf_s("%d", &y1);
	printf("月 : "); scanf_s("%d", &m1);

	printf("終了年月を入力してください。\n");
	printf("年 : "); scanf_s("%d", &y2);
	printf("月 : "); scanf_s("%d", &m2);

	putchar('\n');

	put_calenders(y1, m1, y2, m2);
}

#ifdef _0600a
int main(void) {
	disp_UTC();
	return 0;
}
#endif

#ifdef _0600b
int main(int argc, char* argv[]) {
	int y = 0, m = 0;
	time_t t = time(NULL);
	struct tm local {};
	localtime_s(&local, &t);

	y = local.tm_year + 1900;
	m = local.tm_mon + 1;

	if (argc >= 2) {
		m = get_month(argv[1]);
		if (m < 0 || m > 12) {
			fprintf_s(stderr, "月の値が不正です。\n");
			return 1;
		}
	}
	if (argc >= 3) {
		y = atoi(argv[2]);
		if (y < 0) {
			fprintf_s(stderr, "年の値が不正です。\n");
			return 1;
		}
	}

	printf("%d年%d月\n\n", y, m);

	put_calender(y, m);

	return 0;
}
#endif

#ifdef _0601
void make_calender2(int y, int m, char s[7][22], int n) {
	int k = 0;
	int wd = dayofweek(y, m, 1);
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
void print2(char sbuf[3][7][22], int n) {
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

	for (i = 1; i < 7; i++) {
		for (int j = 0; j < n; j++) {
			printf("%s   ", sbuf[j][i]);
		}
		putchar('\n');
	}
	putchar('\n');
}
void put_calenders2(int y1, int m1, int y2, int m2) {
	int y = y1;
	int m = m1;
	int n = 0;
	char sbuf[3][7][22]{ 0 };

	while (y <= y2) {
		if (y == y2 && m > m2) break;
		make_calender2(y, m, sbuf[n++], n);
		if (n == 3) {
			print2(sbuf, n);
			n = 0;
		}
		m++;
		if (m == 13 && y < y2) {
			y++;
			m = 1;
		}
	}
	if (n) {
		print2(sbuf, n);
	}
}

int main(void) {
	int y1 = 0, m1 = 0, y2 = 0, m2 = 0;

	printf("カレンダーを表示します。\n");

	printf("開始年月を入力してください。\n");
	printf("年 : "); scanf_s("%d", &y1);
	printf("月 : "); scanf_s("%d", &m1);

	printf("終了年月を入力してください。\n");
	printf("年 : "); scanf_s("%d", &y2);
	printf("月 : "); scanf_s("%d", &m2);

	putchar('\n');

	put_calenders2(y1, m1, y2, m2);

	return 0;
}
#endif

#ifdef _0602
void make_calender2(int y, int m, char s[7][22], int n) {
	int k = 0;
	int wd = dayofweek(y, m, 1);
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
void print2(char sbuf[3][7][22], int n) {
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

	for (i = 1; i < 7; i++) {
		for (int j = 0; j < n; j++) {
			printf("%s   ", sbuf[j][i]);
		}
		putchar('\n');
	}
	putchar('\n');
}
void put_calenders2(int y1, int m1, int y2, int m2) {
	int y = y1;
	int m = m1;
	int n = 0;
	char sbuf[3][7][22]{ 0 };

	while (y <= y2) {
		if (y == y2 && m > m2) break;
		make_calender2(y, m, sbuf[n++], n);
		if (n == 3) {
			print2(sbuf, n);
			n = 0;
		}
		m++;
		if (m == 13 && y < y2) {
			y++;
			m = 1;
		}
	}
	if (n) {
		print2(sbuf, n);
	}
}
int typecheck(int y1, int m1, int y2, int m2) {
	if (m1 < 1 || m1 > 12 || m2 < 1 || m2 > 12) {
		printf("\a1月から12月の範囲で入力してください。\n\n");
		return -1;
	}

	if ((y2 * 4 + m2) - (y1 * 4 + m1) < 0) {
		printf("\a開始年月が終了年月を超えています。\n\n");
		return -1;
	}

	return 0;
}

int main(void) {
	int y1 = 0, m1 = 0, y2 = 0, m2 = 0;
	int err = 0;

	printf("カレンダーを表示します。\n");

	do {
		printf("開始年月を入力してください。\n");
		printf("年 : "); scanf_s("%d", &y1);
		printf("月 : "); scanf_s("%d", &m1);

		printf("終了年月を入力してください。\n");
		printf("年 : "); scanf_s("%d", &y2);
		printf("月 : "); scanf_s("%d", &m2);

		err = typecheck(y1, m1, y2, m2);
	} while (err < 0);
	


	putchar('\n');

	put_calenders2(y1, m1, y2, m2);

	return 0;
}
#endif

#ifdef _0603
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
	int numweek = 0 ;

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
int typecheck(int y1, int m1, int y2, int m2) {
	if (m1 < 1 || m1 > 12 || m2 < 1 || m2 > 12) {
		printf("\a1月から12月の範囲で入力してください。\n\n");
		return -1;
	}

	if ((y2 * 4 + m2) - (y1 * 4 + m1) < 0) {
		printf("\a開始年月が終了年月を超えています。\n\n");
		return -1;
	}

	return 0;
}

int main(void) {
	int y1 = 0, m1 = 0, y2 = 0, m2 = 0;
	int err = 0;

	printf("カレンダーを表示します。\n");

	do {
		printf("開始年月を入力してください。\n");
		printf("年 : "); scanf_s("%d", &y1);
		printf("月 : "); scanf_s("%d", &m1);

		printf("終了年月を入力してください。\n");
		printf("年 : "); scanf_s("%d", &y2);
		printf("月 : "); scanf_s("%d", &m2);

		err = typecheck(y1, m1, y2, m2);
	} while (err < 0);



	putchar('\n');

	put_calenders3(y1, m1, y2, m2);

	return 0;
}
#endif

#ifdef _0604
void make_calender3(int y, int m, char s[7][22], int n) {
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
	
	while (++k < 7) {
		sprintf_s(s[k], 22, "%21s", "");
	}
}
void print3(char sbuf[3][7][22], int n, int numweek) {
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
				printf("%-21s   ", sbuf[j][i]);
			}
			putchar('\n');
		}
	}
	else {
		for (i = 1; i < 6; i++) {
			for (int j = 0; j < n; j++) {
				printf("%-21s   ", sbuf[j][i]);
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
		make_calender3(y, m, sbuf[n++], n);
		if (n == 3) {
			print3(sbuf, n, numweek);
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
		print3(sbuf, n, numweek);
	}
}
int typecheck(int y1, int m1, int y2, int m2) {
	if (m1 < 1 || m1 > 12 || m2 < 1 || m2 > 12) {
		printf("\a1月から12月の範囲で入力してください。\n\n");
		return -1;
	}

	if ((y2 * 4 + m2) - (y1 * 4 + m1) < 0) {
		printf("\a開始年月が終了年月を超えています。\n\n");
		return -1;
	}

	return 0;
}

int main(void) {
	int y1 = 0, m1 = 0, y2 = 0, m2 = 0;
	int err = 0;

	printf("カレンダーを表示します。\n");

	do {
		printf("開始年月を入力してください。\n");
		printf("年 : "); scanf_s("%d", &y1);
		printf("月 : "); scanf_s("%d", &m1);

		printf("終了年月を入力してください。\n");
		printf("年 : "); scanf_s("%d", &y2);
		printf("月 : "); scanf_s("%d", &m2);

		err = typecheck(y1, m1, y2, m2);
	} while (err < 0);



	putchar('\n');

	put_calenders3(y1, m1, y2, m2);

	return 0;
}
#endif

#ifdef _0605
int strncmpx2(const char* s1, const char* s2, size_t n) {
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
int get_month2(char* s) {
	int m = 0;
	const char* month[13][8] = { "        ", "January ", "Febuary ", "March   ", "April   ",
							"May     ", "June    ", "July    ", "August  ", "Septmber ",
							"October ", "November ", "December " };

	m = atoi(s);
	if (m >= 1 && m <= 12) {
		return m;
	}

	for (int i = 1; i <= 12; i++) {
		if (strncmpx2(*month[i], s, 8) == 0) {
			return i;
		}
	}

	return -1;
}

int main(int argc, char* argv[]) {
	int y = 0, m = 0;
	time_t t = time(NULL);
	struct tm local {};
	localtime_s(&local, &t);

	y = local.tm_year + 1900;
	m = local.tm_mon + 1;

	if (argc >= 2) {
		m = get_month2(argv[1]);
		if (m < 0 || m > 12) {
			fprintf_s(stderr, "月の値が不正です。\n");
			return 1;
		}
	}
	if (argc >= 3) {
		y = atoi(argv[2]);
		if (y < 0) {
			fprintf_s(stderr, "年の値が不正です。\n");
			return 1;
		}
	}

	printf("%d年%d月\n\n", y, m);

	put_calender(y, m);

	return 0;
}
#endif

//0606
/* ----------- 演習6-6について -----------

・準備
１.エクスプローラーから"0606.cpp"をコピーする
２.Cドライブに"code"と名付けてファイルを作る
３."code"内に"0606.cpp"を貼り付ける

・実行手順
１."x64 Native Tools Command Prompt for VS 2022"を起動
２.以下を順に入力
   「cl」
   「cd c:\code」
   「notepad 0606.cpp」
   ※ここでメモ帳が表示されるが閉じる
   　ファイルが見つからない場合は手順、入力内容を確認する
   「dir」
   「cl 0606.cpp」
３.実行
   (例)「0606」→ 現在から三か月分表示
   (例)「0606 5」→ 現在の年の5月から三か月分表示
   (例)「0606 11 1999」→ 1999年11月から三か月分表示

４.終了
   「exit」

 --------------------------------------- */

#ifdef _0607
unsigned long num(int y, int m, int d) {
	unsigned long n = 0;
	n += y * (365 + is_leap(y));
	for (int i = 1; i < m; i++) {
		n += mday[i];
	}
	n += d;
	return n;
}
int datecheck(int y, int m, int d, int Y, int M, int D) {
	if (y < Y) return 1;
	if (Y == y && M > m) return 1;
	if (Y == y && M == m && D > d) return 1;
	if (Y < y - 20) return 2;
	if (Y == y - 20 && M < m) return 2;
	if (Y == y - 20 && M == m && D < d) return 2;
	if (Y < 0) return 3;
	if (M > 12 || M < 0) return 3;
	if (is_leap(Y)) if (D > mday_leap[M - 1]) return 3;
	else { if (D > mday[M - 1]) return 3; }
	return 0;
}
int main(void) {
	int day[3] = { 0 };
	unsigned long day_num = 0;
	int ans[3] = { 0 };
	unsigned long ans_num = 0;	
	int err = 0;
	time_t t = time(NULL);
	struct tm local {};
	localtime_s(&local, &t);

	int y = local.tm_year + 1900;
	int m = local.tm_mon + 1;
	int d = local.tm_mday;

	srand((unsigned)time(NULL));
	ans[0] = rand() % 20 + (y - 20);
	do {
		ans[1] = rand() % 12 + 1;

		if (is_leap(ans[0])) ans[2] = rand() % mday_leap[ans[1] - 1];
		else ans[2] = rand() % mday[ans[1] - 1];
	} while (datecheck(y, m , d, ans[0], ans[1], ans[2]) > 0);
	ans_num = num(ans[0], ans[1], ans[2]);

	printf("現在から20年前までの範囲の年月日を当ててください。\n\n");

	do {
		err = 0;
		do {
			switch (err) {
			case 1: puts("\a現在より先の年月日です。\n"); break;
			case 2: puts("\a20年以上前の年月日です。\n"); break;
			case 3: puts("\a無効な数値の入力です。\n"); break;
			default: break;
			}
			if (err > 0) puts("再度入力してください。");
			printf("年 :"); scanf_s("%d", &day[0]);
			printf("月 :"); scanf_s("%d", &day[1]);
			printf("日 :"); scanf_s("%d", &day[2]);
			err = datecheck(y, m, d, day[0], day[1], day[2]);
		} while (err > 0);
		day_num = num(day[0], day[1], day[2]);

		if (day_num > ans_num) {
			printf("\aそれよりも前です\n");
			if (ans[0] == day[0] && ans[1] ==day[1]) {
				printf("年・月は合っています。\n");
			}
		}
		else if (day_num < ans_num) {
			printf("\aそれよりも後です\n");
			if (ans[0] == day[0] && ans[1] == day[1]) {
				printf("年・月は合っています。\n");
			}
		}
		putchar('\n');
	} while (ans_num != day_num);

	puts("正解です。");
	return 0;
}
#endif