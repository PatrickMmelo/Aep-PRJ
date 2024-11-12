#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#define users_maximos 50

struct usuario {
    char nome[50];
    char senha[50];
};

int i;

struct usuario u[users_maximos];
int total_usuarios = 0;

void cifra_cesar(char *senha) {
    for (i = 0; senha[i] != '\0'; i++) {
        if (senha[i] >= 'A' && senha[i] <= 'Z') {
            senha[i] = ((senha[i] - 'A' + 7) % 26) + 'A';
        } else if (senha[i] >= 'a' && senha[i] <= 'z') {
            senha[i] = ((senha[i] - 'a' + 7) % 26) + 'a';
        } else if (senha[i] >= '0' && senha[i] <= '9') {
            senha[i] = ((senha[i] - '0' + 7) % 10) + '0';
        }
    }
}

void salvar_user() {
    FILE *file = fopen("usuarios.txt", "w");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo para salvar!\n");
        return;
    }
    for (i = 0; i < total_usuarios; i++) {
        fprintf(file, "%s %s\n", u[i].nome, u[i].senha);
    }
    fclose(file);
}

void carregar_user() {
    FILE *file = fopen("usuarios.txt", "r");
    if (file == NULL) {
        return;
    }
    total_usuarios = 0;
    while (fscanf(file, "%s %s", u[total_usuarios].nome, u[total_usuarios].senha) != EOF) {
        total_usuarios++;
    }
    fclose(file);
}

void cadastrar() {
    if (total_usuarios >= users_maximos) {
        printf("Limite máximo de usuários alcançado!\n");
        return;
    }

    printf("\nDigite o nome do usuário: ");
    scanf("%49s", u[total_usuarios].nome);

    printf("Digite a senha: ");
    scanf("%49s", u[total_usuarios].senha);

    cifra_cesar(u[total_usuarios].senha);
    total_usuarios++;
    salvar_user();

    printf("\nUsuário cadastrado com sucesso!\n");
    getchar();
}

void listar() {
    printf("Usuários cadastrados:\n");

    for (i = 0; i < total_usuarios; i++) {
        printf("%d - %s\n", i + 1, u[i].nome);
    }

    printf("\nPressione Enter para voltar ao menu.");
    getchar(); 
}

void atualizar() {
    int usuarioSelecionado;
    char senhaAtual[50];

    listar();
    printf("\nDigite o número do usuário a atualizar: ");
    scanf("%d", &usuarioSelecionado);
    usuarioSelecionado--;

    if (usuarioSelecionado < 0 || usuarioSelecionado >= total_usuarios) {
        printf("Usuário inválido!\n");
        return;
    }

    printf("Digite a senha atual: ");
    scanf("%49s", senhaAtual);
    cifra_cesar(senhaAtual);

    if (strcmp(u[usuarioSelecionado].senha, senhaAtual) == 0) {
        printf("Digite a nova senha: ");
        scanf("%49s", u[usuarioSelecionado].senha);
        cifra_cesar(u[usuarioSelecionado].senha);
        salvar_user();

        printf("Usuário atualizado com sucesso!\n");
    } else {
        printf("Senha incorreta!\n");
    }

    getchar(); 
}

void deletar() {
    int usuarioSelecionado;
    char senhaDel[50];

    listar();
    printf("\nDigite o número do usuário a deletar: ");
    scanf("%d", &usuarioSelecionado);
    usuarioSelecionado--;

    if (usuarioSelecionado < 0 || usuarioSelecionado >= total_usuarios) {
        printf("Usuário inválido!\n");
        return;
    }

    printf("\nDigite a senha para confirmar exclusão: ");
    scanf("%49s", senhaDel);
    cifra_cesar(senhaDel);

    if (strcmp(u[usuarioSelecionado].senha, senhaDel) == 0) {
        for (i = usuarioSelecionado; i < total_usuarios - 1; i++) {
            u[i] = u[i + 1];
        }
        total_usuarios--;
        salvar_user();

        printf("Usuário deletado com sucesso!\n");
    } else {
        printf("Senha incorreta!\n");
    }

    getchar();
}

void menu() {
    int opcao;

    while (1) {
        printf("\nMENU PRINCIPAL\n");
        printf("1. Cadastrar Cliente\n");
        printf("2. Lista de Clientes\n");
        printf("3. Atualizar Cliente\n");
        printf("4. Deletar Cliente\n");
        printf("5. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar(); 

        switch (opcao) {
            case 1:
                cadastrar();
                break;
            case 2:
                listar();
                break;
            case 3:
            	
                atualizar();
                break;
            case 4:
                deletar();
                break;
            case 5:
                printf("Saindo do programa...\n");
                return;
            default:
                printf("Opção inválida! Tente novamente.\n");
                getchar(); 
                break;
        }
    }
}

int main() {
    setlocale(LC_ALL, "portuguese");
    carregar_user();
    menu();
    return 0;
}

