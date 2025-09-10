#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#define QTD_MAX_DE_CLIENTES 1001

typedef struct{
    char nome_cliente[101];
    char cpf[15];
    int dia_nascimento;
    int mes_nascimento;
    int ano_nascimento;
    char numero_telefone[15];
    char email[50];
}Clientes;
Clientes cliente[QTD_MAX_DE_CLIENTES];


                                                          //VALIDACOOES//


bool validacao_nome(char nome[]){
    
    if(strlen(nome) < 4 ||  strlen(nome) > 100){
        return false;
    }
    for(int i = 0;nome[i] != '\0';i++){
        if(!isalpha(nome[i]) && nome[i] != ' ' && nome[i] != '-' && nome[i] != '\''){
            return false;
        }
    }
      return true;
} 


bool validacao_cpf(char cpf[]){

   // Clientes cliente[QTD_MAX_DE_CLIENTES];

   

    int tamanho = strlen(cpf);
    int tamanho1 = tamanho - 2; 
    int tamanho2 = tamanho - 1;

    if(tamanho != 11 && tamanho != 14 ){
        return false;
    }

   
    for(int i = 0;cpf[i] != '\0';i++){
        if(!isdigit(cpf[i]) && cpf[i] != '.' && cpf[i] != '-'){
            return false;
        }
        else if(tamanho == 14){
            if(cpf[3] != '.' || cpf[7] != '.'){
                return false;
            }        
            if(cpf[11] != '-'){
                return false;
            }
        }
    }

    // add para que nao seja iguais
    int cont = 0;
    for(int i = 1;cpf[i] != '\0';i++){
        if(isdigit(cpf[i])){
            if(cpf[0] == cpf[i]){
                cont++;
                if(cont == 10){
                    return false;
                    break;
                }
            }
        }
    }
    
    // Verificando o primeiro digito
    
    int soma1 = 0;
    int cont1 = 0;
    for(int multi = 10; multi >= 2; multi--){
        while(!isdigit(cpf[cont1])) cont1++; 
        soma1 += (cpf[cont1] - '0') * multi;
        cont1++;
    }
        int resto1 = 11 - (soma1 % 11);
        int D1 = cpf[tamanho1] - '0';
        if(resto1 >= 10 && D1 != 0){
            return false;
        }
        else if(resto1 < 10 && D1 != resto1 ){
            return false;
        }

    // Verificando o segundo digito

    int soma2 = 0;
    int cont2 = 0;
   for(int multi = 11; multi >= 2; multi--){
        while(!isdigit(cpf[cont2])) cont2++;
        soma2 += (cpf[cont2] - '0') * multi;
        cont2++;
    }

    int resto2 = 11 - (soma2 % 11);
    int D2 = cpf[tamanho2] - '0';
    if(resto2 >= 10 &&  D2 != 0){
        return false;
    }
    else if(resto2 < 10 && D2 != resto2){ 
        return false;
    }
   //push e pull
    
    return true;

}

bool validacao_data_de_nascimento(int dia_nascimento, int mes_nascimento, int ano_nascimento){
        
    switch (mes_nascimento){
        case 2 :
          if((ano_nascimento % 4 == 0 && (ano_nascimento % 100 != 0 || ano_nascimento % 400 == 0))){
             if(dia_nascimento < 1 || dia_nascimento > 29){
                return false;
             }else if(dia_nascimento < 1 || dia_nascimento > 28){
                return false;
             } 
        }
        break;

        case 1 :case 3:case 5:case 7:case 8:case 10:case 12:
        if(dia_nascimento < 1 || dia_nascimento > 31){
            return false;
        }
        break;

        case 4: case 6: case 9: case 11:
        if(dia_nascimento < 1 || dia_nascimento > 30){
            return false;
        }
        break;

        default:
        return false;

    }

    return true;
}

