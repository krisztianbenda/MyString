Első szorgalmi: egyformán inicializált sztringek

Adott az alábbi kódrészlet:

MyString a = "helló világ";
MyString b = "helló világ";

Az eddig kódváltozatban ez nem egy, hanem két tömböt hoz létre – tehát a memóriában kétszer van benne ugyanaz a tömb. Ez a redundancia kikerülhető, ha a létrehozáskor a sztringek mindig megnézik, hogy létezik-e már ugyanolyan tartalmú sztringérték, mint amilyen értéket fel kell venniük. Ha igen, akkor elég csak azt meghivatkozni. Ehhez azonban ismerni kell az összes sztringérték objektumot. Valamilyen módon, például egy láncolt listában (vagy jobb ötlet: keresőfában) nyilvántartást kell vezetni arról, hogy milyen sztringérték objektumok léteznek. A feladat ezt implementálni; ehhez használhatsz beépített tárolót is.

Második szorgalmi: helyettesítő objektum az indexeléshez (okosított indexelő operátor)

Tekintsük a következő kódrészletet:

MyString a = "helló világ";
MyString b = a;
std::cout << b[1];  /* e */

Ebben a másolat objektumot megindexeljük, ami hatására meghívódik az indexelő operátora. De a két indexelő közül (konstans és nem konstans) a nem konstans fog meghívódni, mivel a b objektumnak nincs const minősítője. Ez pedig sajnos különválasztja a két sztringet, pedig nem is módosul a b értéke. A probléma az, hogy az indexelés pillanatában még nem tudjuk, hogy a következő művelet egy írás vagy egy olvasás lesz, úgyhogy igazából az indexelő operátor még nem tudja eldönteni, hogy külön kell-e választani a két sztringet (copy-on-write) vagy nem. A helyzetet úgy tudod megoldani, ha egy helyettesítő (proxy) objektumot használsz. Az indexelő operátornak nem egy karakter referenciájával kell visszatérnie, hanem egy olyan objektumnak, amely a sztring megindexelt karakterét reprezentálja. Ez az objektum tehát tudja, hogy melyik sztring melyik karakteréről szól. Az írás és az olvasás a helyettesítő objektumon már külön műveletnek fog látszani. Lehet olyan értékadó operátort írni neki, amely karaktert vesz át (erre ő a kapott karaktert beleírja a hivatkozott sztringbe, esetleg közben szétválasztja a sztringeket), és kaphat olyan konverziós operátort is, amely ezt karakterré alakítja (értelemszerűen ilyenkor kiolvasva a hivatkozott sztring hivatkozott karakterét).
