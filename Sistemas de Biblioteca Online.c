#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>
#include <stdbool.h>


typedef struct{
    char nome[80];
    int idade;
    char email[51];
}Usuario;
Usuario leitor[20];




bool validacao_nome (char nome[]){
 
   if(strlen(nome) < 3){
       printf("Nome Curto,minimo tres caracteres\n");
       return false;
   }
  return true;
}

bool validacao_idade(int idade){
    if(idade < 12){
        printf("O usuario deve ser maior de 12 anos.\n");
        return false;
    }
    return true;
}

bool validacao_email(char email[50]){
    if(strlen(email) > 50){
        printf("Email muito grande.Maximo de 50 caracteres.\n");
        return false;
    }else if(!isalnum(email[0]) && email[0] != '_'){
        printf("O Email so pode comecar com caractere alfanumerico ou _.\n");
        return false;
    }

    int QTD_CARACTERES = 0;
    int QTD_ARROBA = 0;
    int cont = 0;
    for(int i = 0;email[i] != '\0';i++){
        if(!isalnum(email[i]) && email[i] != '.' && email[i] != '-' && email[i] != '_' && email[i] != '@' ){
            printf("Username so pode ser composto por caracteres alfanumericos,'.','_','-' e '@'.\n");
            return false;
        }else if(email[i] == '.'){
            if(email[i + 1] == '.' || email[i - 1] == '.'){
                printf("Nao pode ter ponto seguido.\n");
                return false;
            }
        }else if(email[i] == '@'){
            QTD_ARROBA++;
            cont = i;
        }
        QTD_CARACTERES++;
    }
    
    if(QTD_CARACTERES < 3){
        printf("Email deve ter no minimo 3 caracteres");
        return false;
    }
    else if(QTD_ARROBA != 1){
        printf("O Email so pode ter um @.\n");
        return false;
    }else if(email[cont] == '@'){
        if(!isalnum(email[cont + 1]) || !isalnum(email[cont - 1])){
            printf("Antes e Depois do @ so pode conter caracteres alfanumericos.\n");
            return false;
        }
    }
    
    int QTD_PONTOS = 0;
    for(int i = cont + 1;email[i] != '\0';i++){
        if(!isalnum(email[i]) && email[i] != '.' && email[i] != '-'){
            printf("O dominio so pode conter caracteres alfanumericos,'.' ou '-'.\n");
            return false;
        }
        else if(email[i] == '.'){
            if(!isalpha(email[i + 1]) || !isalpha(email[i - 1])){
                printf("Escreva um dominio valido\n");
                return false;
            }else if(email[i + 1] == '\0'){
                printf("O Email nao pode terminar com ponto\n");
                return false;
            }
            QTD_PONTOS++;
        }
    }
     
    if(QTD_PONTOS == 0){
        printf("O seu Email esta faltando . e o tld.\n");
        return false;
    }
    return true;
}


int main(){
    char usuario[20];
    int idade;
    char email[51];

    /*printf("Digite seu Nome:");
    scanf("%s", usuario);
    getchar();
    validacao_nome(usuario);

    printf("Digite sua Idade:");
    scanf("%d", &idade);
    getchar();
    validacao_idade(idade);*/

    printf("Digite seu email:");
    scanf("%s",email);
    getchar();
    validacao_email(email);

    return 0;

}