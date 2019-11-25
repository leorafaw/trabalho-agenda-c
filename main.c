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

struct Aluno* removerAluno(struct Aluno* agenda);

struct Aluno* limparLista(struct Aluno* agenda);

struct Aluno* carregarAgenda(struct Aluno* agenda);

int adicionarTelefone();

void escreverAluno(struct Aluno aluno);

void listarTodosAlunos(struct Aluno* agenda);

void abrirMenu();

void getTotalAlunos(struct Aluno* agenda);

void getTotalTelefones(struct Aluno* agenda);

void salvarAgenda(struct Aluno* ageda);

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
        } else if (opcao == 3) {
            agenda = removerAluno(agenda);
        } else if (opcao == 4) {
            getTotalAlunos(agenda);
        } else if (opcao == 5) {
            getTotalTelefones(agenda);
        } else if (opcao == 6) {
            agenda = limparLista(agenda);
        } else if (opcao == 7) {
            salvarAgenda(agenda);
        } else if (opcao == 8) {
            agenda = carregarAgenda(agenda);
        } else if (opcao == 9) {
            listarTodosAlunos(agenda);
        }
    } while(opcao != 0);

}

struct Aluno* carregarAgenda(struct Aluno* agenda) {
    FILE *arquivo;
    int i, j;

    arquivo = fopen("agenda.txt", "wb");

    if(arquivo != NULL) {
        while(!feof(arquivo)) {
            for(i = 0; i < tamanhoAlunos; i++) {
                if(agenda[i].matricula == 0) {
                    fscanf(arquivo, "%d %s %d %c %s %d %d %d %d ", agenda->matricula, agenda->nome, agenda->idade, agenda->sexo, agenda->email, agenda->telefones[0], agenda->telefones[1], agenda->telefones[2], agenda->telefones[3]);
                }
            }
        }
    }
}

void salvarAgenda(struct Aluno* agenda) {
    FILE *arquivo;
    int i, j;

    system("clear");
    printf("Salvando...");

    arquivo = fopen("agenda.txt", "wb");
    fclose(arquivo);

    for(i = 0; i < tamanhoAlunos; i++) {
        if(agenda[i].matricula!= 0) {
            fprintf (arquivo, "%d %s %d %c %s ", agenda[i].matricula, agenda[i].nome, agenda[i].idade, agenda[i].sexo, agenda[i].email);

            for(j = 0; j < numeroTelefones; j++){
                fprintf(arquivo, "%d ", agenda[i].telefones[j]);
            }
            fprintf(arquivo, "\n");
        }
    }

    sleep(2);
    system("clear");
    printf("Salvo com sucesso!");
    sleep(1);
    system("clear");
}

struct Aluno* limparLista(struct Aluno* agenda) {
    printf("\n");
    system("clear");
    printf("Limpando...");
    for(int i = 0; i < tamanhoAlunos; i++) {
        if(agenda[i].matricula != 0) {
            agenda[i].matricula = 0;
            memset(agenda[i].nome, '\0', sizeof(agenda[i].nome));
            memset(agenda[i].email, '\0', sizeof(agenda[i].email));
            agenda[i].sexo = '\0';
            for(int j = 0; j < numeroTelefones; j++) {
                agenda[i].telefones[j] = 0;
            }
            agenda[i].idade = 0;
        }
    }
    sleep(2);
    system("clear");
    printf("Limpo com sucesso!");
    sleep(1);
    system("clear");

    return agenda;
}

void getTotalTelefones(struct Aluno* agenda) {
    int i, j, count = 0;
    system("clear");
    for(i = 0; i < tamanhoAlunos; i++) {
        if(agenda[i].matricula != 0) {
            for(j = 0; j < numeroTelefones; j++) {
                if(agenda[i].telefones[j] != 0) {
                    count++;
                }
            }
        }
    }

    printf("Total de telefones: %d\n", count);

    sleep(3);
    printf("\nVoltando para o menu... \n");
    sleep(2);
    system("clear");  
}

void getTotalAlunos(struct Aluno* agenda) {
    int i, count = 0;
    system("clear");
    for(i = 0; i < tamanhoAlunos; i++) {
        if(agenda[i].matricula != 0) {
            count++;
        }
    }

    printf("Total de alunos: %d\n", count);

    sleep(3);
    printf("\nVoltando para o menu... \n");
    sleep(2);
    system("clear");   
}

struct Aluno* removerAluno(struct Aluno* agenda) {
    int i, j, matriculaRemover;

