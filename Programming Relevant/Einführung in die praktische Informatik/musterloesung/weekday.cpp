#include <iostream>
#include <cassert>
#include <cmath>

bool is_leap_year(int y)
{
    return  (y%4 == 0)
                ? (y%100 == 0)
                    ? (y%400==0)
                       ? 1
                       : 0
                    : 1
                : 0;
}

// Aufgabenteil a)
int weekday2001(int d, int m, int y) {
	int z = y - 2001;
	int j = (365*z + (z/4) - (z/100) + (z/400)) % 7;

	int p = (m == 1)
                ? d
                : (m == 2)
                    ? d+31
                    : (m > 2 && !is_leap_year(y))
                        ? d + 59 + (153*m-457)/5
                        : d + 60 + (153*m-457)/5;

	return (j+p-1) % 7;
}

// Aufgabenteil b)
/* Die Ueberlegung hier ist, dass uns die Addition von b-1 im positiveen gerade
 * ueber die naechste ganze Zahl hievt. Im Positiven entspraeche das dem
 * Aufrunden, im negativen also dem Abrunden, das wir suchen.
 * Fuer alle anderen Faelle nutzen wir truncating division.
 */
int floorDiv(int a, int b) {
	int betrag_a = (a >= 0)
                      ?  a
                      : -a;
	int betrag_b = (b >= 0)
                      ?  b
                      : -b;

	int c = betrag_b - 1;

	return (a*b < 0)
              ? -((betrag_a + c)/betrag_b)
              :  a/b;
}

// Aufgabenteil c)
/* Ist der erste Operand negativ, gibt regulaeres modulo einen negativen Wert,
 * floorMod einen positiven. Ist der zweite Operand negativ, gibt regulaeres
 * modulo einen positiven, floorMod einen negativen Wert. In beiden Faellen
 * unterscheiden sich die Werte offensichtlich gerade um b.
 */
int floorMod(int a, int b) {
	return a - floorDiv(a,b)*b;  // Implementation nach Definition des Rests
}

// Aufgabenteil d)
int weekday(int d, int m, int y) {
	int z = y - 2001;
	int j = floorMod(365*z + floorDiv(z,4) - floorDiv(z,100) + floorDiv(z,400), 7);

	int p = (m == 1)
                ? d
                : (m == 2)
                    ? d+31
                    : (m > 2 && !is_leap_year(y))
                        ? d + 59 + (153*m-457)/5
                        : d + 60 + (153*m-457)/5;

	return floorMod(j+p-1, 7);
}

// Aufgabenteil e)
/* Rein algorithmisch laesst sich hier argumentieren, dass wir z genau zur
 * Berechnung von j nutzen. Subtrahieren wir fuer die Berechnung von z nun
 * 1 statt 2001, unterscheidet sich das resultierende z um genau 2000.
 * Passenderweise ist (365*2000+2000/4-2000/100+2000/400)%7 == 0, was also
 * keinen Einfluss auf unser Ergebnis hat.
 *
 * Das Analogon hierzu in der Realitaet ist, dass der 1.1.1 den gleichen
 * Wochentag hat wie der 1.1.2001, sprich sich die Rechnung analog durchfuehren
 * laesst.
 *
 * Durch das Basisjahr 1 sind nun alle Argumente der Division positiv, sodass
 * die Unterscheidung von trancating division und floor division nicht mehr
 * relevant ist.
 */
int weekday1(int d, int m, int y) {
	int z = y - 1;
	int j = (365*z + (z/4) - (z/100) + (z/400)) % 7;

	int p = (m == 1)
                ? d
                : (m == 2)
                    ? d+31
                    : (m > 2 && !is_leap_year(y))
                        ? d + 59 + (153*m-457)/5
                        : d + 60 + (153*m-457)/5;

	return (j+p-1) % 7;
}

int main() {
	// Aufgabenteil a)
	assert(weekday2001(5,1,2001) == 4);
	assert(weekday2001(20,2,2001) == 1);
	assert(weekday2001(29,3,2004) == 0);
	assert(weekday2001(29,3,2001) == 3);
	assert(weekday2001(29,2,2004) == 6);
	assert(weekday2001(29,2,2001) == 3);
	assert(weekday2001(10,1,1998) != 5);
	assert(weekday2001(13,2,1998) != 4);
	assert(weekday2001(13,3,1996) != 2);
	assert(weekday2001(13,3,1998) == 5); //trotz falscher Rechnung kann sich der richtige Wochentag ergeben.

	// Aufgabenteil d)
	// vor 2001, kein Schaltjahr
	assert(weekday(10,1,1998) == 5);
	assert(weekday(13,3,1998) == 4);
	// vor 2001, Schaltjahr
	assert(weekday(4,2,1996) == 6);
	assert(weekday(13,3,1996) == 2);
	// vor 2001, ausfallendes Schaltjahr
	assert(weekday(4,2,1900) == 6);
	assert(weekday(13,3,1900) == 1);
	// nach 2001, kein Schaltjahr
	assert(weekday(20,2,2001) == 1);
	assert(weekday(29,3,2001) == 3);
	// nach 2001, Schaltjahr
	assert(weekday(29,3,2004) == 0);
	assert(weekday(29,2,2004) == 6);
	// nach 2001, ausfallendes Schaltjahr
	assert(weekday(3,1,2100) == 6);
	assert(weekday(11,4,2100) == 6);
	// 4 weitere random testcases
	assert(weekday(1,1,1634) == 6);
	assert(weekday(28,12,1834) == 6);
	assert(weekday(25,5,1994) == 2);
	assert(weekday(19,7,1997) == 5);

	// Aufgabenteil e)
	// vor 2001, kein Schaltjahr
	assert(weekday1(10,1,1998) == 5);
	assert(weekday1(13,3,1998) == 4);
	// vor 2001, Schaltjahr
	assert(weekday1(4,2,1996) == 6);
	assert(weekday1(13,3,1996) == 2);
	// vor 2001, ausfallendes Schaltjahr
	assert(weekday1(4,2,1900) == 6);
	assert(weekday1(13,3,1900) == 1);
	// nach 2001, kein Schaltjahr
	assert(weekday1(20,2,2001) == 1);
	assert(weekday1(29,3,2001) == 3);
	// nach 2001, Schaltjahr
	assert(weekday1(29,3,2004) == 0);
	assert(weekday1(29,2,2004) == 6);
	// nach 2001, ausfallendes Schaltjahr
	assert(weekday1(3,1,2100) == 6);
	assert(weekday1(11,4,2100) == 6);
	// 4 weitere random testcases
	assert(weekday1(1,1,1634) == 6);
	assert(weekday1(28,12,1834) == 6);
	assert(weekday1(25,5,1994) == 2);
	assert(weekday1(19,7,1997) == 5);
}
