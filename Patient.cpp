//
// Created by jlleupol on 11/2/2020.
//

#include "Patient.h"

// increments by 1 with every patient added
int Patient::numberOfPatients = 0;


int Patient::compareTo(const Patient &other) {
    if (this->priorityCode == other.priorityCode)
        return this->arrivalOrder - other.arrivalOrder;
    else
        return this->priorityCode - other.priorityCode;
}


std::string Patient::toString() {
    std::string priority = "";

    if (priorityCode == IMMEDIATE)
        priority = "IMMEDIATE";
    else if (priorityCode == EMERGENCY)
        priority = "EMERGENCY";
    else if (priorityCode == URGENT)
        priority = "URGENT";
    else
        priority = "MINIMAL";

    return name + " {priority: " + priority + ", arrival: " + std::to_string(arrivalOrder) + "}";
}


