#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "cryfs.h"
#include <assert.h>
#include <string.h>
#include <unistd.h>
#include "simpletest.h"

#define TESTDIR "kk00"

#define OK(a,b) printf("%s test%d:%d OK %s\n",KGRN,a,b,KNRM)
#define FAIL(a,b) printf("%s test%d:%d FAIL %s\n",KRED, a,b, KNRM)

/* quantos descritores de arquivo por bloco? */
#define NUM_DESCS (BLOCO/sizeof(descritor_t))

/* ultimo bloco para blocos livres */
#define METADADOS 20

const char teste[]="1234567890abcdefghijklmnoprstuvwxyz1234567890ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890abcdefghijklmnoprstuvwxyz1234567890ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890abcdefghijklmnoprstuvwxyz1234567890ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890abcdefghijklmnoprstuvwxyz1234567890ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890abcdefghijklmnoprstuvwxyz1234567890ABCDEFGHIJKLMNOPQRSTUVWXYZ";


char* concat(char *s1, char *s2)
{
    char *result = malloc(strlen(s1)+strlen(s2)+1);//+1 for the zero-terminator
    //in real code you would check for errors in malloc here
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}
int test1(){

  char * fsname;
  int grade = 0;

  DESCRIBE("Teste de criação de sistemas de arquivos");


  /* nome do arquivo sera testes/testexxx */
  assert(fsname = concat(TESTDIR, "test1"));

  IF("Eu crio um FS com poucos blocos");
  THEN("Não deve criar");
  /* poucos blocos */
  if (initfs(fsname, 5)==FALHA){
    OK(1,1);
    grade=5;
  }
  else{
    FAIL(1,1);
    if (unlink(fsname)){ /* mentiu sobre criacao do arquivo */
      grade=-5;
    }
  }


  /* quantidade razoavel de blocos */
  IF("Crio um FS com número razoável de blocos para dados e metadados");
  THEN("Deve criar");
  if (initfs(fsname, METADADOS*5)==SUCESSO){
    OK(1,2);
    grade+=5;
  }
  else {
      FAIL(1,2);
      /* nao tem como continuar */
      return 0;
  }
  return grade;
}

int test2(){

    char *fsname;
    int grade = 0;
    cry_desc_t * cryme;
    indice_arquivo_t  FH;

    int lengthy = strlen(teste) + 1; // para incluir o "\0"

    DESCRIBE("Testes básicos de criação e abertura de arquivos no FS criado");

    /* nome do arquivo sera testes/testexxx */
    assert(fsname = concat(TESTDIR, "test2"));

    /* quantidade razoavel de blocos */

    if (initfs(fsname, METADADOS*5)==SUCESSO){
      OK(2,1);
      // grade++;
    }
    else {
        FAIL(2,1);
        /* nao tem como continuar */
        return 0;
    }
    IF("Abro um FS criado");
    THEN("Deve abrir");

    cryme = cry_openfs(fsname);
    if (!cryme){
      FAIL(2,2);
      /*  nao tem como continuar */
      return 0;
    }
    else{
      OK(2,2);
      grade++;
    }

    IF("Abro um arquivo inexistente");
    THEN("Não deve abrir");
    /* deve falhar, arquivo ainda nao existe */
    FH = cry_open(cryme, "teste1", LEITURA, 0);

    if (FH==FALHA){
      OK(2,3);
      grade++;
    }
    else{
      FAIL(2,3);
    }

    /* deve falhar, ja que arquivo nao existe */
    FH = cry_open(cryme, "teste2", LEITURA, 3);
    if (FH==FALHA){
      OK(2,4);
      grade++;
    }
    else{
      FAIL(2,4);
    }

    IF("Abre um novo arquivo para escrita");
    THEN("Deve abrir");
    /* escreve um bloco */
    FH = cry_open(cryme, "teste3", ESCRITA, 3);
    if (FH==FALHA){
      FAIL(2,5);
    }
    else{
      OK(2,5);
      IF("Se escreve no arquivo");
      THEN("Deve escrever");
      if(cry_write(FH, lengthy, (char *) teste)==SUCESSO){
        char buffer[4096];
        cry_close(FH);

        THEN("Deve conseguir reabrir o arquivo");
        FH = cry_open(cryme, "teste3", LEITURA, 3);
        if (FH==FALHA){
          FAIL(2,6);
        }
        else OK(2,6);
        THEN("Deve conseguir ler o valor escrito no arquivo");

        if(cry_read(FH, lengthy, buffer)!=lengthy){
            FAIL(2,7);
        } else{
          OK(2,7);
          /* verifica se mesmo conteudo que escreveu */
          if (strcmp(buffer, teste)!=0){
            printf("buffer -- %s -- teste %s", buffer, teste);
            FAIL(2,8);
          }
          else{
            OK(2,8);
            grade++;
          }
        }
        cry_close(FH);

        IF("Abre com seek maior que o arquivo");
        THEN("Não deve abrir");
        /* abre com deslocamento errado */
        FH = cry_open(cryme, "teste3", LEITURA, 5);
        if (FH==FALHA){
          FAIL(2,9);
        }
        else OK(2,9);
        IF("Se tentar ler n bytes");
        THEN("Deve conseguir ler");
        if(cry_read(FH, strlen(teste), buffer)!=strlen(teste)){
            FAIL(2,10);
        } else{
          OK(2,10);
          /* verifica se mesmo conteudo que escreveu */
          /* se 2.8 falhou, aqui pode dar certo e falhar */
          THEN("Valor lido e armazenado devem ser iguais");
          if (strcmp(buffer, teste)==0){
            FAIL(2,11);
          }
          else{
            OK(2,12);
            grade++;
          }
        }

      }
      cry_close(FH);
    }
    return grade*2;
}



