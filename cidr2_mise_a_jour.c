#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

void entrer_cidr();
char* to_decimal(char * binaire,char *decimal);
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

char* binaire(char* a, int f)
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
    ///printf("%s", a);
    return a;
}

char* calcul_binaire(char * ip_binaire, char * mask_binaire,char * reseau)
{
		
		int i = 0;
		
		while(i< 32)
		{
				reseau[i] = ip_binaire[i] & mask_binaire[i]; 
				i++;
		}
		
		return reseau;
}

char* broad_initial(char * reseau,int sr_initial,char* broad)
{
	
	broad[0] = '\0'; 
	int i = 0;
	
	while(i < 32)
	 {
		 if(i < sr_initial)
		 {
			broad[i] = reseau [i];
			
			i++;
		}
	
		if(i >= sr_initial)
		{
				broad[i] = '1';
				i++;
		}
	}
	broad[i] = '\0';

	return broad;
}

void sous_reseau_broad(char * reseau_initial,char*broad_one,int decoupe,char * broad_fin_decimal)
{
		char reseau_second[100] = {0};
		char broad_next_decimal[100] = {0};
		char broad_next[100] = {0};
		char next_broad[100] = {0};
		char tmp_chaine_one[100] = {0};
		char tmp_chaine_two[100] = {0};
		char tmp_chaine_three[100] = {0};
		char tmp_chaine_four[100] = {0};
		char chaine[1000] = {0};
		char decimal[100] = {0};
		
		int one = 0;
		int two = 0;
		int three = 0;
		int four = 0;
		int a = 0;
		int b = 0;
		int c = 0;
		int d = 0;
		int k = 1;
			
		printf("\n\tadresse reseau a partir du masque => %s", reseau_initial);
		printf("\n\tadresse broadcast a partir du masque => %s", broad_fin_decimal);
		if (decoupe < 31)
		{	
		do
		{
		///vider les variables pour eviter les accumulation
		printf("\n\n\tsous reseau %d\n\t**********************************", k);
			reseau_second[0] = '\0';
			broad_next_decimal[0] = '\0';
			broad_next[0] = '\0';
			next_broad[0] = '\0';
			tmp_chaine_one[0] = '\0';
			tmp_chaine_two[0] = '\0';
			tmp_chaine_three[0] = '\0';
			tmp_chaine_four[0] = '\0';
			decimal[0] = '\0';
		
			printf("\nadresse sous reseau =%s", reseau_initial);
			printf("\nadresse broadcast = %s", broad_one);
		
			sscanf(broad_one ,"%d.%d.%d.%d" , &a,&b,&c,&d);
			
			if(d == 0)
			{
					c = c + 1;
			}
			if(d == 255)
			{
					d = 0;
					if(c == 255)
					{
							c = 0;
							if(b == 255)
							{
									b = 0;
							}
							else
							{
									b = b+1;
							}
							
					}
					else
					{
							c = c + 1;
					}
			}
						
				sprintf(reseau_second , "%d.%d.%d.%d", a,b,c,d);
				reseau_initial[0] = '\0';
				
				
				strcpy(reseau_initial,reseau_second);
			
			
				sscanf(reseau_initial, "%d.%d.%d.%d", &one,&two,&three,&four);
			
				ip_binaire(tmp_chaine_one,one);
				ip_binaire(tmp_chaine_two,two);
				ip_binaire(tmp_chaine_three,three);
				ip_binaire(tmp_chaine_four, four);
				chaine[0] = '\0';
			
				sprintf(chaine, "%s%s%s%s", tmp_chaine_one, tmp_chaine_two, tmp_chaine_three, tmp_chaine_four);
        
				strcat(broad_next,broad_initial(chaine,decoupe,next_broad));
			 
				strcat (broad_next_decimal,  to_decimal(broad_next,decimal));
			
				strcpy( broad_one , broad_next_decimal);
        
			k++;
			///assure l fin du boucle
			if (strcmp(broad_one, broad_fin_decimal) >= 0) 
			{
			printf("\n\n\tsous reseau %d\n\t**********************************", k);
			printf("\nadresse reseau =%s", reseau_second);
			printf("\nadresse broadcast = %s\n",broad_fin_decimal);
			
			
			return;
			}
				
		}while(strstr(broad_one, broad_fin_decimal) == NULL );
		printf("adresse broadcast = %s",broad_fin_decimal);
	}
	else
	{
				printf("\nfin decoupage ");
	}

    
}
int nombre_machine(int sr,int nbr,int sr_decoupe,int d)
{
	
	int hote_decoupe= 0;
	int  hote = 0;
	
	hote = 32 - sr;
	nbr = pow(2, hote) - 2;
	hote_decoupe = 32 - sr_decoupe;
	d = pow(2, hote_decoupe) - 2;
	printf("\t nombre de machine  => %d\n",nbr);
	printf("\t nombre de machine pour chaque sous_reseau  => %d\n",d);
	return nbr;
}

