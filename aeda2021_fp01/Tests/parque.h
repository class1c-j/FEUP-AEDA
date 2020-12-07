#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <algorithm>


class InfoCartao {
public:
	std::string nome;
	bool presente;
	InfoCartao(std::string name, bool present) : nome(std::move(name)), presente(present) {}
    bool operator==(const InfoCartao &rhs) const {
        return nome == rhs.nome && presente == rhs.presente;
    }
};

class ParqueEstacionamento {
	unsigned int vagas;
	const unsigned int lotacao;
	std::vector<InfoCartao> clientes;
	const unsigned int numMaximoClientes;
public:
	ParqueEstacionamento(unsigned int lot, unsigned int nMaxCli);
	bool adicionaCliente(const std::string & nome);
	bool retiraCliente(const std::string & nome);
	bool entrar(const std::string & nome);
	bool sair(const std::string & nome);
	int posicaoCliente(const std::string & nome) const;
	unsigned getNumLugares() const;
	unsigned getNumMaximoClientes() const;
	unsigned getNumLugaresOcupados() const;
	unsigned getNumClientesAtuais() const;
};
