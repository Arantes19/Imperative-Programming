#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM 100

typedef struct atleta
{
    int codigo1, codigo2, codigo3;
    char nome[50];
    int contacto;
    int idade;
    int data1, data2, data3;
    char atividade[50];
    char planoatividade[50];
    int duração;
    int km;
    int datainicio1, datainicio2, datainicio3;
    int horainicio1, horainicio2;
    int datafim1, datafim2, datafim3;
    int horafim1, horafim2;
    int meta;
    char medida2[25], medida3[25];
}Atleta;


int menu()
{int opcao;
    do
    {  
        printf("\t\t\nM E N U\n");
        printf("1-Carregar dados\n");
        printf("2-Numero de atletas que realizaram determinada atividade, num determinado periodo\n");
        printf("3-Listar atletas, de ordem decrescente que realizaram alguma atividade, num determinado periodo\n");
        printf("4-Apresentar plano de atividades para um determinado periodo, atividade e praticante\n");
        printf("5-Media dos tempos de cada praticante\n");
        printf("6-Gerar tabela de atividades planeadas e realizadas\n");
        printf("7-Gerar tabela da avaliacao de um determinado periodo de tempo\n");
        printf("8-Exportar tabela da avaliacao para um ficheiro binario\n");
        printf("0-Sair\n");
        printf("Opcao?");
        scanf("%d",&opcao);
    } while ((opcao<0)||(opcao>8));
    return(opcao);
}

int ExportarDadosBin(Atleta Lista[])
{
    FILE *finp;
    FILE *fout;
    unsigned int cod, d1, d2, d3, d4, d5, d6, dt, tt, dd1, dd2, dd3, di1, di2, di3, df1, df2, df3;
    char nome[25], medidad[25], medidat[25];
    unsigned char buffer[256];
    unsigned int num;
    int i, len;

    finp = fopen("tabela_avaliacao.txt", "r");
    fout = fopen("tabela_avaliacao.bin", "wb");

    while((len = fgetc(finp))!= EOF)
    {
        fread(buffer, len, 1, finp);
        buffer[len] ='\0';
        num |= (unsigned int)fgetc(finp) <<24;
        num |= fgetc(finp) << 16; 
        num |= fgetc(finp) << 8;
        num |= fgetc(finp);
        fprintf(fout, "%s %d\n", (char*)buffer, num);
    }
    
    /*while(1)
    {
        fscanf(finp, "%d %s %d %d %d %d %d %d %d %s %d %s %d %d %d\n", &cod, nome, &d1, &d2, &d3, &d4,
                                        &d5, &d6, &dt, medidad, &tt, medidat,
                                        &dd1, &dd2, &dd3, di1, di2, di3, df1, df2, df3
                                        );
        if(feof(finp))
            break;
        fwrite(&cod, sizeof(struct atleta), 1, fout);
        fwrite(nome, (strlen(nome)+1), sizeof(char), fout);
        fwrite(&d1,  1, sizeof(unsigned int), fout);
        fwrite(&d2,  1, sizeof(unsigned int), fout);
        fwrite(&d3,  1, sizeof(unsigned int), fout);
        fwrite(&d4,  1, sizeof(unsigned int), fout);
        fwrite(&d5,  1, sizeof(unsigned int), fout);
        fwrite(&d6,  1, sizeof(unsigned int), fout);
        fwrite(&dt,  1, sizeof(unsigned int), fout);
        fwrite(medidad, (strlen(medidad)+1), sizeof(char), fout);
        fwrite(&tt,  1, sizeof(unsigned int), fout);
        fwrite(medidat,(strlen(medidat)+1), sizeof(char), fout);
        fwrite(&dd1,  1, sizeof(unsigned int), fout);
        fwrite(&dd2,  1, sizeof(unsigned int), fout);
        fwrite(&dd3,  1, sizeof(unsigned int), fout);
    }*/
    
    fclose(finp);
    fclose(fout);
}
/// @brief Consuma esta sub-rotina para gerar uma tabela das atividadas planeadas e realizadas
/// @param Lista 
/// @param quantidade 
/// @return tabela_informacao.txt
int GerarTabela1(Atleta Lista[], int quantidade)
{FILE* fp;
 int i=0;
 fp = fopen("tabela_informacao.txt","w");
    if (fp != NULL)
    {
        fprintf( fp, "|---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|\n");
        fprintf( fp, "|\t\tCodigo\t\t|\t\tNome\t\t|\t\tAtividade Planeada\t\t|\t\tValor/medida\t\t|\t\tAtividade Realizada\t\t|\t\tData Inicio\t\t|\t\tData Fim\t\t|\t\tValor/medida\t\t|\n");
        fprintf( fp, "|---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|\n");
        do
        {
            fprintf( fp, "|\t\t%d\t\t|\t\t%s\t\t|\t\t\t%s\t\t\t\t|\t\t\t%d%s\t\t\t|\t\t\t%s\t\t\t\t|\t\t%d-%d-%d\t\t|\t\t%d-%d-%d\t\t|\t\t\t%d%s\t\t\t\t|\n", 
                                                                    Lista[i].codigo1,
                                                                    Lista[i].nome, 
                                                                    Lista[i].planoatividade, 
                                                                    Lista[i].meta, 
                                                                    Lista[i].medida3, 
                                                                    Lista[i].atividade, 
                                                                    Lista[i].datainicio1, 
                                                                    Lista[i].datainicio2, 
                                                                    Lista[i].datainicio3, 
                                                                    Lista[i].datafim1, 
                                                                    Lista[i].datafim2, 
                                                                    Lista[i].datafim3, 
                                                                    Lista[i].km, 
                                                                    Lista[i].medida2);
                for (int j = i+1; j < quantidade; j++)
                {
                    if ((Lista[i].codigo1 == Lista[j].codigo3) && (Lista[j].codigo3 > 0))
                    {
                         fprintf( fp, "|\t\t%d\t\t|\t\t%s\t\t|\t\t\t%s\t\t\t\t|\t\t\t%d%s\t\t\t|\t\t\t%s\t\t\t\t|\t\t%d-%d-%d\t\t|\t\t%d-%d-%d\t\t|\t\t\t%d%s\t\t\t\t|\n", 
                                                                    Lista[j].codigo3,
                                                                    Lista[i].nome, 
                                                                    Lista[j].planoatividade, 
                                                                    Lista[j].meta, 
                                                                    Lista[j].medida3, 
                                                                    Lista[i].atividade, 
                                                                    Lista[j].datainicio1, 
                                                                    Lista[j].datainicio2, 
                                                                    Lista[j].datainicio3, 
                                                                    Lista[j].datafim1, 
                                                                    Lista[j].datafim2, 
                                                                    Lista[j].datafim3, 
                                                                    Lista[i].km, 
                                                                    Lista[i].medida2);
                    }
                }
                fprintf( fp, "|---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|\n");       
            i++;
        } while(!feof(fp) && (Lista[i].codigo1 >0));
        fclose(fp);
        return(i);
    }
    else return(-1);
        printf("Erro a ler o ficheiro!!");
}

