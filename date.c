#include "types.h"  // datatypes
#include "user.h"   // prototypes system calls
#include "date.h"   // struct rtcdate

long long power(int,int);
int check_leap(int);
void month_name(int);
void day_name(int,int,int);
void time(void);
void yesterday(void);
void today(void);
void tomorrow(void);
void particular_day(char *);
void utc_day(void);
void day(char *);

int main(int argc, char *argv[])
{
	if(argc==1){
		today();  // (IST format)
	}
	else
	{
		if((argc==3)&&(strcmp("-d",*(argv+1))==0)){
			day(*(argv+2));  
		}
		else if((argc==2)&&(strcmp("-u",*(argv+1))==0)){
			utc_day();  // (UTC format)
		}
		else{
			printf(1,"Invalid\n");
		}
	}
	exit();
}

// hitung pangkat
long long power(int x,int y)
{
	long long number = 1;
	for(int i=0;i<y;i++)
	{
		number=number*x;
	}
	return(number);
}

// cek tahun kabisat
int check_leap(int y)
{
	int result=0;
	if((y%400==0) || (y%4==0)){
		result=1;
	}
	else{ 
		result=0;
	}
	return(result);
}

// cek nama bulan
void month_name(int m)
{
	switch(m)
	{
		case 1:
			printf(1," Jan");
			break;
		case 2:
			printf(1," Feb");
		       	break;
		case 3:
			printf(1," Mar");
		       	break;
		case 4:
			printf(1," Apr");
		       	break;
		case 5:
			printf(1," Mei");
		       	break;
		case 6:
			printf(1," Jun");
		       	break;
		case 7:
			printf(1," Jul");
		       	break;
		case 8:
			printf(1," Agt");
		       	break;
		case 9:
			printf(1," Sep");
		       	break;
		case 10:
			printf(1," Okt");
		       	break;
		case 11:
			printf(1," Nov");
		       	break;
		case 12:printf(1," Des");
		       break;
	}
}

// cek nama hari
void day_name(int x,int y,int z)
{
	int initial=4, count=0;
	if(x>1900)
	{
		for(int i=1900;i<x;i++)
		{
			if(check_leap(i)){
				count += 366;
			}
			else{
				count += 365;
			}
		}
	}
	for(int i=1;i<y;i++)
	{
		if(i==2)
		{
			if(check_leap(x)){
				count += 29;
			}
			else{
				count += 28;
			}
		}
		else if((i<8)&&(i%2==1)){
			count += 31;
		}
		else if((i<8)&&(i%2==0)){
			count += 30;
		}
		else if((i>=8)&&(i%2==0)){
			count += 31;
		}
		else{
			count += 30;
		}
	}
	int final = (initial+count+z-1)%7;
	switch(final)
	{
		case 0:
			printf(1,"Ming");
		       	break;
		case 1:
			printf(1,"Sen");
		       	break;
		case 2:
			printf(1,"Sel");
		       	break;
		case 3:
			printf(1,"Rab");
		       	break;
		case 4:
			printf(1,"Kam");
		       	break;
		case 5:
			printf(1,"Jum");
		       	break;
		case 6:
			printf(1,"Sab");
		       	break;
	 }
}

// IST format
void time()
{
	struct rtcdate r;
	if (date(&r)){
		printf(1, "Failed\n");
		exit();
	}
	if(r.minute+30>59){
		r.hour += 6;
		r.minute = r.minute+30-59;
	}
	else{
		r.hour += 5;
		r.minute += 30;
	}
	if(r.hour>=24){
		r.hour -= 24;
	}
	printf(1," %d:%d:%d",r.hour,r.minute,r.second);
}

// hari kemarin
void yesterday()
{
	struct rtcdate r;
	if (date(&r)){
		printf(1, "Failed\n");
		exit();
	}

	// bulan maret
	if(r.month == 3){
		if(check_leap(r.year))
		{
			if(r.day==1){
				r.month -= 1;
				r.day = 29;
			}
			else{
				r.day -= 1;
			}
		}
		else
		{
			if(r.day==1){
				r.month -= 1;
				r.day = 28;
			}
			else{
				r.day -= 1;
			}
		}
	}

	// 1 januari
	else if((r.day==1)&&(r.month==1))
	{
		r.month = 12;
		r.day = 31;
		r.year -= 1;
	}

	else
	{
		if(r.month<9)
		{
			if(r.month%2==0)
			{
				if(r.day==1)
				{
					r.month -= 1;
					r.day = 31;
				}
				else{
					r.day -= 1;
				}
			}
			else
			{
				if(r.day==1)
				{
					r.month -= 1;
					r.day = 30;
				}
				else{
					r.day -= 1;
				}
			}
		}
		else
		{
			if(r.month%2==1)
			{
				if(r.day==1)
				{
					r.month -= 1;
					r.day = 31;
				}
				else{
					r.day -= 1;
				}
			}
			else
			{
				if(r.day==1)
				{
					r.month -= 1;
					r.day = 30;
				}
				else{
					r.day -= 1;
				}
			}
		}
	}
	day_name(r.year,r.month,r.day);  // hari kemarin
	month_name(r.month);  // bulan kemarin
	printf(1," %d",r.day);  // tanggal kemarin
	time();  // waktu kemarin
	printf(1," IST %d\n",r.year);  // tahun kemarin
}
	     
