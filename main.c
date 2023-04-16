#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <conio.h>
#include"package/option.h"
//*****************************************************************************************
/*le fichier est supposé rempli comme suite */
/*nom prenom med1 qt1 med2 qt2 med3 qt3....*/
/*med = médicament & qt = quantité*/
//*****************************************************************************************
#define t_buffer 300 // t_buffer c'est la taille max du tompon
//*****************************************************************************************
typedef struct medicament
{
    char*id_med;// le nom du medicament
    int quantite;// la quantité préscrite
    struct medicament *med_svt;// medicament suivant
} medicament ;

//*****************************************************************************************
typedef struct patient
{
    char*id_pat; // nom & prenom du patient
    medicament* liste_med;// la liste de medicaments préscrits
    struct patient *pat_svt;// patient suivant
    struct patient *pat_prec;// patient precedent
} patient ;
//*****************************************************************************************
typedef struct H
{
    struct patient*a;
    struct patient*b;
}H;

//*****************************************************************************************
void  convert(char*ch)//fonction qui convertit le buffer en minuscule
{
    int l=strlen(ch);
    int i;
    for(i=0 ; i < l ; i++ )
    {
        if ( ch[i] >=65 && ch[i]<=90)
            ch[i] = ch[i]+32 ;
    }
}
//*****************************************************************************************
int menu()//retourne le choix selectionner a l'aide des fléches ( bas & haut) le choix est mis en couleur
{
    int  choix=1;
    char touche;
    printf("\n");
    textcolor(12);
    printf("                            	  ***********                       \n");
    printf("                            	  * M E N U *                       \n");
    printf("                            	  ***********                       \n");
    textcolor(15);

    while (touche!=13) //CODE ASCII DE LA TOUCHE ENTERER
    {
        gotoxy(1,1);

        if (choix==1) textcolor(10);
        else textcolor(15);
        printf("\n");
        printf("\n");
        printf("\n");
        printf("\n");
        printf("               	  *********************************************\n");
        printf(" 		  * 1  AFFICHER LA LISTE DE TOUT LES PATIENTS *\n");
        printf("               	  *********************************************\n");
//-----------------------------------------------------------------------
        if (choix==2) textcolor(10);
        else textcolor(15);
        printf("               	  *********************************************\n");
        printf(" 		  * 2  RECHERCHE D UN PATIENT                 *\n");
        printf("               	  *********************************************\n");
//-----------------------------------------------------------------------
        if (choix==3) textcolor(10);
        else textcolor(15);
        printf("               	  *********************************************\n");
        printf(" 		  * 3  SUPPRIMER UN PATIENT                   *\n");
        printf("               	  *********************************************\n");
//-----------------------------------------------------------------------
        if (choix==4) textcolor(10);
        else textcolor(15);
        printf("               	  *********************************************\n");
        printf(" 		  * 4  AJOUTER UN PATIENT                     *\n");
        printf("               	  *********************************************\n");
//-----------------------------------------------------------------------
        if (choix==5) textcolor(10);
        else textcolor(15);
        printf("               	  *********************************************\n");
        printf(" 		  * 5  CONSOMMER UN MEDICAMENT                *\n");
        printf("               	  *********************************************\n");
//-----------------------------------------------------------------------
        if (choix==6) textcolor(10);
        else textcolor(15);
        printf("               	  *********************************************\n");
        printf(" 		  * 6  QUITTER LE PROGRAMME                   *\n");
        printf("               	  *********************************************\n");
        textcolor(15);
        touche=getch();
        if (touche==80) //CODE ASCII DE LA FLECHE BAS
        {
            choix++;
            if (choix==7) choix=1;
        }
        if (touche==72) //CODE ASCII DE LA FLECHE HAUT
        {
            choix--;
            if (choix==0) choix=6;
        }
    }
    return choix;
}

//*****************************************************************************************
void progress_bar()// cette fonction affiche une barre de progression
{
    int i;
    char a=176,b=219;
    SetConsoleTitle(_T("Gestion_d un_hopital"));
    textcolor(10);
    system("cls");
    gotoxy(26,10);
    printf("        CHARGEMENT ... ! \n");
    gotoxy(26,11);
    for(i=0;i<=27;i++)
    {
        printf("%c",a);

    }
    textcolor(2);
    gotoxy(26,11);
    for(i=0;i<=13;i++)
    {
        printf("%c",b);
        printf("%c",b);
        Sleep(1000);
    }
    textcolor(15);
    system("cls");

}

