## Programme Test pour STM32L073 (Nucl�o L073RZ)  

Projet r�alis� sous STM32CubeIDE

### Programmation de la carte :
1. T�l�charger le fichier [/Debug/STM32L073_Nucleo.bin](https://github.com/SylvainMontagny/STM32L073/blob/master/Debug/STM32L073_Nucleo.bin) depuis Github
2. Brancher votre carte Nucl�o L073RZ sur un port USB de votre ordinateur, un nouveau lecteur [ NODE_L073RZ ] doit appara�tre dans votre explorateur
3. Faire glisser le fichier STM32L073_Nucleo.bin dans le lecteur NODE_L073RZ. La carte est programm�e et pr�te, vous pouvez passer � la partie "Utilisation de l'application ci dessous".

### Compilation et utilisation du projet dans STM32CubeIDE:
1. Ouvrir STM32CubeIDE
2. D�finir un workspace (dossier contenant tous vos projets) si vous n'en avez pas un.
3. T�l�charger l'ensemble du projet depuis Github (https://github.com/SylvainMontagny/STM32L073/) et dezippez-le dans votre workspace
4. Dans STM32CubeIDE : File > Open File from filesystem > Directory > Browse. Selectionner le dossier de votre workspace
5. Cochez le projet a importer , puis Finish.
6. STM32CubeIDE > Run > Run pour lancer le projet OU STM32CubeIDE > Run > Debug as pour Debbuger le projet



### Utilisation de l'application :
1. Programmer votre carte (utiliser une des deux m�thodes ci-dessus)
2. Ouvrir un terminal s�rie : Putty, hyperterm, ...
3. Configurer le port COM : 115200 bps, 8 bits, sans parit�.
4. Reseter la carte, le menu suivant doit apparaitre dans votre terminal, suivez les instructions :
 
**Programme TEST des p�riph�riques**

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
    		(M) Mesure Temps PA11
    (s) SPI  
    		
    (u) UART 
    		(P) Mode Polling (scrutation)
    		(I) Mode Iterrupt (Interruption)
    		(D) Mode DMA
