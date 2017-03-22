#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "cryfs.h"

int  atualizaDescritoresNovoArquivo(int totalBytes, char *nome, int acesso, FILE * filePointer, cry_desc_t * descritor);
void atualizaDescritoresArquivo(int acesso, int indiceDescritor, int indiceAberto, int tamanho, cry_desc_t * descritor);

cry_desc_t *currFileSys;
int tamanhoFat;
int *fat;
int numeroArquivosAbertos = 0;
int primeiroBloco[256] = {0};
FILE *ponteirosArquivos[256] = {NULL};
int totalBlocosUsados = 0;

int nain() {
	FILE *fp;
	char *nomeArquivo = "teste.bin";
	initfs(nomeArquivo, 100);

	int i;
	currFileSys = cry_openfs(nomeArquivo);


	
	indice_arquivo_t FH = cry_open(currFileSys, "sssss", LEITURA, 0);

	/* LEITURA
	for(i=0; i<256; i++){
//		printf("fat[%d]: %d\n", i, fat[i]);
	}

	int cpu = cry_open(currFileSys, "cpu_info", 0, 0);
	printf("primeiro bloco 0 %d\n", primeiroBloco[0]);
	printf("cpu: %d\n", cpu);
	char leitura[13403];

	printf("tamanho %d\n", currFileSys->descritores[0].tamanho);
	printf("nome %s\n", currFileSys->descritores[0].nome);
	printf("ult acesso %d\n", currFileSys->descritores[0].ultimo_acesso);
	printf("lidos %d\t\n", cry_read(0, 13403, leitura));
	//*/

	/*ESCRITA

	printf("sizeof(descritor %ld\n", sizeof(descritor_t));
	printf("sizeof(parametros) %ld\n", 256*sizeof(char) + sizeof(time_t) + sizeof(time_t) + sizeof(time_t) + sizeof(uint32_t));
	for(i=0; i<256; i++){
		printf("fat[%d]: %d\n", i, fat[i]);
	}
	indice_arquivo_t teste = cry_open(currFileSys, "cpu_info", 1, 0);	//0
	fp = fopen("cpu_info", "r");
	char buffer[8001];
	fread(buffer, 8000, sizeof(char), fp);
	int cpu1 = cry_write(0, 8000, buffer);
	//FILE *fp2 = fopen("cpu_out")
	//fwrite(buffer, 8000, sizeof(char), fp2);


	char buffer2[5404];
	fread(buffer2, 5404, sizeof(char), fp);
	int cpu2 = cry_write(0, 5403, buffer2);

	for(i=0; i<256; i++){
		printf("fat[%d]: %d\n", i, fat[i]);
	}

	printf("primeiro bloco[%d] = %d\n", 0, primeiroBloco[0] );
	/*
	char nome[256];
	time_t criacao, modificacao, ultimo_acesso;
	uint32_t tamanho;

	fseek(currFileSys->arquivo_host, 0, SEEK_SET);
	fread(nome, 256, sizeof(char), currFileSys->arquivo_host);
	printf("nomeArq %s\n",nome);

	fseek(currFileSys->arquivo_host, sizeof(char)*256, SEEK_SET);
	fread(&criacao, 1, sizeof(time_t), currFileSys->arquivo_host);
	printf("criacaoArq %ld\n",criacao);

	fseek(currFileSys->arquivo_host, sizeof(char)*256 + sizeof(time_t), SEEK_SET);
	fread(&modificacao, 1, sizeof(time_t), currFileSys->arquivo_host);
	printf("modificacaoArq %ld\n",modificacao);

	fseek(currFileSys->arquivo_host, sizeof(char)*256 + 2*sizeof(time_t), SEEK_SET);
	fread(&ultimo_acesso, 1, sizeof(time_t), currFileSys->arquivo_host);
	printf("uktAcesso %ld\n",ultimo_acesso);

	fseek(currFileSys->arquivo_host, sizeof(char)*256 + 3*sizeof(time_t), SEEK_SET);
	fread(&tamanho, 1, sizeof(uint32_t), currFileSys->arquivo_host);
	printf("tamanhoArq %d\n",tamanho);	
*/
//	uint32_t tamanhoBin;
//	fseek(currFileSys->arquivo_host)
	//fwrite(buffer2, 5403, sizeof(char), fp2);
	//*/

	/*
	indice_arquivo_t video = cry_open(currFileSys, "BasketballDrive_QP27_str.bin", 1, 0);//1
	char buffer3[525856];
	FILE *fp3 = fopen("BasketballDrive_QP27_str.bin", "r");
	fread(buffer3, 525855, sizeof(char), fp3);
	int drive = cry_write(1, 525855, buffer3);
	FILE *fp4 = fopen("str_out.bin", "wb");
	fwrite(buffer3, 525855, sizeof(char), fp4);

	//indice_arquivo_t teste2 = cry_open(currFileSys, "cpu_info", 1, 0);
	indice_arquivo_t video2 = cry_open(currFileSys, "k.txt", 1, 0);	//2
	//int close = cry_close(0);
	//indice_arquivo_t k = cry_open(currFileSys, "cpu_info", 1, 0);

	indice_arquivo_t hm = cry_open(currFileSys, "hm.txt", 1, 0); //3
	indice_arquivo_t img = cry_open(currFileSys, "img.png", 1, 0); //4
	
    char cpuInfo[13403];
    char kk[381];
    char hm2[2459];
    char img2[233769];

    FILE *fp_k = fopen("k.txt", "r");
    fread(kk, 381, sizeof(char), fp_k);
    int k_ret = cry_write(2, 381, kk);

    FILE *fp_hm = fopen("hm.txt", "r");
    fread(hm2, 2459, sizeof(char), fp_hm);

    int hm_ret = cry_write(3, 2459, hm2);

    FILE *fp_img2 = fopen("img.png", "r");
    fread(hm2, 233729, sizeof(char), fp_img2);
    int img2_ret = cry_write(4, 233729, hm2);
*/
	

	/*printf("FAT ANTES DELETE\n");
	for(i = 0; i < 256; i++) {
		//printf("fat[%d]: %d\n", i, fat[i]);
	}		

	//int deleteCPU = cry_delete(0);
	//printf("\nDELETE CPU\n");
	for(i = 0; i < 256; i++) {
		//printf("fat[%d]: %d\n", i, fat[i]);
	}		
	//int deleteBin = cry_delete(1);
	printf("\nDELETE BIN\n");
	for(i = 0; i < 256; i++) {
		printf("fat[%d]: %d\n", i, fat[i]);
	}	
	//int deletek = cry_delete(2);
	printf("SEGUNDO DELETE\n");
	for(i = 0; i < 256; i++) {
		//printf("fat[%d]: %d\n", i, fat[i]);
	}	
	//int deletehm = cry_delete(3);
	printf("TERCEIRO DELETE\n");
	for(i = 0; i < 256; i++) {
		printf("fat[%d]: %d\n", i, fat[i]);
	}	
	int deleteimg = cry_delete(4);
	printf("QUARTO DELETE\n");
	for(i = 0; i < 256; i++) {
		printf("fat[%d]: %d\n", i, fat[i]);
	}
	
	//int i;
	//for(i = 0; i < 256; i++) {
	//	printf("fat[%d]: %d\n", i, fat[i]);
	//}

	printf(">> %d\n", teste);
	printf(">> %d\n", video);
	printf(">> %d\n", teste2);
	printf(">> %d\n", video2);
	printf(">> %d\n", k);
    
	printf("@@ %d\n", deleteCPU);
	printf("@@ %d\n", deleteBin);
	printf("@@ %d\n", deletek);
	printf("@@ %d\n", deletehm);
	printf("@@ %d\n", deleteimg);*/


    //printf("lidos %d\t%s\n", cry_read(0, 13403, cpuInfo), cpuInfo);
    //printf("lidos %d\t%s\n", cry_read(1, 525855, buffer3), buffer3); 
	//printf("lidos %d\t%s\n", cry_read(2, 381, kk), kk);
	//printf("lidos-HM %d\t%s\n", cry_read(3, 2459, hm2), hm2);
	//printf("lidos0-IMG %d\t%s\n", cry_read(4, 233729, img2), img2);
	
	//indice_arquivo_t punk = cry_open(currFileSys, "arq_30kb", 1, 0);	//0

	for(i = 0; i < 256; i++) {
		//printf("fat[%d]: %d\n", i, fat[i]);
	}	

	return 0;

}

