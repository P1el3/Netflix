===Piele Mihai Teodor====
=========311 CB==========
=========READ ME=========

Lista.c
-> acest fisier este responsabil de creerea listelor si functiilor aferente folosite
-> functia initLista initializeaza o lista noua
-> functia alocareCelula are rolul de a creea o noua celula
-> functia de inserare are rolul de a insera un element la sfarsitul listei
-> functia inserareOrdonata insereaza elementele dupa conditia returnata de fct cmp
-> functia inserarePrimul are rolul de a insera la inceputul listei
-> functia inserarePePozitie insereaza element la o pozitie data
-> functia cautare are rolul de a cauta un element in lista
-> functia extragere are rolul de a cauta, returna si elemina un element din lista
-> functia extragerePrimul are rolul de a returna si elimina primul element din lista
-> functia stergePrimul are rolul de a sterge primul element din lista
-> functia stere, cauta si sterge un element din lista
-> functia distruge are rolul de a elibera mem alocata
-> functia afisare are rolul a printa lista

Stiva.c
-> acest fisier este responsabil de crearea stivelor si functiilor aferente folosite
-> functia initStiva face stiva
-> functia distrugeStiva are rolul de a elibera mem alocata
-> functia push insereaza un element la inceputul stivei
-> functia pop extrage primul element din stiva
-> functia are rolul de a creea o stiva auxiliara folosita in cautarea unui element dat

Coada.c
-> acest fisier este responsabil de crearea cozilor si functiilor aferente folosite
-> functia initCoada face coada
-> functia distrugeCoada are rolul de a elibera mem alocata
-> functia  nq are rolul de a adauga un element la sfarsitul cozii
-> functia  dq are rolul de a extrage primul element din coada
-> functia are rolul de a creea o coada auxiliara folosita in cautarea unui element dat

main.c

-> liniile  8-16 realizeaza structura alocata serialului
-> liniile 18-22 realizeaza strucutra alocata sezonului
-> liniile 24-27 realizeaza structura alocata episodului
-> liniile 36-49 contin functii responsabile de stergerea:
	~sezonului
	~serialului
	~episodului
-> liniile 51-55 contin functia de afisare a serialului
-> liniile 57-68 compara serialele dupa 2 criterii
	1) daca cele 2 au acelasi rating funcita le ordoneaza alfabetic
	2) sunt ordonate dupa rating descrescator
-> liniile 70-75 compara 2 seriale dupa nume
-> liniile  76-100 adauga in lista cele top10 seriale
(in caz ca lista este plina, ultimul element nu este afisat iar cel nou este inserat la pozitia lui)
-> liniile 102-333 contin functia main unde se petrec urmatoarele:
	~alocarea listelor,stivelor si a cozilor
	~declararea unui vector de caractere utilizat in citirea fisierelor
	~functia de la linia 117 are rolul de a incepe citirea prin fisier
	~in functie de parametrii primiti programul intra pe diferite ramuri

========= Happy Easter <3 =========




















