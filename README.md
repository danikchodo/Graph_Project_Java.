# Wizualizacja Grafów Planarnych

Celem projektu jest stworzenie dwóch aplikacji – pierwszej w języku C, a drugiej w języku Java – służących do wyznaczania współrzędnych węzłów w celu estetycznej wizualizacji grafu planarnego. 

## Opis Projektu (C)
Aplikacja napisana w języku C jest programem konsolowym, sterowanym wyłącznie za pomocą argumentów i opcji z linii poleceń. Jej głównym zadaniem jest przetworzenie listy krawędzi i obliczenie optymalnego położenia wierzchołków na płaszczyźnie.

### Zaimplementowane Algorytmy
W ramach projektu zaimplementowano i przetestowano dwa różne podejścia do układania grafów:
1.  **Algorytm Fruchtermana–Reingolda** (model siłowy).
2.  **Algorytm Tutte’a** (relaksacja barycentryczna).

---

## Dokumentacja Funkcjonalna

### Instrukcja obsługi (CLI)
Program uruchamiany jest z linii poleceń według składni:
`./grafy -i <plik_wejsciowy> -a <algorytm> [opcje]`

**Dostępne flagi:**
* `-i <path>` : (Wymagane) Ścieżka do pliku wejściowego z listą krawędzi.
* `-a <name>` : Wybór algorytmu: `fr` (Fruchterman) lub `tutte` (Tutte).
* `-o <path>` : Ścieżka do pliku wyjściowego (domyślnie: konsola).
* `-v` : Tryb Verbose (szczegółowe logi działania).
* `-h` : Wyświetlenie pomocy.

---

## Dokumentacja Implementacyjna

### Format wejściowy
Program przyjmuje pliki tekstowe generowane przez moduł Java, gdzie każda linia definiuje jedną krawędź w formacie:
`<nazwa_krawędzi> <id_wierzchołka_1> <id_wierzchołka_2> <waga>`

### Format wyjściowy
Wynikiem działania jest lista współrzędnych przypisana do identyfikatorów wierzchołków, sformatowana w sposób umożliwiający łatwy import do modułu wizualizacji:
`ID_WIERZCHOŁKA  WSPÓŁRZĘDNA_X  WSPÓŁRZĘDNA_Y`

### Architektura rozwiązania
Projekt został podzielony na moduły:
* `graph.c/h`: Struktury danych i zarządzanie pamięcią grafu.
* `algorithms.c/h`: Logika matematyczna algorytmów FR i Tutte.
* `cli.c/h`: Parser argumentów linii poleceń.
* `io.c/h`: Obsługa wczytywania plików tekstowych i zapisu wyników.

### Budowanie projektu
Kompilacja odbywa się automatycznie za pomocą narzędzia `make`:
```bash
make        # Kompilacja programu głównego
make test   # Uruchomienie testów jednostkowych
make clean  # Usunięcie plików obiektowych