/** Inicializa o arquivo no sistema de arquivos hospedeiro.
 *
 *  Deve ser chamada apenas uma vez para um determinado sistema de arquivos.
 *  Caso o nome de arquivo já exista, deve retornar erro.
 *  Também deve retornar erro caso o número de blocos não seja o suficiente
 *  para armazenar os metadados pelo menos.
 *
 *  @param arquivo nome do arquivo no sistema de arquivos hospedeiro
 *  @param blocos número de blocos do arquivo
 *  @return SUCCESSO ou FALHA
 */
int initfs(char * arquivo, int blocos) {
	int i;
	//tamanhoFat = blocos - 19 - (blocos-19)/1024;
	tamanhoFat = blocos - 20;
	FILE *fp;
	char *zeros;
	fat = (int *) malloc(sizeof(int) * blocos);
	
	if(blocos < 21){	//SE TENTAR CRIAR FS COM MENOS BLOCOS DO QUE O MINIMO (19 META, 1 FAT E 1 DADO)	
		return FALHA;
	}

	if((fp = fopen(arquivo, "wb")) == NULL)
		return FALHA;
	else {
		zeros = (char*) malloc(BLOCO * blocos);

		for(i = 0; i < BLOCO * blocos; i++) {
			zeros[i] = 0;
		}

		fwrite(zeros, sizeof(char), BLOCO * blocos, fp);

		for(i = 0; i < tamanhoFat; i++) {
			if(i < tamanhoFat-1)
				fat[i] = i + 1;
			else
				fat[i] = 0;
			//printf("init fat[%d] %d\n", i, fat[i]);	
		}


		fseek(fp, BLOCO * 19, SEEK_SET);

		fwrite(fat, sizeof(int), sizeof(int) * tamanhoFat, fp);


		//for(i=0; i<tamanhoFat; i++)
			//printf("fat[%d]: %d\n", i, fat[i]);
		fclose(fp);
		return SUCESSO;
	}
}