char* to_decimal(char * binaire,char *decimal)
{
		char decimal_one[100] = {0};
		char decimal_two[100] = {0};
		char decimal_three[100] = {0};
		char decimal_four[100] = {0};
		int one = 0;
		int two = 0;
		int three = 0;
		int four = 0;
		
		///extraction  binaire 
		strncpy(decimal_one, binaire, 8);
		strncpy(decimal_two, binaire + 8, 8);
		strncpy(decimal_three, binaire + 16, 8);
		strncpy(decimal_four, binaire + 24, 8);

	///convertie le binaire en decimale
		for(int i = 0; i <8 ; i++)
		{
			if (decimal_one[i] == '1')
			{
				one += pow(2, 7 - i);
			}
		}
		for(int i = 0; i < 8; i++)
		{
			if (decimal_two[i] == '1')
			{
				two += pow(2, 7 - i);
			}
		}
		for(int i = 0; i < 8; i++)
		{
			if (decimal_three[i] == '1')
			{
				three += pow(2, 7 - i);
			}
		}
		for(int i = 0; i < 8; i++)
		{
			if (decimal_four[i] == '1')
			{
				four += pow(2, 7 - i);
			}
		}	
    
		sprintf(decimal , "%d.%d.%d.%d", one,two,three,four);
	
		return decimal;
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
		char chaine_decoupe[100] = {0};
		char broad_fin [100] = {0};    
		char broad_one [100] = {0};
		char reseau_initial[100] = {0};
		char tmp_reseau [33] = {0};
		char broad[33] = {0};
		char decimal[100] = {0};
		char broad_decimal[100] = {0};
		char temp[33] = {0};
		int nbr = 0;
		int d =0;
    
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
			
			///ip en binaire		
			strcat(chaine , ip_binaire(tmp_chaine_one,one));
			strcat(chaine, ip_binaire(tmp_chaine_two,two));
			strcat(chaine , ip_binaire(tmp_chaine_three,three));
			strcat(chaine ,ip_binaire(tmp_chaine_four, four));
			
			
			mask(sr, maskchn);
			int n =0;
			printf("entrer le nombre de decoupe = " );
			scanf("%d",&n);
			char adresse_initial[100] = {0};
			 char decimal_first[100] = {0};
		   
			int sr_decoupe = 0;
			sr_decoupe = sr + n;
			mask(sr_decoupe , chaine_decoupe);
		
		   
		   strcat (reseau_initial , calcul_binaire(chaine, maskchn, tmp_reseau));
		   
		   strcat (broad_fin, broad_initial(reseau_initial,sr,broad));
		   
		   strcat(broad_one, broad_initial(reseau_initial,sr_decoupe,temp));
		
		   to_decimal(maskchn,decimal);
		   printf("\n\n\t masque de sous reseau => %s\n",decimal);
	
		   nombre_machine(sr,nbr,sr_decoupe,d);
		   
		   strcat(adresse_initial,to_decimal(reseau_initial,decimal_first));
		  
		   char broad_decimal_fin [100]= {0};
		   strcat(broad_decimal_fin ,to_decimal(broad_fin,broad_decimal));
		   char broad_first[100] = {0};
			strcat(broad_first, to_decimal(broad_one,broad_decimal));
		///juste pour verifier
		if (strcmp(broad_one, broad_decimal) >= 0) {
			printf("Reached the final broadcast address. Stopping recursion.\n");
			return;
		}
		sous_reseau_broad(adresse_initial,broad_first,sr_decoupe,broad_decimal_fin);
		
			printf("\n\t----thank you, finished----\n");
			

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