    system("clear");
    printf("\nDigite a matricula do aluno que deseja remover: ");
    fflush(stdin);
    scanf("%d", &matriculaRemover);

    for(i = 0; i < tamanhoAlunos; i++) {
        if(agenda[i].matricula == matriculaRemover) {
            agenda[i].matricula = 0;
            memset(agenda[i].nome, '\0', sizeof(agenda[i].nome));
            memset(agenda[i].email, '\0', sizeof(agenda[i].email));
            agenda[i].sexo = '\0';
            for(j = 0; j < numeroTelefones; j++) {
                agenda[i].telefones[j] = 0;
            }
            agenda[i].idade = 0;
        }
    }

    return agenda;
}

struct Aluno* cadastrarAluno(struct Aluno* agenda) {

    int i, j;
    struct Aluno aluno;
    char resposta;
    system("clear");
    printf ("\nDigite a matricula: ");
    fflush(stdin);
    scanf("%d", &aluno.matricula);

    printf ("\nDigite o nome: ");
    fflush(stdin);
    scanf("%s", &aluno.nome);

    printf ("\nDigite a idade: ");
    fflush(stdin);
    scanf("%d", &aluno.idade);

    printf("\nDigite o sexo: ");
    fflush(stdin);
    scanf("%s", &aluno.sexo);

    printf("\nDigite o email: ");
    fflush(stdin);
    scanf("%s", &aluno.email);

    for(j = 0; j < numeroTelefones; j++) {
        aluno.telefones[j] = 0;
    }

    i = 0;

    do {
        aluno.telefones[i] = adicionarTelefone();

        i++;

        printf("\ntelefones: %d\nGostaria de cadastrar mais um telefone? (s para sim, qualquer outro caractere para não)", i);
        fflush(stdin);
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

    sleep(1);
    system("clear");
    printf("Cadastrado com sucesso!\n\n");

    return agenda;
}

struct Aluno* pesquisarAluno(struct Aluno* agenda) {
    int matricula, opcao, i, j, telefoneDeletar, count;
    system("clear");

    printf ("Digite a matricula do aluno que deseja buscar: ");
    fflush(stdin);
    scanf("%d", &matricula);

    count = 0;

    for(i = 0; i < tamanhoAlunos; i++) {
        if(agenda[i].matricula == matricula) {
            count++;
            printf("Aluno encontrado: \n");

            do {
                escreverAluno(agenda[i]);
                printf("O que deseja fazer: \n1 - Adicionar telefone\n2 - Remover telefone\n3 - Voltar para o menu\n\n");
                fflush(stdin);
                scanf("%d", &opcao);

                if (opcao == 1) {
                    for(j = 0; j < numeroTelefones; j++) {
                        if(agenda[i].telefones[j] == 0) {
                            agenda[i].telefones[j] = adicionarTelefone(agenda[i].telefones);
                            break;
                        } else if(agenda[i].telefones[j] == numeroTelefones -1 && agenda[i].telefones[j] != 0) {
                            printf("Espaço insuficiente!");
                        }
                    }
                } else if(opcao == 2) {
                    printf("Digite o indice do telefone a remover: ");
                    fflush(stdin);
                    scanf("%d", &telefoneDeletar);
                    agenda[i].telefones[telefoneDeletar - 1] = 0;
                } else if(opcao == 3) {
                    system("clear");
                    return agenda;
                } else {
                    system("clear");
                    printf("Opção inválida");
                }
            } while(opcao != 3);
            system("clear");
        }
    }

    if(count == 0) {
        printf("Nenhum aluno encontrado! Voltando para o menu...\n");
        sleep(2);
        system("clear");
        return agenda;
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
    int contAlunos = 0;
    system("clear");
    printf("Carregando...\n");
    sleep(1);
    system("clear");
    for(int i = 0; i < tamanhoAlunos; i++) {
        if(agenda[i].matricula != 0) {
            escreverAluno(agenda[i]);
            contAlunos++;
        }
    }

    if (contAlunos == 0) {
        printf("Nenhum aluno cadastrado!\n\n");
        sleep(2);
        system("clear");
    }
}

void escreverAluno(struct Aluno aluno){
    int i;

    printf ("Matricula: %d \nNome: %s \nEmail: %s \nSexo: %c\n", aluno.matricula, aluno.nome, aluno.email, aluno.sexo);

    printf("\ntelefones:");

    for(i = 0; i < tamanhoAlunos; i++) {
        if(aluno.telefones[i]!=0) {
            printf ("\n%d - %d", i+1, aluno.telefones[i]);
        }
    }

    printf("\n\n");
}