/** Abre um sistema de arquivos.
 *
 *  @param nome do arquivo no sistema de arquivos hospedeiro
 *  @return ponteiro para descritor de sistema de arquivos ou FALHA
 */
cry_desc_t * cry_openfs(char * arquivo) {
	int i;
	FILE *fp;
	cry_desc_t *fileSystem = (cry_desc_t *) malloc(sizeof(cry_desc_t));

	fp = fopen(arquivo, "r+");
	fileSystem->arquivo_host = fp;

	fseek(fp, 0, SEEK_SET); // volta pro inicio do arquivo

	for(i = 0; i < 256; i++) {
		fread(fileSystem->descritores[i].nome, sizeof(char), 256, fp);
		fread(&fileSystem->descritores[i].criacao, sizeof(time_t), 1, fp);
		fread(&fileSystem->descritores[i].modificacao, sizeof(time_t), 1, fp);
		fread(&fileSystem->descritores[i].ultimo_acesso, sizeof(time_t), 1, fp);
		fread(&fileSystem->descritores[i].tamanho, sizeof(uint32_t), 1, fp);
		fileSystem->abertos[i].arquivo = NULL; // inicializa os arquivos abertos com 0
	}

	fseek(fp, 19 * BLOCO, SEEK_SET); // posiciona seek na fat
	//######################################################################
	//TEMPORARIO AJUSTAR
	fat = (int *) malloc(sizeof(int) * tamanhoFat);
	//TEMPORARIO AJUSTAR
	//######################################################################	
	fread(fat, sizeof(int), tamanhoFat, fp);
		for(i=0; i<256; i++){
		//printf("fat[%d]: %d\n", i, fat[i]);
		}
	currFileSys = fileSystem;
	return fileSystem;
}

/** Fecha um arquivo criptografado.
 *
 * @param arquivo índice para a tabela de arquivos abertos
 * @return SUCESSO OU FALHA
 */
int cry_close(indice_arquivo_t arquivo) {
	if(currFileSys->abertos[arquivo].arquivo == NULL) { //não existe
		//printf("FALHA\n");
		return FALHA;
	}
	else { // existe
		currFileSys->abertos[arquivo].arquivo = NULL;
		fclose(ponteirosArquivos[arquivo]);
		ponteirosArquivos[arquivo] = NULL;

		return SUCESSO;
	}
}

/** Escreve bytes em um arquivo criptografado aberto.
 *
 * A escrita é sempre realizada no modo append, ou seja, no fim do arquivo.
 *
 * @param arquivo índice para a tabela de arquivos abertos
 * @param tamanho número de bytes a serem escritos
 * @param buffer ponteiro para conteúdo a ser escrito
 * @return SUCESSO ou FALHA
 */
