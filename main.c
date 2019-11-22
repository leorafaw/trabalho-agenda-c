#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define tamanhoAlunos 2
#define numeroTelefones 4

struct Aluno {
    int matricula, idade, telefones[numeroTelefones];
    char nome[31], sexo, email[100];
};

struct Aluno* cadastrarAluno(struct Aluno* agenda);

struct Aluno* pesquisarAluno(struct Aluno* agenda);

void escreverAluno(struct Aluno escrita);

void listarTodosAlunos(struct Aluno* agenda);

int adicionarTelefone();

void abrirMenu();

int main() {
    abrirMenu();
    return 0;
}

void abrirMenu() {
    int opcao, i;
    struct Aluno* agenda = malloc(sizeof(struct Aluno) * tamanhoAlunos);


    do {
        printf("Escolha uma das opções abaixo:\n1 - Cadastrar aluno\n2 - Pesquisar aluno\n3 - Remover aluno\n4 - Ver total de alunos\n5 - Ver total de telefones\n6 - Limpar todos os alunos\n7 - Salvar alunos em disco\n8 - Carregar lista de alunos do disco\n9 - Listar alunos\n0 - Sair\n\n");
        fflush(stdin);
        scanf("%d", &opcao);

        if(opcao == 1) {
            agenda = cadastrarAluno(agenda);
        } else if (opcao == 2) {
            agenda = pesquisarAluno(agenda);
        } else if (opcao == 9) {
            listarTodosAlunos(agenda);
        }
    } while(opcao != 0);

}

struct Aluno* cadastrarAluno(struct Aluno* agenda) {

    int i;
    struct Aluno aluno;
    char resposta;

    printf ("\nDigite a matricula: ");
    fflush(stdin);
    scanf("%d", &aluno.matricula);

    printf ("\nDigite o nome: ");
    fflush(stdin);
    scanf("%s", &aluno.nome);
    //fgets(aluno.nome, sizeof(aluno.nome), stdin);

    printf("\nDigite o sexo: ");
    scanf("%s", &aluno.sexo);

    printf("\nDigite o email: ");
    fflush(stdin);
    scanf("%s", &aluno.email);
    // fgets(aluno.email, sizeof(aluno.email), stdin);

    i = 0;

    do {
        aluno.telefones[i] = adicionarTelefone();

        i++;

        printf("\nGostaria de cadastrar mais um telefone? (s para sim, qualquer outro caractere para não)");
        scanf("%s", &resposta);
    } while (resposta == 's' && i < numeroTelefones);

    for(i = 0; i < tamanhoAlunos; i++) {
        if(agenda[i].matricula == 0) {
            agenda[i] = aluno;
            break;
        } else if(i == tamanhoAlunos -1 && agenda[i].matricula != 0) {
            printf("Não há espaço disponível, apague algum registro antes de continuar!");
        }
    }

    return agenda;
}

struct Aluno* pesquisarAluno(struct Aluno* agenda) {
    int matricula, opcao, i, j, telefoneDeletar;

    printf ("Digite a matricula do aluno que deseja buscar: ");
    fflush(stdin);
    scanf("%d", &matricula);

    for(i = 0; i < tamanhoAlunos; i++) {
        if(agenda[i].matricula == matricula) {
            printf("Aluno encontrado: \n");
            escreverAluno(agenda[i]);

            do {
                printf("O que deseja fazer: \n1 - Adicionar telefone\n2 - Remover telefone\n3 - Voltar para o menu\n\n");
                fflush(stdin);
                scanf("%d", &opcao);

                if (opcao == 1) {
                    for(j = 0; j < numeroTelefones; j++) {
                        if(agenda[i].telefones[j] == 0) {
                            agenda[i].telefones[j] = adicionarTelefone(agenda[i].telefones);
                        } else if(agenda[i].telefones[j] == numeroTelefones -1 && agenda[i].telefones[j] != 0) {
                            printf("Espaço insuficiente!");
                        }
                    }
                } else if(opcao == 2) {
                    printf("Digite o indice do telefone a remover");
                    fflush(stdin);
                    scanf("%d", &telefoneDeletar);
                    agenda[i].telefones[telefoneDeletar + 1] = 0;
                } else if(opcao == 3) {
                    return agenda;
                } else {
                    system('cls');
                    printf("Opção inválida");
                }
            } while(opcao != 1 || opcao != 2 || opcao != 3);
        }
    }
}

int adicionarTelefone() {
    int numeroAdicionar;

    printf("\nDigite um numero para adicionar: ");
    fflush(stdin);
    scanf("%d", &numeroAdicionar);

    return numeroAdicionar;
}

void listarTodosAlunos(struct Aluno* agenda) {
    system("clear");
    printf("Carregando...\n");
    sleep(1);
    for(int i = 0; i < tamanhoAlunos; i++) {
        if(agenda[i].matricula != 0) {
            escreverAluno(agenda[i]);
        } else if(i == tamanhoAlunos -1 && agenda[i].matricula == 0) {
            printf("Nenhum aluno cadastrado!\n\n");
            sleep(2);
            system("clear");
        }
    }
}

void escreverAluno(struct Aluno aluno){
    int i;

    printf ("Matricula: %d \nNome: %s \nEmail: %s \nSexo: %c", aluno.matricula, aluno.nome, aluno.email, aluno.sexo);

    printf("telefones: \n");

    for(i = 0; i < tamanhoAlunos; i++) {
        if(aluno.telefones[i]!=0) {
            printf ("\n%d - %d", i+1, aluno.telefones[i]);
        }
    }
}