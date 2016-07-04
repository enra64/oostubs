# 2
Ein Seitenfehler tritt auf, wenn ein Programm auf einen Speicherbereich zugreift, der sich gerade nicht im Hauptspeicher befindet oder für den ein MMU-Eintrag fehlt.

page fault -> trap -> laden des speicherbereichs in den Hauptspeicher **oder** MMU-Eintrag

# 3
Ja, der *paging supervisor* hält sogenannte *pinned pages* immer im Speicher, zum Beispiel für Interrupthandling.

# 4
## ASLR - Address space layout randomization
ASLR verändert alle Speicherpositionen zufällig, so dass nicht bei jeder Ausführung eines Programmes Daten an der gleichen Stelle stehen. Dadurch kann ein Angreifer sich nicht auf diese Adresse verlassen.

## XD - eXecute Disable
The XD bit (or NX bit or XN bit) disables execution of memory areas to avoid executing data loaded by an attacker.

# 9
## MBR - Master Boot Record
* ersten 512 byte eines mediums
* boot-code (maximal eine boot-partition) und partitionstabellen für 4 partitionen
* es gibt primäre und maximal eine erweiterte Partition, wobei die letztere wiederum logische Partitionen enthalten kann
* es gibt versteckte/reservierte Sektoren

## GPT - GUID (Globally Unique Identifier) Partition Table
* Modernere Partitionsmethode
* Kann mehr als 2 TB
* Kann MBR-Boot-Sektor haben, um Abwärtskompatibilität zu sichern
* eine Partition belegt das gesamte Speichermedium
* MBR enthält sofern möglich die gleichen ersten Partitionen
* 128 Partitionen
* ein Partitionseintrag hat 128 Byte
* am Ende des Speichermediums gibt es eine Kopie der Partitionstabelle und der GPT-Header

# 8

## Write-Through
* bei Cache Hit werden sowohl Hauptspeicher als auch Kopie im Cache sofort aktualisiert 
* bei Cache Miss wird der Hauptspeicher aktualisiert, aber der Cache bleibt unverändert

## Write-Back
* bei Cache Hit 
  * wird nur die Kopie im Cache verändert, der Hauptspeicher bleibt unverändert 
  * Cache-Eintrag muss mit Dirty-Bit markiert werden 
  * bei späterer Verdrängung muss Wert in den Hauptspeicher zurückgeschrieben werden 
* bei Cache Miss wird der Hauptspeicher aktualisiert, aber der Cache bleibt unverändert

## Sinnhaftigkeit dauerhafte Konsistenz
Nicht sinnvoll, weil man nur zu benutzenden Daten erlauben sollte, Arbeit zu beanspruchen. Eine dauerhafte Konsistenzhaltung müsste auch nicht benötigte Daten aktuell halten.

## Write-Allocate
Daten an der missed write location werden in den cache geladen, woraufhin dorthin geschrieben wird (dirty bit wird gesetzt).

## No-Write-Allocate
Der Block wird nur im RAM beschrieben und nicht eingelagert.