int cry_write(indice_arquivo_t arquivo, uint32_t tamanho, char *buffer) {
	int contadorBytes = 0, trocaBlocoLivre, blocoAtual, posAtualBloco, contadorAux = 0, i, j;
	char temp[tamanho];

	if(totalBlocosUsados + ceil(tamanho/4096) >= tamanhoFat){
		return FALHA;	//não existem mais blocos livres
	}
	
	if(currFileSys->descritores[arquivo].tamanho == -1) { //printf("ARQUIVO NOVO\n");
		if(tamanho < BLOCO) { //printf("< 1 bloco\n");

			/* ATUALIZA A TABELA DE PRIMEIRO BLOCO */
			blocoAtual = fat[0];
			primeiroBloco[arquivo] = blocoAtual;
			trocaBlocoLivre = fat[blocoAtual];
			fat[0] = trocaBlocoLivre;

			/* ATUALIZA FAT */
			fseek(currFileSys->arquivo_host, BLOCO * 19, SEEK_SET);
			fwrite(fat, sizeof(uint8_t), sizeof(uint8_t) * 256, currFileSys->arquivo_host);

			/* ESCREVE ARQUIVO NO FS */
			fseek(currFileSys->arquivo_host, BLOCO * (19 + blocoAtual), SEEK_SET);
			//printf("tamanho: %d-%d", blocoAtual, BLOCO * (20 + blocoAtual));
			fwrite(buffer, sizeof(char), tamanho, currFileSys->arquivo_host);
			
			atualizaDescritoresArquivo(-1, arquivo, 1, tamanho, currFileSys);
		     
	     	totalBlocosUsados++;	//incrementa o total de blocos usados no FS
			fat[blocoAtual] = 0;


			return SUCESSO;
		}
		else { printf("+ 1 bloco\n");
			blocoAtual = fat[0];
			primeiroBloco[arquivo] = fat[0];
			//printf("BLOCO ATUAL: %d", blocoAtual);
			trocaBlocoLivre = fat[blocoAtual];
			fat[0] = trocaBlocoLivre;

			posAtualBloco = 0;
			//contadorAux = posAtualBloco;
			printf("bloco atual %d\n", blocoAtual);
			while(contadorBytes < tamanho){
				for(j = 0; j < 4096; j++) {
					temp[j] = buffer[contadorBytes];
					contadorBytes++;
					contadorAux++;

					if(contadorBytes == tamanho) {
						break;
					}
					if(contadorAux == BLOCO) {
						break;
					}
				}

				/* ESCREVE BLOCO NO SISTEMA DE ARQUIVOS */
				fseek(currFileSys->arquivo_host, BLOCO * (19 + blocoAtual) + posAtualBloco, SEEK_SET);

				fwrite(temp, sizeof(char), contadorAux, currFileSys->arquivo_host);
	     		totalBlocosUsados++;	//incrementa o total de blocos usados no FS
					

				contadorAux = 0;
				posAtualBloco = 0;

				if(contadorBytes != tamanho) {
					fat[blocoAtual] = fat[0];
					blocoAtual = fat[blocoAtual];
					trocaBlocoLivre = fat[blocoAtual];
					fat[0] = trocaBlocoLivre;
				}
				else {
					trocaBlocoLivre = fat[blocoAtual];
					fat[blocoAtual] = 0;
					fat[0] = trocaBlocoLivre;
				}

			}
			fat[blocoAtual] = 0; // último bloco que foi escrito

			/* ATUALIZA FAT */
			fseek(currFileSys->arquivo_host, BLOCO * 19, SEEK_SET);
			fwrite(fat, sizeof(uint8_t), sizeof(uint8_t) * 256, currFileSys->arquivo_host);
			atualizaDescritoresArquivo(-1, arquivo, 1, tamanho, currFileSys);

			return SUCESSO;
		}		
	}
	else { //printf("ARQUIVO EXISTE\n");
		blocoAtual = primeiroBloco[arquivo];

		for(i = 0; i < ceil((float)currFileSys->descritores[arquivo].tamanho/BLOCO); i++) {
			if(fat[blocoAtual] == 0)
				break;
			blocoAtual = fat[blocoAtual];
		}

		posAtualBloco = currFileSys->descritores[arquivo].tamanho % BLOCO;

		contadorAux = posAtualBloco;

		while(contadorBytes < tamanho){
			for(j = 0; j < 4096; j++) {
				temp[j] = buffer[contadorBytes];
				contadorBytes++;
				contadorAux++;

				if(contadorAux == BLOCO){
			     	totalBlocosUsados++;	//incrementa o total de blocos usados no FS
					break;
				}
				if(contadorBytes == tamanho){
			     	totalBlocosUsados++;	//incrementa o total de blocos usados no FS
					break;
				}
			}

			/* ESCREVE BLOCO NO SISTEMA DE ARQUIVOS */
			fseek(currFileSys->arquivo_host, BLOCO * (19 + blocoAtual) + posAtualBloco, SEEK_SET);
			fwrite(temp, sizeof(char), contadorAux - posAtualBloco, currFileSys->arquivo_host);

			contadorAux = 0;
			posAtualBloco = 0;

			//blocoAtual = fat[0];
			if(contadorBytes != tamanho) {
				fat[blocoAtual] = fat[0];
				blocoAtual = fat[blocoAtual];
				trocaBlocoLivre = fat[blocoAtual];
				fat[0] = trocaBlocoLivre;
			}
			else { 
				trocaBlocoLivre = fat[blocoAtual];
				fat[blocoAtual] = 0;
				fat[0] = trocaBlocoLivre;

			}
		}


		fat[blocoAtual] = 0; // último bloco que foi escrito

		/* ATUALIZA FAT */
		fseek(currFileSys->arquivo_host, BLOCO * 19, SEEK_SET);
		fwrite(fat, sizeof(uint8_t), sizeof(uint8_t) * 256, currFileSys->arquivo_host);
		atualizaDescritoresArquivo(-1, arquivo, 1, tamanho, currFileSys);

		return SUCESSO;
	}		
}

