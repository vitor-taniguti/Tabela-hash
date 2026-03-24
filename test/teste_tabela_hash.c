#include "tabela_hash.h"
#include "unity.h"

void teste_criarEInicializarTabela(){
    tabela t = criarEInicializarTabela();
    TEST_ASSERT_NOT_NULL(t);
    liberarTabela(t);
}

void teste_getTamanhoTabela(){
    tabela t = criarEInicializarTabela();
    TEST_ASSERT_EQUAL_INT(2, getTamanhoTabela(t));
    liberarTabela(t);
}

void teste_extenderTabela(){
    tabela t = criarEInicializarTabela();
    int tamanhoAntigo = getTamanhoTabela(t);
    extenderTabela(t);
    TEST_ASSERT_EQUAL_INT(tamanhoAntigo*2, getTamanhoTabela(t));
    liberarTabela(t);
}

void teste_funcaoHash(){
    TEST_ASSERT_EQUAL_INT(funcaoHash(0, 10), 0);
    TEST_ASSERT_EQUAL_INT(funcaoHash(1, 10), 1);
    TEST_ASSERT_EQUAL_INT(funcaoHash(2, 10), 2);
    TEST_ASSERT_EQUAL_INT(funcaoHash(3, 10), 3);
    TEST_ASSERT_EQUAL_INT(funcaoHash(4, 10), 4);
    TEST_ASSERT_EQUAL_INT(funcaoHash(5, 10), 5);
    TEST_ASSERT_EQUAL_INT(funcaoHash(6, 10), 6);
    TEST_ASSERT_EQUAL_INT(funcaoHash(7, 10), 7);
    TEST_ASSERT_EQUAL_INT(funcaoHash(8, 10), 8);
    TEST_ASSERT_EQUAL_INT(funcaoHash(9, 10), 9);
    TEST_ASSERT_EQUAL_INT(funcaoHash(10, 10), 0);
}

void teste_criarConteudo(){
    conteudo c = criarConteudo(1);
    TEST_ASSERT_NOT_NULL(c);
    free(c);
}

void teste_inserirConteudo(){
    tabela t = criarEInicializarTabela();
    conteudo c1 = criarConteudo(2);
    conteudo c2 = criarConteudo(4);
    conteudo c3 = criarConteudo(6);
    conteudo c4 = criarConteudo(8);
    int tamanhoAntigo = getTamanhoTabela(t);

    inserirConteudo(t, c1);
    inserirConteudo(t, c2);
    inserirConteudo(t, c3);
    inserirConteudo(t, c4);

    TEST_ASSERT_EQUAL_INT(tamanhoAntigo*2, getTamanhoTabela(t));

    liberarTabela(t);
}

void teste_buscarConteudo(){
    tabela t = criarEInicializarTabela();
    conteudo c = criarConteudo(1);

    TEST_ASSERT_NULL(buscarConteudo(t, c));

    inserirConteudo(t, c);

    TEST_ASSERT_NOT_NULL(buscarConteudo(t, c));

    liberarTabela(t);
}

void teste_removerConteudo(){
    tabela t = criarEInicializarTabela();
    conteudo c = criarConteudo(1);

    inserirConteudo(t, c);

    TEST_ASSERT_NOT_NULL(buscarConteudo(t, c));

    removerConteudo(t, c);

    TEST_ASSERT_NULL(buscarConteudo(t, c));

    liberarTabela(t);
}

void teste_liberarTabela(){
    tabela t = criarEInicializarTabela();

    TEST_ASSERT_NOT_NULL(t);

    liberarTabela(t);
}