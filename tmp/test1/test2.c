// 📑 SUJET BÊTA : Le Système de Cache en RAM (Shared Memory, Mutex de Processus)
// Énoncé
// On souhaite concevoir une structure de cache de données partagée entre deux programmes distincts sans lien de parenté : lecteur_cache et modificateur_cache.

// Les deux programmes partagent une structure nommée cache_t via un objet de mémoire partagée POSIX nommé "/shm_data". Cette structure contient :

// Un tableau d'entiers donnees[5].

// Un entier mise_a_jour_pret qui vaut 1 si de nouvelles données ont été écrites, 0 sinon.

// Pour protéger ce cache, on utilise un unique sémaphore nommé "/sem_lock" faisant office de Mutex (initialisé à 1).

// Le programme Modificateur (-m) : Prend le verrou, génère 5 nouveaux entiers aléatoires dans le tableau, passe mise_a_jour_pret à 1, libère le verrou, puis s'arrête.

// Le programme Lecteur (-l) : Boucle de manière non-bloquante (avec une pause de 500ms entre chaque vérification). Il prend le verrou, regarde si mise_a_jour_pret vaut 1. Si oui, il affiche les 5 entiers, remet le flag à 0, libère le verrou et s'arrête. Sinon, il relâche immédiatement le verrou pour ne pas bloquer le système et réessaie au tour suivant.

// Le programme Reset (-r) : Nettoie les structures de l'OS.