## Enumération
### Nmap

Apres avoir vérifier que la machine a compromettre est 10.10.10.50, on lance tout de suite la reconnaissance avec nmap:
```sh
$ nmap -sS -sC -sV -oA nmap/boot2root 10.10.10.50
```
`-sS` : Scan SYN complet.
`-sC` : Executer les scripts par defaults.
`-sV` : Enumerer les versions logiciels.
`-oA nmaap/boot2root` : exporte le rapport en 3 formats. (gnmap/nmap/xml)
`10.10.10.50` : notre cible.

![scan](https://user-images.githubusercontent.com/29956389/67637898-635dd500-f8df-11e9-8224-cc1c897554a1.png)

On observe que grace a l'execution des script par défault, qu'un acces anonyme au server FTP n'est pas possible, il nous faudra des credentials pour y acceder.
![ftp](https://user-images.githubusercontent.com/29956389/67638171-13ccd880-f8e2-11e9-8146-c490dc6c0017.png)

On observe un serveur SSH 5.9:
![ssh](https://user-images.githubusercontent.com/29956389/67638195-319a3d80-f8e2-11e9-883a-dfa6be4935f3.png)

Un ou deux serveur web sur le port 80 et 443, respectivement http et https, qui tourne sur apache 2.2.22:
![http](https://user-images.githubusercontent.com/29956389/67638205-4ecf0c00-f8e2-11e9-995e-6494030006ff.png)

Et quelque chose de plutot intéréssant, le port 143 et 933, qui sont utilisé pour du traffic imap. (Mail):
![imap](https://user-images.githubusercontent.com/29956389/67638232-7aea8d00-f8e2-11e9-9e77-ed7c2e52587f.png)

### Web
Je décide de me pencher sur les serveurs web en premier:

![website](https://user-images.githubusercontent.com/29956389/67638287-06641e00-f8e3-11e9-879e-c9b54556867c.png)

Rien de particulier sur les sites, les console, ou encore leurs code source. Pas non plus de fichier `robots.txt`.

![robots443](https://user-images.githubusercontent.com/29956389/67638297-34e1f900-f8e3-11e9-9e4f-ed002cf2a0e2.png)

### Dirbuster
Dirbuster est un outils qui va tester tous les nom de fichier/dossier présent dans une wordlist pour voir lesquels dentre eux réponde sur le server web spécifié.

![dirb](https://user-images.githubusercontent.com/29956389/67638340-9904bd00-f8e3-11e9-8a86-e622396610e3.png)

Les chemins trouvé sur le port 80 nous renvois tous le code 403 (Forbidden).
Par contre, en https on accède a `/forum/`, a `/webmail/src/login.php` qui est probablement en lien avec les port 143 et 993, et a `/phpmyadmin/index.php`:

![forum](https://user-images.githubusercontent.com/29956389/67638449-c9009000-f8e4-11e9-89d5-f911da6cf733.png)
![mail](https://user-images.githubusercontent.com/29956389/67638451-ca31bd00-f8e4-11e9-8a92-c7dd56b4e8bf.png)
![phpmyadm](https://user-images.githubusercontent.com/29956389/67638678-a15ef700-f8e7-11e9-90cb-820d4cd7e48c.png)

## Recherche sur le forum

Apres quelque minutes sur le forum j'observe plusieurs choses, une liste d'utilisateurs enregistré sur le site, etr que le forum est probablement construit sur le framework `my little forum`:

![users](https://user-images.githubusercontent.com/29956389/67638517-63f96a00-f8e5-11e9-9fed-9a3fe0e5a30e.png)


Ainsi qu'un fichier qui ressemble beaucoup a un syslog, dans lequel on observe une tentative de connection échoué avec un username plutot aléatoire (qui ressemble fortement a un mot de passe), et a peine 30 secondes plus tard, une connection reussi de la part du user `lmezard`:

![auth](https://user-images.githubusercontent.com/29956389/67638523-7b385780-f8e5-11e9-87d7-843d9342cb0f.png)

On l'essaye tout de suite sur le forum:

![log](https://user-images.githubusercontent.com/29956389/67638707-074b7e80-f8e8-11e9-8299-b1eff113ccf8.png)

Et ca marche:

![profile](https://user-images.githubusercontent.com/29956389/67638710-116d7d00-f8e8-11e9-8ca7-f30dd2510cbd.png)

On note l'adresse mail qui nous est montré ici et on va directement l'essayer sur la page webmail:

![mailcon](https://user-images.githubusercontent.com/29956389/67638719-26e2a700-f8e8-11e9-8d2c-e10b1713dbf0.png)

Cela marche a nouveau et on obtient apparement un login root (déja ??):

![ft_root](https://user-images.githubusercontent.com/29956389/67638730-437edf00-f8e8-11e9-81de-9cee905b999e.png)




