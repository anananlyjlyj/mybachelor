#include <cassert>
int floorDiv(int a, int b)
{
	int x = (a > 0)? a : -a;
	int y = (b > 0)? b : -b;
	int c = (x % y == 0)? 0 : y - x % y;
	return (a * b > 0)?  a / b : -((x + c)/ y) ;  
}
int floorMod(int a, int b)
{
	return a - floorDiv(a, b) * b;
}
int weekday2001(int d, int m, int y)
{
	int z = y - 2001;
	int j1 = (365 * z + z / 4 - z / 100 + z / 400) % 7;
	int p = (m == 1)?	d
					:	(m == 2)?	d + 31
					:	(m > 2 && ((y % 4 == 0 && y % 100 != 0) || y % 400 == 0) )?	d + 60 + (153 * m - 457) / 5
					:	d + 59 + (153 * m - 457) / 5;
	int w = (j1 + p - 1) % 7;
	return w;
}
int weekday1(int d, int m, int y)
{
	int z = y - 1;
	int j1 = (365 * z + z / 4 - z / 100 + z / 400) % 7;
	int p = (m == 1)?	d
					:	(m == 2)?	d + 31
					:	(m > 2 && ((y % 4 == 0 && y % 100 != 0) || y % 400 == 0) )?	d + 60 + (153 * m - 457) / 5
					:	d + 59 + (153 * m - 457) / 5;
	int w = (j1 + p - 1) % 7;
	return w;
}
/*
(e)Warum funktioniert?
	1) wenn y > 2001,
	z = y - 2001;
	j1(z) = (365 * z + z / 4 - z / 100 + z / 400) % 7;
	sei z' = y - 1 = z + 2000;
	j1(z') = (365 * z' + z' / 4 - z' / 100 + z' / 400) % 7 
		   = (365 * z + z / 4 - z / 100 + z / 400) % 7 + (365 * 2000 + 2000 / 4 - 2000 / 100 + 2000 / 400) % 7;
	wobei (365 * 2000 + 2000 / 4 - 2000 / 100 + 2000 / 400) % 7 = 0 gilt, also j1(z') = j1(z);
	2) wenn 1 < y < 2001, 
	z' = y - 1 > 0 => z / 4 > 0, z / 100 > 0, z / 400 > 0,
	da in C++ positive Ergebnisse abgrundet werden, gilt j1(z') = j1, die in weekday() definiert wird.
	Deshalb bekommt man die selbe Ergebnisse.
*/
int weekday(int d, int m, int y)
{
	int z = y - 2001;
	int j1 = floorMod((365 * z + floorDiv(z,4) - floorDiv(z, 100) + floorDiv(z, 400)), 7);
	int p = (m == 1)?	d
					:	(m == 2)?	d + 31
					:	(m > 2 && ((y % 4 == 0 && y % 100 != 0) || y % 400 == 0) )?	d + 60 + (153 * m - 457) / 5
					:	d + 59 + (153 * m - 457) / 5;
	int w = (j1 + p - 1) % 7;
	return (y>2001)? weekday2001(d,m,y) : w;
	
}
int main()
{
	//weekday2001 testen
	assert (weekday2001(2,2,2100) == 1);		
	assert (weekday2001(13,3,2100) == 5);		
	assert (weekday2001(13,4,2016) == 2);		
	assert (weekday2001(15,1,2015) == 3);		
	assert (weekday2001(15,5,2013) == 2);		
	assert (weekday2001(1,2,2012) == 2);		
	assert (weekday2001(15,1,2001) == 0);		
	assert (weekday2001(15,8,2001) == 2);	
	
	//weekday testen
	assert (weekday(2,2,2100) == 1);		//nach 2001, ausfallendes Schaltjahr, vor Schalttag
	assert (weekday(13,3,2100) == 5);		//nach 2001, ausfallendes Schaltjahr, nach Schalttag
	assert (weekday(13,4,2016) == 2);		//nach 2001, Schaltjahr, nach Schalttag
	assert (weekday(15,1,2015) == 3);		//nach 2001, kein Schaltjahr, vor Schalttag
	assert (weekday(15,5,2013) == 2);		//nach 2001, kein Schaltjahr, nach Schalttag
	assert (weekday(1,2,2012) == 2);		//nach 2001, Schaltjahr, vor Schalttag
	assert (weekday(15,1,2001) == 0);		//2001, kein Schaltjahr, vor Schalttag
	assert (weekday(15,8,2001) == 2);		//2001, kein Schaltjahr, nach Schalttag
	assert (weekday(1,6,1916) == 3);		//vor 2001, Schaltjahr, nach Schalttag
	assert (weekday(30,9,1817) == 1);		//vor 2001, kein Schaltjahr, nach Schalttag
	assert (weekday(12,2,1716) == 2);		//vor 2001, Schaltjahr, vor Schalttag
	assert (weekday(31,10,1700) == 6);		//vor 2001, ausfallendes Schaltjahr, nach Schalttag
	assert (weekday(1,11,1616) == 1);		//vor 2001, Schaltjahr, nach Schalttag
	assert (weekday(31,1,1600) == 0);		//vor 2001, ausfallendes Schaltjahr, vor Schalttag
	assert (weekday(13,12,1583) == 1);		//vor 2001, kein Schaltjahr, nach Schalttag
	assert (weekday(1,1,1583) == 5);		//vor 2001, kein Schaltjahr, vor Schalttag
	
	//weekday1 testen
	assert (weekday1(2,2,2100) == 1);		//nach 2001, ausfallendes Schaltjahr, vor Schalttag
	assert (weekday1(13,3,2100) == 5);		//nach 2001, ausfallendes Schaltjahr, nach Schalttag
	assert (weekday1(13,4,2016) == 2);		//nach 2001, Schaltjahr, nach Schalttag
	assert (weekday1(15,1,2015) == 3);		//nach 2001, kein Schaltjahr, vor Schalttag
	assert (weekday1(15,5,2013) == 2);		//nach 2001, kein Schaltjahr, nach Schalttag
	assert (weekday1(1,2,2012) == 2);		//nach 2001, Schaltjahr, vor Schalttag
	assert (weekday1(15,1,2001) == 0);		//2001, kein Schaltjahr, vor Schalttag
	assert (weekday1(15,8,2001) == 2);		//2001, kein Schaltjahr, nach Schalttag
	assert (weekday1(1,6,1916) == 3);		//vor 2001, Schaltjahr, nach Schalttag
	assert (weekday1(30,9,1817) == 1);		//vor 2001, kein Schaltjahr, nach Schalttag
	assert (weekday1(12,2,1716) == 2);		//vor 2001, Schaltjahr, vor Schalttag
	assert (weekday1(31,10,1700) == 6);		//vor 2001, ausfallendes Schaltjahr, nach Schalttag
	assert (weekday1(1,11,1616) == 1);		//vor 2001, Schaltjahr, nach Schalttag
	assert (weekday1(31,1,1600) == 0);		//vor 2001, ausfallendes Schaltjahr, vor Schalttag
	assert (weekday1(13,12,1583) == 1);		//vor 2001, kein Schaltjahr, nach Schalttag
	assert (weekday1(1,1,1583) == 5);		//vor 2001, kein Schaltjahr, vor Schalttag
    

	return 0;
}