/** Modifica a posição atual de leitura ou escrita do arquivo
 *
 * @param arquivo índice para a tabela de arquivos abertos
 * @param seek deslocamento em relação ao início do arquivo 
 * @return SUCESSO ou FALHA
 */
int cry_seek(indice_arquivo_t arquivo, uint32_t seek) {
	if(currFileSys->abertos[arquivo].arquivo == NULL)
		return FALHA;

	int i, blocoSeek = primeiroBloco[arquivo];
	int numeroBlocosUsados = ceil((float)(seek)/BLOCO);
	int seekDentroBloco = seek % BLOCO;

	if(seek > currFileSys->descritores[arquivo].tamanho)
		return FALHA;
	else {
		for(i = 0; i < numeroBlocosUsados; i++) {
			blocoSeek = fat[blocoSeek];

			if(i < (numeroBlocosUsados - 1) && blocoSeek == 0)
				return FALHA;
		}

		fseek(ponteirosArquivos[arquivo], BLOCO * (20 + blocoSeek) + seekDentroBloco, SEEK_SET);
		currFileSys->abertos[arquivo].posicao = ftell(ponteirosArquivos[arquivo]);

		return SUCESSO;
	}
}

/** Apaga um arquivo e o fecha.
 *
 * @param arquivo índice para a tabela de arquivos abertos
 * @return SUCESSO ou FALHA
 */
int cry_delete(indice_arquivo_t arquivo) { 
	if(currFileSys->abertos[arquivo].arquivo == NULL)
		return FALHA;

	int i, blocoAtual = primeiroBloco[arquivo], blocoAux;
	char zero = 0;

	while(blocoAtual != 0) {
		printf("bloco: %d\n", blocoAtual);
		fseek(currFileSys->arquivo_host, BLOCO * (20 + blocoAtual), SEEK_SET);
		
		for(i = 0; i < 4096; i++)
			fwrite(&zero, sizeof(char), 1, currFileSys->arquivo_host);
		
		blocoAtual = fat[blocoAtual];
	}

	blocoAtual = primeiroBloco[arquivo];
	
	for(i = 0; i < ceil((float)currFileSys->descritores[arquivo].tamanho/BLOCO); i++) {
		blocoAux = fat[blocoAtual];
		fat[blocoAtual] = fat[0];
		fat[0] = blocoAtual;
		blocoAtual = blocoAux;
	}

	for(i=0; i<256; i++)
		currFileSys->descritores[arquivo].nome[i] = '\0';
	totalBlocosUsados = totalBlocosUsados - (ceil((float)currFileSys->descritores[arquivo].tamanho/4096));

	fclose(ponteirosArquivos[arquivo]);
	ponteirosArquivos[arquivo] = NULL;

	return SUCESSO;
}