int test3(){

    char *fsname;
    int grade = 0;
    cry_desc_t * cryme;
    indice_arquivo_t  FH;

    char buffer[4096];
    int i;


    DESCRIBE("Testes com arquivos maiores");


    /* teste com um monte de a */
    for(i=0; i<4095; i++){
      buffer[i] = 'a';
    }
    buffer[4095]='\0';

    /* nome do arquivo sera testes/testexxx */
    assert(fsname = concat(TESTDIR, "test3"));

    /* quantidade razoavel de blocos */

    if (initfs(fsname, METADADOS+30)==SUCESSO){
      OK(3,1);
    }
    else {
        FAIL(3,1);
        /* nao tem como continuar */
        return grade;
    }

    cryme = cry_openfs(fsname);
    if (!cryme){
      FAIL(3,2);
      /*  nao tem como continuar */
      return grade;
    }
    else{
      OK(3,2);
    }

    IF("Eu escrevo até o fim dos blocos");
    THEN("Deve parar no último bloco de dados");

    /* escreve ate nao conseguir mais */
    FH = cry_open(cryme, "teste3", ESCRITA, 3);
    if (FH==FALHA){
      FAIL(3,3);
      return grade;
    }

    OK(3,3);
    uint32_t vezes = 0;

    while (cry_write(FH, 4096, buffer) == SUCESSO){
      //  printf("erro 1 \n");
      vezes++;
      if (vezes>30){ /*Escrevendo mais blocos que existem no FS */
        FAIL(3,4);
        return grade;
      }
    }
    if (vezes==0){
      FAIL(3,4);
      return grade;
    }
    OK(3,4);

    IF("Apago arquivo");
    THEN("Deve ser removido e blocos liberados");
    cry_delete(FH);


    FH = cry_open(cryme, "teste3", LEITURA, 3);
    if (FH==SUCESSO){ /* foi removido */
      FAIL(3,5);
      return grade;
    }
    OK(3,5);
    grade++;

    /* escreve vezes blocos - 1, deve ter que usar um bloco que foi liberado */

    FH = cry_open(cryme, "teste4", ESCRITA, 3);
    if (FH==FALHA){
      FAIL(3,7);
      return grade;
    }
    else OK(3,7);

    for(i=0; i<vezes; i++){
      if (cry_write(FH, 4096, buffer)==FALHA){
        FAIL(3,8);
        cry_close(FH);
        return grade;
      }
    }
    cry_close(FH);
    OK(3,8);
    grade+=2;

    IF("Escrevo o arquivo");
    THEN("O conteúdo não pode ter mudado");

    /* testa se escreveu bonitinho */
    FH = cry_open(cryme, "teste4", LEITURA, 3);
    if (FH==FALHA){
      FAIL(3,9);
      return grade;
    }
    OK(3,9);
    for(i=0; i<vezes; i++){
      char tmp[4096];
      printf("indice arq %d\n", FH);
      printf("nome desc %s\n", cryme->descritores[FH].nome);
      for (int i = 0; i < 4096; ++i)
      {
        tmp[i]=0;
      }
      
      if (cry_read(FH, 4096, tmp)==FALHA){
        FAIL(3,10);
        cry_close(FH);
        return grade;
      }
      if(strcmp(buffer,tmp)!=0){
          //printf("BUFFER -- %s \n TMP -- %s", buffer, tmp);
        FAIL(3,11);
        return grade+1;
      }
    }
    cry_close(FH);
    OK(3,10);
    OK(3,11);

    grade+=2;

    return grade;
}



/* Forca a parte de gerencia de blocos livres a se virar */




/* faz o show acontecer */
int main(int argc, char ** argv){

  int grades[6], maxgrades[6], pesos[6];
  float finalgrade = 0.0;

#define GRADEIT(x)\
  printf("TESTE %d - nota %d de %d, total %f\n", x, grades[x-1],\
   maxgrades[x-1], grades[x-1]/(float)maxgrades[x-1]); \
   finalgrade = finalgrade + (grades[x-1]/(float)maxgrades[x-1])*pesos[x-1];


  maxgrades[0]=10; pesos[0]=1;
  maxgrades[1]=10; pesos[1]=2;
  maxgrades[2]=10; pesos[2]=2;
  maxgrades[3]=10; pesos[3]=2;
  maxgrades[4]=10; pesos[4]=2;
  maxgrades[5]=10; pesos[5]=1;


  grades[0] = grades[1] = grades[2] = grades[3] = grades[4] = 0 ;grades[5] = 0; 

  assert(pesos[0]+pesos[1]+pesos[2]+pesos[3]+pesos[4]+pesos[5] == 10);

  grades[0]=test1();
  GRADEIT(1);
  grades[1]=test2();
  GRADEIT(2);
  grades[2]=test3();
  GRADEIT(3);
 

  printf("NOTA FINAL %.2f\n",finalgrade);

  return 0;
}