bool validacao_email(char email[]){
     int tamanho = strlen(email) - 1;

    if(strlen(email) > 49){
        return false;
    }

    if(!isalpha(email[0]) && !isdigit(email[0]) && !isalpha(email[tamanho]) && !isdigit(email[tamanho]) ){
        return false;
    }


    int QTD_Arroba = 0;
    int QTD_Ponto = 0;
    int Ult_Ponto = 0;
    for(int i = 0;email[i] != '\0';i++){
        if(!isalpha(email[i]) && !isdigit(email[i]) && email[i] != '.' && email[i] != '-' && email[i] != '@' && email[i] != '_' ){
            return false;
        }
        
        else if(email[i] == '@'){
            QTD_Arroba++;
            if(QTD_Arroba != 1){
                return false;
            }
            if(!isalpha(email[i - 1]) && !isdigit(email[i - 1])){
                return false;
            }
            if(!isalpha(email[i + 1]) && !isdigit(email[i + 1])){
                return false;
            }
            int cont = 0;
            cont = i;
            
            for(int pos = cont;email[pos] != '\0';pos++){
                if(email[pos] == '_'){
                    return false;
                }
                if(email[pos] == '.'){
                    QTD_Ponto++;
                    Ult_Ponto = pos;
                }
            }
        }
        
        else if(email[i] == '.'){
            if(email[i - 1] == '.' || email[i + 1] == '.'){
                return false;
            }
        }
    }
    if(QTD_Ponto == 0){
        return false;
    }

    int contador = 0;
    for(int i = Ult_Ponto + 1;email[i] != '\0';i++){
        contador++;
        if(!isalpha(email[i])){
            return false;
        }
    }
    if(contador < 2){
        return false;
    }
    
   return true;
}


bool validacao_numero(char numero_telefone[]){
    int ddd1 = numero_telefone[0] - '0';
    int ddd2 = numero_telefone[1] - '0';
    int tam = strlen(numero_telefone);

    int QTD_Hifens = 0;
    for(int i = 0;numero_telefone[i] != '\0';i++){
        if(!isdigit(numero_telefone[i]) && numero_telefone[i] != '-' && numero_telefone[i] != ' '){
            return false;
        }
        if(numero_telefone[i] == '-'){
            QTD_Hifens++;
            if(QTD_Hifens != 1 && QTD_Hifens != 2){
                return false;
            }
        }
    }

    if(tam == 12 || tam == 13){
        if(numero_telefone[3] != '9'){
            return false;
        }
    }
     if(tam == 11){
        if(numero_telefone[2] != '9'){
            return false;
        }
    }
        if(ddd1 == 0 || ddd2 == 0){
            return false;
        }
        else if(ddd1 == 2 && (ddd2 == 3 || ddd2 == 5  || ddd2 == 6 || ddd2 == 9)){
            return false;
        }
        else if(ddd1 == 3 && (ddd2 == 6 || ddd2 == 39)){
            return false;
        }
        else if(ddd1 == 5 && (ddd2 == 2 || (ddd2 >= 6 && ddd2 <= 9))){
            return false;
        }
        else if(ddd1 == 7 && (ddd2 == 2 || ddd2 == 6 || ddd2 == 8)){
            return false;
        }
    return true;
}

int  alterar_cadastro(Clientes cliente[],int indice){
    int escolha;
    int um_ou_zero;


    do{
        printf("\nDeseja alterar algum dado?(1 ou 0):");

        scanf("%d", &um_ou_zero);
        getchar();

        if(um_ou_zero == 0){
        return 0;
    }

    printf("1.Alterar Nome \n 2.Alterar CPF \n 3.Alterar Data \n 4.Alterar Numero \n 5.Alterar Email  \n");
    do{
        scanf("%d", &escolha);
        getchar();
    }while(escolha < 1 || escolha > 5);

    switch(escolha){
        case 1 :
            
        printf("Digite seu nome:");
        fgets(cliente[indice].nome_cliente,101,stdin);
        cliente[indice].nome_cliente[strcspn(cliente[indice].nome_cliente, "\n")] = '\0';
       
        break;
        
        case 2 :

        printf("Digite seu CPF:");
        fgets(cliente[indice].cpf,15,stdin);
        cliente[indice].cpf[strcspn(cliente[indice].cpf, "\n")] = '\0';
       
        break;
         case 3 :

        printf("Digite sua Data:");
        scanf("%d/%d/%d", &cliente[indice].dia_nascimento,  &cliente[indice].mes_nascimento,  &cliente[indice].ano_nascimento);
        getchar();
        
        break;
         case 4 :

        printf("Digite seu numero:");
        fgets(cliente[indice].numero_telefone,15,stdin);
        cliente[indice].numero_telefone[strcspn(cliente[indice].numero_telefone, "\n")] = '\0';
       
        break;
         case 5 :

        printf("Digite seu Email:");
        fgets(cliente[indice].email,50,stdin);
        cliente[indice].email[strcspn(cliente[indice].email, "\n")] = '\0';
        break;

    }

    printf("\nDados Alterados:\n");
    printf("Nome:%s\n",cliente[indice].nome_cliente);
    printf("CPF:%s\n", cliente[indice].cpf);
    printf("Data:%d/%d/%d\n", cliente[indice].dia_nascimento, cliente[indice].mes_nascimento, cliente[indice].ano_nascimento);
    printf("Numero:%s\n", cliente[indice].numero_telefone);
    printf("Email:%s\n", cliente[indice].email);

    printf("\n");
    printf("Dados atualizados com sucesso");
    printf("\n");

    }while(um_ou_zero != 0);

    
    return 0;
    
}



