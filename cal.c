#include "types.h"
#include "stat.h"
#include "user.h"



int isLeapYear( int year );
int leapYears( int year );
int todayOf( int y, int m, int d);
long days( int y, int m, int d);
void calendar( int y, int m);

int
main(int argc, char* argv[])
{
    int year, month;
    if(argc == 1)
    {
        calendar(2020,5);
    }
    else if(argc == 3)
    {
        year = atoi(argv[2]);
        month = atoi(argv[1]);
        calendar(year, month);
    }
    else
    {
        printf( 1,"error : Can only Take 1 argument or 3 arguments\n");
    }
    return 0;
}

int isLeapYear( int y)
{
    return( y % 400 == 0) || ((y % 4 == 0 )&& (y % 100 != 0));
}

int leapYears( int y)
{
    return y/4 - y/100 + y/400;
}

int todayOf( int y, int m, int d)
{
    static int DayOfMonth[] = {-1,0,31,59,90,120,151,181,212,243,304,334};

    return DayOfMonth[m] + d + ((m>2 && isLeapYear(y))? 1 : 0);
}

long days( int y, int m, int d)
{
    int lastYear;
    lastYear = y - 1;

    return 365L * lastYear + leapYears(lastYear) + todayOf(y,m,d);
}

void calendar(int y, int m)
{
    const char *NameOfMonth[] = {"dump", "Januari", "Februari", "Maret", "April", "Mei", "Juni", "Juli", "Agustus", "September", "Oktober", "Novemeber", "Desember"};
    char week[] = "Mi Se Se Ra Ka Ju Sa";
    int DayOfMonth[] = {-1,31,28,31,30,31,30,31,31,30,31,30,31};
    int weekOfTodpDay;
    int i,day;

    weekOfTodpDay = days(y,m,1)%7;
    if(isLeapYear(y))
        DayOfMonth[2] = 29;
    printf( 1,"\n%s %d\n", NameOfMonth[m], y);
    printf( 1,"%s\n", week);

    for ( i = 0; i < weekOfTodpDay; i++)
    {
        printf(1,"   ");
    }
    for (i = weekOfTodpDay, day=1;day <= DayOfMonth[m] ; i++,day++)
    {
        if(day < 10)
            printf(1,"%d  ",day);
        else 
            printf(1,"%d ",day);
        if( i % 7 == 6)
            printf(1,"\n");
    }
    printf(1,"\n");
    
    
}