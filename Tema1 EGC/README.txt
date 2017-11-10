Moisa Anca-Elena 331CA
Tema 1 EGC - Geometry Wars

Utilizare aplicatie
-------------------

Nava se controleaza astfel:
W - sus
A - stanga
S - jos
D - dreapta
Click stanga mouse - se va lansa un proiectil
Cu ajutorul mouse-ului, nava se va roti dupa acesta

Survive Guide
-------------
- primul inamic va aparea dupa 2 secunde; acest interval scade pana la 0.5 secunde;
- eroul are 3 vieti; in cazul in care este atins de o nava inamic, aceasta se va distruge, iar eroul 
pierde o viata; jocul se termina in momentul in care va ramane fara vieti
- inamicii sunt de doua feluri: simpli si avansati; acestia se deosebesc prin culori - cei cu o viata 
vor fi albastri, iar cei cu doua vieti mov; cand inamicul cu doua vieti pierd o viata, el se scaleaza
la jumatate si viteza i se dubleaza

Detalii de implementare
------------------------

Am lucrat in doua fisiere: Laborator3_Vis2D si Object2D.
*Object2D*
	- cuprinde 3 metode; acestea sunt CreateSpaceShip
									  CreateScore
									  CreatePewPew
	- ele sunt declarate in header-ul aferent, Object2D.h
	- metoda CreateSpaceShip - aici imi modelez nava spatiala din indici si noduri
							 - metoda primeste ca parametri un nume prin care obiectul va fi 
							   identificat, pozitia la care va fi plasat initial, si o culoare 
							   prin care se va deosebi de restul elementelor
							 - am creat nava in jurul originii (0, 0)
	- metoda CreatePewPew - asemenea metodei CreateSpaceShip, obiectul il 
							localizez initial in jurul originii
	- metoda CreateScore - obiectul este desenat cu coltul din stanga jos, in
						   origine

