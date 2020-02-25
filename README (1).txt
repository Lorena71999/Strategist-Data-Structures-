

    Pentru realizarea cerintelor mi-am creat structurile (graf_metrou, clineti, 
strazi, statie_Metrou, graf_client, rute_metrou) necesare citirii datelor
din fisierul de date in main. 
	De asemenea, mi-am creat un vector de cerinte, pentru care am citit din
fisierul de date dimensiunea lui, aceasta fiind numarul de strategii care trebuie
implementate, verificand fiecare element al vectorului in parte pentru a apela
functia corespunzatoare fiecarei strategii.

	Functiile implementate:

graf_client * create: Aceasta functie construieste graful unui client folosind o
matrice de adiacenta in care sunt trecuti timpii dintre clienti. Pentru a face 
un graf de clienti pentru fiecare statie, mi-am initializat un vector de grafuri
 de clienti fiecare pozitie fiind o statie.

graf_metrou * create: Aceasta functie construieste graful metroului folosind o 
matrice de adiacenta in care sunt trecute distantele intre statii asemenea 
functiei graf_client * create.

void legatura: Aceasta functie realizeaza strategia "legatura" din cerinte 
afisand toate statiile care sunt conectate in mod direct de statia data ca 
parametru prin x. Acest lucru l-am facut folosindu-ma de matrice de adiacenta a 
distantelor dintre grafuri verificand daca elemtele sunt diferite de 0 si diferite 
de INFINITY care a fost folosit pentru blocarea tunelurilor.

graf_metrou * adauga_ruta: Aceasta functie adauga o ruta intre doua statii de metrou
si le adauga in matricea de adiacenta a metroului distanta primita ca parametru,
cautand parametrii X si Y in statii.nume memorand pozitiile pe care acestia se afla.

graf_metrou * sterge_ruta: Aceasta functie sterge o ruta intre doua statii de metrou
si suprascrie distanta din matricea de adiacenta a metroului cu 0. X si Y sunt 
cautati asemenea functiei aduaga_ruta.

void comanda_statie: Aceasta functie afiseaza statiile in urma carora curierul 
obtine o suma mai mare sau egala cu numarul “Valoare_suma”. Pentru a realiza aceasta 
strategie mi-am creat un vector in care mi-am salavat suma totala de bani din fiecare 
statie adunand suma pe care o are fiecare client de platit, iar dupa am comparat acea 
suma cu valoare_suma primita ca parametru din fisierul de date si am salavat numele 
fiecarei statii in alt vector pentru ca dupa terminarea comparatiei sa il scriu in 
fisierul de iesire.

void drum_metrou: Aceasta functie caluceaza drumul minim dintre doua statii de metorul 
folosind algoritmul lui Dijkstra, adaptand o varianta a acestuia de pe internet 
grafului meu si folosind parametrii necesari cautand parmatrii X si Y in vectorii 
cu numele statiilor.


void drum_strada: Aceasta functie funcioneaza asemenea functiei drum_metrou doar ca 
calculeaza drumul minim dintre doi clienti aflati intr-o statie. Procedand la fel 
doar ca am am cautat inainte numele clientilor pentru a vedea in ce statie se afla aceastia.

graf_client * adauga_strada: Aceasta functie adauga o strada intre doi clienti
adaugand in matricea de adiacenta timpul primit ca parametru, cautand parametrii 
x si y in statii.cl.nume_client memorand pozitiile pe care acestia se afla.

graf_client * sterge_strada: Aceasta functie sterge o strada intre doi clienti.
Cautam pozitia celor doi clienti si inlocuim valoarea din matricea de 
adiacenta cu 0;

graf_metrou * blocaj_tunel: Cautam pozitiile celor doua statii si inlocuim
in matricea de adiacenta elementul respectiv cu INFINITY. INFINITY este 
definit la inceputul programului si are o valoare foarte mare.

graf_client * blocaj_strada: Cautam pozitia celor doi clienti si schimbam
valoarea din matricea de adiacenta la fel cum am facut si la cerinta 
anterioara.

void conexiune: Aceasta functie ne spune daca avem sau nu conexiune directa
intre doi clienti verificand daca elementul din pozitia pe care se afla 
este diferit sau nu de 0.

void timp_minim : Aceasta functie caluleaza timpul minim necesar pentru a livra toate comenzile 
dintr-o statie. Am realizat aceasta functie cautand timpul minim necesar curierului sa ajunga 
la una dintre statii, salvand pozitia acetuia, si am cautat in matricea de adiacenta a timpilor 
incepand de la linia care are aceeasi valoare cu pozitia salvata toate valorile diferite de 0, 
salvandu-le intr-un vector intermediar, vector folosit pnetru calcularea minimului acesta, minim 
care reprezinta urmatorul timp pana la urmatoarea statie, iar daca acesta nu mai are nicio conexiune cu un alt client se intoarce la statie de metrou ducandu-se la cel mai apropiat client inlocuind in matricea de adiacenta timpul dintre drumui cu 0, deoarece acel client a fost deja vizitat, pentru a pastra matricea nemodificata, am lucarat cu o copie a matricei. Iar la final 
am adaugat timpul de la ultimul client care a fost vizitat la suma totala si am afisat-o in fisierul de iesire.

Backtracking : Aceasta cerinta am implementat-o folosind un algoritm de tip backtracking pentru a calcula toate rutele posibile dintr-un colt al matricei in cel opus deplasandu-ma doar pe 2 directii. Dupa aceea am calculat suma fiecarui drum si i-am calulcat minimiul, acesta fiind drumul pe care curierul trebuie sa il parcuga pentru a depunde banii la unul din sedii. Am folosit variabile globale pentru realizarea cerintei si mi-am mai creat o structura numita Point, pe care am folosit-o la gasirea tuturor durmurilor, aceasta fiind formata din 2 variabile de timp int, i si j , pozitii in matrice. Pentru a citii din fisier datele pentru cerinta am verficat daca am ajuns la finalul fisierului cand am incercat citirea dimensiunii matricei data in fisierul de date.









