# NHF Monte Carlo módszerek

# Felépítés
Két fő rész: 
- main.cpp
- plotter.py
## main.cpp
- változók inicializálása
- simulateTransport futtatása
- build: g++ -std=c++20 main.cpp simulateTransport.cpp crossSections.cpp interpolate.cpp point3d.cpp energies.cpp -o gamma_simulation -lgsl -lgslcblas -lpthread
## simulateTransport.cpp
- minden részecske szimulációja végén a detektorba leadott energiát a plotternek való átadáshoz output.txt fileba kiírja a program
- ezt követően beolvassa a XCOM oldalról letöltött csv filet a csv.h külső library segítségével és elkészíti a kellő adathalmazt a hatáskeresztmetszetekhez
- ezután szimulálja a részecskék életútját
- Energies energies típus tárolja a különböző fontos energiákat lehetőséget ad a hatásfokok kiszámítására ezen értékeket a kód során frissítem
- a simulate transporton kívül a másik fontos file a point3d ami tárolja a foton tulajdonságait és azok kiszámítására is lehetőséget ad
- a simulate transport először megnézi hogy az adott pontból a generált irányba húzott egyenes metszi e a detektor hengert ha igen akkor a helyét a metszéspontra módosítja(figyelembe véve a henger magasságát és ha az nem egyezik rávetíti a fedőlapokra) egyébként ez a ciklus végez is. ezt követően a hatáskeresztmetszetekkel súlyozottan generálja hogy foto-effektus vagy compton szórás vagy pár kelltés lesz. Foto-effektusnál az összes energia baszorbálódik, compton szórásnál a Khan methódust használva generálok egy random irányt és egy energia változást a párkeltésnél pedig ketté osztódik a szimuláció és a keletkező két foton random ellentétes irányba történő terjedését vizsgálja, ezek egyenként fotoeffektust vagy compton szórásokat még elszenvedhetnek.
- kiírja fileba a hengerben leadott energiát, kiírja az etákat.
- FWHM jellemzővel rendelkező eloszlással vannak az energia értékek megszórva
- kiírt eta-kat fogok menteni a feladatokhoz
## plotter.py
- plotter matplotlibbel ábrázol, lehetővé téve az axis feliratok range-k megadását és egy gombot elhelyezve a log axis váltására
- E * 1.2 a maximuma mindig az x tengelynek
- 5 s-enként frissül a plot valós időben
- matplotlibnek hála menthetőek a plotok
## interpolator a hatáskeresztmetszeteket interpolálja az aktuális energiákhoz
- két lehetséges metódus alapján
- lineáris, spline
# run_simulation.sh
- ez a bash script elindítja a szimulációt majd rá 1 másodpercel az ábrázolást ezzel lehet futtatni a kódot ha kész a cpp applikáció