int atualizaDescritoresNovoArquivo(int totalBytes, char *nome, int acesso, FILE * filePointer, cry_desc_t * descritor) {
	/* ATUALIZA DESCRITOR DE ARQUIVO */
	int fileIndex, primeiroLivre;
	for(fileIndex = 1; fileIndex < 256; fileIndex++){
		if(descritor->descritores[fileIndex].tamanho == 0){
			primeiroLivre = fileIndex;
            //printf("primeiro livre %d\n", primeiroLivre);
			break;	
		}
	}
	
	/* SALVA PONTEIRO DO ARQUIVO */
	ponteirosArquivos[primeiroLivre] = filePointer;

	strcpy(descritor->descritores[primeiroLivre].nome, nome);
	time(&descritor->descritores[primeiroLivre].criacao);
	time(&descritor->descritores[primeiroLivre].modificacao);
	time(&descritor->descritores[primeiroLivre].ultimo_acesso);
	descritor->descritores[primeiroLivre].tamanho = totalBytes;

	fseek(descritor->arquivo_host, sizeof(descritor_t) * primeiroLivre, SEEK_SET);
	
	fwrite(descritor->descritores[primeiroLivre].nome, sizeof(char), 256, descritor->arquivo_host);
	fwrite(&descritor->descritores[primeiroLivre].criacao, sizeof(time_t), 1, descritor->arquivo_host);
	fwrite(&descritor->descritores[primeiroLivre].modificacao, sizeof(time_t), 1, descritor->arquivo_host);
	fwrite(&descritor->descritores[primeiroLivre].ultimo_acesso, sizeof(time_t), 1, descritor->arquivo_host);
	fwrite(&descritor->descritores[primeiroLivre].tamanho, sizeof(uint32_t), 1, descritor->arquivo_host);

	descritor->abertos[primeiroLivre].acesso = acesso;
	descritor->abertos[primeiroLivre].posicao = ftell(filePointer);
	descritor->abertos[primeiroLivre].arquivo = &descritor->descritores[primeiroLivre];
	if(primeiroLivre == 0)
		return -1;
	else
		return primeiroLivre;
}

void atualizaDescritoresArquivo(int acesso, int indiceDescritor, int indiceAberto, int tamanho, cry_desc_t * descritor) {
	//printf("indice descritor %d\n", indiceDescritor);
	/* SE O TAMANHO FOR -1 (RESERVADO), SOMA A PARTIR DE ZERO */
	/* SENAO, INCREMENTA */
	if((int) descritor->descritores[indiceDescritor].tamanho < 0){
		descritor->descritores[indiceDescritor].tamanho = tamanho;
	}
	else{
		descritor->descritores[indiceDescritor].tamanho += tamanho;	
	}
	
	
	time(&descritor->descritores[indiceDescritor].ultimo_acesso);

	fseek(descritor->arquivo_host, (sizeof(descritor_t) * indiceDescritor) + 256 + sizeof(time_t)*2, SEEK_SET);	//seta seek para posicao de ultimo acesso
	fwrite(&descritor->descritores[indiceDescritor].ultimo_acesso, sizeof(time_t), 1, descritor->arquivo_host);

	fseek(descritor->arquivo_host, (sizeof(descritor_t) * indiceDescritor) + 256 + sizeof(time_t)*3, SEEK_SET);	//seta seek para posicao de tamanho
	fwrite(&descritor->descritores[indiceDescritor].tamanho, sizeof(uint32_t), 1, descritor->arquivo_host);

	descritor->abertos[indiceAberto].acesso = acesso;
	//currFileSys->abertos[indiceAberto].posicao = ftell(filePointer);
	descritor->abertos[indiceAberto].arquivo = &descritor->descritores[indiceDescritor];
}

/** Lê bytes de um arquivo criptografado aberto.
 *
 * @param arquivo índice para a tabela de arquivos abertos
 * @param tamanho número de bytes a serem lidos
 * @param buffer ponteiro para buffer onde serão armazenados os bytes lidos
 * @return número de bytes lidos
 */
