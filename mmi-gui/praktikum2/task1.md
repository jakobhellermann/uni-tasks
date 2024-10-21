a) 

```cpp
int x = 5;            // initialisierung und Wertzuweisung auf 5
int &r = x;           // r wird als Referenz auf x angelegt
r = 6;                // der Wert 6 wird der Referenz r, und somit auch x zugewiesen
cout << x << endl;    // 6
```

b)

```cpp
int x = 5;
int y = 10;
int &r = x;
r = y;                // der Wert von y (10) wird r (und somit x) zugewiesen. Keine Neuzuweisung für Referenzen möglich.
r = 6;                // Der Wert 6 wird r (und somit x) zugewiesen.
cout << y << endl;    // 10
```

c)
```cpp
int array[] = {1, 2, 3};        // array wird initialisiert 
int *p = &array[0];             // es wird die Adresse von array[0] gelesen, und in die Variable p (vom typ int*) gespeichert
*(p + 1) = 5;                   // der Pointer p wird um einen int verschoben dereferenziert, und an die Stelle wird der Wert 5 geschrieben
cout << array[1] << endl;       // 5
```

d)
```cpp
char name[64] = "MMI und GUI-Programmierung";   // name wird als char-array deklariert und initialisiert
char* p = name;                                 // Die Pointervariable p wird initialisiert auf die Adresse des Starts des Arrays "name"
char* &q = p;                                   // Eine Referenz q (typ char*) wird von p erstellt.
q += 4;                                         // q (und somit p) wird um 4 char verschoben
*p = '!';                                       // p wird dereferenziert und and die Stelle wird '!' geschrieben
cout << name << endl;                           // MMI !nd GUI-Programmierung
```