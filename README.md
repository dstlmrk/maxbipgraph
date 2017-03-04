# Maximum Bipartite Graph

## Vstupní data:

* n = přirozené číslo představující počet uzlů grafu G, n >= 5
* k = přirozené číslo řádu jednotek představující průměrný stupeň uzlu grafu G, n>=k>=3
* G(V,E) = jednoduchý neorientovaný neohodnocený souvislý graf
  o n uzlech a průměrném stupni k

## Doporučení pro algoritmus generování G:

Použijte generator grafu s typem grafu `-t AD`, který vygeneruje
neorientovaný neohodnocený souvislý graf o n uzlech a průměrném stupni k.

## Definice:

Graf G(V,E) je bipartitní jestliže můžeme rozdělit množinu uzlů na disjunktní
pomnožiny U a W tak, že každá hrana v G spojuje uzel z U s uzlem z W.
Jinak řečeno, bipartitní graf je možné uzlově obarvit 2 barvami.

## Úkol:

Graf G(V,E) je definován množinou uzlů V a množinou hran E. Úkolem je
nalézt maximální podmnožinu hran F takovou, že graf G(V,F) je bipartitní.
Řešení existuje vždy, nemusí být jednoznačné.
 
## Výstup algoritmu:

Výpis obou podmnožin uzlů bipartitního podgrafu a výpis množiny jeho hran F.

## Sekvenční algoritmus:

Sekvenční algoritmus je typu BB-DFS s omezenou hloubkou stavového stromu.

Přípustný mezistav je podmnožina hran F, která tvoří bipartitní podgraf G(V,F).
Cena, kterou maximalizujeme, je počet hran v F. Pokud je graf G bipartitní, pak
triviálně F=E, jinak F je podmnožinou E. Proto vstupní graf nejprve otestujte,
zda je bipartitní (lineární algoritmus) a algoritmus prohledávání BB-DFS
použijte pouze, pokud není. K problému lze přistoupit 2 způsoby. Bud lze
do prázdného grafu přidávat hrany tak, aby vznikající podgraf zůstával
bipartitní (budování množiny F inkrementálně z prázdné množiny) nebo lze
z množiny E postupně odebírat hrany, dokud nevznikne bipartitní graf
(budování množiny F dekrementálně z množiny E). Pro tuto úlohu je
výhodnějsi druhý způsob, protože prohledávání se může navracet v mezistavech
s |F|=n-1 (strom je triviálně bipartitní, proto musi existovat řešení
s |F|=n-1). Jedná se tedy o úplné prohledávání stavového prostoru
do hloubky |E|-n.

Triviální dolní mez je |F|=n-1.

Těsná horní mez na |F| není známa. Triviální horní mez je |F|=m.