uint32_t cry_read(indice_arquivo_t arquivo, uint32_t tamanho, char *buffer) {
	//nao usada
	//FILE * arquivoLeitura = ponteirosArquivos[arquivo];
	printf("cry_read\n");
	//printf("nome arquivo parametro %s\n", currFileSys->abertos[arquivo]->arquivo->nome);
	//printf("nome arquivo parametro %s\n", currFileSys->abertos[arquivo].arquivo->nome);
	for(int b=0; b<256; b++){
	//	printf("nome arquivo desc   %d: %s\n",b,  currFileSys->descritores[b].nome);
	//	printf("nome arquivo aberto %d: %s\n",b,  currFileSys->abertos[b].arquivo->nome);
	}

	int numLidos;//, k;
	if(currFileSys->abertos[arquivo].arquivo != NULL) { 
		printf("NAO NULL\n");
		if(currFileSys->descritores[arquivo].tamanho <= 4096){
			//printf("<1 bloco\n");
			//int seekArquivo = currFileSys->abertos[arquivo].posicao; // ARRUMAAAAAAAARRRRRRRR ISSO
			int seekArquivo = 0;

			if(seekArquivo + tamanho <= 4096) {
				fseek(currFileSys->arquivo_host, BLOCO * (primeiroBloco[arquivo] + 20) + seekArquivo, SEEK_SET); 

				numLidos = fread(buffer, sizeof(char), tamanho, currFileSys->arquivo_host);

				//printf("buffer read: %s\n", buffer);
				printf("num lidos\n");
				return numLidos;	
			}
			else{	//SEEK DO ARQUIVO + NUMERO DE BYTES EXTRAPOLA TAMANHO DO ARQUIVO
				return FALHA;
			}
		}
		else { 
			//printf("+1 bloco\n");
			//nao utilizado
			//int numBlocos = ceil(((float) currFileSys->descritores[arquivo].tamanho)/BLOCO);
			int i, contadorBytes = 0, blocoAtual = primeiroBloco[arquivo], contadorAux = 0;
			char aux;
			
			//int seekArquivo = currFileSys->abertos[arquivo].posicao;
			int seekArquivo = 0;
			int numeroBlocos = seekArquivo/BLOCO;

			/* PERCORE A FAT ATÉ CHEGAR NO BLOCO CORRESPONDENTE AO SEEK */
			for(i=0; i<numeroBlocos; i++){
				blocoAtual = fat[blocoAtual];
			}
			

			fseek(currFileSys->arquivo_host, BLOCO * (blocoAtual + 20) + seekArquivo, SEEK_SET);

			int restoBloco = BLOCO - (seekArquivo % BLOCO);

			if(seekArquivo/BLOCO > 0) {
				contadorAux = restoBloco;
			}

			while(contadorBytes < tamanho) {
				/* LÊ CONTEÚDO PARA 1 BLOCO OU MENOS */
				while(fread(&aux, 1, 1, currFileSys->arquivo_host)) {
					buffer[contadorBytes] = aux;
					printf("%c", buffer[contadorBytes]);
					contadorBytes++;
					contadorAux++;

					if(contadorAux == BLOCO || contadorBytes == tamanho){
						//printf("contAux%d\tcontBytes %d\n", contadorAux, contadorBytes);
						break;
					}
				}
				contadorAux = 0;
				blocoAtual = fat[blocoAtual];

				fseek(currFileSys->arquivo_host, BLOCO * (blocoAtual + 20), SEEK_SET);
			}

			printf("num lidos\n");
			return contadorBytes;
		}		
	}
	else{	//o indice do arquivo passado nao está aberto
		printf("é NULL\n");
		return FALHA;
	}
}

/** Abre um arquivo criptografado.
 *
 *
 * @param cry_desc o descritor do sistema de arquivos criptografado
 * @param nome o arquivo a ser aberto
 * @param acesso LEITURA, ESCRITA ou LEITURAESCRITA
 * @param chave deslocamento a ser usado nos acessos
 * @return índice do arquivo aberto, FALHA se não abrir
 */
