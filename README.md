## Programme Test pour STM32L073 (Nucléo L073RZ)  

Projet réalisé sous System Workbench : SW4STM32


### Programmation de la carte :
1. Télécharger le fichier /Debug/STM32L073_Nucleo.bin
2. Brancher votre carte nucléo sur un port USB de votre Ordinateur, un nouveau lecteur NODE_L073RZ doit apparaître dans votre explorateur
3. Faire glisser le fichier STM32L073_Nucleo.bin dans le lecteur NODE_L073RZ. La carte est prête.

### Compilation du projet :
1. Ouvrir System Workbench
2. Définir un workspace (dossier contenant tous vos projets) si vous n'en avez pas un.
3. Télécharger l'ensemble du projet (environ 10 M) et dezippez-le dans votre workspace
4. Dans System Workbench : File > Import > General > Existing Projects into Workspace > Browse. Selectionner le dossier de votre workspace
5. Cochez le projet à importer (STM32L073-master), puis Finish.
6. Clic droit sur le projet > Build Project
7. Branchez votre carte nucléo
8. Programmer la carte : Clic droit sur le projet > Run As > AC6 Application

### Utilisation de l'application :
1. Programmer votre carte (utiliser une des deux méthodes ci dessus)
2. Ouvrez un terminal série : Putty, hyperterm, ...
3. Configurez le port COM correspondant à votre carte nucléo : 115200, 8 bits, sans parité.
4. Reset la carte, le menu suivant doit apparaitre dans votre terminal :
GPIO