//*****************************************************************************************
void liberer_liste_med(medicament*LM)// cette fonction libere la liste des medicaments
{

    medicament*temp;

    while(LM!=NULL)
    {
        temp=LM;
        LM=LM->med_svt;
        free(temp);
    }
}
//*****************************************************************************************
void liberer_liste_patient(patient*LP)//cette fonction libere la liste des patients
{
    patient*temp;

    while(LP!=NULL)
    {
        temp=LP;
        liberer_liste_med(temp->liste_med);
        LP=LP->pat_svt;
        free(temp);
    }
}
//*****************************************************************************************

int test_fichier(FILE*F) // tester l existance du fichier pour debuter la creation de la structure
{

    if(F==NULL)
    {
        textcolor(12);
        printf("ERREUR ... LE FICHIER N EXTSTE PAS DANS LE MEME REPERTOIRE QUE L EXECUTABLE \n");
        printf("OU LE FICHIER N EXISTE PAS \n");
        textcolor(15);
        return 0;
    }
    else return 1;
}
//*****************************************************************************************
char* nom_prenom(char*buffer)// cette fonction retourne le nom et prenom a partire du buffer
{
    char*copie=(char*)malloc(t_buffer*(sizeof(char)));
    char*result=(char*)malloc(t_buffer*(sizeof(char)));
    char* token;
    strcpy(copie,buffer);// copier le buffer sur dans une chaine 'copie'  car  strtok modifie la chaine
    token = strtok(copie," ");// traitement sur la copie du buffer car o aura besion de l original lors de la creation de la liste des medicament
    strcpy(result,token);
    strcat(result," ");
    token = strtok(NULL," ");
    strcat(result,token);
    return result;

}
//*****************************************************************************************
medicament* liste_medicaments(char*buffer) // retourne la liste des medicaments de chaque patient (ligne de fichier)
{
    char* token;
    medicament*p,*q,*tete;
    token=strtok(buffer," ");// ici le token est égale au nom
    token=strtok(NULL, " ");// ici le token  est égale au prénom
    token=strtok(NULL, " ");//ici le token  est égale au premier medicament  (id_du _medicament ou la marque)
    if((token!=NULL)&&(token[0]!='\n'))
    {
        tete=(medicament*)malloc(sizeof(medicament));
        tete->id_med=(char*)malloc((strlen(token))*sizeof(char));// allocation dynamique de l id du medicament
        strcpy(tete->id_med,token);
        token=strtok(NULL, " ");
        tete->quantite=atoi(token);
        tete->med_svt=NULL;
        q=tete;
        token=strtok(NULL, " ");
        while(token!=NULL)
        {
            p=(medicament*)malloc(sizeof(medicament));
            p->id_med=(char*)malloc((strlen(token))*sizeof(char));// allocation dynamique de l id du medicament
            strcpy(p->id_med,token);
            token=strtok(NULL, " ");
            p->quantite=atoi(token);
            p->med_svt=NULL;
            q->med_svt=p;
            q=p;
            token=strtok(NULL, " ");
        }
    }
    else
        tete=NULL;
    return tete;
}

