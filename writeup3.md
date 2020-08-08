
# Writeup 3

## Détourner le processus de boot standart
 ! Cette solution néccésite un accès physique a la machine. ( Ici il s'agit d'une machine virtuelle ) !

Au lancement de la machine, appuyer sur la touche LeftShift, jusqu'a voir apparaitre ce prompt:

![image](https://user-images.githubusercontent.com/29956389/89707841-6b6c9a00-d972-11ea-9900-01b9a6429d54.png)

Il s'agit soit du prompt de LILO (Linux Loader) soit de GRUB2.

Aucune commande standart n'est reconnu ici:

![image](https://user-images.githubusercontent.com/29956389/89707871-9c4ccf00-d972-11ea-86c6-1e7e2365c7f7.png)

Par contre, en appuyant sur la touch `<tab>`, l'autocomplétion nous propose la commande `live`.

En exécutant cette commande, le processus de boot reprend correctement et nous arrivons sur le login prompt d'ubuntu.

Apres quelques minutes de recherche on tombe sur cet article :
- https://superuser.com/questions/215590/how-to-boot-grub2-into-the-simplest-linux-shell/215604#215604

Cet article nous explique qu'il est possible de lancer un shell au démarrage avec la commande `init=/bin/sh`.

Malheureusement cela ne fonctionne pas ici, la meme erreur qu'auparavent apparait: `Could not find kernel image: init=/bin/sh`

On essaye donc de combiner cet commande avec la seule commande qui fonctionne: `live init=/bin/sh` :

![image](https://user-images.githubusercontent.com/29956389/89707990-96a3b900-d973-11ea-8a3e-a6fd99e87084.png)

 ### Et ca fonctionne !
 
 ![image](https://user-images.githubusercontent.com/29956389/89708033-ebdfca80-d973-11ea-9425-6164696ef24a.png)
 
 ### On est bien id 0, avec accès a /etc/shadow !