/// @brief Consuma esta sub-rotina para gerar uma tabela da avaliação das atividades realizadas
/// @param Lista 
/// @param quantidade 
/// @return tabela_avaliacao.txt
int GerarTabela2(Atleta Lista[], int quantidade)
{
    FILE* fp;
    int i=0, di1, di2, di3, df1, df2, df3, daysoffeb1, daysoffeb2, daysoffeb3, daysi=0, daysf=0, daysL=0, dayD1, dayD2, dayD3, total, tempo, maiorKm;
    printf("\nIntroduza a data inicial:(d m a) ");
    scanf("%d-%d-%d", &di1, &di2, &di3);
    printf("\nIntroduza a data final:(d m a) ");
    scanf("%d-%d-%d", &df1, &df2, &df3);
    if ((di3%4 == 0) && (di3%100 != 0) || (di3%400 == 0))
        daysoffeb1 = 29;
    else
        daysoffeb1 = 28;

    switch (di2)
    {
        case 1:
                daysi += di1;
                break;
        case 2:
                daysi += 31+di1;
            break;
        case 3:
                daysi += 31+daysoffeb1+di1;
            break;
        case 4:
                daysi += 31+daysoffeb1+31+di1;
            break;
        case 5:
                daysi += 31+daysoffeb1+31+30+di1;
             break;
        case 6:
                daysi += 31+daysoffeb1+31+30+31+di1;
             break;
        case 7:
                daysi += 31+daysoffeb1+31+30+31+30+di1;
            break;
        case 8:
                daysi += 31+daysoffeb1+31+30+31+30+31+di1;
            break;
        case 9:
                daysi += 31+daysoffeb1+31+30+31+30+31+31+di1;
            break;
        case 10:
                daysi += 31+daysoffeb1+31+30+31+30+31+31+30+di1;
            break;
        case 11:
                daysi += 31+daysoffeb1+31+30+31+30+31+31+30+31+di1;
            break;
        case 12:
                daysi += 31+daysoffeb1+31+30+31+30+31+31+30+31+30+di1;
            break;
    }

    if ((df3%4 == 0) && (df3%100 != 0) || (df3%400 == 0))
        daysoffeb2 = 29;
    else
        daysoffeb2 = 28;

    switch (df2)
    {
        case 1: 
            daysf += df1;
            break;
        case 2:
                daysf += 31+df1;
            break;
        case 3:
                daysf += 31+daysoffeb2+df1;
            break;
        case 4:
                daysf += 31+daysoffeb2+31+df1;
            break;
        case 5:
                daysf += 31+daysoffeb2+31+30+df1;
             break;
        case 6:
                daysf += 31+daysoffeb2+31+30+31+df1;
             break;
        case 7:
                daysf += 31+daysoffeb2+31+30+31+30+df1;
            break;
        case 8:
                daysf += 31+daysoffeb2+31+30+31+30+31+df1;
            break;
        case 9:
                daysf += 31+daysoffeb2+31+30+31+30+31+31+df1;
            break;
        case 10:
                daysf += 31+daysoffeb2+31+30+31+30+31+31+30+df1;
            break;
        case 11:
                daysf += 31+daysoffeb2+31+30+31+30+31+31+30+31+df1;
            break;
        case 12:
                daysf += 31+daysoffeb2+31+30+31+30+31+31+30+31+30+df1;
            break;
    }

    if ((daysi < daysf))
    {
        fp = fopen("tabela_avaliacao.txt","w");
        if (fp != NULL)
        {
            fprintf(fp, "|---------------------------------------------------------------------------------------------------------------------------------------------------------------|\n");
            fprintf(fp, "|\tN.Participante\t|\t\tNome\t\t|\t\tData Inicio\t\t|\t\tData Fim\t\t|\tDistancia total\t\t|\tTempo total\t\t|\t\t\tDia D\t\t\t|\n");
            fprintf(fp, "|---------------------------------------------------------------------------------------------------------------------------------------------------------------|\n");
            do
            {
                tempo = 0;
                total = 0;
                daysL = 0;
                if ((Lista[i].data3%4 == 0) && (Lista[i].data3%100==0) || (Lista[i].data3%400 == 0))
                daysoffeb3 = 29;
                else
                daysoffeb3 = 28;

                switch (Lista[i].data2)
                {
                    case 1: 
                        daysL += Lista[i].data1;
                            break;
                    case 2:
                        daysL += 31+Lista[i].data1;
                            break;
                    case 3:
                        daysL += 31+daysoffeb3+Lista[i].data1;
                            break;
                    case 4:
                        daysL += 31+daysoffeb3+31+Lista[i].data1;
                            break;
                    case 5:
                        daysL += 31+daysoffeb3+31+30+Lista[i].data1;
                            break;
                    case 6:
                        daysL += 31+daysoffeb3+31+30+31+Lista[i].data1;
                            break;
                    case 7:
                        daysL += 31+daysoffeb3+31+30+31+30+Lista[i].data1;
                            break;
                    case 8:
                        daysL += 31+daysoffeb3+31+30+31+30+31+Lista[i].data1;
                            break;
                    case 9:
                        daysL += 31+daysoffeb3+31+30+31+30+31+31+Lista[i].data1;
                            break;
                    case 10:
                        daysL += 31+daysoffeb3+31+30+31+30+31+31+30+Lista[i].data1;
                            break;
                    case 11:
                        daysL += 31+daysoffeb3+31+30+31+30+31+31+30+31+Lista[i].data1;
                            break;
                    case 12:
                        daysL += 31+daysoffeb3+31+30+31+30+31+31+30+31+30+Lista[i].data1;
                            break;
                }

                if ((daysi < daysL) && (daysL < daysf))
                {
                    dayD1 = Lista[i].data1;
                    dayD2 = Lista[i].data2;
                    dayD3 = Lista[i].data3;
                    maiorKm = Lista[i].km;
                    total += Lista[i].km;
                    tempo += Lista[i].duração;
                    for (int j = i+1; j < quantidade; j++)
                    { 
                        if ((Lista[i].codigo1 == Lista[j].codigo2) && (Lista[j].codigo2 > 0) && (Lista[j].km >= maiorKm)) //para deixar total tempo e total km a funcionar -> delete (Lista[j].km >= maiorKm)
                        {
                            total += Lista[j].km;
                            tempo += Lista[j].duração;
                            dayD1 = Lista[j].data1;
                            dayD2 = Lista[j].data2;
                            dayD3 = Lista[j].data3;
                            maiorKm = Lista[j].km;

                            /*if (Lista[j].km >= maiorKm)
                            {
                                dayD1 = Lista[j].data1;
                                dayD2 = Lista[j].data2;
                                dayD3 = Lista[j].data3;
                                maiorKm = Lista[j].km;
                            }*/
                            
                        }
                    }
 
                    fprintf(fp,"|\t\t%d\t\t|\t\t%s\t\t|\t\t%d-%d-%d\t\t|\t\t%d-%d-%d\t\t|\t\t\t%d%s\t\t\t|\t\t%dh\t\t\t|\t\t%d-%d-%d\t\t\t|\n", Lista[i].codigo1,
		                        Lista[i].nome,
		                        di1, di2, di3,
                                df1, df2, df3, total, Lista[i].medida2, tempo, 
                                dayD1, dayD2, dayD3);
                    fprintf(fp, "|---------------------------------------------------------------------------------------------------------------------------------------------------------------|\n");
                }
                i++;
                
            }while(!feof(fp) && (Lista[i].codigo1 > 0)); 
            fclose(fp);
            return(i);
        }
        else return(-1);
        printf("Erro a ler o ficheiro!!");
    }
    else
    printf("Data inicial maior que data final!");
}