//*****************************************************************************************
patient*liste_patients(FILE*F,char c)//la liste des patient dont leurs id commence par le caractére donné
{
    patient *t,*q,*p;
    char ch[t_buffer];
    int l;
    t=NULL;
    while(!feof(F))
    {
        fgets(ch,t_buffer,F);
        if(ch[0]==c)
        {
            if(t==NULL)
            {

                t=(patient*)malloc(sizeof(patient));
                l=strlen(nom_prenom(ch));
                t->id_pat=(char*)malloc(l*sizeof(char));// allocation dynamique de l id du patient
                strcpy(t->id_pat,nom_prenom(ch));
                t->pat_svt=NULL;
                t->pat_prec=NULL;
                t->liste_med=liste_medicaments(ch);
                q=t;
            }
            else
            {
                p=(patient*)malloc(sizeof(patient));
                l=strlen(nom_prenom(ch));
                p->id_pat=(char*)malloc(l*sizeof(char));
                strcpy(p->id_pat,nom_prenom(ch));
                p->pat_svt=NULL;
                q->pat_svt=p;
                p->pat_prec=q;
                p->liste_med=liste_medicaments(ch);
                q=p;
            }
        }
    }
    //ici on est en fin de fichier
    rewind(F);// ici on est au debut du fichier
    return t;
}
//*****************************************************************************************
void trie_liste_patients(patient*tete)// cette fonction trie la liste des patients
{
    patient*p,*q;
    p=tete;
    char *tmp;

    medicament*tmp_med;
    tmp=(char*)malloc((t_buffer)*sizeof(char));
    while(p->pat_svt!=NULL)
    {
        q=p->pat_svt;
        while(q!=NULL)
        {
            if(strcmp(p->id_pat,q->id_pat)>0)
            {
                strcpy(tmp,p->id_pat);
                tmp_med=p->liste_med;
                strcpy(p->id_pat,q->id_pat);
                p->liste_med=q->liste_med;
                strcpy(q->id_pat,tmp);
                q->liste_med=tmp_med;

            }
            else
                q=q->pat_svt;
        }
        p=p->pat_svt;
    }
}
//*****************************************************************************************
void afficher_medicaments(medicament*tete)// fonction qui afficher la liste des medicaments
{
    medicament*q=tete;
    if(q==NULL)
    {
        textcolor(12);
        puts("LISTE DE MEDICAMENTS NON DISPONIBLE ... !");// ce message est afficher en rouge
        textcolor(15);
    }
    else
    {
        while(q!=NULL)
        {

            puts(q->id_med);
            printf("%d\n",q->quantite);
            q=q->med_svt;
        }
    }

}
//*****************************************************************************************
void afficher_patients(patient*tete)//fonction qui afficher le liste des patients(nom et prenom)
{
    patient*q=tete  ;
    while(q!=NULL)
    {
        textcolor(2);
        puts(q->id_pat);// nom et prenom du patient en vert
        textcolor(15);
        afficher_medicaments(q->liste_med);// liste de medicament en blanc
        q=q->pat_svt;
    }

}
//*****************************************************************************************
patient*dernier(patient*premier) // fonction qui retourne le dernier patient
{
    patient*d;
    d=premier;
    while(d->pat_svt!=NULL)
    {
        d=d->pat_svt;
    }
    return d;
}

