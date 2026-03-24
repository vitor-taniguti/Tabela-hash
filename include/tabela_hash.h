#ifndef TABELA_HASH
#define TABELA_HASH

typedef void* tabela;
typedef void* conteudo;

/// @brief Cria e inicializa a tabela hash com tamanho inicial 2
/// @return O diretório criado
tabela criarEInicializarTabela();

/// @brief Pega o tamanho da tabela
/// @param t Tabela que o tamanho será pego
/// @return Tamanho da tabela
int getTamanhoTabela(tabela t);

/// @brief Extende a tabela, dobrando seu tamanho
/// @param d Diretorio que será extendido
void extenderTabela(tabela t);

/// @brief Função responsável pelo espalhamento da tabela
/// @param id Identificador único do conteúdo
/// @param tamanho Tamanho do tabela
/// @return A chave codificada pela função
int funcaoHash(int id, int tamanho);

/// @brief Cria um conteúdo
/// @param id Identificador único do conteúdo
/// @return Um ponteiro para o conteúdo criado
conteudo criarConteudo(int id);

/// @brief Pega o Id do conteúdo
/// @param c Ponteiro para o conteúdo
/// @return O identificador do conteúdo
int getIdConteudo(conteudo c);

/// @brief Insere a chave na tabela utilizando a função hash
/// @param t Tabela onde a conteúdo será inserido
/// @param c Conteúdo que será inserido
void inserirConteudo(tabela t, conteudo c);

/// @brief Busca a chave na tabela hash
/// @param t Tabela onde o conteúdo será buscado
/// @param c Conteúdo que será buscado
/// @return Retorna o endereço do conteudo, se encontrada, caso contrário, retorna NULL
conteudo buscarConteudo(tabela t, conteudo c);

/// @brief Remove a chave da tabela hash
/// @param t Tabela onde o conteúdo será removido 
/// @param c Conteudo que será removido
void removerConteudo(tabela t, conteudo c);

/// @brief Libera a memória alocada para a tabela hash
/// @param tabela Ponteiro para a tabela
void liberarTabela(tabela t);

#endif