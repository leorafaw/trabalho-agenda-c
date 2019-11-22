#include <stdio.h>
#include <stdlib.h>

#define tamanhoAlunos 2
#define numeroTelefones 4

struct Aluno {
    int matricula, idade, telefone[numeroTelefones];
    char nome[31], sexo, email[100];
};

struct Aluno cadastrarAluno (struct Aluno aluno);

void escreveAluno (struct Aluno escrita);

void abreMenu();

int main() {
    abreMenu();

    int i, busca;

    ///exibe lista
    for(i = 0; i < tamanhoAlunos; i++) {
        escreveAluno(agenda[i]);
    }

    ///busca
    printf ("Digite a matricula do aluno que deseja buscar: ");
    fflush(stdin);
    scanf("%d", &busca);
    for(i = 0; i < tamanhoAlunos; i++) {
        if(agenda[i].matricula == busca) {
            printf ("\n\n %d \n %s  \n %s %c ", agenda[i].matricula, agenda[i].nome, agenda[i].email, agenda[i].sexo);
            ///mostra dados de telefone
            int j;
            for(j = 0; j < numeroTelefones; j++) {
                if(agenda[i].telefone[j] != 0) {
                    printf("telefone %d: %d", j, agenda[i].telefone[j]);
                }
            }
        }
    }

    return 0;
}

void abreMenu() {
    int opcao, i;
    struct Aluno agenda[tamanhoAlunos];

    printf("Escolhe uma das opções abaixo: \n
            1 - Cadastrar aluno\n
            2 - Pesquisar aluno\n
            3 - Remover aluno\n
            4 - Ver total de alunos\n
            5 - Ver total de telefones\n
            6 - Limpar todos os alunos\n
            7 - Salvar alunos em disco\n
            8 - Carregar lista de alunos do disco");
    fflush(stdin);
    scanf("%d", &opcao);

    if(opcao == 1) {
        for(i = 0; i < tamanhoAlunos; i++) {
            if(agenda[i].matricula == 0) {
                agenda[i] = cadastrarAluno();
            }
        }
    } else if (opcao == 2) {

    }
}

struct Aluno cadastrarAluno () {

    int i;
    struct Aluno aluno;

    printf ("\nDigite a matricula: ");
    scanf("%d", &aluno.matricula);

    printf ("\nDigite o nome: ");
    fflush(stdin);
    fgets(aluno.nome, sizeof(aluno.nome), stdin);

    printf("\nDigite o sexo: ");
    fflush(stdin);
    scanf("%c", &aluno.sexo);

    printf("\nDigite o email: ");
    fflush(stdin);
    scanf("%s", &aluno.email);

    char resposta = 's';
    i = 0;

    do {
        printf("\nDigite o telefone(%d): ", i);
        scanf ("%d", &aluno.telefone[i]);

        i++;

        printf("\nGostaria de cadastrar mais um telefone? (s para sim, qualquer outro caractere para não) ");
        fflush(stdin);
        scanf("%c", &resposta);
    } while (resposta == 's' && i < numeroTelefones);

    return aluno;
}

void escreveAluno (struct Aluno escrita){

    int i;

    printf ("\n\nMatricula: %d \nNome: %s  \nEmail: %s \nSexo: %c", escrita.matricula, escrita.nome, escrita.email, escrita.sexo);
    for(i = 0; i < tamanhoAlunos; i++) {
        if(escrita.telefone[i]!=0) {
            printf ("\n\n %d", escrita.telefone[i]);
        }
    }

}