#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>
#include <stdbool.h>
#define QTQ_MAXIMA 100

typedef struct{
    char nome[80];
    int idade;
    char email[51];
}Usuario;
Usuario leitor[QTQ_MAXIMA];

typedef struct{
    char titulo[3777];
    char autor[100];
    int ano_de_publicacao;
}Livro;
Livro livro[QTQ_MAXIMA];




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
    }
    else if(!isalnum(email[0]) && email[0] != '_'){
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

int cadastro_leitor(Usuario leitor[], int *QTD_LEITOR){
    char escolha;
    int indice = *QTD_LEITOR;
    int cont_nome = 0;
    int cont_email = 0;
    int cadastro_completo = 0;

    printf("Cadastro do Usuario %d.\n", indice+1);

    // Parte do Nome
    printf("Digite seu Nome(sem espacos):");
    scanf("%s", leitor[indice].nome);
    getchar();

   for(int i = 0;i < indice;i++){
        if(strcmp(leitor[i].nome, leitor[indice].nome) == 0){
            printf("Este Nome ja existe.Tente Novamente.\n");
            printf("Digite seu Nome:");
            fgets(leitor[indice].nome,50, stdin);
            leitor[indice].nome[strcspn(leitor[indice].nome, "\n")] = '\0';
            cont_nome++;
        }else if(cont_nome == (indice - i)){
            printf("Tentativas Excedidas.");
            return false;
        }
    }
    cont_nome = 0;

        
    if(!validacao_nome(leitor[indice].nome)){
        printf("Nome Invalido.Deseja Tentar Novamente(S/N)?");
        scanf("%c", &escolha);
        getchar();
        
        do{
            if(escolha == 'S'){
                fgets(leitor[indice].nome,80,stdin);
                leitor[indice].nome[strcspn(leitor[indice].nome, "\n")] = '\0';
                cont_nome++;
                if(cont_nome == 3){
                    printf("Numero de Tentativas excedidas.");
                    break;
                }
            }
            else{
                cadastro_completo++;
                break;
            }
        }while(!validacao_nome(leitor[indice].nome));
        cont_nome = 0;
    }
       
    // Parte da Idade
    printf("Digite sua Idade:");
    scanf("%d", &leitor[indice].idade);
    getchar();

    if(!validacao_idade(leitor[indice].idade)){
        return 0;
    }

    // Parte do Email
    printf("Digite seu Email:");
    fgets(leitor[indice].email,50, stdin);
    leitor[indice].email[strcspn(leitor[indice].email, "\n")] = '\0';

    for(int i = 0;i < indice;i++){
        if(strcmp(leitor[i].email, leitor[indice].email) == 0){
            printf("Este Email ja existe.Tente Novamente.\n");
            printf("Digite seu Email:");
            fgets(leitor[indice].email,50, stdin);
            leitor[indice].email[strcspn(leitor[indice].email, "\n")] = '\0';
            cont_email++;
        }else if(cont_email == (indice-i)){
            printf("Tentativas Excedidas.");
            return false;
        }
    }

    cont_email = 0;

    if(!(validacao_email(leitor[indice].email))){
        cadastro_completo++;
        printf("Email Invalido.Deseja Tentar novamente(S/N)?");
        scanf("%c", &escolha);
        do{
            if(escolha == 'S'){
                fgets(leitor[indice].email,50, stdin);
                leitor[indice].email[strcspn(leitor[indice].nome, "\n")] = '\0';
                cont_email++;
                if(cont_email == 3){
                    printf("Numero de tentativas excedidas");
                    break;
                }
            }else{
                cadastro_completo++;
                break;
            }
        }while(!validacao_email(leitor[indice].email));
        cont_email = 0;
    }

    if(cadastro_completo == 1 || cadastro_completo == 2){
        printf("O cadastro precisa ser completo.");
        return false;
    }
    cadastro_completo = 0;
    

    (*QTD_LEITOR)++;
    return 0;

}

int alterar_cadastro(Usuario leitor[], int *QTD_LEITOR){
        int indice = *QTD_LEITOR;
        int alterar;
        int cont_nome = 0,cont_email = 0;

        printf("Deseja alterar qual Informacao?");
        printf("1.Nome\n 2.Email\n");

        scanf("%d", &alterar);

        switch (alterar){
        case 1:
            do{
                printf("Digite o novo Nome:");
                scanf("%s", leitor[indice].nome);
                getchar();

                if(!validacao_nome(leitor[indice].nome)){
                    printf("Nome Invalido");
                    if(cont_nome == 3){
                        printf("Tentativas Excedidas");
                        return 0;
                    }
                    cont_nome++;
                }else{
                    printf("Nome alterado com Sucesso");
                    strcpy(leitor[indice].nome, leitor[indice].nome);
                }
            }while(!validacao_nome(leitor[indice].nome));
            break;

        case 2:
        do{
                printf("Digite o novo Email:");
                fgets(leitor[indice].email,51,stdin);
                leitor[indice].email[strcspn(leitor[indice].email, "\n")] = '\0';
                if(!validacao_nome(leitor[indice].email)){
                    printf("Email Invalido");
                    cont_email++;
                    if(cont_email == 3){
                        printf("Tentativas Excedidas");
                        return 0;
                    }
                }else{
                    printf("Email alterado com Sucesso.");
                }
            }while(!validacao_nome(leitor[indice].email));
            break;
        
        default:
            break;
        }

        printf("Dados alterados com sucesso:\n");
        printf("Nome:%s\n", leitor[indice].nome);
        printf("Idade:%d\n", leitor[indice].idade);
        printf("Email:%s", leitor[indice].email);
        printf("\n");

      return 0;
    }

void listar_usuario(Usuario leitor[], int *QTD_LEITOR){
    int indice = *QTD_LEITOR;
    printf("Lista de todos o usuarios:\n");

    for(int i = 0;i < indice;i++ ){
        printf("Nome:%s\n", leitor[i].nome);
        printf("Idade:%d\n", leitor[i].idade);
        printf("Email:%s", leitor[i].email);
        printf("\n");
    }

}

void Gerenciar_Livros(Livro livro[], Usuario leitor[], int *QTQ_LEITOR){
    char escolha;
    int indice = *QTQ_LEITOR;
    int cont_data = 0;

    printf("Deseja Adicionar um Livro?(S/N)?");
    scanf("%s", &escolha);

    printf("Escreva as informacoes do Livro que deseja atualizar(Titulo, Autor e Ano de Publicacao):\n");
    printf("Titulo:");
    fgets(livro[indice].titulo, 3777, stdin);
    livro[indice].titulo[strcspn(livro[indice].titulo, "\n")] = '\0';

    printf("Autor:");
    fgets(livro[indice].autor, 100, stdin);
    livro[indice].autor[strcspn(livro[indice].autor, "\n")] = '\0';
    printf("Ano Publicacao:");

    scanf("%d", &livro[indice].ano_de_publicacao);
    getchar();

    //Validações das leituras acima

    do{
        if(livro[indice].ano_de_publicacao < 1500){
            printf("O ano do Livro deve ser entre 1500 e o atual.");
            scanf("%d", &livro[indice].ano_de_publicacao);
            getchar();
            cont_data++;
                if(cont_data == 3){
                    printf("Numero de Tentativas de Excedidas.");
                    return 0;
                }
        }
    }while(cont_data == 3);

    int cont_titulo = 0;
    for(int i = 0;i < livro[indice].titulo[i] != '\0';i++){
        if(isalnum(livro[indice].titulo[i])){
            cont_titulo++;
        }
    }

    if(cont_titulo == 0){
        printf("Preencha o titulo:");
        do{
            fgets(livro[indice].titulo, 3777, stdin);
            livro[indice].titulo[strcspn(livro[indice].titulo, "\n")] = '\0';

        }while(cont_titulo == 3);
        return false;
    }


}


int main(){
    int QTD_LEITOR = 0;
    int escolha;

   do{
        printf("\n");
        printf("\nBem Vindo a uma Biblioteca Online,projetada para voce leitor que deseja praticidade em organizar a sua leitura.\n Aqui vai algumas das opcoes para voce:\n 1.Cadastro de usuario \n 2.Alterar Cadastro \n 3.Listar Usuarios \n 4.Gerenciar Livros \n 5.Gerenciar Emprestimos \n 0.Sair \n");
        printf("\n");
        printf("Escolha uma das Opcoes acima:");
        scanf(" %d", &escolha);
        printf("\n");

        switch (escolha){
            case 1:
                cadastro_leitor(leitor, &QTD_LEITOR);
                break;
    
            case 2:
                alterar_cadastro(leitor, &QTD_LEITOR);
                break;
        
            case 3:
                listar_usuario(leitor, &QTD_LEITOR);
                break;

            case 4:
                printf("Ainda em processo de construcao");
                break;
    
            case 5:
                printf("Ainda em processo de construcao");
                break;
            
            case 0:
             
                return 0;
                break;
            
            default:
                break;
        }
    }while(escolha != 0);

    return 0;
}