/// @brief Leitura dos dados do ficheiro 1
/// @param Lista 
/// @return tabela_informacao.txt
int lerDadosFile1(Atleta Lista[])
{FILE* fp;
 int i=0;
 fp = fopen("file1.txt","rt");  // read text
 if (fp != NULL)
 {
  do
  {
  fscanf(fp,"%d;%[^;];%d;%d\n", &Lista[i].codigo1,
		                        Lista[i].nome,
		                        &Lista[i].contacto,
		                        &Lista[i].idade);
  i++;
  } while(!feof(fp));
  fclose(fp);
 return(i);
 }
 else return(-1);
 printf("Erro a ler o ficheiro!!");
}

/// @brief Leitura dos dados do ficheiro 2
/// @param Lista 
/// @return 
int lerDadosFile2(Atleta Lista[])
{FILE* fp;
 int i=0;
 fp = fopen("file2.txt","rt");
 if (fp != NULL)
 {
  do
  {
  fscanf(fp,"%d;%d-%d-%d;%[^;];%d;%d%s\n", &Lista[i].codigo2,
		                        &Lista[i].data1,
                                &Lista[i].data2,
                                &Lista[i].data3,
		                        Lista[i].atividade,
		                        &Lista[i].duração,
                                &Lista[i].km,
                                &Lista[i].medida2);
  i++;
  } while(!feof(fp));
  fclose(fp);
 return(i);
 }
 else return(-1);
 printf("Erro a ler o ficheiro!!");
}

