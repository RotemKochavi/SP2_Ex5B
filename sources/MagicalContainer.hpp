#include <iostream>
#include <vector>
using namespace std;

namespace ariel{

    class MagicalContainer{
        private:
            vector <int> elements; //vector contains -> numbers
            vector <int*> prime_elements; //vector contains -> pointers of prime numbers
            
        public:
            MagicalContainer(); // Default constructor
            void addElement(int); // Adding element to the container
            void removeElement(int); // Removing element from the container
            
            size_t size() const { 
                return elements.size();
            }; // return -> size of the container

            vector<int> getElements() const { 
                return elements;
            } // return -> vector of numbers
            
            vector<int*> getPrimeElements() const { 
                return prime_elements;
            } // return -> vector of prime numbers

            class Iterator{

                private:
                    MagicalContainer& container;
                    size_t curr_index;

                public:
                    
                    // constructors    
                    Iterator(MagicalContainer& magicalContainer): container(magicalContainer), curr_index(0){}
                    Iterator(MagicalContainer& magicalContainer, size_t index): container(magicalContainer), curr_index(index){}
                    Iterator(const Iterator& other):container(other.container), curr_index(other.curr_index){}

                    // Needed to pass "make tidy"
                    Iterator() = delete; 
                    Iterator(Iterator&&) = delete;
                    Iterator& operator=(Iterator&&) = delete;  

                    void increase(size_t num){ 
                        curr_index += num;
                    }
                    void setContainer(MagicalContainer& cont){ 
                        container = cont;
                    }
                    void setIndex(size_t num){ 
                        curr_index = num;
                    }
                    MagicalContainer& getContainer() const{
                        return container;
                    }
                    size_t getIndex() const{
                        return curr_index;
                    }

                    // comparison functions //

                    virtual bool operator==(const Iterator& other) const{
                        return &container == &other.container && curr_index == other.curr_index;
                    } // Equality comparison  

                    virtual bool operator!=(const Iterator& other) const{
                        return !(*this == other);
                    } // Inequality comparison   

                    virtual bool operator>(const Iterator& other) const{
                        return curr_index > other.curr_index;
                    } // Greater than comparison 

                    virtual bool operator<(const Iterator& other) const{
                        return curr_index < other.curr_index;
                    } // Less than comparison  

                    virtual int operator*() const { 
                        return getContainer().getElements().at(getIndex()); 
                    }

                    Iterator& operator=(const Iterator& other);

                    virtual ~Iterator(); // destructor

            };


        class AscendingIterator: public Iterator{

            public:
                // constructors
                AscendingIterator( MagicalContainer &, size_t);
                AscendingIterator( MagicalContainer& magicalContainer);
                AscendingIterator(const AscendingIterator& other);// Copy constructor     

                // Needed to pass "make tidy"
                AscendingIterator() = delete; 
                AscendingIterator(AscendingIterator&&) = delete;
                AscendingIterator& operator=(AscendingIterator&&) = delete;
                AscendingIterator& operator=(const AscendingIterator& other) = default; // Assignment operator    

                AscendingIterator& operator++(); // ++i

                AscendingIterator begin()const ;
                AscendingIterator end()const ;
                
                ~AscendingIterator() override; // destructor  
        };

        class SideCrossIterator : public Iterator{

            public:
                    // constructors
                    SideCrossIterator( MagicalContainer &, size_t);
                    SideCrossIterator( MagicalContainer& magicalContainer);                
                    SideCrossIterator(const SideCrossIterator& other); // Copy constructor              
                        
                    // Needed to pass "make tidy"
                    SideCrossIterator() = delete; 
                    SideCrossIterator(SideCrossIterator&&) = delete;
                    SideCrossIterator& operator=(SideCrossIterator&&) = delete;
                    SideCrossIterator& operator=(const SideCrossIterator& other) = default;// Assignment operator      
    
                    int operator*() const override;               
                    SideCrossIterator& operator++(); // ++i

                    SideCrossIterator begin()const;
                    SideCrossIterator end()const;
                    
                    ~SideCrossIterator() override; // destructor    
        };

        class PrimeIterator : public Iterator{

            public:
                    // constructors
                    PrimeIterator( MagicalContainer &, size_t);
                    PrimeIterator( MagicalContainer& magicalContainer);
                    PrimeIterator(const PrimeIterator& other); // Copy constructor
                    
                    // Needed to pass "make tidy"
                    PrimeIterator() = delete; 
                    PrimeIterator(PrimeIterator&&) = delete;
                    PrimeIterator& operator=(PrimeIterator&&) = delete;
                    PrimeIterator& operator=(const PrimeIterator& other) = default;// Assignment operator

                    int operator*() const override;
                    PrimeIterator& operator++(); // ++i

                    PrimeIterator begin()const;
                    PrimeIterator end() const;
                    
                    ~PrimeIterator() override; // destructor 
        };
    };
}