﻿`		`*PROJET REALISE PAR :*

- DJENNAOUI RAOUF  

*Remarque :*

Afin d’executer le programme, il faut que l’utilisateur introduise le nom du fichier (nom\_fichier.txt) . En cas d’ erreur dans la saisie du  nom ou  que le fichier txt  n’est pas dans le même répertoire que l’exécutable le programme va s’interrompre. 

Aussi  si dans le fichier on a par exemple  nom(1 ou plusieurs espaces) prénom (il faut avoir un espace) cette espace permet de distingué le prénom avec le nom du médicament même si le médicament n existe pas il faut qui cette espace  existe lors du strtok le tokken va être égal a ‘\n’ le saut de ligne donc il n y a pas de liste de médicament  

1. *LE MENU DU PROJET :*

![c1.PNG](Aspose.Words.4c2aa64b-4279-4dc7-9d0b-00cb0f6cd47e.001.png)

L’utilisateur doit sélectionner a l’aide des flèches haut & bas , alors son choix sera affiché en vert.

Lors que le message « appuyer sur une touche  pour continuer »apparait, et que l’utilisateur appuie sur une  touche ,  le retour au menu principale est automatique.

1. *LES FONCTIONS  UTILISEES :*

Le fichier d’entête option.h  contient  une fonction qui affiche un texte en couleur (textecolor) 

fonction qui positionne le curseur dans la position x,y (gotoxy).   

`	`Pour les chaines de caractères ,  on a utilisé les fonctions suivantes :

strcpy  pour copier une chaine pleine dans une autre vide.



`       		`strcmp  pour comparer deux chaines de caractères. 

`		`strtok   pour retourner une chaine selon un séparateur (split).

`  		`strcat    pour concaténer  une chaine de caractères a une autre.

`		`strlen 	retourne la longueur d’une chaine.

void progress\_bar()  est la fonction qui affiche une barre de progression.

`       `void liberer\_liste\_med(medicament\*LM)  est la fonction  qui libère la liste des médicaments.

void liberer\_liste\_patient(patient\*LP)  est la fonction qui libère la liste des patients.

int test\_fichier(FILE\*F)    teste l’existence du fichier pour débuter la création de la structure.

char\* nom\_prenom(char\*buffer)  est la fonction qui retourne le nom et prénom a partir du buffer.

medicament\* liste\_medicaments(char\*buffer)  retourne la liste des médicaments de chaque patient (ligne de fichier).

patient\*liste\_patients(FILE\*F,char c)  est la liste des patients dont l’id commence par le caractère donné.

void trie\_liste\_patients(patient\*tete)   est une fonction qui trie la liste des patients.

void afficher\_medicaments(medicament\*tete) est la fonction qui afficher la liste des médicaments

void afficher\_patients(patient\*tete) est la fonction qui affiche la liste des patients(nom et prénom).

patient\*dernier(patient\*premier)  est la fonction qui retourne le dernier patient.

H\*structure(FILE\*F)   crée la structure.

patient\*rechercher(H\*tab,char\*id)   est la fonction qui recherche un patient dont le nom et le prénom égale a (id)

medicament\*rechercher\_med(medicament\*LM,char\*id\_m) est la fonction qui recherche un médicament donné.

medicament\* medicament\_patient(patient\*p,char\*id\_m) retourne la liste des médicaments du patient (p) donné.

void ajuster(patient\*p,medicament\*m,int qte)  est la fonction qui ajuste la quantité de médicament en effectuant le calcul ( qte prescrite  - qte donnée). Elle supprime le médicament si le  résultat est égal a 0.

patient\*new\_patient(char\*ch)    allouer un patient dont l'info est égal a ch.

void inserer\_patient(H\*tab,patient\*p)   est la fonction qui permet d’insérer un patient.

void supprimer\_patient(H\*tab,patient\*p)   supprime un patient donnée

void afficher\_structure(H\*tab, int i)   affiche les patients qui se trouvent dans l’ indice i donné

void convert(char\*ch)  elle convertit du majuscule au minuscule 






*REMARQUE :*

![c2.PNG](Aspose.Words.4c2aa64b-4279-4dc7-9d0b-00cb0f6cd47e.002.png)

Dans le tableau  tab[0]  (‘a’) : s’il est vide alors, le caractère ‘a’ est affiché en rouge et affiche « NULL » ; si non en bleu et son contenu  nom prénom du patient en vert si la liste des médicaments   n’est pas vide ,alors il affiche son contenu ; sinon un message en rouge sera affiché. 

Lorsqu’ on arrive a  la fin de l’ affichage un message d’avertissement  s’affiche en rouge. 

Idem pour rechercher  ,supprimer ,ajouter un patient : un message en bleu s’affiche  en cas de succès, en rouge dans le cas contraire . 