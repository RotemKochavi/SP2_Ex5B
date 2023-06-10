#include "MagicalContainer.hpp"
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

namespace ariel{

    // Func:: Check if prime
    bool isPrime(int num) {
        if (num <= 1)
            return false;
        for (int i = 2; i <= std::sqrt(num); i++) {
            if (num % i == 0)
                return false;
        }
        return true;
    }

    //************************* MagicalContainer Class *************************//

    MagicalContainer::MagicalContainer() {}

    void MagicalContainer::addElement(int element) {
        elements.push_back(element); // add the element to the vector elements
        std::sort(elements.begin(), elements.end()); // sort the elements

        // add pointer to the vector prime_elements if the element is a prime number
        prime_elements.clear();
        for(size_t i = 0; i < elements.size(); i++)
        if(isPrime(elements.at(i))){
            prime_elements.push_back(&elements.at(i));
        }
    }

    void MagicalContainer::removeElement(int element) {
        bool element_in_the_container = false;// If the element was in the container
        if (isPrime(element)) { // If the number is prime, remove from the prime container.
            for (auto item = prime_elements.begin(); item != prime_elements.end(); ++item) {
                if (**item == element) { //  If we found it -> remove the element
                    prime_elements.erase(item);
                    break;
                }
            }
        }
        for (auto it = elements.begin(); it != elements.end(); ++it) {
            if (*it == element) { // If we found it -> remove the element 
                elements.erase(it);
                element_in_the_container = true;
                break;
            }
        }
        if(!element_in_the_container) // If element doesn't exist -> throw error
            throw std::runtime_error("Error: Element isn't exist");
    }

    //************************* Iterator Class *************************//

    // Assignment operator
    MagicalContainer::Iterator& MagicalContainer::Iterator::operator=(const Iterator& other) {
        if(&getContainer() != &other.getContainer()){ //  If we try to assign different containers -> throw error
            throw runtime_error("Error: Iterators cannot be assigned if they are from different containers.");
        }
        if (this != &other) {
            setContainer(other.getContainer());
            setIndex(other.getIndex());
        }
        return *this;
    }

    MagicalContainer::Iterator::~Iterator() {}


    //************************* AscendingIterator Class *************************//

    MagicalContainer::AscendingIterator::AscendingIterator( MagicalContainer &cont, size_t index) : Iterator(cont,index){}
    
    // Default constructor
    MagicalContainer::AscendingIterator::AscendingIterator( MagicalContainer& magicalContainer) : Iterator(magicalContainer){} 
    
    // Copy constructor
    MagicalContainer::AscendingIterator::AscendingIterator(const AscendingIterator& other) :Iterator(other.getContainer(),other.getIndex()){}
    
    // Destructor
    MagicalContainer::AscendingIterator::~AscendingIterator() {}
    
    // Pre-increment operator
    MagicalContainer::AscendingIterator& MagicalContainer::AscendingIterator::operator++() {
        if(getIndex() >= getContainer().getElements().size() || *this == end()){ // If try to increase while we at the end ->throw error
            throw runtime_error("Error: Iterator out of bounds!");
        }
        increase(1); //  ++curr_index 
        return *this;
    }

    // Method to get an AscendingIterator pointing to the first element
    MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::begin() const {
        return AscendingIterator(getContainer(),0); 
    }

    // Method to get an AscendingIterator pointing one position past the last element
    MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::end() const {
        return AscendingIterator(getContainer(),getContainer().size());
    }


    //************************* SideCrossIterator Class *************************//
  
    MagicalContainer::SideCrossIterator::SideCrossIterator( MagicalContainer &cont, size_t index) : Iterator(cont,index){}

    MagicalContainer::SideCrossIterator::SideCrossIterator(MagicalContainer& magicalContainer) : Iterator(magicalContainer,0){}

    // Copy constructor
    MagicalContainer::SideCrossIterator::SideCrossIterator(const SideCrossIterator& other) : Iterator(other.getContainer(), other.getIndex()){}
        
    // Destructor
    MagicalContainer::SideCrossIterator::~SideCrossIterator() {}

    // Dereference operator
    int MagicalContainer::SideCrossIterator::operator*() const { 
        if (!(getIndex() % 2)) { // if the index is even return the value from start
            return getContainer().elements.at((getIndex() / 2));
        }
        else { // if the index is odd return the value from the end
            return getContainer().elements.at((getContainer().size() - 1 - (getIndex() - 1 ) / 2));
        }
    }

    // Pre-increment operator
    MagicalContainer::SideCrossIterator& MagicalContainer::SideCrossIterator::operator++() {
        if(getIndex() >= getContainer().getElements().size() || *this == end()){ // If try to increase while we at the end ->throw error
            throw runtime_error("Error: Iterator out of bounds!");
        }
        increase(1); //  ++curr_index
        return *this;
    }

    // Method to get a SideCrossIterator pointing to the first element
    MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::begin() const {
        return SideCrossIterator(getContainer(),0); 
    }

    // Method to get a SideCrossIterator pointing one position past the last element
    MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::end() const {
        return SideCrossIterator(getContainer(),getContainer().size());
    }



    //************************* PrimeIterator Class *************************//

    MagicalContainer::PrimeIterator::PrimeIterator( MagicalContainer &cont, size_t index) : Iterator(cont,index){}

    // Default constructor
    MagicalContainer::PrimeIterator::PrimeIterator( MagicalContainer& magicalContainer) : Iterator(magicalContainer, 0){}

    // Copy constructor
    MagicalContainer::PrimeIterator::PrimeIterator(const PrimeIterator& other) : Iterator(other.getContainer(), other.getIndex()){}
    

    // Destructor
    MagicalContainer::PrimeIterator::~PrimeIterator() {}

    // Dereference operator
    int MagicalContainer::PrimeIterator::operator*() const {
        return *getContainer().getPrimeElements().at(getIndex());
    }

    // Pre-increment operator
    MagicalContainer::PrimeIterator& MagicalContainer::PrimeIterator::operator++() {
        if(getIndex() >= getContainer().getPrimeElements().size() || *this == end()){ // If try to increase while we at the end ->throw error
            throw runtime_error("Error: Iterator out of bounds!");
        }
        increase(1); // ++curr_index
        return *this;
    }

    // Method to get a PrimeIterator pointing to the first prime element
    MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::begin() const {
        return PrimeIterator(getContainer(),0);
    }

    // Method to get a PrimeIterator pointing one position past the last prime element
    MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::end() const {
        return PrimeIterator(getContainer(),getContainer().getPrimeElements().size());
    }

}






    