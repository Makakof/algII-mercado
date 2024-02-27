#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "listas.h"
#include "arquivos.h"
#include "produto.h"

/******************************************
* Nome: Luiz Henrique Santos da Silva     *
* Ra: 2022.0743.003-8                     *
* Trabalho Prático                        *
* Disciplina: Algortimos e Programação II *
* Professores: Ivone, Mauro e Ronaldo     *
*                                         *
******************************************/


int main(void)
{
    Produto *listadeProdutos = NULL, *listaDeReposicao = NULL, *novo;
    char comando[10], nome[30], parametro[2];
    int codigo, quantidade, contaProdutos = 0, sair = 0;
    float preco, total = 0;

    novo = (Produto *) malloc(sizeof(Produto));
    if(novo == NULL)
    {
        salvaProdutosDat(listadeProdutos);
        exit(1);
    }
    printf("%d produtos carregados\n",carregaProdutosDat(&listadeProdutos));

    while(sair != 1)
    {
        scanf(" %s", comando);
        if(strcmp(comando,"inserir") == 0)
        {
            scanf(" %d %s %d %f",&codigo,nome,&quantidade,&preco);
            if(validaCodigo(listadeProdutos, codigo))
            {
                insereEmOrdem(&listadeProdutos,codigo,nome,quantidade,preco);
                printf("Produto %d inserido com sucesso!\n", codigo);
            }
            else
                printf("Erro ao inserir o produto %d\n", codigo);
        }
        else if(strcmp(comando,"excluir") == 0)
        {
            scanf(" %d",&codigo);
            if(!validaCodigo(listadeProdutos, codigo))
            {
                excluiProduto(&listadeProdutos, codigo);
                printf("Produto %d excluido com sucesso!\n",codigo);
            }
            else
                printf("Produto %d nao cadastrado\n",codigo);
        }
        else if(strcmp(comando,"atualizar") == 0)
        {
            scanf(" %s %d %f",parametro,&codigo,&preco);
            if(!validaCodigo(listadeProdutos, codigo))
            {
                atualizaProduto(&listadeProdutos,parametro,codigo,preco);
                printf("Produto %d atualizado com sucesso!\n",codigo);
            }
            else
                printf("Produto %d nao cadastrado!\n",codigo);
        }
        else if(strcmp(comando,"consultar") == 0)
        {
            scanf(" %s",nome);
            if(consultarProdutos(listadeProdutos,nome))
                exibeConsultaProdutos(listadeProdutos,nome);
            else
                printf("Nenhum produto encontrado\n");
        }
        else if(strcmp(comando,"relatorio") == 0)
        {
            relatorioDeProdutos(listadeProdutos);
        }
        else if(strcmp(comando,"importar") == 0)
        {
            scanf(" %s",nome);
            quantidade = importaProdutosTxt(&listadeProdutos,nome,&contaProdutos);
            if(quantidade)
                printf("%d/%d produtos importados\n",contaProdutos,quantidade);
            else
                printf("Erro ao importar do arquivo %s", nome);
            contaProdutos = 0;
        }
        else if(strcmp(comando,"vender") == 0)
        {
            scanf(" %d",&codigo);
            do
            {
                if(!validaCodigo(listadeProdutos,codigo))
                {
                    novo = buscaProduto(listadeProdutos, codigo);
                    if(novo->quantidade > 0)
                    {
                        printf("%d - %s - %d - %0.2f\n",novo->codigo,novo->descricao,novo->quantidade,novo->preco);
                        totalDeVenda(&total,novo);
                    }
                    else
                        printf("Produto em falta no estoque\n");
                }
                else
                    printf("Produto nao cadastrado\n");
                scanf(" %d",&codigo);
            }while(codigo != 0);
            printf("--------------\n");
            printf("Total R$ %0.2f\n",total);
            total = 0;
        }
        else if(strcmp(comando,"help") == 0)
        {
            help("help.txt");
        }
        else if(strcmp(comando,"sair") == 0)
        {
            sair = 1;
        }
        else
        {
            printf("Comando invalido, tente novamente!\n");
        }
    }
    salvaProdutosDat(listadeProdutos);
    geraListaReposicao(listadeProdutos,&listaDeReposicao);
    geraCompraTxt(listaDeReposicao);
    mostraLista(listaDeReposicao);
    printf("Arquivo Compra.Txt gerado com sucesso!\n");
    return 0;
}