/// @brief Leitura dos dados do ficheiro 3
/// @param Lista 
/// @return 
int lerDadosFile3(Atleta Lista[])
{FILE* fp;
 int i=0;
 fp = fopen("file3.txt","rt");
 if (fp != NULL)
 {
  do
  {
  fscanf(fp,"%d;%d-%d-%d;%dh%d;%d-%d-%d;%dh%d;%[^;];%d%s\n",&Lista[i].codigo3,
                                &Lista[i].datainicio1,
                                &Lista[i].datainicio2,
                                &Lista[i].datainicio3,
		                        &Lista[i].horainicio1,
                                &Lista[i].horainicio2,
		                        &Lista[i].datafim1,
                                &Lista[i].datafim2,
                                &Lista[i].datafim3,
		                        &Lista[i].horafim1,
                                &Lista[i].horafim2,
                                &Lista[i].planoatividade,
                                &Lista[i].meta,
                                &Lista[i].medida3);
  i++;
  } while(!feof(fp));
  fclose(fp);
 return(i);
 }
 else return(-1);
 printf("Erro a ler o ficheiro!!");
}

/// @brief Sub-rotina responsável por contar os atletas que realizaram uma determinada atividade num determinado periodo
/// @param Lista 
/// @param quantidade 
void contaAtividade(Atleta Lista[], int quantidade)
{
    int i=0, di1, di2, di3, df1, df2, df3, daysoffeb1, daysoffeb2, daysoffeb3, daysi=0, daysf=0, daysL=0, dayD1, dayD2, dayD3;
    int ca = 0, tam1, tam2;
    char a[50];
    printf("\nAtividade: ");
    scanf("%s", &a);
    printf("\nIntroduza a data inicial:(d m a) ");
    scanf("%d-%d-%d", &di1, &di2, &di3);
    printf("\nIntroduza a data final:(d m a) ");
    scanf("%d-%d-%d", &df1, &df2, &df3);
    if ((di3%4 == 0) && (di3%100 != 0) || (di3%400 == 0))
        daysoffeb1 = 29;
    else
        daysoffeb1 = 28;

    switch (di2)
    {
        case 1:
                daysi += di1;
                break;
        case 2:
                daysi += 31+di1;
            break;
        case 3:
                daysi += 31+daysoffeb1+di1;
            break;
        case 4:
                daysi += 31+daysoffeb1+31+di1;
            break;
        case 5:
                daysi += 31+daysoffeb1+31+30+di1;
             break;
        case 6:
                daysi += 31+daysoffeb1+31+30+31+di1;
             break;
        case 7:
                daysi += 31+daysoffeb1+31+30+31+30+di1;
            break;
        case 8:
                daysi += 31+daysoffeb1+31+30+31+30+31+di1;
            break;
        case 9:
                daysi += 31+daysoffeb1+31+30+31+30+31+31+di1;
            break;
        case 10:
                daysi += 31+daysoffeb1+31+30+31+30+31+31+30+di1;
            break;
        case 11:
                daysi += 31+daysoffeb1+31+30+31+30+31+31+30+31+di1;
            break;
        case 12:
                daysi += 31+daysoffeb1+31+30+31+30+31+31+30+31+30+di1;
            break;
    }
    if ((df3%4 == 0) && (df3%100 != 0) || (df3%400 == 0))
        daysoffeb2 = 29;
    else
        daysoffeb2 = 28;

    switch (df2)
    {
        case 1: 
            daysf += df1;
            break;
        case 2:
                daysf += 31+df1;
            break;
        case 3:
                daysf += 31+daysoffeb2+df1;
            break;
        case 4:
                daysf += 31+daysoffeb2+31+df1;
            break;
        case 5:
                daysf += 31+daysoffeb2+31+30+df1;
             break;
        case 6:
                daysf += 31+daysoffeb2+31+30+31+df1;
             break;
        case 7:
                daysf += 31+daysoffeb2+31+30+31+30+df1;
            break;
        case 8:
                daysf += 31+daysoffeb2+31+30+31+30+31+df1;
            break;
        case 9:
                daysf += 31+daysoffeb2+31+30+31+30+31+31+df1;
            break;
        case 10:
                daysf += 31+daysoffeb2+31+30+31+30+31+31+30+df1;
            break;
        case 11:
                daysf += 31+daysoffeb2+31+30+31+30+31+31+30+31+df1;
            break;
        case 12:
                daysf += 31+daysoffeb2+31+30+31+30+31+31+30+31+30+df1;
            break;
    }
    for (int i = 0; i < quantidade; i++)
    {
        if(Lista[i].codigo2 > 0)
        {
            if ((Lista[i].data3%4 == 0) && (Lista[i].data3%100==0) || (Lista[i].data3%400 == 0))
            daysoffeb3 = 29;
            else
            daysoffeb3 = 28;

            switch (Lista[i].data2)
            {
            case 1: 
            daysL += Lista[i].data1;
                 break;
            case 2:
            daysL += 31+Lista[i].data1;
                break;
            case 3:
            daysL += 31+daysoffeb3+Lista[i].data1;
                break;
            case 4:
            daysL += 31+daysoffeb3+31+Lista[i].data1;
                break;
            case 5:
            daysL += 31+daysoffeb3+31+30+Lista[i].data1;
                break;
            case 6:
            daysL += 31+daysoffeb3+31+30+31+Lista[i].data1;
                break;
            case 7:
            daysL += 31+daysoffeb3+31+30+31+30+Lista[i].data1;
                break;
            case 8:
            daysL += 31+daysoffeb3+31+30+31+30+31+Lista[i].data1;
                break;
            case 9:
            daysL += 31+daysoffeb3+31+30+31+30+31+31+Lista[i].data1;
                break;
            case 10:
            daysL += 31+daysoffeb3+31+30+31+30+31+31+30+Lista[i].data1;
                break;
            case 11:
            daysL += 31+daysoffeb3+31+30+31+30+31+31+30+31+Lista[i].data1;
                break;
            case 12:
            daysL += 31+daysoffeb3+31+30+31+30+31+31+30+31+30+Lista[i].data1;
                break;
            }
            if ((daysi <= daysL) && (daysL <= daysf))
            {
                if (strcmp(Lista[i].atividade, a) == 0)
                {
                ca++;
                }
            }
            daysL = 0;
        }
    }
    printf("\nO numero de atletas que praticam %s e: %d\n\n", a, ca);
}

