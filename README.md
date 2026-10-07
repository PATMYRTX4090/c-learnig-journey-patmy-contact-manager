
PIERWSZE ZADANIE
START:		06.10.2026
KONIEC:		31.10.2026 ?


Etap I (Tygodnie 1-9)			
Projekt 1 - Mened¿er kontaktów 
								
Przechowywanie:				
								
imiê,							
nazwisko,						
telefon,						
email.						  
								
Funkcjonalnoœci:				
								
dodawanie,					  
usuwanie,						
wyszukiwanie,					
zapis do pliku,				
odczyt z pliku.				
								
Czego nauczysz siê przy okazji:
								
struktury,					   
tablice struktur,				
operacje na plikach,			
organizacja programu.			
										



Nie zaczynaj jeszcze pisaæ kodu. Najpierw zaprojektuj.

Projekt 1: Mened¿er kontaktów

Przygotuj odpowiedŸ na nastêpuj¹ce pytania:

1. Jak bêdzie wygl¹da³a struktura Contact?
2. Jakie funkcje bêd¹ potrzebne?
3. Jak bêd¹ przechowywane kontakty w pamiêci?
4. Jaki format pliku wybierzesz: tekstowy czy binarny?
5. Jak podzielisz projekt na pliki .c i .h?

Opisz mi sam projekt i architekturê. Nie pokazuj jeszcze kodu.

ODP_1:
	Deklaracja struktury Conctact, bêdzie sk³ada³a siê z 4 tablic znaków odpowiednio dla imienia, nazwiska, numeru telefonów, oraz adresu email.
	Wszystkim zmiennym rozmiar alokowanej pamiêci bêdzie przydzielany przez funckjê malloc(), Szkoda np. dla imienia które bêdzie mia³o 5 znaków + znak zerowy na sztywno
	deklarowaæ wielkoœæ tablicy na 20 znaków, podobny tok myœlenia dla pozosta³ych zmiennych. Numer telefonu jako tablica char - nie bêd¹ wykonywane ¿adne operacje arytmetyczne. 
	A iloœæ cyfr w numerze mo¿e byæ ró¿na. Dobrze by by³o dodaæ do struktury numer porz¹dkowy - coœ na miarê klucza podstawowego. 
	Wykorzystam tablicê która bêdzie tymczasowym buforem a znacznej wielkoœæ - uproszczeniem bêdzie je¿eli interfejs bêdzie pyta³ o ka¿d¹ zmienn¹ z osobna. 
	
ODP_2:
	Przede wszystkim standardowe funkcje z opracowanych ju¿ bibliotek <stdio.h>, z pewnoœci¹ konieczne bêdzie stworzenie funckji obs³uguj¹cej wprowadzanie ³añcuchów tekstowych (wpisywanie do bufora, 
	dodawanie znaku zerowego, oraz obs³uga - zjadanie ENTERA). Konieczne bêdzie utworzenie menu, z mo¿liwoœcia wyboru instersuj¹cych Nas opcji tj. funckji aplikacji, do których bêd¹ nale¿a³y:
	dodawanie, usuwanie, wyszukiwanie, je¿eli wyszukiwania to oczywiœcie EDYCJA (numer telefonu oraz email zawsze mo¿na zmieniæ, chocia¿ i by z faktu zmiany firmy). 
	Kluczowe bêd¹ funkcjê umo¿liwiajace odczyt i zapis danych z plików - inaczej Contact Manager nie bêdzie mia³ sensu.
ODP_3:
	W strukturze, musmi wykorzystaæ listê ³¹czon¹ - gdy¿ alokowanie na sztywno w pamiêci bêdzie prostym rozwi¹zaniem ale jednoczeœnie nie efektywnym.
ODP_4:
	Na pocz¹tku skorzytam z pliku tekstowego, w czasie tworzenia testowania, bêdzie du¿o ³atwiej wy³apaæ ewentulane b³êdy. Dodatkowo w ostatecznym tescie, bêdzie mo¿na wygenerowaæ
	przyk³adowy plik txt zgodnie z obs³ugiwanym odczytem danym z pliku i sprawdziæ funkcjonalnoœæ np. dla 1000 kontaktów. 
ODP_5
	Ka¿da z funkcji w osobnym pliku .c, deklaracje funkcji w pliku nag³ówkowym .h 
	Zmienne globalne w³asny plik .c oraz plik nag³ówkowy .h ze s³owem kluczowym extern. Porz¹dek porz¹dek i jeszcze raz porz¹dek, mo¿e przesadzam ale chodzi o wygodê analizy i tworzenia czytelnego kodu. 

Potem przejdziemy przez review projektu dok³adnie tak, jak zrobi³by to senior podczas przegl¹du projektu w pracy.

07.10.2026 17:51
Pytanie mentorskie:

Jeœli baza ma 1000 kontaktów, ile pamiêci "stracisz" stosuj¹c sta³e tablice?
Z moim obliczeñ wynika, ¿e przy za³o¿eniu 1000 kontaktów ca³y plik powinien wa¿yæ oko³o 144 kb ~ 0,1 Mb.


Czy nowy kontakt dostanie ID = 15 czy ID = 21?
Nie odpowiadaj od razu.
Przemyœl konsekwencje obu rozwi¹zañ. 
Do struktury dodam zmienna bool, true - oznaczaæ bêdzie ¿e numer ID jest wype³niony, natomias false - ¿e, miejsce jest wolne i mo¿na je wype³niæ. Wi¹¿e, siê to z tym, ¿e w
funckji dodaj¹cej kontakt, konieczne bêdzie zaimplementowanie dodatkowej pêtli sprawdzaj¹cej dostêpnoœæ. 

Jaki bêdzie najczêstszy scenariusz?
z pewnoœci¹ dodawanie, ale w tym przypadku pewnie dodawanie, bêdzie u¿yte kilka razy, w celu sprawdzenie funkcjonalnoœci, clue dzia³ania, bêdzie opiera³o siê na
odczytaniu pliku i zapisaniun w zaalokowanej pamiêci. Nie wybra¿am siê wpisywanie 1000 kontaktów dla testów. 

Co jest szybsze do iterowania?
tablica dynamiczna - szybko i przgotowanie kodu bêdzie du¿o prostrze. 

Czy ten program w ogóle potrzebuje zmiennych globalnych?
To by³a moja pierwsza myœl, globale i sprawa zmiennych rozwi¹zana. OK, tak skonstruje program, aby globalnych zmiennych nie by³o. 

Najwa¿niejsze pytanie na nastêpne spotkanie

Chcia³bym, ¿ebyœ przemyœla³ jeden temat:

Dynamiczna tablica czy lista jednokierunkowa?

Przygotuj argumenty:

Dynamiczna tablica

Plusy:

+ ³atwoœæ, tworzenia, obs³ugi, pêtli 

Minusy:

- z pewnoœci¹ fakt, ¿e pêtla na sta³e przydziela pamiêæ, jednak je¿eli Moje obliczenia s¹ prawid³owe to tylko 144 kb.

Lista jednokierunkowa

Napiszê dlaczego chcia³em spróbowaæ listy - poniewa¿ w czasie przerabiania Jêzyk C Szko³a Programowania, wielokrotnie zetkn¹³em siê z tablicami. 
Lista mia³a podnieœæ poprzeczkê, ale myœle, ¿e w tym projekcie i tak bêdzie kilka problemów, z które bêd¹ wymaga³y rozwi¹zania. 
A lista mog³a by to tylko niepotrzebnie skomplikowaæ.


Plusy:

? wyzwanie i podniesienie poprzeczki, 

Minusy:

? komplikacje, które mog³y by opóŸniæ realizacjê projektu. 

Decyzja: dynamiczna tablica. 

Podzia³ modu³ów (wstêpny)

main.c		-> trzon programu, z szablonem dostêpnych mo¿liwoœci oraz mo¿liwoœci¹ zamkniêcia aplikacji. 
contacts.c	-> definicje funckji odpowiedzialnych za obs³ugê kontaktów: dodawanie, usuwanie, edycja, wyszukiwanie, wyœwietlenie dostepnych kontaktów, funkcja obs³uguj¹ca ³añcuchy znakowe,
files.c		-> definicje funkcji odpowiedzialnych za: zapis do pliku oraz odczyt z pliku,
cf.h		-> deklaracje funckcji, tu chcia³bym umiesciæ równie¿ deklaracje struktury.
oczywiœcie dostêpne biblioteki np. stdio.h, string.h, stdlib.h

Przep³yw programu:
Pierwsze uruchomienie.
1. Uruchomienie programu (nie mamy ¿adnego pliku z kontaktami, tablica dynamiczna pamiêæ przydzielona dla tablicy z jedn¹ struktur¹), 
2. Wybranie funkcji dodawania kontaktów - dodanie kontaktu bezpoœrednio do struktury, 
	- wprowadzenie imienia
	- wprowadzenie nazwiska,
	- wprawdzenie numeru telefonu,
	- wprawdzenie adresu email, 
	- zmiana zmienna bool -  na true - pozycja wype³niona,
	- realokacja pamiêci dla i+1 - robimy miejsce dla kolejnego kontaktu,
3. Korzytanie z funkcji obs³uguj¹cych kontakty,
4. Zapis do pliku, zapytamy o nazwê i rozrzerzenie pliku, atrybuty zapisu - wymazania bie¿acej zawartoœci i wprowadzenie nowej.
W pierwszym wierszu zapisanego pliku musi znajdowaæ siê wartoœæ ca³kowita - bêdzie potrzebna podczas uruchamiana funckji odczytuj¹cych pozwoli na 
przydzielenie odpowieodniej iloœæi pamiêci dla tablicy struktur. 
5. Odczyt z pliku: odczytanie sta³ej ca³kowitej realokacja pamiêci, odczytywanie i zapis w pamiêci. 


