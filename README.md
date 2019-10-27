# Boot2Root

Ce projet a pour but de nous faire découvrir, via plusieurs petits challenges, la sécurité en informatique dans plusieurs domaines.



# Installation

- Télécharger une iso récente de Kali Linux, ainsi que l'iso fournit en ressource du projet.
- Installer un logiciel de virtualisation, nous utiliserons VMware Workstation dans ce writeup.
- Installer les deux iso, et configurer le réseau, pour que les deux machines puissent communiquer :

![vm2](https://user-images.githubusercontent.com/29956389/67637693-4d4f1500-f8dd-11e9-8b20-6d0d873d2702.png)

![vm](https://user-images.githubusercontent.com/29956389/67637696-56d87d00-f8dd-11e9-90cd-74e6dbfb86cd.png)

### Méthodes et outils utilisés


La méthodologie générale que nous allons utiliser est la suivante :

- Reconnaissance (active/passive)
- Obtenir un accès (exploitation)
- Escalation de privilèges
- Établir une persistance
- Extraction de données
- Effacer ses traces

Bien que nous allons utiliser que les trois premières étapes pour ce challenge.

Tous les logiciels utilisés pour résoudre ce CTF, sont présents de base dans la distribution Kali Linux.

| Logiciel | Lien |
| ------ | ------ |
| Kali Linux | [https://www.kali.org/] |
| Tmux | [https://github.com/tmux/tmux/wiki] |
| Cherry Tree | [https://www.giuspen.com/cherrytree/] |
| Nmap | [https://nmap.org/] |
| Dirbuster | [https://tools.kali.org/web-applications/dirbuster] |
| ncat| [https://nmap.org/ncat/] |