/// @brief Através desta sub-rotina é listado os atletas pela ordem decrescente do seu código de acordo com um certo periodo de tempo
/// @param Lista 
/// @param quantidade    
void listarEquipaDecrescente(Atleta Lista[], int quantidade)
{
    int di1, di2, di3, df1, df2, df3, daysoffeb1, daysoffeb2, daysoffeb3, daysi=0, daysf=0, daysL=0, dayD1, dayD2, dayD3;
    int i = 0, maiorcodigo1, maiorcodigo2, maiorcodigo3, mcontact, mage, md1, md2, md3, mdu, mkm;
    int mdi1, mdi2, mdi3, mdf1, mdf2, mdf3, mhi1, mhi2, mhf1, mhf2, mm;
    char ma[50], mmedi2[25];

    printf("\nIntroduza a data inicial:(d m a) ");
    scanf("%d-%d-%d", &di1, &di2, &di3);
    printf("\nIntroduza a data final:(d m a) ");
    scanf("%d-%d-%d", &df1, &df2, &df3);
    if ((di3%4 == 0) && (di3%100 != 0) || (di3%400 == 0))
        daysoffeb1 = 29;
    else
        daysoffeb1 = 28;

    switch (di2)
    {
        case 1:
                daysi += di1;
                break;
        case 2:
                daysi += 31+di1;
            break;
        case 3:
                daysi += 31+daysoffeb1+di1;
            break;
        case 4:
                daysi += 31+daysoffeb1+31+di1;
            break;
        case 5:
                daysi += 31+daysoffeb1+31+30+di1;
             break;
        case 6:
                daysi += 31+daysoffeb1+31+30+31+di1;
             break;
        case 7:
                daysi += 31+daysoffeb1+31+30+31+30+di1;
            break;
        case 8:
                daysi += 31+daysoffeb1+31+30+31+30+31+di1;
            break;
        case 9:
                daysi += 31+daysoffeb1+31+30+31+30+31+31+di1;
            break;
        case 10:
                daysi += 31+daysoffeb1+31+30+31+30+31+31+30+di1;
            break;
        case 11:
                daysi += 31+daysoffeb1+31+30+31+30+31+31+30+31+di1;
            break;
        case 12:
                daysi += 31+daysoffeb1+31+30+31+30+31+31+30+31+30+di1;
            break;
    }
    if ((df3%4 == 0) && (df3%100 != 0) || (df3%400 == 0))
        daysoffeb2 = 29;
    else
        daysoffeb2 = 28;

    switch (df2)
    {
        case 1: 
            daysf += df1;
            break;
        case 2:
                daysf += 31+df1;
            break;
        case 3:
                daysf += 31+daysoffeb2+df1;
            break;
        case 4:
                daysf += 31+daysoffeb2+31+df1;
            break;
        case 5:
                daysf += 31+daysoffeb2+31+30+df1;
             break;
        case 6:
                daysf += 31+daysoffeb2+31+30+31+df1;
             break;
        case 7:
                daysf += 31+daysoffeb2+31+30+31+30+df1;
            break;
        case 8:
                daysf += 31+daysoffeb2+31+30+31+30+31+df1;
            break;
        case 9:
                daysf += 31+daysoffeb2+31+30+31+30+31+31+df1;
            break;
        case 10:
                daysf += 31+daysoffeb2+31+30+31+30+31+31+30+df1;
            break;
        case 11:
                daysf += 31+daysoffeb2+31+30+31+30+31+31+30+31+df1;
            break;
        case 12:
                daysf += 31+daysoffeb2+31+30+31+30+31+31+30+31+30+df1;
            break;
    }
    
    for (int i = 0; i < quantidade; i++)
    {
        if ((Lista[i].codigo2 > 0))
	    {
            for (int j = i+1; j < quantidade; j++)
            {
                if (Lista[i].codigo2 < Lista[j].codigo2)
                {
                    maiorcodigo2 = Lista[i].codigo2;
                    Lista[i].codigo2 = Lista[j].codigo2;
                    Lista[j].codigo2 = maiorcodigo2;

                    md1 = Lista[i].data1;
                    Lista[i].data1 = Lista[j].data1;
                    Lista[j].data1 = md1;

                    md2 = Lista[i].data2;
                    Lista[i].data2 = Lista[j].data2;
                    Lista[j].data2 = md2;

                    md3 = Lista[i].data3;
                    Lista[i].data3 = Lista[j].data3;
                    Lista[j].data3 = md3;

                    strcpy(ma,Lista[i].atividade);
                    strcpy(Lista[i].atividade,Lista[j].atividade);
                    strcpy(Lista[j].atividade,ma);

                    mdu = Lista[i].duração;
                    Lista[i].duração = Lista[j].duração;
                    Lista[j].duração = mdu;

                    mkm = Lista[i].km;
                    Lista[i].km = Lista[j].km;
                    Lista[j].km = mkm;

                    strcpy(mmedi2,Lista[i].medida2);
                    strcpy(Lista[i].medida2,Lista[j].medida2);
                    strcpy(Lista[j].medida2,mmedi2);
                }
            }
        }
	}

    for (int i = 0; i < quantidade; i++)
    {
        if ((Lista[i].data3%4 == 0) && (Lista[i].data3%100==0) || (Lista[i].data3%400 == 0))
            daysoffeb3 = 29;
            else
            daysoffeb3 = 28;

        switch (Lista[i].data2)
            {
            case 1: 
            daysL += Lista[i].data1;
                 break;
            case 2:
            daysL += 31+Lista[i].data1;
                break;
            case 3:
            daysL += 31+daysoffeb3+Lista[i].data1;
                break;
            case 4:
            daysL += 31+daysoffeb3+31+Lista[i].data1;
                break;
            case 5:
            daysL += 31+daysoffeb3+31+30+Lista[i].data1;
                break;
            case 6:
            daysL += 31+daysoffeb3+31+30+31+Lista[i].data1;
                break;
            case 7:
            daysL += 31+daysoffeb3+31+30+31+30+Lista[i].data1;
                break;
            case 8:
            daysL += 31+daysoffeb3+31+30+31+30+31+Lista[i].data1;
                break;
            case 9:
            daysL += 31+daysoffeb3+31+30+31+30+31+31+Lista[i].data1;
                break;
            case 10:
            daysL += 31+daysoffeb3+31+30+31+30+31+31+30+Lista[i].data1;
                break;
            case 11:
            daysL += 31+daysoffeb3+31+30+31+30+31+31+30+31+Lista[i].data1;
                break;
            case 12:
            daysL += 31+daysoffeb3+31+30+31+30+31+31+30+31+30+Lista[i].data1;
                break;
            }
        if ((daysi < daysL) && (daysL < daysf))
        {
         printf("\n%d\t%d-%d-%d\t%s\t%d\t%d%s\n", Lista[i].codigo2,
		                        Lista[i].data1,
                                Lista[i].data2,
                                Lista[i].data3,
		                        Lista[i].atividade,
		                        Lista[i].duração,
                                Lista[i].km,
                                Lista[i].medida2);   
        }
        daysL=0;
    }
    
    /*for (int i = 0; i < quantidade; i++)
    {
        if ((Lista[i].codigo2 > 0))
	    {
            for (int j = i+1; j < quantidade; j++)
            {
                if (Lista[i].codigo2 < Lista[j].codigo2)
                {
                    maiorcodigo2 = Lista[i].codigo2;
                    Lista[i].codigo2 = Lista[j].codigo2;
                    Lista[j].codigo2 = maiorcodigo2;

                    md1 = Lista[i].data1;
                    Lista[i].data1 = Lista[j].data1;
                    Lista[j].data1 = md1;

                    md2 = Lista[i].data2;
                    Lista[i].data2 = Lista[j].data2;
                    Lista[j].data2 = md2;

                    md3 = Lista[i].data3;
                    Lista[i].data3 = Lista[j].data3;
                    Lista[j].data3 = md3;

                    strcpy(ma,Lista[i].atividade);
                    strcpy(Lista[i].atividade,Lista[j].atividade);
                    strcpy(Lista[j].atividade,ma);

                    mdu = Lista[i].duração;
                    Lista[i].duração = Lista[j].duração;
                    Lista[j].duração = mdu;

                    mkm = Lista[i].km;
                    Lista[i].km = Lista[j].km;
                    Lista[j].km = mkm;

                    strcpy(mmedi2,Lista[i].medida2);
                    strcpy(Lista[i].medida2,Lista[j].medida2);
                    strcpy(Lista[j].medida2,mmedi2);
                }
            }
        }
	}
    printf("\t\t\tListagem:\n\n");
    while(i<quantidade)
    {
        if ((Lista[i].codigo2 > 0))
	    {printf("%d\t%d-%d-%d\t%s\t%d\t%d%s\n", Lista[i].codigo2,
		                        Lista[i].data1,
                                Lista[i].data2,
                                Lista[i].data3,
		                        Lista[i].atividade,
		                        Lista[i].duração,
                                Lista[i].km,
                                Lista[i].medida2);
        }
        i++;
    }*/
}