indice_arquivo_t cry_open(cry_desc_t *cry_desc, char * nome,  int acesso, char deslocamento) {
	//printf("open arquivo %s\n", nome);
	int j, k;
	//int totalBytesArquivo = 0, contadorBytes = 0;
	int valorRetornoIndiceArquivo;
	//int contadorAux = 0; retorno = 0; // parada da leitura dos blocos e bloco incompleto - cry_write
	//uint8_t blocoLivre, trocaBlocoLivre;
	int existeArq = 0;
	//indice_arquivo_t teste;
	FILE *fp;
	//char *buffer, temp[BLOCO], aux, *bufferUmBloco;
	//int pi;
	//for(pi = 0; pi < 256; pi++) {
//		printf("fat[%d]: %d\n", pi, fat[pi]);
	//}

	//printf("nome %s\n", currFileSys->descritores[0].nome);
        
	//buffer = (char *) malloc(sizeof(char));
	for(j = 0; j < 256; j++) {
		//printf("j %d\n", j);
		if(!(strcmp(cry_desc->descritores[j].nome, nome))) {
			existeArq = 1;
			printf("descritor coincide: %d\n", j);
			break;
		}
	}

	for(k = 0; k < 256; k++) {
		if(cry_desc->abertos[k].arquivo == NULL){
			printf("aberto disponpivel %d\n", k);
			break;
		}
	}
	/*######################################## ARQUIVO EXISTE ########################################*/
	if(existeArq == 1) { printf("EXISTE ARQUIVO\n");
			if(acesso == LEITURA) { //printf("EXISTE LEITURA\n");
				if((fp = fopen(nome, "rb")) == NULL) 
					return FALHA;
				else {
					cry_desc->abertos[k].arquivo = &cry_desc->descritores[j];
					cry_desc->abertos[k].acesso = acesso;

					atualizaDescritoresArquivo(acesso, j, k, 0, cry_desc);
					ponteirosArquivos[k] = fp;
					
                    if(j == 0)
                    	return -1;
                    else
						return (indice_arquivo_t) j;
				}
			}

			if(acesso == ESCRITA) { //printf("EXISTE ESCRITA\n");
				fp = fopen(nome, "r+");

				cry_desc->abertos[j].arquivo = &cry_desc->descritores[j];
				cry_desc->abertos[j].acesso = acesso;

				atualizaDescritoresArquivo(acesso, j, k, 0, cry_desc);	//AQUIIIIIII
				ponteirosArquivos[k] = fp;


                if(j == 0)
                	return -1;
                else
					return (indice_arquivo_t) j;
			}

			if(acesso == LEITURAESCRITA) {//printf("EXISTE LEITURAESCRITA\n");
				fp = fopen(nome, "r+");

				cry_desc->abertos[j].arquivo = &cry_desc->descritores[j];
				cry_desc->abertos[j].acesso = acesso;

				atualizaDescritoresArquivo(acesso, j, k, 0, cry_desc);
				ponteirosArquivos[k] = fp;

                
                if(j == 0)
                	return -1;
                else
					return (indice_arquivo_t) j;
			}
			if(acesso >= 3)	//TENTOU ACESSAR NUM MODO INEXISTENTE
				return FALHA;
	}
	/*######################################## ARQUIVO NOVO ########################################*/
	else { printf("NÃO EXISTE ARQUIVO\n");
		/*######################################## LEITURA ########################################*/
		if(acesso == LEITURA) { //printf("NAOEXISTE LEITURA\n");
			if((fp = fopen(nome, "rb")) == NULL) {
				return FALHA;
			}
			else {
				/*for(totalBytesArquivo = 0; fread(&aux, 1, 1, fp); totalBytesArquivo++) {
					buffer[totalBytesArquivo] = aux;
					buffer = (char *) realloc(buffer, sizeof(char) * (totalBytesArquivo + 2));
					//printf("%c", buffer[totalBytesArquivo]);
				}*/

				valorRetornoIndiceArquivo = atualizaDescritoresNovoArquivo(-1, nome, acesso, fp, cry_desc);
				return valorRetornoIndiceArquivo;

				
			}
		}

		/*######################################## ESCRITA ########################################*/
		if(acesso == ESCRITA) { //printf("NAOEXISTE ESCRITA\n");
			/* VERIFICAR MODO LEITURA DE ARQUIVO */
			fp = fopen(nome, "w+");

/*			if(fp != NULL){
				printf("nao null\n");
			}
			else{
				printf("é null\n");
			}*/

			valorRetornoIndiceArquivo = atualizaDescritoresNovoArquivo(-1, nome, acesso, fp, cry_desc); // atualiza descritores   
			return valorRetornoIndiceArquivo;
		}

		/*######################################## LEITURA/ESCRITA ########################################*/
		if(acesso == LEITURAESCRITA) { //printf("NAOEXISTE LEITURA/ESCRITA\n");
			/* VERIFICAR MODO LEITURA DE ARQUIVO */
			fp = fopen(nome, "r+");

			valorRetornoIndiceArquivo = atualizaDescritoresNovoArquivo(-1, nome, acesso, fp, cry_desc);
			return valorRetornoIndiceArquivo;
		}
		if(acesso >= 3)	//TENTOU ACESSAR DE UM MODO INEXISTENTE
			return FALHA;
	}
	return FALHA;	//parece estar falntando return em algum outro lugar, conferir
}
/** Retorna o tempo em que o arquivo foi criado
 *
 * @param arquivo índice para a tabela de arquivos abertos
 * @return tempo
 */
time_t cry_creation(indice_arquivo_t arquivo){
	return currFileSys->descritores[arquivo].criacao;
}

/** Retorna o tempo em que o arquivo foi acessado
 *
 * @param arquivo índice para a tabela de arquivos abertos
 * @return tempo
 */
time_t cry_accessed(indice_arquivo_t arquivo){
	return currFileSys->descritores[arquivo].modificacao;
}

/** Retorna o tempo em que o arquivo foi modificado
 *
 * @param arquivo índice para a tabela de arquivos abertos
 * @return tempo
 */
time_t cry_last_modified(indice_arquivo_t arquivo){
	return currFileSys->descritores[arquivo].ultimo_acesso;
}