//*****************************************************************************************
H*structure(FILE*F)// creation de la structure
{
    H*tab=(H*)malloc(26*sizeof(H));
    int i;
    char c;
    patient*p;
    i=0; c='a';
    while((i<=25)&&(c<='z'))
    {
        tab[i].a=liste_patients(F,c);
        i++;
        c++;
    }
    for(i=0;i<=25;i++)
    {
        if(tab[i].a!=NULL)
        {
            trie_liste_patients(tab[i].a);
            tab[i].b=dernier(tab[i].a);
        }
    }

    return tab;
}
//*****************************************************************************************
patient*rechercher(H*tab,char*id)// fonction qui recherche un patient dont le nom et prenom égal a (id)
{
    patient*p;
    int i,flag,cmp;
    char j,c;
    c=id[0];
    j='a';
    while(j<c)
    {
        i++;
        j++;
    }
    p=tab[i].a;
    flag=0;
    while((p!=NULL)&&(flag==0))
    {
        cmp=strcmp(p->id_pat,id);
        if(cmp==0)
        {
            flag=1;
        }
        else
        {
            p=p->pat_svt;
        }
    }
    return p;
}
//*****************************************************************************************
medicament*rechercher_med(medicament*LM,char*id_m)//cette fonction rechercher un medicament donné
{
    medicament*m;
    int flag;
    int cmp;
    m=LM;
    flag=0;
    while((m!=NULL)&&((flag==0)))
    {
        cmp=strcmp(m->id_med,id_m);
        if(cmp==0)
        {
            flag=1;
        }
        else
        {
            m=m->med_svt;
        }
    }
    return m;
}
//*****************************************************************************************
medicament* medicament_patient(patient*p,char*id_m)// retourne la liste des medicaments du patient p donné
{
    medicament*m;
    m=rechercher_med(p->liste_med,id_m);
    return m;
}
//*****************************************************************************************
void ajuster(patient*p,medicament*m,int qte)//cette fonction ajuste effectue  quantité de medicament - qte donnée
{											//et  supprime le medicament si sa quantite égal a 0
    medicament*temp,*prec;
    m->quantite=m->quantite-qte;

    if(p->liste_med==m)
    {
        if(m->quantite==0)
        {
            temp=p->liste_med;
            p->liste_med=p->liste_med->med_svt;
            free(temp);
        }
    }
    else
    {
        if(m->quantite==0)
        {
            prec=p->liste_med;
            while(prec->med_svt!=m)
            {
                prec=prec->med_svt;
            }
            prec->med_svt=m->med_svt;
            free(m);
        }
    }

}
//*****************************************************************************************
patient*new_patient(char*ch)
{
    patient*p;
    int l;
    p=(patient*)malloc(sizeof(patient));
    l=strlen(nom_prenom(ch));
    p->id_pat=(char*)malloc(l*sizeof(char));// allocation dynamique de l id du patient
    strcpy(p->id_pat,nom_prenom(ch));
    p->pat_svt=NULL;
    p->pat_prec=NULL;
    p->liste_med=liste_medicaments(ch);

    return p;
}
//*****************************************************************************************
void inserer_patient(H*tab,patient*p)// cette fonction permet d inserer un patient
{
    int i;
    char j,c;
    patient*temp1,*temp2;
    c=p->id_pat[0];
    j='a';
    i=0;
    while(j<c)
    {
        i++;
        j++;
    }
    if(tab[i].a==NULL)
    {
        p->pat_svt=NULL;
        p->pat_prec=NULL;
        tab[i].a=p;
        tab[i].b=p;
    }
    else
    {

        if(strcmp(tab[i].a->id_pat,p->id_pat)>=0)
        {
            p->pat_svt=tab[i].a;
            p->pat_prec=NULL;
            tab[i].a->pat_prec=p;
            tab[i].a=p;
        }
        else
        {
            temp1=tab[i].a;
            temp2=tab[i].a->pat_svt;
            while(temp2!=NULL && strcmp(temp2->id_pat,p->id_pat)<=0 )
            {
                temp1=temp2;
                temp2=temp2->pat_svt;
            }
            p->pat_svt=temp1->pat_svt;;
            p->pat_prec=temp1;
            temp1->pat_svt=p;
            if(p->pat_svt==NULL)
            {
                tab[i].b=p;
            }
        }
    }

}
//*****************************************************************************************
void supprimer_patient(H*tab,patient*p)// cette fonction supprime un patient donnée
{
    patient*temp,*x,*y;
    int flag;
    char c,j;
    int i;
    c=p->id_pat[0];
    j='a';
    i=0;
    while(j<c)
    {
        i++;
        j++;
    }

    if(tab[i].a==p)
    {   //suppression en tete
        temp=p;
        p=p->pat_svt;
        if(p==NULL)
        {
            tab[i].b=NULL;
        }
        else
        {
            p->pat_prec=NULL;
        }
        tab[i].a=p;
        liberer_liste_med(temp->liste_med);
        free(temp);
    }
    else
    {
        temp=p;
        x=p->pat_prec;
        y=p->pat_svt;
        x->pat_svt=y;
        if(y==NULL)
        {
            tab[i].b=x;
        }
        else
        {
            y->pat_prec=x;
        }

        liberer_liste_med(temp->liste_med);
        free(temp);

    }
}
//*****************************************************************************************
void afficher_structure(H*tab, int i)// cette fonction affiche les patients qui se trouvent dans l indice i donné
{
    int j;
    char c;
    c='a';
    j=0;
    while(j<i)
    {
        j++;
        c++;
    }


    if(tab[i].a!=NULL)
    {
        textcolor(9);
        printf("		%c \n",c);
        printf("		***\n");
        textcolor(15);
        afficher_patients(tab[i].a);

    }
    else
    {
        textcolor(12);
        printf("		%c \n",c);
        printf("		***\n");
        textcolor(15);

        puts("NULL ... !");
    }

}

