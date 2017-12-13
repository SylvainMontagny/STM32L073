## Programme Test pour STM32L073 (Nucléo L073RZ)  

Projet réalisé sous System Workbench (SW4STM32)


### Programmation de la carte :
1. Télécharger le fichier [/Debug/STM32L073_Nucleo.bin](https://github.com/SylvainMontagny/STM32L073/blob/master/Debug/STM32L073_Nucleo.bin) depuis Github
2. Installer le [driver USB](http://www.st.com/en/development-tools/stsw-link009.html) pour les cartes Nucléo STM32 (ST-LINK/V2-1)
3. Brancher votre carte Nucléo L073RZ sur un port USB de votre ordinateur, un nouveau lecteur [ NODE_L073RZ ] doit apparaître dans votre explorateur
4. Faire glisser le fichier STM32L073_Nucleo.bin dans le lecteur NODE_L073RZ. La carte est programmée et prête, vous pouvez passer à la partie "Utilisation de l'application ci dessous".

### Compilation et utilisation du projet dans System Workbench:
1. Ouvrir System Workbench
2. Définir un workspace (dossier contenant tous vos projets) si vous n'en avez pas un.
3. Télécharger l'ensemble du projet (environ 10 M) et dezippez-le dans votre workspace
4. Dans System Workbench : File > Import > General > Existing Projects into Workspace > Browse. Selectionner le dossier de votre workspace
5. Cochez le projet à importer (STM32L073-master), puis Finish.
6. Clic droit sur le projet > Build Project (Pour compiler uniquement)
7. Clic droit sur le projet > Run As > AC6 Application (Pour compiler **et** programmer la carte)


### Utilisation de l'application :
1. Programmer votre carte (utiliser une des deux méthodes ci-dessus)
2. Ouvrir un terminal série : Putty, hyperterm, ...
3. Configurer le port COM : 115200 bps, 8 bits, sans parité.
4. Reseter la carte, le menu suivant doit apparaitre dans votre terminal :
 
**Programme TEST des périphériques**

    (g) GPIO 
    		(P) Mode Polling
    		(I) Mode Iterrupt 
    (a) ADC  
    		(I) IN1 Channel : PA0 (A0 Nucl�o)
    		(T) Temperature Internal
    		(C) Calibration ADC
    (r) RTC 
     		(G) Get Date-Heure
     		(S) Set Date-Heure
     		(A) Alarme (IT) toutes les secondes
    (t) TIMER
    		(B) Basic Timer TIM6
    		(I) Input Capture TIM3
    (s) SPI  
    		
    (u) UART 
    		(P) Mode Polling (scrutation)
    		(I) Mode Iterrupt (Interruption)
    		(D) Mode DMA
