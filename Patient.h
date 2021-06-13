//
// Created by jlleupol on 11/2/2020.
//

#pragma once
#include <string>



class Patient {
public:
    /**
     * list of priority codes at the hospital
     */
    enum PriorityCode {
        IMMEDIATE = 1, EMERGENCY = 2, URGENT = 3, MINIMAL = 4
    };

    /**
     * default constructor
     */
    Patient() {
        this->name = "Bruce Wayne";
        this->priorityCode = MINIMAL;
        numberOfPatients++;
        this->arrivalOrder = numberOfPatients;
    }

    /**
     * constructor with patient attributes
     * @param patientName
     * @param patientPriority taken from the enum list
     */
    Patient(std::string patientName, PriorityCode patientPriority){
        this->name = patientName;
        this->priorityCode = patientPriority;
        numberOfPatients++;
        this->arrivalOrder = numberOfPatients;
    };

    /**
     * firt check priority code, then check arrival order
     * @param other patient to compare against
     * @return negative number if this patient is a higher priority, positive number if lower priority
     */
    int compareTo(const Patient &other);

    /**
     * allows client to print patient name, priority, and arrival order
     * @return
     */
    std::string toString();

private:
    std::string name;
    PriorityCode priorityCode;
    int arrivalOrder;
    static int numberOfPatients;
};

//int Patient::numberOfPatients = 0;

