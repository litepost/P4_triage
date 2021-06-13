//
// Created by jlleupol on 11/2/2020.
//

#include <stdexcept>
#include "PatientPriorityQueue.h"


//PatientPriorityQueue::PatientPriorityQueue(const std::vector<Patient> &data) : data(data) {}
PatientPriorityQueue::PatientPriorityQueue() {}

int PatientPriorityQueue::size() const {
    return data.size();
}


void PatientPriorityQueue::enqueue(const Patient& newPatient) {
    data.push_back(newPatient);
    percolateUp(size() - 1);
}


Patient PatientPriorityQueue::dequeue() {
    //copy root to temp obj
    Patient pat = peek();
    //copy last obj to root
    data[ROOT] = data[size()-1];
    //remove last obj
    data.pop_back();
    //heap sort
    percolateDown(ROOT);

    return pat;
}


const Patient &PatientPriorityQueue::peek() const {
    if (data.empty())
        throw std::invalid_argument("empty queue");
    return data[ROOT];
}


const Patient &PatientPriorityQueue::peek(const int index) const {
    if (data.empty())
        throw std::invalid_argument("empty queue");
    return data[index];
}


void PatientPriorityQueue::percolateUp(int child) {
    if (child > ROOT) {
        int p = parent(child);
        if (data[child].compareTo(data[p]) < 0) {
            std::swap(data[p], data[child]);
            percolateUp(p);
        }
    }
}


void PatientPriorityQueue::percolateDown(int parent) {
    if (hasLeft(parent)) {
        int child = left(parent);
        if (hasRight(parent)) {
            int r = right(parent);
            if (data[r].compareTo(data[child]) < 0)
                child = r;
        }
        if (data[child].compareTo(data[parent]) < 0) {
            std::swap(data[parent], data[child]);
            percolateDown(child);
        }
    }
}


int PatientPriorityQueue::parent(int childIndex) {
    return (childIndex - 1) / 2;
}


bool PatientPriorityQueue::hasLeft(int parentIndex) {
    return left(parentIndex) < data.size();
}


bool PatientPriorityQueue::hasRight(int parentIndex) const {
    return right(parentIndex) < data.size();
}


int PatientPriorityQueue::left(int parentIndex) {
    return parentIndex * 2 + 1;
}


int PatientPriorityQueue::right(int parentIndex) {
    return left(parentIndex) + 1;
}














