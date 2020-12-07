#include "parque.h"
#include <vector>

ParqueEstacionamento::ParqueEstacionamento(unsigned int lot, unsigned int nMaxCli) : lotacao(lot),
    numMaximoClientes(nMaxCli), vagas(lot), clientes(std::vector<InfoCartao>()) {
}

unsigned ParqueEstacionamento::getNumLugares() const {
    return lotacao;
}

unsigned ParqueEstacionamento::getNumMaximoClientes() const {
    return numMaximoClientes;
}

int ParqueEstacionamento::posicaoCliente(const std::string &nome) const {

    auto found1 = std::find(clientes.begin(), clientes.end(), InfoCartao(nome, true));
    auto found2 = std::find(clientes.begin(), clientes.end(), InfoCartao(nome, false));

    if (found1 != clientes.end()) return found1-clientes.begin();
    else if (found2 != clientes.end()) return found2-clientes.begin();
    else return -1;
}

bool ParqueEstacionamento::adicionaCliente(const std::string &nome) {
    clientes.emplace_back(nome, false);
    return clientes.size() <= numMaximoClientes;
}

bool ParqueEstacionamento::entrar(const std::string &nome) {
    int pos = posicaoCliente(nome);
    if (pos != -1 && vagas && !clientes.at(pos).presente) {
        clientes.at(pos).presente = true;
        vagas --;
        return true;
    }
    return false;
}

bool ParqueEstacionamento::retiraCliente(const std::string &nome) {
    int pos = posicaoCliente(nome);
    if (pos != -1 && !clientes.at(pos).presente) {
        auto it = clientes.erase(clientes.begin() + pos);
        return true;
    }
    return false;
}

bool ParqueEstacionamento::sair(const std::string &nome) {
    int pos = posicaoCliente(nome);
    if (pos != -1 && clientes.at(pos).presente) {
        clientes.at(pos).presente = false;
        vagas ++;
        return true;
    }
    return false;
}

unsigned ParqueEstacionamento::getNumLugaresOcupados() const {
    return lotacao - vagas;
}

unsigned ParqueEstacionamento::getNumClientesAtuais() const {
    return clientes.size();
}