// hari ini
void today()
{
	struct rtcdate r;
	if (date(&r)) 
	{
		printf(1, "Failed\n");
		exit();
	}
	day_name(r.year,r.month,r.day);	 // hari
	month_name(r.month);  // bulan
	printf(1," %d",r.day);  // tanggal
	time();  // waktu
	printf(1," IST %d\n",r.year);  // tahun
}

// hari besok
void tomorrow()
{
	struct rtcdate r;
	if (date(&r)) 
	{
		printf(1, "Failed\n");
		exit();
	}

	// bulan Februari
	if(r.month == 2)
	{
		if(check_leap(r.year))
		{
			if(r.day==29)
			{
				r.month += 1;
				r.day = 1;
			}
			else{
				r.day += 1;
			}
		}
		else
		{
			if(r.day==28)
			{
				r.month += 1;
				r.day = 1;
			}
			else{
				r.day += 1;
			}
		}
	}

	// 31 Desember
	else if((r.day==31)&&(r.month==12))
	{
		r.month = 1;
		r.day = 1;
		r.year += 1;
	}

	else
	{
		if(r.month<8)
		{
			if(r.month%2==1)
			{
				if(r.day==31)
				{
					r.month += 1;
					r.day = 1;
				}
				else
					r.day += 1;
			}
			else
			{
				if(r.day==30)
				{
					r.month += 1;
					r.day = 1;
				}
				else
					r.day += 1;
			}
		}
		else
		{
			if(r.month%2==1)
			{
				if(r.day==30)
				{
					r.month += 1;
					r.day = 1;
				}
				else{
					r.day += 1;
				}
			}
			else
			{
				if(r.day==31)
				{
					r.month += 1;
					r.day = 1;
				}
				else{
					r.day += 1;
				}
			}
		}
	}
	day_name(r.year,r.month,r.day);  // hari besok
	month_name(r.month);  // bulan besok
	printf(1," %d",r.day);  // tanggal besok
	time();  // waktu besok
	printf(1," IST %d\n",r.year); // tahun besok
}

// tanggal tertentu
void particular_day(char *x)
{
	int flag = 1;
	for(int i=0;i<4;i++)
	{
		if(*(x+i)=='-')
		{
			flag = 0;
			break;
		}
	}
	for(int i=5;i<7;i++)
	{
		if(*(x+i)=='-')
		{
			flag = 0;
			break;
		}
	}
	for(int i=8;i<10;i++)
	{
		if(*(x+i)=='-')
		{
			flag = 0;
			break;
		}
	}
	if(flag==0)
	{
		printf(1,"Invalid date\n");
		exit();
	}

	int y=0, m=0, d=0;

	for(int i=0;i<4;i++)
	{
		y += (*(x+i) - '0')*power(10,3-i);
	}
	for(int i=5;i<7;i++)
	{
		m += (*(x+i) - '0')*power(10,6-i);
	}
	for(int i=8;i<10;i++)
	{
		d += (*(x+i) - '0')*power(10,9-i);
	}	
	if((m>12)||(d>31)||(m<1)||(d<1)||(y<1900))
	{
		printf(1,"Invalid date\n");
		exit();
	}	
	else if(m==2)
	{
		if(d>28)
		{
			if(check_leap(y))
			{
				if(d>29)
				{
					printf(1,"Invalid date\n");
					exit();
				}
			}
			else
			{
				printf(1,"Invalid date\n");
				exit();
			}
		}
	}			
	day_name(y,m,d);
	month_name(m);
	printf(1," %d 00:00:00 IST %d\n",d,y);
}	

// UTC Format
void utc_day()
{
	struct rtcdate r;
	if (date(&r)) 
	{
		printf(1, "Failed\n");
		exit();
	}
	day_name(r.year,r.month,r.day);	 // hari
	month_name(r.month);  // bulan
	printf(1," %d %d:%d:%d UTC %d\n",r.day,r.hour,r.minute,r.second,r.year);  // tanggal
}
	
// opsi user
void day(char *x)
{
	switch(*(x+2))
	{
		case 'd':
			today(); // huruf ketiga d (sekarang)
		        break;
		case 'm':
			tomorrow(); // huruf ketiga m (besok)
		        break;
		case 's':
			yesterday(); // huruf ketiga s (kemarin)
		        break;
		default:
			particular_day(x); // tanggal tertentu
			break;
	}
}
