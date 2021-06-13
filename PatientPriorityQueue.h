//
// Created by jlleupol on 11/2/2020.
//

#pragma once
#include <vector>
#include "Patient.h"

class PatientPriorityQueue {
public:
    PatientPriorityQueue();

    /**
     * Add patient to the queue
     * @param newPatient in the priority queue
     */
    void enqueue(const Patient& newPatient);

    /**
     * remove one patient from the queue
     * @return the patient that was removed
     */
    Patient dequeue();

    /**
     * return the patient that will be removed next
     * @return
     */
    const Patient &peek() const;

    /**
     * see the patient at the desired index
     * @param index location within the queue
     * @return patient at the specified index
     */
    const Patient &peek(const int index) const;

    /**
     * the number of paitents currently in the queue
     * @return integer
     */
    int size() const;

private:
    static const int ROOT = 0;
    std::vector<Patient> data;

    /**
     * helper function to execute a heap sort after adding a patient
     * @param child
     */
    void percolateUp(int child);

    /**
     * helper function to execute heap sort after removing a patient
     * @param parentIndex
     */
    void percolateDown(int parentIndex);

    /**
     * Get the index of the parent of a given node in this heap.
     * Does not check if parent index is the root (parent(0) returns 0).
     *
     * @param childIndex child address
     * @return index of the left child of parentIndex in the data array
     */
    static int parent(int childIndex);

    /**
     * Check if the given node has a left child.
     *
     * @param parentIndex parent address
     * @return true if the left child of parentIndex is a current member of the
     *         heap
     */
    bool hasLeft(int parentIndex);

    /**
     * Check if the given node has a right child.
     *
     * @param parentIndex parent address
     * @return true if the right child of parentIndex is a current member of
     *         the heap
     */
    bool hasRight(int parentIndex) const;

    /**
     * Get the index of the left child of a given node in this heap.
     * Does not check if the child is a current member of this heap.
     *
     * @param parentIndex parent address
     * @return index of the left child of parentIndex in the data array
     */
    static int left(int parentIndex);

    /**
     * Get the index of the right child of a given node in this heap.
     * Does not check if the child is a current member of this heap.
     *
     * @param parentIndex parent address
     * @return index of the right child of parentIndex in the data array
     */
    static int right(int parentIndex);
};


