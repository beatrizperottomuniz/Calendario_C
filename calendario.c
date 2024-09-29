
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int checa_bisse(int);
int imprimir(int, int, int,int);
int pegar_primeiro_dia(int,int);
void menu();
// int argc,char*argv[] - argc=quantos parametros estao sendo recebidos, argv
// guarda o que foi recebido parametros delimitados por espa�o
//  sem nada = quant � 1 , e a primeira posi�o de argv � o nome do arquivo
int main(int argC,char*argV[]) { // vai pedir parametros e vamos checar se e um mes valido
  int ano;
  int mes;
  int modo=0;
  int p_dia;//que dia da semana é o primeiro dia
  int i;
  int proximo_prim_dia;
  struct tm*hoje; // data de hoje por padrao
  time_t agora;// seconds elapsed since 00:00 hours, Jan 1, 1970 UTC
  time (&agora);
  hoje = localtime (&agora);
  ano=(*hoje).tm_year;
  mes=(*hoje).tm_mon;
  if (argC==1){
    modo=1;//modo mes
  }//calendario desse mes desse ano
 else if(argC==2){
    modo=0;//modo ano
    ano=atoi(argV[1])-1900;
    }//calendario desse ano
 else if(argC==3){
    if (atoi(argV[1])<1 || atoi(argV[1])>12){//mes valido ou não
        menu();
        return 0;
      }
    else{
        mes=atoi(argV[1])-1;//meses desde janeiro
        ano=atoi(argV[2])-1900;//anos desde 1900
        modo=1;//modo mes
      }
    }
 else{
      menu();
      return 0;
    }//mais de 3 parametros dá erro
  p_dia=pegar_primeiro_dia(mes,ano);//pega o primeiro dia do mes
  printf("Ano : %d", ano+1900);//ano formatado
  if (modo == 0) {
    for (i = 0; i < 12; i++) {
      proximo_prim_dia=imprimir(i, ano, p_dia,0);
      p_dia=proximo_prim_dia;
      printf("\n");
    }
  }
  else {
    imprimir(mes, ano, p_dia,1);
  }
  return 0;
}

int imprimir(int mes, int ano, int p_dia,int modo) {
  int i;
  float j = 1;
  char *meses[] = {"Janeiro",  "Fevereiro", "Marco",    "Abril",
                   "Maio",     "Junho",     "Julho",    "Agosto",
                   "Setembro", "Outubro",   "Novembro", "Dezembro"};
  int quant_dias[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  char *dias_semana[] = {"D", "S", "T", "Q", "Q", "S", "S"};
  if (mes == 1 && checa_bisse(ano+1900) == 1) {
    quant_dias[1] = 29;
  } // mudar quant dias de fev para 29 se bisse
  printf("\n%s\n\n", meses[mes]);
  for (i = 0; i < 7; i++) {
    printf(" %s ", dias_semana[i]); // ocupa 3 espacos
  }
  printf("\n");
  for (i = 0; i < quant_dias[mes] + p_dia;i++) { // vai falar qual numero imprimir
    if(i%7==0){ printf("\n"); }//pular para outra semana
    if (i < p_dia) { printf("   "); }//printar os espaços em branco
    else { printf("%2.f ", j); j++; }//j começa a contar a partir que i>p_dia
  }
  if (modo==0){
    return (i%7); //� o do proximo mes , pois o i aumenta e dai testa e sai do loop
    //ex esse mes tem 0 + 31 = 31%7=3 - o quer quer dizer que o proximo mes começa na quarta ( 3+0)
  }
  return 0;
}
int checa_bisse(int ano) {
  return ((ano % 4 == 0 &&ano % 100 != 0 )||ano % 400 == 0);
}
int pegar_primeiro_dia(int mes,int ano){
  time_t agora;
  struct tm *primeiro_dia;
  time (&agora); // pega o tempo corrente, data e hora da execucao
  primeiro_dia = localtime (&agora); // preenche a struct tm com os atributos corretos usando o time_t
  //primeiro dia tem as info hoje;
  // converter para mes e ano certo
  primeiro_dia->tm_mday=1;//dia 1 do mes
  primeiro_dia->tm_mon=mes;//do mes que queremos
  primeiro_dia->tm_year=ano;//do ano que queremos
  agora = mktime(primeiro_dia);//altera os outros dados da struct com base naqueles que mudamos
  return primeiro_dia->tm_wday;//retorna que dia da semana é o primeiro dia desse mes e ano
}
void menu(){
  printf("Houve um erro na passagem de parametros !\n Voce pode ter cometido o seguinte erro : ter passado mais parametros que o necessario ou ter colocado um mes invalido");
  printf("\n As opcoes possiveis sao: calendario = mostra o calendario do mes corrente do ano corrente\ncalendario ano(inteiro) = calendario dos 12 meses daquele ano\ncalendario mes(inteiro de 0 a 11) ano(inteiro) =mostra o calendario desse mes e ano ");
}
