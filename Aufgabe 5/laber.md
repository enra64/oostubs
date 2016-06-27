# 1: Beschreibung des Algorithmus
* Bei Aufruf von **getKey** wird semaphore.wait() -> p() -> organizer.block(), so dass der thread in die queue der semaphore verschoben wird und danach vergessen wird.
* Bei Aufruf des Interrupthandlers wird semaphore.signal() -> v() -> organizer.wakeup() aufgerufen, so dass der thread aus dem Warteraum wieder in die aktive Queue des Schedulers geschoben wird.

Dadurch kann ein thread immer nur nach einer keyboard-eingabe weiterlaufen.

# 2:
## Analyse Job, JobManager
Job ist ein Objekt, das eine Application (Grundklasse aller oostubs-Applikationen) kapselt. Dabei weiß es, ob der job gerade läuft oder nicht, und kann ihn starten und stoppen.  
JobManager ist ein Objekt, das alle Jobs speichert und starten und stoppen kann. 

## Customer vs Thread
Customer ist eine Unterklasse von Thread, die weiß, ob und in welchem Waiting-Room sie sich befindet.

## "Blockiert" ohne je "Bereit" gewesen zu sein?
Nein, denn der JobManager und der Job kennen die Bereitschaftsqueue nicht weiter; der Thread muss sich also selber blockieren.

# Änderungen im Scheduler:
* Neue Funktion "reactivate(Thread& unblocked)" eingefügt, so dass der Organizer bei wakeup den Thread für die Ausführung schedulen kann.
