Programm aufruf:
```
MIECCompiler.exe -in input.miec -out output.iex
```
```
..\Debug\MIECCompiler.exe -in input1.miec -out output.iex
```

# TODO:
[ ] rename SynErr to fir Tests [Parser.cpp:246](./MiniIEC/Parser.cpp)

# Fehler-Checkliste
Die folgende Fehlerliste dient als Hilfestellung für die Übungsausarbeitung.
Prüfen Sie Ihren Source-Code auf die hier angeführten Fehler um unnötige
Punkteabzüge zu vermeiden.
1. const, const-Referenz und const_iterator verwenden wo möglich
und nötig (-0.5 bis max. -2 Pkte.)
2. call by value versus call by reference: Kopieren Sie Parameter nur
wenn nötig. (-1 bis max. -3 Pkte.)
3. magic numbers: Für alle verwendeten Zahlen und Nummern im Source-
Code entsprechende Konstanten verwenden. (-0.5 bis max. -2 Pkte.)
Bitte nicht übertreiben: 1 -> cONE; z.B.: Bit-Shiftoperationen: x << 1
ist ok!
Im Testtreiber sind magic numbers erlaubt!
4. std::cerr für Fehlerausgabe verwenden. (-1 Pkt)
5. Exception-Handling: Behandeln Sie Fehler im Programm mit ent-
sprechenden Exceptions. (-1 bis max. -2 Pkte.)
• std::bac_alloc abfangen, wenn dynmischer Speicher angefordert
wird.
6. Implementierung von CopyCTor, Assign-Op wenn nötig. (jeweils -1
bis max. -3 je nach Aufwand bzw. möglicher verursachter Speicherlei-
chen)
7. memory leaks allgemein. (-2 Pkte.) => vld verwenden!!!
8. namespace im Header geöffnet? (-1 Pkt)
9. multiple inclusion protection vergessen (-1 Pkt)
10. eingebaute STL-Datentypen verwenden, wenn möglich! (-0,5 Pkte)
11. C++ Cast anstatt C-Cast verwenden: static_cast<T>() (-0.5 Pkte)
12. Keine STL-Container dynamisch anlegen. (-2 Pkte)
13. Keine globalen Variablen in Modulen verwenden. -> Entweder Klas-
senmember oder modulinterne Variablen anlegen (-1 Pkt)
1
HSD/SDP3 (c) F. Wiesinger
14. Dateiströme schlieÿen: Dateien sollten so bald wie möglich wieder
geschlossen werden. (-0.5 Pkte)
15. Dateiströme auf Gültigkeit prüfen (-1 Pkt)
16. Compiler Warnings beachten!
17. Methoden im cpp implementieren: Ausnahme Templates! (-1 Pkt)
18. Pointer prüfen: Pointer sollten vor Verwendung auf nullptr geprüft
werden. In modulinternen bzw. privaten Methoden reicht eine Prüfung
via Assertion.
19. Klassendiagramme:
• gemeinesame Basisklasse 'Object' verwenden (-1 Pkt)
• Kardinalitäten einzeichnen (0.5 bis max. -1 Pkt)
• Beziehungen (Vererbung, Schnittstellenvererbung, Aggregation, Use)
richtig einzeichnen. (-0.5 bis max. -1 Pkt)
• Reine Interfaces werden nicht von 'Object' abgeleitet! (-0.5 bis
max. -1 Pkt)
• Fehlender Destruktor in Interfaces (-1 Punkt)




Unknown identifier