int  cadastro_de_clientes(Clientes cliente[],int *QTD_CLIENTES){
    int pos = *QTD_CLIENTES;   

       // Nome
        int cont = 0;
       do
       {
        printf("Digite seu nome:");
        fgets(cliente[*QTD_CLIENTES].nome_cliente,101,stdin);
        cliente[*QTD_CLIENTES].nome_cliente[strcspn(cliente[*QTD_CLIENTES].nome_cliente, "\n")] = '\0';
       
        if(validacao_nome(cliente[*QTD_CLIENTES].nome_cliente)){
            break;
        }else{
            printf("Nome Invalido.Tente novamente");
            cont++;
            printf("\n");
        }

       } while(cont < 3);
       if(cont == 3){
        printf("Muitas Tentativas,tente se cadastrar novamente");
        return 1;
    } 

    //CPF

       int cont2 = 0;
       do
       {
        printf("Digite seu CPF(ABC.DEF.GHI-JK):");
        fgets(cliente[*QTD_CLIENTES].cpf, 16,stdin);
        cliente[*QTD_CLIENTES].cpf[strcspn(cliente[*QTD_CLIENTES].cpf, "\n")] = '\0';
        
       
        if(validacao_cpf(cliente[*QTD_CLIENTES].cpf)){
            break;
        }
        else{
            printf("CPF Invalido,tente novamente");
            cont2++;
            printf("\n");
        }

    } while (cont2 < 3);
    if(cont2 == 3){
        printf("Muitas Tentativas,tente se cadastrar novamente");
        return 1;
    }

    // Data

    int cont3 = 0;
    do{
        printf("Digite sua data de nascimento(dd/mm/aaaa):");
        scanf("%d/%d/%d", &cliente[*QTD_CLIENTES].dia_nascimento, &cliente[*QTD_CLIENTES].mes_nascimento, &cliente[*QTD_CLIENTES].ano_nascimento);
        getchar();

        if(validacao_data_de_nascimento(cliente[*QTD_CLIENTES].dia_nascimento, cliente[*QTD_CLIENTES].mes_nascimento, cliente[*QTD_CLIENTES].ano_nascimento)){
            break;
        }
        else{
            printf("Data Invalida,tente novamente.");
            cont3++;
            printf("\n");
        }

    }while(cont3 < 3);
    if(cont3 == 3){
        printf("Muitas tentativas,tente se cadastrar novamente");
        return 1;
    }
 
     // NUmero

    int cont4 = 0;
    do
    {
       printf("Digite seu Numero(DD-99999-9999):");
       fgets(cliente[*QTD_CLIENTES].numero_telefone,15,stdin);
       cliente[*QTD_CLIENTES].numero_telefone[strcspn(cliente[*QTD_CLIENTES].numero_telefone, "\n")] = '\0';
       
       if(validacao_numero(cliente[*QTD_CLIENTES].numero_telefone)){
        break;
       }
       else{
        printf("Numero de celular invalido,tente novamente");
        cont4++;
        printf("\n");
       }

    } while (cont4 < 3);
    if(cont4 == 3){
        printf("Muitas tentativas,tente se cadastrar novamente");
        return 1;
    }

    // Email

    int cont5 = 0;
     do
    {
       printf("Digite seu Email(username@dominio):");
       fgets(cliente[*QTD_CLIENTES].email,50,stdin);
       cliente[*QTD_CLIENTES].email[strcspn(cliente[*QTD_CLIENTES].email, "\n")] = '\0';
       
       if(validacao_email(cliente[*QTD_CLIENTES].email)){
        break;
       }
       else{
        printf("Email Invalido,tente novamente");
        cont5++;
        printf("\n");
       }

    } while (cont5 < 3);
    if(cont5 == 3){
        printf("Muitas tentativas,tente se cadastrar novamente");
        return 1;
    }

    printf("\nDados Criados:\n");
    printf("Nome:%s\n",cliente[*QTD_CLIENTES].nome_cliente);
    printf("CPF:%s\n", cliente[*QTD_CLIENTES].cpf);
    printf("Data:%d/%d/%d\n", cliente[*QTD_CLIENTES].dia_nascimento, cliente[*QTD_CLIENTES].mes_nascimento, cliente[*QTD_CLIENTES].ano_nascimento);
    printf("Numero:%s\n", cliente[*QTD_CLIENTES].numero_telefone);
    printf("Email:%s\n", cliente[*QTD_CLIENTES].email);

    printf("\n");
    printf("Dados Cadastrados com Sucesso do cliente %d", *QTD_CLIENTES);
    printf("\n");


    alterar_cadastro(cliente, pos);
    
    (*QTD_CLIENTES)++;
   
   
    

    return 0;

}

