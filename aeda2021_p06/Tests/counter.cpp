#include <queue>
#include <cstdlib>
#include "counter.h"
#include "exceptions.h"
using namespace std;

Client::Client() {
    numGifts = rand() % 5 + 1;
}


unsigned Client::getNumGifts() const {
    return numGifts;
}



Counter::Counter(unsigned wt): wrappingTime(wt), actualTime(0), nextLeave(0), numAttendedClients(0){
    nextEnter = rand() % 20 + 1;
}


unsigned Counter::getActualTime() const {
    return actualTime;
}


unsigned Counter::getNextEnter() const {
    return nextEnter;
}


unsigned Counter::getNumAttendedClients() const {
    return numAttendedClients;
}


unsigned Counter::getWrappingTime() const {
    return wrappingTime;
}


unsigned Counter::getNextLeave() const {
    return nextLeave;
}


Client & Counter::getNextClient() {
    if (clients.empty()) throw EmptyQueue();
    return clients.front();
}


void Counter::enter() {
    Client client{};
    clients.push(client);
    nextEnter = rand() % 20 + 1;
    if (clients.size() == 1) nextLeave = actualTime + client.getNumGifts()*wrappingTime;
    std::cout << "actual time: " << actualTime;
    std::cout << "\nnew customer arrived with " << client.getNumGifts() << " gifts\n";
}


void Counter::leave() {
    if (clients.empty()) throw EmptyQueue();
    Client left = clients.front();
    clients.pop();
    nextLeave = actualTime + clients.front().getNumGifts()*wrappingTime;
    numAttendedClients++;
    std::cout << "actual time: " << actualTime;
    std::cout << "\nlast client left with " << left.getNumGifts() << " gifts\n";
}


void Counter:: nextEvent() {

    if (nextLeave <= nextEnter && !clients.empty()) {leave(); actualTime += nextLeave;}
    else if (nextLeave >= nextEnter || clients.empty()) {enter(); actualTime += nextEnter;};

}



ostream & operator << (ostream & out, const Counter & c2) {
    out << "Attended : " << c2.getNumAttendedClients() << "\nPending : " << c2.clients.size();
    return out;
}


