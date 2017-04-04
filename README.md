# MyString
C11 és C++11 programozás című tárgy házi feladata

A feladat leírása:

Referenciaszámlálást nem csak azért használunk, hogy tudjuk, hivatkozik-e még okos pointer egy objektumra, vagy fel lehet-e szabadítani. Arra is jó lehet, hogy a fölösleges másolásokat elkerüljük. Ha több objektum ugyanazzal az értékkel rendelkezik, akkor nincs értelme több másolatot is tartani a memóriában az értékről, hanem az objektumok osztozhatnak az érték egy közös reprezentációján. Így nem csak memóriát, hanem időt is spórolhatunk. Erre is példa a szokásos állatorvosi lovunk, a sztring:

MyString a, b, c;
a = b = c = "helló világ";

Ha nem osztjuk meg a karaktertömböket az egyes sztring objektumok között (1. ábra), a pazarlás nyilvánvaló. Ezért azt szeretnénk, ha a sztringek közös tömbbel rendelkezénének (2. ábra). Ez azonban így nem működhet, mert azt is kell tudnunk, hogy hány sztring használja ugyanazt a tömböt. Ezért jön a referenciaszámlálás a képbe (3. ábra). Fontos megfigyelni, hogy a referenciaszámlálók itt sem a sztring objektumokban, hanem a sztringértékeket tároló objektumokban vannak, mert az egyes tömböket hivatkozó objektumokat kell számolni. Ez egy erős csatolást jelent a karaktertömb és a referenciaszámláló között, ezért azokat érdemes egy objektumba tenni.


A legalapvetőbb sztringműveletek így néznek ki:

Létrehozás: char const *-ból létrehozáskor le kell másolni a tömböt. A létrejövő sztring egy 1-es referenciaszámlálóval rendelkező sztringértékre mutat.
Sztring lemásolásakor a sztringértéket nem kell lemásolni, csak megnövelni a referenciaszámlálóját.
Sztring megszűnésekor a hivatkozott sztringérték referenciaszámlálóját csökkenteni kell. Ha nulla lett, akkor a sztringérték is törölhető.
Ez a kép addig ilyen szép, amíg nem engedjük meg a sztring osztály használóinak, hogy módosítsa a sztringeket. Ha módosítani is lehet őket, akkor nagyon kell vigyázni a közös másolatokkal:

MyString a = "helló világ";
MyString b = a;
a[0] = 'H';
std::cout << a;     /* Helló világ */
std::cout << b;     /* helló világ */
Ebben a kódban az a sztringet módosítjuk, amitől a b sztringnek nem szabad megváltoznia. Konstans objektum indexelésénél nem lenne ilyen gond, mivel ott nem változhat a sztring. A nem konstans sztring viszont változhat, ezért a potenciális módosítás miatt a sztringérték objektumot le kell másolni, ha több sztring dolgozik rajta. (Ha csak egy, akkor nincs ilyen gond.) Ezt úgy hívják, hogy „copy-on-write”, és az operációs rendszerekben gyakran alkalmazott módszer.

A feladatkiírás

A fentiek alapján implementáld a MyString osztályt, és írj hozzá rövid tesztprogramot, amelyben minden függvényét legalább egyszer használod!

 * Beadandó a több modulra osztott forráskód: mystring.cpp, mystring.h és test.cpp. A feltöltött ZIP-nek ezt a három fájlt kell tartalmaznia.
 * A sztring legyen másolható és értékadható. Valósítsd meg a mozgató konstruktort és értékadást is! Ne használj STL-t, std::string-et sem! (A C-s sztringkezelő függvényeket lehet.)
 * Valósítsd meg a következő műveleteket: létrehozás üresen, létrehozás karaktertömbből, két sztring összefűzése (+ és +=), sztring és karakter összefűzése (+ és +=), kiírás és beolvasás (<< és >>), hossz lekérdezése, indexelés.
 * Az egyes függvények működése legyen kommentekkel magyarázva! Igaz, elvileg rossz kód egyik ismérve, ha túl sokat kell magyarázni, de ez most tanulós kód. Pl.
/* az új sztring helye; +1 hely kell a lezáró nullának */
char* buf = new char[len + 1];
Illetve:
/* csökkentjük a referenciaszámlálót.
/* ha nullára csökkent, az adat törölhető. */
if (-- *refcount == 0) {
    /* ... */
}
 * Írj mindent C++11-esen, amit csak lehet!

