#include <iostream>
#include <vector>
#include <numeric>

template <class N, class E> class Edge;

template <class N, class E>
class Node {
public:
    N info;
    std::vector< Edge<N,E> > edges;
    explicit Node(N inf) {
        info = inf;
    }
    bool operator==(const Node &rhs) const {
        return info == rhs.info && edges == rhs.edges;
    }
};

template <class N, class E>
class Edge {
public:
    E value;
    Node<N,E> *destination;
    Edge(Node<N,E> *dest, E val) {
        value = val;
        destination = dest;
    }

    bool operator==(const Edge &rhs) const {
        return destination == rhs.destination;
    }
    bool operator!=(const Edge &rhs) const {
        return rhs != *this;
    }

};

template <class N, class E>
class Graph {
    std::vector< Node<N,E> *> nodes;
public:
    Graph();
    ~Graph();
    Graph & addNode(const N &inf);
    Graph & addEdge(const N &begin, const N &end, const E &val);
    Graph & removeEdge(const N &begin, const N &end);
    E & edgeValue(const N &begin, const N &end);
    unsigned numEdges() const;
    unsigned numNodes() const;
    void print(std::ostream &os) const;
};

template <class N, class E>
std::ostream & operator<<(std::ostream &out, const Graph<N,E> &g);

template<class N, class E>
Graph<N, E>::Graph() : nodes() {

}

template<class N, class E>
Graph<N, E>::~Graph() {
    for (auto & node : nodes) {
        delete node;
    }
    nodes.clear();
}

template<class N, class E>
unsigned Graph<N, E>::numEdges() const {
    unsigned edges = std::accumulate(nodes.begin(), nodes.end(), 0, [](unsigned accumulate, Node<N, E>* node){
        return accumulate + (node->edges).size();
    });
    return edges;
}

template<class N, class E>
unsigned Graph<N, E>::numNodes() const {
    return nodes.size();
}

// exception NodeAlreadyExists
template <class N>
class NodeAlreadyExists {
public:
    N info;
    explicit NodeAlreadyExists(N inf) { info=inf; }
};

// exception NodeDoesNotExist
template <class N>
class NodeDoesNotExist {
public:
    N info;
    explicit NodeDoesNotExist(N inf) : info(inf) {}
};

template <class N>
std::ostream & operator<<(std::ostream &out, const NodeDoesNotExist<N> &no)
{ out << "Node does not exist: " << no.info; return out; }

// exception EdgeAlreadyExists
template <class N>
class EdgeAlreadyExists
{
public:
    N m_start, m_destination;
    EdgeAlreadyExists<N>(N start, N destination);
};

template<class N>
EdgeAlreadyExists<N>::EdgeAlreadyExists(N start, N destination) : m_start(start), m_destination(destination) {

}

template <class N>
std::ostream & operator<<(std::ostream &out, const EdgeAlreadyExists<N> &edge) {
    out << "Edge already exists: " << edge.m_start << " , " << edge.m_destination;
    return out;
}


// exception EdgeAlreadyExists
template <class N>
class EdgeDoesNotExist
{
public:
    N m_start, m_destination;
    EdgeDoesNotExist<N>(N start, N destination);
};

template<class N>
EdgeDoesNotExist<N>::EdgeDoesNotExist(N start, N destination) : m_start(start), m_destination(destination) {

}

template <class N>
std::ostream & operator<<(std::ostream &out, const EdgeDoesNotExist<N> &edge) {
    out << "Edge does not exist: " << edge.m_start << " , " << edge.m_destination;
    return out;
}


template<class N, class E>
Graph<N, E>& Graph<N, E>::addNode(const N &inf) {
    auto node = new Node<N, E>(inf);
    auto found = find_if(nodes.begin(), nodes.end(), [&node](Node<N, E>* node1){
        return node1->info == node->info  && node1->edges == node->edges;
    });
    if (found != nodes.end()) throw NodeAlreadyExists<N>(inf);
    nodes.push_back(node);
    return *this;
}

template<class N, class E>
Graph<N, E>& Graph<N, E>::addEdge(const N &begin, const N &end, const E &val) {
    auto findBegin = find_if(nodes.begin(), nodes.end(), [&begin](Node<N, E>* node1){
        return node1->info == Node<N, E>(begin).info;
    });
    auto findEnd = find_if(nodes.begin(), nodes.end(), [&end](Node<N, E>* node1){
        return node1->info == Node<N, E>(end).info;
    });
    if (findBegin == nodes.end()) throw NodeDoesNotExist<N>(begin);
    else if (findEnd == nodes.end()) throw NodeDoesNotExist<N>(end);

    Edge<N,E> edge = Edge<N, E> (*findEnd, val);
    auto findEdge = std::find(((*findBegin)->edges).begin(), ((*findBegin)->edges).end(), edge);
    if (findEdge != ((*findBegin)->edges).end()) throw EdgeAlreadyExists<N>(begin, end);

    (*findBegin)->edges.push_back(edge);
    return *this;
}

template<class N, class E>
E& Graph<N, E>::edgeValue(const N &begin, const N &end) {

    auto findBegin = find_if(nodes.begin(), nodes.end(), [&begin](Node<N, E>* node1){
        return node1->info == Node<N, E>(begin).info;
    });

    auto findEnd = find_if(nodes.begin(), nodes.end(), [&end](Node<N, E>* node1){
        return node1->info == Node<N, E>(end).info;
    });
    if (findBegin == nodes.end()) throw NodeDoesNotExist<N>(begin);
    else if (findEnd == nodes.end()) throw NodeDoesNotExist<N>(end);

    auto foundEdge = std::find_if((*findBegin)->edges.begin(), (*findBegin)->edges.end(), [&findBegin, &findEnd] (Edge<N, E> edge) {
        return edge.destination == *findEnd;
    });
    if (foundEdge == (*findBegin)->edges.end()) throw EdgeDoesNotExist<N>(begin, end);
    return (*foundEdge).value;
}

template<class N, class E>
Graph<N, E>& Graph<N, E>::removeEdge(const N &begin, const N &end) {

    auto findBegin = find_if(nodes.begin(), nodes.end(), [&begin](Node<N, E>* node1){
        return node1->info == Node<N, E>(begin).info;
    });

    if (findBegin == nodes.end()) throw NodeDoesNotExist<N>(begin);

    auto findEnd = find_if(nodes.begin(), nodes.end(), [&end](Node<N, E>* node1){
        return node1->info == Node<N, E>(end).info;
    });

    auto foundEdge = std::remove_if((*findBegin)->edges.begin(), (*findBegin)->edges.end(), [&findBegin, &findEnd] (Edge<N, E> edge) {
        return edge.destination == *findEnd;
    });

    if (foundEdge == (*findBegin)->edges.end()) {
        throw EdgeDoesNotExist<N>(begin, end);
    } else {
        (*findBegin)->edges.erase(foundEdge);
    }

    return *this;
}

template<class N, class E>
void Graph<N, E>::print(std::ostream &os) const {
    for (const auto &node : nodes) {
        os << "( " << node->info;
        for (const auto &edge : node->edges) {
            os << "[ " << edge.destination->info << " " << edge.value << "] ";
        }
        os << ") ";
    }
}

template <class N, class E>
std::ostream & operator<<(std::ostream &out, const Graph<N,E> &g) {
    g.print(out);
    return out;
}


template <class N>
std::ostream & operator<<(std::ostream &out, const NodeAlreadyExists<N> &no)
{ out << "Node already exists: " << no.info; return out; }






