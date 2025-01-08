# Labyrinth-Spiel (C++)

Willkommen zu deinem erweiterten Labyrinth-Spiel! Dieses Projekt umfasst verschiedene Geistertypen (Animatronic, Bowie und Connelly), einen Informationsmodus sowie Türen, Schlüssel und ein Ziel-Feld.

## Inhaltsverzeichnis
1. [Überblick](#überblick)  
2. [Struktur des Projekts](#struktur-des-projekts)  
3. [Voraussetzungen](#voraussetzungen)  
4. [Installation](#installation)  
5. [Ausführen](#ausführen)  
6. [Benutzung](#benutzung)  
7. [Spielanleitung](#spielanleitung)  
8. [Weiterführende Ideen](#weiterführende-ideen)  
9. [Lizenz](#lizenz)

---

## Überblick
Dieses Labyrinth-Spiel ist in C++ geschrieben. Es verwendet eine klar strukturierte Aufteilung in Header- und Quelltext-Dateien, um Lesbarkeit und Wartbarkeit zu erhöhen. Enthalten ist ein rudimentäres Beispiel-Maze, verschiedene Geister (mit unterschiedlichen Bewegungsmustern) und ein interaktiver Spielmodus über die Konsole.

## Struktur des Projekts
Das Projekt ist in mehrere Dateien unterteilt:

- **main.cpp**  
    Die Hauptdatei, in der das Spiel gestartet wird und die Schleife für die Befehlseingabe enthalten ist.

- **game_state.h**  
    Enthält die zentrale Datenstruktur GameState, welche das Labyrinth (Maze), die Spielerfigur, den Info-Modus und die Liste der Geister verwaltet.

- **maze.h**, **player.h**  
    Klassen für das Labyrinth (Maze) und die Spielerfigur (Player).

- **ghost_base.h**, **ghosts.cpp**  
    Die Oberklasse GhostBase (Abstraktion für alle Geister) sowie die Implementierung der konkreten Geister-Typen (Animatronic, Bowie, Connelly).

- **ghost_factory.h**  
    Enthält die createGhost-Funktion, die basierend auf einem Zeichen den entsprechenden Geist erzeugt.

- **steps_to_goal.h**, **steps_to_goal.cpp**  
    Eine einfache rekursive Funktion, um die Schrittanzahl (max. 5) bis zum Ziel-Feld zu berechnen (wenn der Informationsmodus eingeschaltet ist).

## Voraussetzungen
- Ein C++-Compiler (z. B. g++ über MinGW auf Windows, clang++ oder gcc auf Linux/Mac).  
- Optional: Eine Entwicklungsumgebung wie Visual Studio Code, CLion, Dev-C++ oder Visual Studio.  
- C++11 oder höher wird empfohlen.

## Installation
1. **Quellcode herunterladen**  
     Lade alle .cpp- und .h-Dateien in ein gemeinsames Verzeichnis herunter oder klone das zugehörige Repository.

2. **Compiler bereitstellen**  
     - Windows:  
         - Installiere MinGW (und sorge dafür, dass g++ in deinem PATH verfügbar ist) oder nutze Visual Studio (MSVC) bzw. das Windows-Subsystem für Linux (WSL).  
     - Linux / macOS:  
         - Ggf. benötigst du das Paket build-essential (Debian/Ubuntu), Xcode Command Line Tools (macOS) oder ein entsprechendes Compiler-Paket.

3. **Kompilieren**  
     Wechsle in das Verzeichnis mit den Projektdateien und führe z. B. folgenden Befehl aus:
     ```bash
     g++ -std=c++11 -o labyrinth main.cpp ghosts.cpp steps_to_goal.cpp ...
     ```
     Achte darauf, dass du alle relevanten .cpp-Dateien in den Aufruf einbindest.

## Ausführen
Starte das Programm durch:
```bash
./labyrinth
```
Unter Windows ggf.:
```cmd
labyrinth.exe
```

## Benutzung
- Starte das Spiel aus deiner Konsole (Terminal oder Eingabeaufforderung).  
- Das Programm zeigt dir das Labyrinth an und wartet auf deine Befehle.  
- Mit den Tastendrücken w, a, s, d steuerst du die Spielerfigur.  
- Manche Felder können Türen (T) oder Wände (#) sein und sind nicht passierbar.  
- Die Geister werden durch spezifische Buchstaben repräsentiert (z. B. B, C).  
- Ein Ziel-Feld kann als 'Z' markiert sein.

## Spielanleitung
### Steuerung
- **w**: Einen Schritt nach oben.  
- **s**: Einen Schritt nach unten.  
- **a**: Einen Schritt nach links.  
- **d**: Einen Schritt nach rechts.  
- **i**: Informationsmodus umschalten (zeigt ggf. die Schrittanzahl zum Ziel an).  
- **h**: Zeigt eine kurze Hilfe an.  
- **q**: Beendet das Spiel.

### Ziel
Bewege dich durch das Labyrinth und erreiche das Zielfeld ('Z'), ohne von einem Geist getroffen zu werden. Wenn ein Geist und die Spielerposition übereinstimmen, ist das Spiel verloren.

### Geister
- **Animatronic (A)**: Bleibt an der gleichen Stelle.  
- **Bowie (B)**: Bewegt sich grundsätzlich horizontal und wechselt die Richtung, wenn er blockiert wird.  
- **Connelly (C)**: Versucht aktiv, der Spielerfigur näherzukommen, indem er den größeren Abstand (horizontal oder vertikal) vorrangig verkleinert.

### Informationsmodus
Mit der Taste **i** aktivierst/deaktivierst du den Info-Modus. Ist er aktiv, wird nach jedem Schritt (falls das Ziel in maximal 5 Schritten erreichbar ist) eine Zeile ausgegeben, die dich darüber informiert, wie viele Schritte noch bis zum Ziel nötig sind.

## Weiterführende Ideen
- Türen & Schlüssel: Füge Logik hinzu, um Türen (T) nur öffnbar zu machen, wenn die Spielerfigur einen Schlüssel (K) dabei hat.  
- Mehr Ziele oder zusätzliche Level: Erweitere das Spielfeld um mehrere Ziele, Schätze oder Aufgaben.  
- Komplexere Geister-Logik: Ergänze neue Geisttypen mit abweichenden Bewegungsmustern (z. B. diagonale Bewegungen, Teleportation etc.).

## Lizenz
Dieses Projekt kann unter einer beliebigen Open-Source-Lizenz deiner Wahl ausgerollt oder als Privatprojekt genutzt werden. Falls nicht anders festgelegt, verwende z. B. die MIT License.

Viel Spaß beim Spielen und Entwickeln!