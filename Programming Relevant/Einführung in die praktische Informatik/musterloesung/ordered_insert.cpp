#include <vector>
#include <iostream>

int main()
{
    std::cout << "Zu sortierende Zahlen eingeben.\n"
                 "Abbruch durch Eingabe einer negativen Zahl.\n"
                 "Bestaetigen Sie mit Enter." << std::endl;

    std::vector<int> ordered_array;
    while(true)
    {
        // naechste Zahl einlesen
        int input;
        std::cin >> input;

        // Abbrechen wenn negativ
        if(input < 0)
            break;

        const int LOESUNG = 1;  // waehle Loesung 1 oder 2
        if(LOESUNG == 1)
        {
            // Loesung 1: Einfuegen mit insert()
            // =================================
            // richtige Position finden
            int k = 0;
            for(; k < ordered_array.size(); ++k)
            {
                if(input < ordered_array[k])
                    break; // input gehoert an Position k => Suche abbrechen
            }

            // Einfuegen bei Index k
            // Beachte: Wenn input groesser ist als alle bisherigen Array-Elemente,
            //          ist die Schleife bis zum Ende durchgelaufen, und es gilt
            //          jetzt k==ordered_array.size(). Das neue Element
            //          wird somit korrekterweise am Ende angefuegt.
            ordered_array.insert(ordered_array.begin()+k, input);
        }
        else
        {
            // Loesung 2: Einfuegen mit manuellem Verschieben
            // ==============================================
            // Array vergroessern (beliebige Zahl anhaengen)
            ordered_array.push_back(0);

            // Werte > input eine Position nach hinten schieben
            int k = ordered_array.size()-1;
            while(k > 0)
            {
                if(ordered_array[k-1] < input)
                    break; // input gehoert an Position k => Verschieben abbrechen
                ordered_array[k] = ordered_array[k-1];  // Verschieben
                --k;
            }

            // k enthaelt jetzt die Position wo input hingehoert
            // Beachte: Wenn input kleiner ist als alle bisherigen Array-Elemente,
            //          ist die Schleife bis zum Ende durchgelaufen, und es gilt
            //          jetzt k==0. Das neue Element wird somit korrekterweise am
            //          Anfang eingefuegt.
            ordered_array[k] = input;
        }
    }

    // 12 34 435 56 2 12 23 6 675 3 23 4 54 34 -1      // Testeingabe
    // 2 3 4 6 12 12 23 23 34 34 54 56 435 675         // Ausgabe
    for(int k=0; k < ordered_array.size(); ++k)
    {
        std::cout << ordered_array[k] << " ";
    }
    std::cout << std::endl;
}