int  buscar_cpf(Clientes cliente[], int *QTD_CLIENTES){
    char busca_cpf[15];
    int cont = 0;
    
    printf("Digite seu CPF(ABC.DEF.GHI-JK):");
    fgets(busca_cpf, 16,stdin);
    busca_cpf[strcspn(busca_cpf, "\n")] = '\0';
        
       
    if(validacao_cpf(busca_cpf)){
        for(int i = 0;i < *QTD_CLIENTES;i++){
        if(strcmp(busca_cpf,cliente[i].cpf) == 0){
            printf("Nome:%s\n",cliente[i].nome_cliente);
            printf("CPF:%s\n", cliente[i].cpf);
            printf("Data:%d/%d/%d\n", cliente[i].dia_nascimento, cliente[i].mes_nascimento, cliente[i].ano_nascimento);
            printf("Numero:%s\n", cliente[i].numero_telefone);
            printf("Email:%s\n", cliente[i].email);
            break;
       }else{
        cont++;
        }
       }
    }

    if(cont == *QTD_CLIENTES){
        printf("CPF nao encontrado,tente novamente");
        int indice = *QTD_CLIENTES;
        int &ref = indice;
        cadastro_de_clientes(cliente, &ref);
    }

    return 0;
}


int mes_aniversariante(Clientes cliente[], int *QTD_CLIENTES){
    int mes_escolhido;
    int cont = 0;

    printf("Digite um mes para listarmos os aniversariantes:");
    scanf("%d", &mes_escolhido);

    for(int i = 0;i < *QTD_CLIENTES;i++){
        int i2 = i;
        if(cliente[i].mes_nascimento == mes_escolhido){
        for(int pos = i + 1; pos < *QTD_CLIENTES;pos++){
            if(cliente[pos].dia_nascimento < cliente[i2].dia_nascimento){
                i2 = pos;
                    Clientes c = cliente[i];
                    cliente[i] = cliente[i2];
                    cliente[i2] = c;
                }
                else if(cliente[pos].ano_nascimento < cliente[i2].ano_nascimento){
                    i2 = pos;
                    Clientes c = cliente[i];
                    cliente[i] = cliente[i2];
                    cliente[i2] = c;
                }
            }
            printf("\nNome:%s\n",cliente[i].nome_cliente);
            printf("CPF:%s\n", cliente[i].cpf);
            printf("Data:%d/%d/%d\n", cliente[i].dia_nascimento, cliente[i].mes_nascimento, cliente[i].ano_nascimento);
            printf("Numero:%s\n", cliente[i].numero_telefone);
            printf("Email:%s\n", cliente[i].email);
            printf("\n");            
        }
        else{
            cont++;
        }
    }

    if(cont == *QTD_CLIENTES){
        printf("\n");
        printf("Nao temos aniversariantes nesse mes,tente outro mes.");
        printf("\n");
    }

    return 0;
}


int main(){
    int num;
    int QTD = 1;
   Clientes cliente[QTD_MAX_DE_CLIENTES];

    do{
     
        printf("\n Bem Vindos a loja de chocolate Nibs,aqui voce tem a melhor experiencia ao comer um chocolate.Nosso atendimento consiste em Quatro Opcoes Abaixo:\n");
    printf("1:Cadastrar Usuario \n 2:Buscar CPF \n 3:Aniversariantes do mes \n 0:Sair \n");

        scanf("%d", &num);
        getchar();



        switch (num){
            case 1:
            cadastro_de_clientes(cliente, &QTD);
            break;
    
            case 2:
            buscar_cpf(cliente, &QTD);
            break;

            case 3:
            mes_aniversariante(cliente, &QTD);
            break;

            case 0:
            break;

            default:
            printf("Opcao Invalida");
        }
    } while (num != 0);
    
   }