//=========================================================================================
void main()
{
    int cpt,c,j,i,qte,flag;
    char fichier[t_buffer];
    char seek[t_buffer];//patient a rechercher
    char med[t_buffer];//medicament a rechercher
    char info[t_buffer];// nom prenom med1 qt1 med2 qt2 ....
    char fin[]="PROJET REALISE PAR : \n DJENNAOUI RAOUF  ";
    FILE*F;
    H*tab;
    patient*p;
    medicament*m;
    puts("DONNER LE NOM DU FICHIER : ");
    gets(fichier);
    F=fopen(fichier,"r");
    if(test_fichier(F)==1)
    {
        tab=structure(F);
        progress_bar();
    }
    else
    {
        system("pause");
        exit(EXIT_FAILURE);
    }

    while(1)
    {
        i=0;
        system("cls");
        c=menu();
        system("cls");
//*****************************************************************************************
        if(c==1)// affichage 4 par 4  a chaque fois que l user selectionne le premier choix
        {

            flag=1;
            while(flag==1)
            {
                cpt=0;
                while((i<26)&&(cpt<4))
                {
                    afficher_structure(tab,i);
                    cpt++;
                    i++;
                }
                puts("VOULEZ VOUS CONTINUER L AFFICHAGE (1/0) ? ");
                scanf("%d",&flag);
                if(i>25)
                {
                    textcolor(12);
                    puts("ATTENTION ... AFFICHAGE TERMINER");
                    textcolor(15);
                }
            }
        }
//*****************************************************************************************
        if(c==2)// rechercher d un patient
        {
            puts("DONNER L ID DU PATIENT QUE VOUS RECHERCHEZ :");
            gets(seek);
            p=rechercher(tab,seek);


            if(p==NULL)
            {
                textcolor(12);
                puts("CE PATIENT N EXISTE PAS DANS LA LISTE");
                textcolor(15);
            }
            else
            {
                textcolor(9);
                puts("CE PATIENT EXISTE DANS LA LISTE");
                textcolor(15);
                if(p->liste_med!=NULL)
                {
                    puts("LA LISTE DE MEDICAMENT DU PATIENT");
                    printf("\n");
                    textcolor(15);
                    textcolor(9);
                    afficher_medicaments(p->liste_med);
                    textcolor(15);
                }
                else
                {
                    afficher_medicaments(p->liste_med);
                }
                textcolor(15);
            }
        }
//*****************************************************************************************
        if(c==3)//suppression d un patients
        {
            puts("DONNER L ID DU PATIENT A SUPPRIMER :");
            gets(seek);
            p=rechercher(tab,seek);
            if(p!=NULL)
            {
                supprimer_patient(tab,p);
            }
            else
            {
                textcolor(12);
                puts("PATIENT NON DISPONIBLE ... !");
                textcolor(15);
            }
        }
//*****************************************************************************************
        if(c==4)
        {
            puts("DONNER LES INFORMATIONS SUR LE PATIENT :");
            gets(info);
            p=new_patient(info);
            inserer_patient(tab,p);
        }
//*****************************************************************************************
        if(c==5)//consomation
        {

            puts("DONNER LE NOM DU CONSOMATEUR :");
            gets(seek);
            p=rechercher(tab,seek);
            if(p!=NULL)
            {
                puts("DONNER L ID DU MEDICAMENT CONSOMME :");
                gets(med);
                m=medicament_patient(p,med);
                if(m!=NULL)
                {
                    do
                    {
                        puts("DONNER LA QUANTITE CONSOMMEE :");
                        scanf("%d",&qte);
                    }while(qte>m->quantite);
                    ajuster(p,m,qte);
                }
                else
                {
                    textcolor(12);
                    puts("MEDICAMENT NON DISPONIBLE ... !");
                    textcolor(15);
                }
                getchar();
            }
            else
            {
                textcolor(12);
                puts("PATIENT NON DISPONIBLE ... !");
                textcolor(15);
            }
        }
//*****************************************************************************************
        if(c==6)//quiter & liberer le vecteur
        {
            for(j=0;j<=25;j++)
            {

                liberer_liste_patient(tab[j].a);//liberer le contenu du tableau
            }
            free(tab);
            int s= 12;
            gotoxy(26,11);
            textcolor(10);
            for(i=0;i<strlen(fin);i++)
            {

                printf("%c",fin[i]);
                if(fin[i]=='\n')
                {
                    gotoxy(26,s);
                    s++;
                }
                Sleep(450);
            }
            textcolor(15);
            exit(EXIT_SUCCESS);

        }
        puts("APPUYER SUR UNE TOUCHE POUR CONTINUER");
        getchar();
    }
    system("pause");
}