/// @brief Através desta sub-rotina é listado o(s) plano(s) conforme o código do participante/atividade e periodo de tempo
/// @param Lista 
/// @param quantidade 
void apresentarplano(Atleta Lista[], int quantidade)
{
    int di1, di2, di3, df1, df2, df3, daysoffeb1, daysoffeb2, daysoffeb3, daysoffeb4, daysi=0, daysf=0, daysLi=0, daysLf = 0, p;
    char atividade[50];

    printf("\nCodigo do praticante: ");
    scanf("%d", &p);
    printf("\nIntroduza a atividade: ");
    scanf("%s", &atividade);
    printf("\nIntroduza a data inicial:(d m a) ");
    scanf("%d-%d-%d", &di1, &di2, &di3);
    printf("Introduza a data final:(d m a) ");
    scanf("%d-%d-%d", &df1, &df2, &df3);
    if ((di3%4 == 0) && (di3%100 != 0) || (di3%400 == 0))
        daysoffeb1 = 29;
    else
        daysoffeb1 = 28;

    switch (di2)
    {
        case 1:
                daysi += di1;
                break;
        case 2:
                daysi += 31+di1;
            break;
        case 3:
                daysi += 31+daysoffeb1+di1;
            break;
        case 4:
                daysi += 31+daysoffeb1+31+di1;
            break;
        case 5:
                daysi += 31+daysoffeb1+31+30+di1;
             break;
        case 6:
                daysi += 31+daysoffeb1+31+30+31+di1;
             break;
        case 7:
                daysi += 31+daysoffeb1+31+30+31+30+di1;
            break;
        case 8:
                daysi += 31+daysoffeb1+31+30+31+30+31+di1;
            break;
        case 9:
                daysi += 31+daysoffeb1+31+30+31+30+31+31+di1;
            break;
        case 10:
                daysi += 31+daysoffeb1+31+30+31+30+31+31+30+di1;
            break;
        case 11:
                daysi += 31+daysoffeb1+31+30+31+30+31+31+30+31+di1;
            break;
        case 12:
                daysi += 31+daysoffeb1+31+30+31+30+31+31+30+31+30+di1;
            break;
    }
    if ((df3%4 == 0) && (df3%100 != 0) || (df3%400 == 0))
        daysoffeb2 = 29;
    else
        daysoffeb2 = 28;

    switch (df2)
    {
        case 1: 
            daysf += df1;
            break;
        case 2:
                daysf += 31+df1;
            break;
        case 3:
                daysf += 31+daysoffeb2+df1;
            break;
        case 4:
                daysf += 31+daysoffeb2+31+df1;
            break;
        case 5:
                daysf += 31+daysoffeb2+31+30+df1;
             break;
        case 6:
                daysf += 31+daysoffeb2+31+30+31+df1;
             break;
        case 7:
                daysf += 31+daysoffeb2+31+30+31+30+df1;
            break;
        case 8:
                daysf += 31+daysoffeb2+31+30+31+30+31+df1;
            break;
        case 9:
                daysf += 31+daysoffeb2+31+30+31+30+31+31+df1;
            break;
        case 10:
                daysf += 31+daysoffeb2+31+30+31+30+31+31+30+df1;
            break;
        case 11:
                daysf += 31+daysoffeb2+31+30+31+30+31+31+30+31+df1;
            break;
        case 12:
                daysf += 31+daysoffeb2+31+30+31+30+31+31+30+31+30+df1;
            break;
    }
    
    printf("\n\n\t\t\tPlano de atividades\n\n");
    for (int i = 0; i < quantidade; i++)
    {
        if ((Lista[i].datainicio3%4 == 0) && (Lista[i].datainicio3%100==0) || (Lista[i].datainicio3%400 == 0))
            daysoffeb3 = 29;
            else
            daysoffeb3 = 28;

        if ((Lista[i].datafim3%4 == 0) && (Lista[i].datafim3%100==0) || (Lista[i].datafim3%400 == 0))
            daysoffeb4 = 29;
            else
            daysoffeb4 = 28;

        switch (Lista[i].datainicio2)
            {
            case 1: 
            daysLi += Lista[i].datainicio1;
                 break;
            case 2:
            daysLi += 31+Lista[i].datainicio1;
                break;
            case 3:
            daysLi += 31+daysoffeb3+Lista[i].datainicio1;
                break;
            case 4:
            daysLi += 31+daysoffeb3+31+Lista[i].datainicio1;
                break;
            case 5:
            daysLi += 31+daysoffeb3+31+30+Lista[i].datainicio1;
                break;
            case 6:
            daysLi += 31+daysoffeb3+31+30+31+Lista[i].datainicio1;
                break;
            case 7:
            daysLi += 31+daysoffeb3+31+30+31+30+Lista[i].datainicio1;
                break;
            case 8:
            daysLi += 31+daysoffeb3+31+30+31+30+31+Lista[i].datainicio1;
                break;
            case 9:
            daysLi += 31+daysoffeb3+31+30+31+30+31+31+Lista[i].datainicio1;
                break;
            case 10:
            daysLi += 31+daysoffeb3+31+30+31+30+31+31+30+Lista[i].datainicio1;
                break;
            case 11:
            daysLi += 31+daysoffeb3+31+30+31+30+31+31+30+31+Lista[i].datainicio1;
                break;
            case 12:
            daysLi += 31+daysoffeb3+31+30+31+30+31+31+30+31+30+Lista[i].datainicio1;
                break;
            }
        
        switch (Lista[i].datafim2)
            {
            case 1: 
            daysLf += Lista[i].datafim1;
                 break;
            case 2:
            daysLf += 31+Lista[i].datafim1;
                break;
            case 3:
            daysLf += 31+daysoffeb3+Lista[i].datafim1;
                break;
            case 4:
            daysLf += 31+daysoffeb3+31+Lista[i].datafim1;
                break;
            case 5:
            daysLf += 31+daysoffeb3+31+30+Lista[i].datafim1;
                break;
            case 6:
            daysLf += 31+daysoffeb3+31+30+31+Lista[i].datafim1;
                break;
            case 7:
            daysLf += 31+daysoffeb3+31+30+31+30+Lista[i].datafim1;
                break;
            case 8:
            daysLf += 31+daysoffeb3+31+30+31+30+31+Lista[i].datafim1;
                break;
            case 9:
            daysLf += 31+daysoffeb3+31+30+31+30+31+31+Lista[i].datafim1;
                break;
            case 10:
            daysLf += 31+daysoffeb3+31+30+31+30+31+31+30+Lista[i].datafim1;
                break;
            case 11:
            daysLf += 31+daysoffeb3+31+30+31+30+31+31+30+31+Lista[i].datafim1;
                break;
            case 12:
            daysLf += 31+daysoffeb3+31+30+31+30+31+31+30+31+30+Lista[i].datafim1;
                break;
            }

        if (((daysi <= daysLi) && (daysLi < daysf)) && ((daysi < daysLf)&&(daysLf <= daysf )))
        {
            if ((p == Lista[i].codigo3) && (strcmp(Lista[i].planoatividade, atividade)==0))
            {
                printf("%d\t%d-%d-%d\t%dh%d\t%d-%d-%d\t%dh%d\t%s\t%d%s\n", Lista[i].codigo3,
                                Lista[i].datainicio1,
                                Lista[i].datainicio2,
                                Lista[i].datainicio3,
		                        Lista[i].horainicio1,
                                Lista[i].horainicio2,
		                        Lista[i].datafim1,
                                Lista[i].datafim2,
                                Lista[i].datafim3,
		                        Lista[i].horafim1,
                                Lista[i].horafim2,
                                Lista[i].planoatividade,
                                Lista[i].meta,
                                Lista[i].medida3);
            }
        }
        daysLi=0;
        daysLf=0;
    }
}

