# Simulateur CLI pour GPIO

Ce projet est un simulateur d'interface en ligne de commande (CLI) développé en C pur, conçu pour interagir et simuler le comportement de General Purpose Input/Output (GPIO) sur un microcontrôleur. Il offre la possibilité de contrôler l'état des pins et de visualiser les registres de mode et de données.

## Fonctionnalités

* **Commandes spécifique du CLI :**
    * `help` : Affiche les commandes pret à étre utilisé.
    * `exit` : Terminé le programme.

* **Contrôle de l'état des pins :**
    * `set gpio<Port> pin<Num> high` : Définit l'état d'une pin spécifique à HIGH.
    * `set gpio<Port> pin<Num> low` : Définit l'état d'une pin spécifique à LOW.
    *(Ex: `set gpioa 5 high`)*
* **Contrôle de modes des pins :**
    * `mode gpio<Port> pin<Num> in` : Définit le mode pin spécifique à input.
    * `mode gpio<Port> pin<Num> out` : Définit le mode pin spécifique à output.
    *(Ex: `mode gpioa 5 out`)*
* **Toggle l'état des pins :**
    * `toggle gpio<Port> pin<Num>` : Toggle l'état d'une pin HIGH ou LOW.
    *(Ex: `toggle gpioa 5`)*
* **Affichage des registres :**
    * `regst gpio<Port>` : Affiche l'état simulé du registre de données (valeur actuelle des pins) pour un port GPIO donné.
    * `regmode gpio<Port>` : Affiche l'état simulé du registre de mode (Input/Output) pour un port GPIO donné.
    *(Ex: `regst gpiob`)*
* **Affichage de l'état d'une pin :**
    * `pinst gpio<Port> pin<Num>` : Affiche l'état actuel (HIGH/LOW) d'une pin spécifique.
    *(Ex: `pinst gpioc 6`)*

Les ports GPIO pris en charge sont A, B, C et D.
Chaque ports GPIO contient uniquement 8 pins.

## Technologies Utilisées

* **Langage :** C
* **Compilateur :** GCC
* **Build System :** Makefile

## Comment Compiler et Exécuter

1.  **Cloner le dépôt :**
    ```bash
    git clone [https://github.com/mmekki96/GPIO-Simulator-CLI.git](https://github.com/mmekki96/GPIO-Simulator-CLI.git)
    cd GPIO-Simulator-CLI
    ```
2.  **Compiler le projet :**
    ```bash
    make
    ```
3.  **Exécuter le simulateur :**
    ```bash
    ./main
    ```

## Exemples d'utilisation

>> set gpioa 4 high
>> mode gpioc 3 out
>> toggle gpiob 1
>> pinmode gpiod 7 