Profesjonalne kontenery zwykle przechowuj¹: to jest bardzo dobra podpowiedŸ. Przy 1000 kontaktów wykonanm 1000 realokacji, przy capacity = 10, ju¿ realokacji bêdzie tylko 100.

Czy usuniêty kontakt powinien nadal zajmowaæ miejsce w tablicy?
Uwa¿am ¿e Wariant A i Wariant B bêd¹ istnia³y razem -   pozostawienie zmiennej active i tak pozwoli na samo naprawianie siê tablicy, gdy¿: zapis do pliku tylko tych rekodrów w których bêdzie active == true,
a po odczytanie takiego pliku wszystkie rekordy bêd¹ zawiera³y tylko te po¿¹dane kontakty. Contact Manager poprzez zapis i odczyt pliku - bêdzie siê samodzielnie "czyœci³".
Czy na pocz¹tku programu istnieje jakikolwiek kontakt?
no nie - wiêc alokacja dopiero po wybraniu opcji dodania lub odczytu danych. 
Dla rêcznego wprowadzania - alokacja dla 5 - 10 kontaktów z wykorzystaniem idei konteneru - gdy size == capacity wówczas realokacja. 
Dla pliku - liczba ca³kowita z pierwszego wersu okreœli ile potrzebujemy aby zmieœciæ zawartoœæ pliku + 5-10 aby umo¿liwiæ rêczne dodanie. 
Równie dobrze mo¿emy zapytaæ wprowadzaj¹cego kontakty ile miejsca potrzebuje. 

informacjê o stanie bazy?

Jak myœlisz, czy warto stworzyæ dodatkow¹ strukturê, np. coœ reprezentuj¹cego ca³¹ ksi¹¿kê kontaktów, a nie tylko pojedynczy kontakt?
Interesuje mnie wy³¹cznie odpowiedŸ architektoniczna: jakie informacje program powinien przechowywaæ oprócz samego kontaktu?
Dodanie struktury z w³asnoœciami ksi¹zki adresowej da mo¿liwoœæ panowania nad zasobem. Oprócz wczeœniej wymienionych w³asnoœci jak: pojemnoœæ oraz stopieñ wype³nienia, pozwoli równie¿
dodaæ informacjê o nazwie pliku z jakiego zosta³a odczytane rekordy, czy te¿ zapisaliœmy bie¿¹c¹ ksi¹zkê adresow¹ - zabezpieczy to przed utrat¹ danych.
Bêdzie mozliwe równie¿ okreœlenie ile rekordu podczas zapisu zostanie usuniête. 

Co zrobisz, jeœli u¿ytkownik rêcznie zmodyfikuje plik?
je¿eli nie bêdzie sztucznie przesuwa³ EOF - wówczas myœle, ¿e zaimplementuje odpwiednia pu³apkê. 

1. Po czym program rozpozna kontakt do usuniêcia?

Po:

ID?
nazwisku?
emailu?
numerze telefonu?

Dlaczego?

¯adna z tych informacje, w strukturze musi byæ dodana zmienna np. bool active, je¿eli bêdzie mia³a wartoœæ false oznaczaæ to bêdzie, ¿e kontakt jest do usuniêcia.

1. Czy dwa kontakty mog¹ mieæ:

Plain Text
to samo imiê
to samo nazwisko

Jak dzia³a wyszukiwanie?
Tak dwa kontakty mog¹ mieæ takie same imiona i nazwiska. Gdy naprzyk³ad wyszukuje kontakt w telefonie, najpierwsz wpisuje imiê, nastêpnie nazwisko.
W tym wypadku zapytam u¿ytkownika wed³ug czego bêdziemy wyszukiwaæ, imiê, nazwisko, numer telefonu, adres email.
Numery rekordów, które bêd¹ zwiera³y trafienia, zapiszê w tablicy liczb ca³kowitych, któr¹ po¿niej wykorzystam do wyœwietlenia wyników. 
U¿ytkownik zdecuduje czy który rekord mu odpowiada. 

Czy program ma obs³ugiwaæ jedn¹ ksi¹¿kê adresow¹ naraz?

Czy wiele?

Jedna ksi¹¿ka adresowa obs³ugiwana naraz, natomiast mogê dodaæ do struktury kontaktu równie¿ np. nazwê firmy lub szko³e.

Gdybym by³ Twoim koleg¹ z zespo³u...

zada³bym Ci jeszcze jedno pytanie przed startem implementacji.
Funkcje te powinny operowaæ na Contact