/// @brief Através desta sub-rotina é calculado a média dos tempos para cada atleta
/// @param Lista 
/// @param quantidade 
void mediaTempos(Atleta Lista[], int quantidade )
{
    int p, count=0;
    float minutosini, minutosfim, horas=0;
    printf("\nPraticante: ");
    scanf("%d", &p);

    for (int i = 0; i < quantidade; i++)
    {
        if (p == Lista[i].codigo3)
        {
        minutosini = Lista[i].horainicio1*60;
        minutosini += Lista[i].horainicio2;

        minutosfim = Lista[i].horafim1*60;
        minutosfim += Lista[i].horafim2;

        horas += (minutosfim-minutosini)/60;
        count++;
        }        
    }
    printf("\n\n\t\t\tMedia dos tempos do praticante %d: %.2f\n\n", p, (horas/count));
}


int main()
{
    Atleta Lista[TAM];
    int quantidade = 0, opcao, r1, r2, r3;
    char atividade[50];
  do
  {opcao = menu();
   switch(opcao)
   {case 1:
        r1 = lerDadosFile1(Lista);
        if (r1!=-1)
	       {quantidade += r1;
	       }
	    else printf("\nInsucesso!");

        r2 = lerDadosFile2(Lista);
        if (r2 != -1)
	    {quantidade += r2;
	    }
	    else printf("\nInsucesso!");

        r3 = lerDadosFile3(Lista);
        if (r3 != -1)
	    {quantidade += r3;
		printf("\nSucesso! %d atletas carregados!\n\n", quantidade);
	    }
	    else printf("\nInsucesso!");

	    break;
    case 2: contaAtividade(Lista, quantidade);
	    break;
    case 3: listarEquipaDecrescente(Lista, quantidade);
	    break;
    case 4: apresentarplano( Lista, quantidade);
	    break;
    case 5: mediaTempos(Lista, quantidade);
	    break;
    case 6: GerarTabela1(Lista, quantidade);
	    break;
    case 7: GerarTabela2(Lista, quantidade);
	    break;
    case 8: ExportarDadosBin(Lista);
        break;
    default:
    }
  }
  while (opcao!=0);

  return 0;
}