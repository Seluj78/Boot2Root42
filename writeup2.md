# Writeup2

## SSH
![image](https://user-images.githubusercontent.com/29956389/89556301-7360f880-d811-11ea-9c35-2549820dcaf7.png)

Une fois connecté en ssh sur la machine avec le compte de laurie, on verifie la version du kernel linux avec la commande `uname -r`.

![image](https://user-images.githubusercontent.com/29956389/89706911-30666880-d96a-11ea-97f0-2cfc9ba74b31.png)

# DirtyCow

Les versions 2.6 jusqu'au versions 3.2 du noyau linux présentent une vulnérabilité basé sur une une `race condition`, appelé `Dirty-CoW`.
Elle porte ce nom car cette faille est basé sur l'exploitation d'un Copy-On-Write(C-o-W).

Elle permet de modifier n'importe quel fichier sur le système (/etc/shadow, binaires SUID, etc...) sans avoir besoin des droits néccésaire habituellement.

De plus amples explication sont disponible sur ces lien: 
- https://github.com/dirtycow/dirtycow.github.io/wiki/VulnerabilityDetails
- https://www.theregister.com/2016/10/21/linux_privilege_escalation_hole/
- https://www.cs.toronto.edu/~arnold/427/18s/427_18S/indepth/dirty-cow/demo.html

Nous allos donc nous rendre sur https://github.com/artemgurzhii/dirty-cow-root-exploit pour télécharger l'exploit.
Et nous allons envoyer le code source vers la machine avec la commande SCP.

On le compile directement sur la machine, qui dispose de `gcc`, `make`, ainsi que la librarie `pthread`.

![image](https://user-images.githubusercontent.com/29956389/89707170-0c0b8b80-d96c-11ea-9fa7-9d832a81a88f.png)

On execute le binaire compilé:

![image](https://user-images.githubusercontent.com/29956389/89707274-eb900100-d96c-11ea-9207-4845a1de51e6.png)

Il nous demande un mot de passe, et nous informe que la ligne

`firefart:firwVQs3fu3rM:0:0:pwned:/root:/bin/bash` 

a été rajouté au fichier `/etc/passwd` et qui nous pouvons a présent se connecter au user `firefart` avec le mdp `toto`.

On essaye donc: 

![image](https://user-images.githubusercontent.com/29956389/89707367-956f8d80-d96d-11ea-95a9-9e0dbaecde11.png)

### Et nous voila ROOT !
