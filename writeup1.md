## Enumération
Pour identifier l'ip de la machine, nous allons utiliser netdiscover. Un outils de reconnaissance ARP, et nous allons l'utiliser de manière passive:

![image](https://user-images.githubusercontent.com/29956389/89550181-98ea0400-d809-11ea-8d71-d89f860e3533.png)

On observe l'ip  192.168.42.101 qui communique.

### Nmap

On vérifie que la machine a compromettre est bien  192.168.42.101 , on lance tout de suite la reconnaissance avec nmap:
```sh
$ nmap 192.168.42.101
```
![image](https://user-images.githubusercontent.com/29956389/89550359-d058b080-d809-11ea-9ba3-df30def08aad.png)

On observe plusieurs ports ouverts, nous allons donc profiter de la puissance de nmap pour obtenir plus de renseignement sur ces ports ouverts.

```
$ nmap -p- -sS -sC -sV 192.168.42.101
```
`-p-` : Scanner tout les 65535 ports de la machine.

`-sS` : Effectuer un scan SYN complet.

`-sC` : Exécuter les scripts par défauts.

`-sV` : Énumérer les versions logiciels.

`192.168.42.101` : notre cible.


![image](https://user-images.githubusercontent.com/29956389/89550647-2decfd00-d80a-11ea-869c-0a2cb4404599.png)

On observe que grâce a l'exécution des script par défault, qu'un acces anonyme au server FTP n'est pas possible, il nous faudra des credentials pour y acceder.

![ftp](https://user-images.githubusercontent.com/29956389/67638171-13ccd880-f8e2-11e9-8146-c490dc6c0017.png)

On observe un serveur SSH 5.9:

![ssh](https://user-images.githubusercontent.com/29956389/67638195-319a3d80-f8e2-11e9-883a-dfa6be4935f3.png)

Un ou deux serveur web sur le port 80 et 443, respectivement http et https, qui tourne sur apache 2.2.22:

![http](https://user-images.githubusercontent.com/29956389/67638205-4ecf0c00-f8e2-11e9-995e-6494030006ff.png)

Et quelque chose de plutot intéréssant, le port 143 et 933, qui sont utilisé pour du traffic imap. (Mail):

![imap](https://user-images.githubusercontent.com/29956389/67638232-7aea8d00-f8e2-11e9-9e77-ed7c2e52587f.png)

## Web
On décide de se pencher sur les serveurs web en premier:

![website](https://user-images.githubusercontent.com/29956389/67638287-06641e00-f8e3-11e9-879e-c9b54556867c.png)

Rien de particulier sur les sites, les console, ou encore leurs code source. Pas non plus de fichier `robots.txt`.

![robots443](https://user-images.githubusercontent.com/29956389/67638297-34e1f900-f8e3-11e9-9e4f-ed002cf2a0e2.png)

## Dirbuster / Gobuster
Dirbuster est un outils qui va tester tous les nom de fichier/dossier présent dans une wordlist pour voir lesquels dentre eux réponde sur le server web spécifié.

On utilisera ici dirbuster ainsi que gobuster en ligne de commande.

Port 80:

![image](https://user-images.githubusercontent.com/29956389/89551504-4f9ab400-d80b-11ea-814b-582250696cb9.png)

Port 443:

![image](https://user-images.githubusercontent.com/29956389/89551449-414c9800-d80b-11ea-978f-277ef2dd9153.png)

Dirbuster nous donne quelque informations supplémentaires:

![image](https://user-images.githubusercontent.com/29956389/89551851-b750ff00-d80b-11ea-8f5b-3e1e25574c70.png)


Les chemins trouvé sur le port 80 nous renvois tous le code 403 (Forbidden).
Par contre, en https on accède a `/forum/`qui se décline en `/forum/images/` `/forum/themes/` et `/forum/templates_c/`. Il y a aussi `/webmail/src/login.php` qui est probablement en lien avec les port 143 et 993, et a `/phpmyadmin/index.php`:

![forum](https://user-images.githubusercontent.com/29956389/67638449-c9009000-f8e4-11e9-89d5-f911da6cf733.png)

![mail](https://user-images.githubusercontent.com/29956389/67638451-ca31bd00-f8e4-11e9-8a92-c7dd56b4e8bf.png)

![phpmyadm](https://user-images.githubusercontent.com/29956389/67638678-a15ef700-f8e7-11e9-90cb-820d4cd7e48c.png)

## Recherche sur le forum

Apres quelque minutes sur le forum j'observe plusieurs choses, une liste d'utilisateurs enregistré sur le site, et que le forum est probablement construit sur le framework `my little forum`:

![users](https://user-images.githubusercontent.com/29956389/67638517-63f96a00-f8e5-11e9-9fed-9a3fe0e5a30e.png)


Ainsi qu'un fichier qui ressemble beaucoup a un syslog, dans lequel on observe une tentative de connection échoué avec un username plutot aléatoire (qui ressemble fortement a un mot de passe), et a peine 30 secondes plus tard, une connection reussi de la part du user `lmezard`:

![auth](https://user-images.githubusercontent.com/29956389/67638523-7b385780-f8e5-11e9-87d7-843d9342cb0f.png)

On l'essaye tout de suite sur le forum:

![log](https://user-images.githubusercontent.com/29956389/67638707-074b7e80-f8e8-11e9-8299-b1eff113ccf8.png)

Et ca marche:

![profile](https://user-images.githubusercontent.com/29956389/67638710-116d7d00-f8e8-11e9-8ca7-f30dd2510cbd.png)
# Webmail
On note l'adresse mail qui nous est montré ici et on va directement l'essayer sur la page webmail, avec le meme mot de passe:

![mailcon](https://user-images.githubusercontent.com/29956389/67638719-26e2a700-f8e8-11e9-8d2c-e10b1713dbf0.png)

Cela marche a nouveau et on obtient apparement un login root pour la base de donnée:

![ft_root](https://user-images.githubusercontent.com/29956389/67638730-437edf00-f8e8-11e9-81de-9cee905b999e.png)

# PhpMyAdmin

On accede donc a phpMyAdmin, et on essaye de se connecter avec ces creedentials, et on arrive sur la page d'acceuil:

![image](https://user-images.githubusercontent.com/29956389/89552437-6d1c4d80-d80c-11ea-8e53-907324c24552.png)

On y voit une base de donnée apellé forum_db, et en la selectionant, on peut y executer une commande SQL.

Nous allons l'utiliser pour injecter un script. Reste plus qu'a savoir ou le placer.

Apres plusieurs tentative, et de code retour 2 (permission denied) et 13 (no such file ?), on finis par le placer dans `/var/www/forum/templates_c/`


![image](https://user-images.githubusercontent.com/29956389/89553064-53c7d100-d80d-11ea-81e6-08df4657c2f2.png)

Le script qui s'apelle `cmd.php` va nous présenter un champ de texte, dont le contenu sera executé avec la fonction `system` de php.

![image](https://user-images.githubusercontent.com/29956389/89553198-81147f00-d80d-11ea-9997-99fd65efaf49.png)

On l'essaye directement avec la commande `id` :

![image](https://user-images.githubusercontent.com/29956389/89553356-b325e100-d80d-11ea-9e2b-4ec0b602e42b.png)

Et on obtien un retour positif !
On continue donc d'explorer le système :

![image](https://user-images.githubusercontent.com/29956389/89553518-e9fbf700-d80d-11ea-93f9-f7507dac4e49.png)

Et on trouve ce dossier LOOKATME accésible au user `www-data` dans lequel il y a un fichier `password`

![image](https://user-images.githubusercontent.com/29956389/89553650-157ee180-d80e-11ea-9b71-9d240991d74f.png)

Qui contient très probablement un user et un password:

![image](https://user-images.githubusercontent.com/29956389/89553785-3fd09f00-d80e-11ea-9f41-1ae72910a10c.png)

# FTP

Apres quelques minutes de recherche, on arrive a se connecter sur le serveur ftp avec ces credentials:

![image](https://user-images.githubusercontent.com/29956389/89554223-dbfaa600-d80e-11ea-9c98-036943cfca15.png)

Qui contient un fichier README, ainsi qu'un archive tar, apellé fun.
On le récupère et on décompresse le fichier, ce qui nous laisse avec ~750 fichier avec l'extension .pcap.
Ceci est un piège car l'utilitaire `file` nous dit qu'il s'agit uniquement de fichiers texte ASCII:

![image](https://user-images.githubusercontent.com/29956389/89554586-5a574800-d80f-11ea-8543-c88e8628ee70.png)

### Analyse des fichiers

Un de ces fichiers sort du lot avec sa taille bien plus grande que les autres fichiers:

![image](https://user-images.githubusercontent.com/29956389/89554697-7bb83400-d80f-11ea-8a22-03d03e174615.png)

On l'affiche, mais il est essentiellement remplis de fonction inutiles :

![image](https://user-images.githubusercontent.com/29956389/89554810-a4402e00-d80f-11ea-8a2f-75a6b06c2711.png)

Sauf pour ce bout de code :

![image](https://user-images.githubusercontent.com/29956389/89554985-d18cdc00-d80f-11ea-93f2-07e000e16904.png)

Il faut donc trouver ces fonctions parmis les fichier `.pcap` pour réassembler le mot de passe.

![image](https://user-images.githubusercontent.com/29956389/89555343-39432700-d810-11ea-86ed-dbc4cc001f63.png)

On observe le commentaire `file5`. En combinant les informations obtenus auparavent, et avec un peu de logique, nous cherchons la suite de cette fonction, qui est probablement dans le fichier 6 soit `file6`.

![image](https://user-images.githubusercontent.com/29956389/89555697-a9ea4380-d810-11ea-8e16-67c4150d2cc3.png)

La première lettre du mot de passe est donc `I`.
On répète cette opération pour les onze autres charactères recherché et on obtiens :
`Iheartpwnage` que nous allons passer a `sha256sum` (précisé dans le README du ftp).

Ce qui nous donne: `330b845f32185747e4f8ca15d40ca59796035c89ea809fb5d30f4da83ecf45a4`

Et nous voila connecté sur le compte de laurie en ssh:

![image](https://user-images.githubusercontent.com/29956389/89556301-7360f880-d811-11ea-9c35-2549820dcaf7.png)

# SSH laurie

Le dossier home de laurie contiens deux elements : un binaire et un readme. Le
readme nous donne les indications sur la marche a suivre.
![image](https://user-images.githubusercontent.com/25014717/89707866-9656ee00-d972-11ea-8b52-a91625754de0.png)


Apres l'avoir lance une premiere fois pour voir son comportement:

![image](https://user-images.githubusercontent.com/25014717/89708008-afac6a00-d973-11ea-8420-850bb722064c.png)

Nous decompilons le binaire a l'aide de cutter:

![image](https://user-images.githubusercontent.com/25014717/89708032-eb473400-d973-11ea-8a91-cd6c789997dd.png)

Nous comprenons que le binaire peut lire sur l'entre standard s'il n'y a pas de
fichier passe en paramettre. La fonction intitialize bomb etant triviale, nous
analysons la premiere phase de la bombe:

![image](https://user-images.githubusercontent.com/25014717/89710094-70d0e100-d980-11ea-9bb4-e9152a0628f9.png)

La premiere reponse reponse pour desamorcer la bombe est simplement "Public speaking is very easy."

Le code de la phase 2 est un peu plus complexe: 

![image](https://user-images.githubusercontent.com/25014717/89710277-a75b2b80-d981-11ea-9b96-35b33768c639.png)

Apres avoir identifie la fonction read_six_numbers, qui lit six nombre dans la
chaine passe en paramettre, et retourne une erreur si six nombre ne sont pas
lus:

![image](https://user-images.githubusercontent.com/25014717/89710324-32d4bc80-d982-11ea-88e5-48086336afb8.png)

Nous avons reverse la function phase_2 pour comprendre l'algorithme: le chiffre
a l'index I est le produit du chiffre precedent par l'index du chiffre recherché:

![image](https://user-images.githubusercontent.com/29956389/89710304-0f117680-d982-11ea-8996-77c4ae2cf235.png)

Grace au README, nous savons que le chiffre a l'index 1 est 2, ce qui nous
permet de completer le reste de la suite, ce qui nous donne : "1 2 6 24 120
720".

Le code de la phase 3 est assez explicite:


![image](https://user-images.githubusercontent.com/25014717/89710443-70861500-d983-11ea-8fe6-dc3ddb20edf1.png)


Le readme nous donne le deuxieme caractere, "b" et le sscanf nous donne le
format de la string, "%d %c %d". Nous avons donc deux int a trouver. A la fin de
la function, on sait que la condition a remplir pour eviter que la bombe explose
est le switch doit valoir 1, 2 ou 7. Le second int est defini pour chaque cas:

- Pour 1, le second int est 0xD6(214)
- Pour 2, le second int est 0x2F3(755)
- Pour 7, le second int est 0x20C(524)

Les trois fonctionnent pour desamorcer l'etape 3.

Le code decompile de l'etape 4 est le suivant:

![image](https://user-images.githubusercontent.com/25014717/89710630-171ee580-d985-11ea-91ac-95cf93b2581c.png)


Nous voyons que nous devons lire un nombre, et que ce nombre, une
fois passe dans la fonction func4, doit retourer 0x37(55). Nous avons donc
reverse le code de la function fun4 et ecrit un shell script testant les
differentes possibilites:

![image](https://user-images.githubusercontent.com/25014717/89711143-b5f91100-d988-11ea-9dea-affbb6e56c9f.png)

![image](https://user-images.githubusercontent.com/25014717/89711141-b396b700-d988-11ea-9261-6330c85911df.png)

Nous obtenons comme resultat 9, qui desamorce bien la phase 4.

![image](https://user-images.githubusercontent.com/25014717/89711193-007a8d80-d989-11ea-89db-cd4899447399.png)

Pour le code de la phase_5 est le suivant : 

![image](https://user-images.githubusercontent.com/25014717/89711237-40417500-d989-11ea-8032-053c5c302fd3.png)

Nous identifions le resultat voulu, "giants" et un charset "isrveawhobpnutfg".
Nous avons donc reverse le code de la function et cree un programme pour trouver
la reponse. L'algorithme est le suivant : Pour chaque charactere de la chaine
"giants", nous allons localiser l'indexe de ce character dans le charset, puis
nous faisons une boucle qui itere les lettres minuscules du tableau ASCII, de
'a'(97) a 'z'(122). Pour chacun de ces characteres, nous faisons un AND bitwise
et regardons si le resultat correspond a l'index de la lettre recherche, nous
avons un match. Il peut il y avoir plusieurs resultats par match.

![image](https://user-images.githubusercontent.com/25014717/89711475-cca06780-d98a-11ea-8d9b-05fe6a8c8e3f.png)

Grace a ce programme, nous obtenons la chaine "opekmq" qui desamorce bien
l'etape 5.

Le code de la phase6 decompile etait assez complexe, avec un certains nombre de
boucles imbriques: 

![image](https://user-images.githubusercontent.com/25014717/89711558-3e78b100-d98b-11ea-8613-c21da014bfd1.png)

Nous avons donc decider de ne reverse que la premiere moitie de l'algorithme, ce
qui nous permet d'avoir une idee assez precise de ce qui est attendu:

![image](https://user-images.githubusercontent.com/25014717/89711617-a62efc00-d98b-11ea-9531-721aeae1fbff.png)

C'est ainsi que nous avons compris que nous devions fournir une suite de six
chiffres compris entre 1 et 6, chaque chiffre ne pouvant apparaitre qu'une fois.
Grace au reademe, nous savions aussi que cette suite commencait par 4.
Fort de ces elements, nous avons generes tout les cas possible, et fait un script
pour tester tout les resultats.

![image](https://user-images.githubusercontent.com/25014717/89711795-c7dcb300-d98c-11ea-89ec-dc9a18baad0d.png)

C'est ainsi que nous avons obtenu le resultat "4 2 6 3 1 5".

En concatenant tout les resultats, nous obtenons la string "Publicspeakingisveryeasy.126241207201b2149opekmq426315", qui est effectivement le mot de passe de thor.

![image](https://user-images.githubusercontent.com/25014717/89712686-b4cce180-d992-11ea-94c9-9c90fe3aa756.png)

## Thor
On observe deux fichiers: README et turtle, un fichier texte.

![image](https://user-images.githubusercontent.com/29956389/89712639-71727300-d992-11ea-888c-86c75a45b3f2.png)

En affichant le fichier turtle, on observe qu'il s'agit d'instructions de déplacement.

![image](https://user-images.githubusercontent.com/29956389/89712663-923ac880-d992-11ea-9e26-52cf050854f9.png)

En effet, il s'agit d'instructions pour l'agorithme `Turtle graphics` pour python:

https://docs.python.org/3/library/turtle.html

On lance alors python, et on importe le module turtle. On lance la commande `turtle.getscreen()` pour avoir un affichage visuel sur un canevas.

Et on lance l'equivalent des instructions du fichier `turtle` dans le programme python:

![image](https://user-images.githubusercontent.com/29956389/89712708-d201b000-d992-11ea-9915-a3afe27d5f57.png)

Voila le resultat avec les instructions présenté ci-dessus.

![image](https://user-images.githubusercontent.com/29956389/89712711-d8902780-d992-11ea-9c5e-3ea6c4707c2d.png)

On effectue cette operation pour toutes les instructions listé, et on obtiens le mot `SLASH`.

La question `Can you digest the message. :)` fait référence au Digest MD5. La fonction de hashage.
On lance alors `echo -n 'SLASH' | md5sum` ce qui nous donne `646da671ca01bb5d84dbb5fb2238dc8e`
