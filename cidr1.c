#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

void entrer_cidr();
void enter_decoupage(int* decoupe)
{
    printf("\n\tEntrez le nombre de découpages successifs = ");
    scanf("%d", decoupe);
}

void* mask(int sous_reseau, char* chaine)
{
    for(int i = 0; i < 32; i++)
    {
        if(i < sous_reseau)
        {
            strcat(chaine, "1");
        }
        else
        {
            strcat(chaine, "0");
        }
    }
    return chaine;
}

char* ip_binaire(char* a, char f)
{
    int p = 0;
    int s = 0;

    for(int i = 7; i >= 0 ; i--)
    {
        p = pow(2, i);
        s = f - p;

        if(s >= 0)
        {
            f = s;
            strcat(a, "1");
        }
        else
        {
            strcat(a, "0");
        }
    }
    return a;
}

void afficher_masque_sous_reseau_decimal(char* masque_binaire)
{
    int masque[4] = {0};

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            masque[i] = masque[i] << 1;
            masque[i] += masque_binaire[i * 8 + j] - '0';
        }
    }

    printf("\nMasque de sous-réseau en décimal : %d.%d.%d.%d\n", masque[0], masque[1], masque[2], masque[3]);
}

void afficher_adresses_reseau(int decoupe, int sr_initial)
{
    int sous_reseaux = 0;
    int sr = 0; 
    int increment = 0;
  
	sous_reseaux = pow(2, decoupe) ;
	 sr = sr_initial + decoupe; 
	 increment = pow(2, 32 - sr);  
	 
    printf("\nAdresses réseau après %d découpages successifs:\n", decoupe);

    for(int i = 0; i < sous_reseaux; i++)
    {
        int adresse_reseau = i * increment;
        printf("Sous-réseau %d: %d.%d.%d.%d\n", i + 1, (adresse_reseau >> 24) & 0xFF,   (adresse_reseau >> 16) & 0xFF,  (adresse_reseau >> 8) & 0xFF, adresse_reseau & 0xFF);
        
    }
}

void afficher_adresses_broadcast(int decoupe, int sr_initial)
{
    int sous_reseaux = 0;
    int sr = 0; 
    int increment = 0;
  
	sous_reseaux = pow(2, decoupe) ;
	 sr = sr_initial + decoupe; 
	 increment = pow(2, 32 - sr);  

    printf("\nAdresses de broadcast après %d découpages successifs:\n", decoupe);

    for(int i = 0; i < sous_reseaux; i++)
    {
        int adresse_reseau = i * increment;
        int adresse_broadcast = adresse_reseau + increment - 1;
        printf("Broadcast Sous-réseau %d: %d.%d.%d.%d\n", i + 1,(adresse_broadcast >> 24) & 0xFF,(adresse_broadcast >> 16) & 0xFF,(adresse_broadcast >> 8) & 0xFF,adresse_broadcast & 0xFF);
            
    }
}

void verify_ip(char* cidr)
{   
    int i = 0;
    int n = 0;
    int p = 0 ;
    
    int one = 0;
    int two = 0;
    int three = 0;
    int four = 0;
    int sr = 0;
    char chaine[1000] = {0};
    char maskchn[33] = {0};
    
    char tmp_chaine_one[100] = {0};
    char tmp_chaine_two[100] = {0};
    char tmp_chaine_three[100] = {0};
    char tmp_chaine_four[100] = {0};
    
    while(cidr[i] != '\0')
    {
        if(cidr[i] == '.')
        {
            n++;
        }
        else if(cidr[i] == '/')
        {
            p++;
        }
        i++;
    }
    if(n == 3 && p == 1)
    {
        sscanf(cidr, "%d.%d.%d.%d/%d",&one,&two,&three,&four,&sr);
        
        strcat(chaine , ip_binaire(tmp_chaine_one,one));
        strcat(chaine, ip_binaire(tmp_chaine_two,two));
        strcat(chaine , ip_binaire(tmp_chaine_three,three));
        strcat(chaine ,ip_binaire(tmp_chaine_four, four));
        
        mask(sr, maskchn);
        afficher_masque_sous_reseau_decimal(maskchn);  // Afficher le masque en décimal
        printf("\n\t----binary conversion finished----\n");
        
        int decoupe = 0;
        enter_decoupage(&decoupe);
        afficher_adresses_reseau(decoupe, sr);
        afficher_adresses_broadcast(decoupe, sr);

        if(one < 0 || two < 0 || three < 0 || four < 0 || one > 255 || two > 255 || three > 255 || four > 255)
        {
            entrer_cidr();
        }
        
    }
    else
    {
        entrer_cidr();
    }
}

void entrer_cidr()
{
    char cidr[100] = {0};
    printf("Entrez Le CIDR (adresse IP / bits de réseau) = ");
    scanf("%s", cidr);
    
    verify_ip(cidr);
}