*Clasa Laborator3_Vis2D*
	- header-ul va cuprinde metodele clasei, variabile si structuri
	- am creat 3 structuri: mySpaceShip, morePews, enemy
	- structura mySpaceShip - am salvat in ea pozitiile initiale ale navei
  						  	  spatiale (in centrul ecranului - ecranul va avea x logic space 18 si y
  						  	  logic space 18, deci nava se la afla in punctul de coordonate (9, 9))
  							- contine dimensiunea navei spatiale si viteza de deplasare pe ecran
	- structura morePews - am creat un vector de tipul acestei structuri(morePewPew)
  					   	   care va retine proiectilele
					 	 - fiecare proiectil este descris printr-o pozitie de start (x, y), viteza 
  					       cu care va fi lansat, dimensiune, si unghiul cu care va porni (unghiul
  					       este conditionat de pozitia mouse-ului)
	- structura enemy - de asemenea am creat un vector de tipul structurii (moreEnemy)
						care va retine multimea inamicilor generati
				  	  - fiecare inamic este si el identificat printr-o viteza 
				    	de deplasare (generata random, dar mai mica decat cea a
				    	navei spatiale), un unghi de rotire catre nava spatiala(initial este 0), o
				    	pozitie de start x si una y
				  	  - cele doua pozitii sunt generate random astfel incat 
				   		inamicii sa vina pe un cerc de raza ray, la un unghi 
				    	random (directionAngle) intre 0 si 360 de grade
				  	  - inamicii sunt identificati si printr-o culoare, si viata; astfel:
				  		inamicii de culoare ALBASTRA vor avea o viata, iar cei 
				  		de culoare MOV doua vieti
	- metodele clasei Laborator3_Vis2D:
		- Init() - aici obiectele vor primi o pozitie de start, un nume (prin care vor fi 
				   identificate la render), o culoare (fiecare va avea propria culoare) 
				   				-> nava spatiala va fi galbena (spaceShip)
		   						-> inamicii vor fi albastri sau mov (enemyShip, smartEnemyShip)
		   						-> inamicii scalati vor avea culoarea portocalie (littleEnemyShip)
		   						-> vietile sunt roz (score)
		   						-> proiectilele sunt verzi (pewpew)
		   		 - am stabilit dimensiunile spatiului logic in care voi lucra (18 lungime, 18 latime)
		- TheEnd() - am pus conditiile pentru sfarsitul jocului:
					 daca nava spatiala nu mai are nicio viata, atunci ecranul isi va 
				     schimba colarea din negru catre rosu printr-o animatie de fading
				   - pentru ca animatia sa nu acopere inamicii ramasi pe ecran si nava
					 spatiala, am randat din nou eroul si inamicii, in acceasi pozitie
				   - nava si inamicii nu se vor mai putea misca (viteza e setata pe 0), 
				 	 si nici nu se va mai roti eroul
		- GenerateEnemy() - am adagat inamicii intr-un vector moreEnemy, 
		  			   	    si fiecare a primit o culoare random (albastru sau mov); 
					        de asemenea, in functie de culoare, au primit si vietile
					      - tot aici, am generat inamicii o data la doua secunde initial, 
					        dupa care timpul a scazut
		- RenderEnemy() - metoda va randa inamicii in functie de culoare
						- inamicii vor fi scalati, rotiti si translatati cu unghiul si 
					      pozitiile corespunzatoare
		 	    		- de asemenea, daca inamicul cu doua vieti va pierde o viata, 
		   			  	  el va fi scalat la jumatate
		- RenderPew() - am randat proiectilele; acestea sunt translatate in centrul 
				        navei spatiale si rotite cu unghiul dat de miscarea mouse-ului
		- RenderHero() - metoda randeaza nava spatiala rotita si translatata cu unghiul si pozitiile aferente
		- Update() - aici se apeleaza metoda DrawScene care face desenarea efectiva a
					 obiectului
				   - tot aici apelez sfarsitul jocului
		- DrawScene() - realizeaza desenarea obiectelor
					  - am apelat functia de generare inamici   
				      - am desenat cele 3 vieti (fiecare se va desena in
				        functie de conditia pusa) - initial 3 variabile first, 
				        second, third sunt puse pe true, deci cele 3 vieti se vor 
				        desena; in cazul in care are loc o coliziune, a treia viata 
				        nu se mai deseneaza la urmatoarea iteratie, la fel si cu 
				        a doua si prima viata (vietile nu le-am bagat intr-un vector 
				        ca sa le pot sterge, ci pur si simplu nu le-am mai randat)
				      - am randat proiectilele
				      - am parcurs vectorul de inamici, si le-am calculat atat unghiul de 
				        rotatie catre nava cat si pozitiile lor prin care se translateaza 
				        catre nava (in principiu am aplicat teorema lui Pitagora)
				      - pentru coliziune, daca diferenta absoluta pe x si y dintre 
				        pozitia navei si cea a inamicului este mai mica decat suma razelor,
				        atunci avem coliziune; in acest caz, dispare o viata, si sterg 
				        din vectorul de inamici un inamic de la pozitia i, folosind un 
				        iterator
				      - daca nu e coliziune, inamicii se randeaza in continuare
				      - pentru coliziunea proiectil inamic am procedat in acelasi mod; in 
				        cazul coliziunii, sterg proiectilul din vector si in functie de 
				        vietile inamicilor procedez in urmatorul fel: cei cu o viata vor 
				        fi stersi; daca inamicul vizat are doua vieti, atunci i se scade o viata, i se 
				        dubleaza viteza, si il scalez; cand ramane si el fara vieti, il sterg
				        de tot din vector;
				      - daca un proiectil iese din window, il sterg
		- OnInputUpdate() - aici am realizat miscarea cu tastele
					      - daca apas tasta W, va creste pozitia pe y, si tot asa pentru fiecare tasta
		- OnMouseMove() - aici are loc miscarea navei dupa pozitia mouse-ului
						- am transformat coordonatele mouse-ului in coordonate logice 
						  si am calculat unghiul de rotatie ca fiind arctg de aceste 
						  coordonate (am scazut un pi/2 pentru a pozitiona nava corect)
		- OnMouseBtnPress() - la fiecare click stanga, creez un obiect de tipul structurii
							- ii stabilesc pozitia de start si unghiul spre care va porni
							- unghiul este acelasi ca cel caculat pentru rotatia navei
							- daca la rotatie am scazut un pi/2, aici il voi adauga 
							  pentru a nu afecta directia
							- dupa ce proiectilul are propriile specificatii, il adaug in
							  vectorul de proiectile

Probleme aparute
----------------
- nu am reusit sa scalez inamicul cu animatie
- aveam probleme cu lansarea proiectilului; acesta pornea din mijloc doar intre 45 si 135 de grade;
  problema am rezolvat-o modificand in Object2D felul in care am modelat obiectele, mai cu seama nava spatiala si 
  proiectilul; inainte, acestea erau formate in origine; le-am mutat in jurul originii si le-am dat si alti 
  indici (inca nu sunt convinsa ca aceasta era unica rezolvare, posibil sa fi gresit unghiul pe care l-am  calculat, 
  sa fi trebuit sa mai adaug vreun pi, sau sa scad / sau translatarile sa le fi facut altfel)
- mici ajustari in cazul in care nu se translatau inamicii dupa mine corect: am adaugat un PI/2
- nava se invartea dupa mouse doar in mijlocul ecranului; astfel am inversat coordonatele axei 
  (inaltimea logica a ecranului - coordonata logica a mouseului pe y)
- in structura enemy, initial pozitiile x si y erau raza * cosinus, respectiv sinus; astfel, inamicii nu se generau 
  in jurul meu (nu eram eu centrul lor de interes), ci apareau doar din partea stanga a ecranului; problema 
  am rezolvat-o adaugand la x si la y pozitia mea initiala (care este (9, 9)), si in felul asta am devenit eu originea, 
  si au inceput sa se genereze corect.

  Continut arhiva
  ---------------
  Sursele temei se afla in folderul Framework-EGC-master->Source->Laboratoare->Laborator3
  Am lucrat in fisierele Laborator3_Vis2D.cpp
  						 Laborator3_Vis2D.h
  						 Object2D.cpp
  						 Object2D.h
  						 Transform2D.h