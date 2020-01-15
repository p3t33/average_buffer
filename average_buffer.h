#ifndef _AverageBuffer_
#define _AverageBuffer_
/*******************************************************************************
*                          average_buffer.h
* 						=====================
* File Name: average_buffer.h
* Related files: main.cpp average_buffer_test.cpp 
* #Version: V 1.0
* Writer: Kobi Medrish       
* Created: 10.1.2020
* Last update: 11.1.2020
*******************************************************************************/

/*============================================================================*/
/*                                  Definitions                               */
/*============================================================================*/
/*                                                      standard  directories */
/*                                                      ~~~~~~~~~~~~~~~~~~~~~ */
#include <memory> // std::shared_ptr
#include <iostream> // std::cout
/*============================================================================*/

namespace med
{
    
template <typename T>
class AverageBuffer
{
    private:
        struct Node; // auxiliary struct to hold buffer data
        using node_ptr = std::shared_ptr<AverageBuffer<T>::Node>;

    public:
        AverageBuffer(size_t buffer_size = 100);
        ~AverageBuffer() = default;

        AverageBuffer(const AverageBuffer&) = delete;
        AverageBuffer& operator=(const AverageBuffer&) = delete;
        AverageBuffer(const AverageBuffer&&) = delete;
        AverageBuffer& operator=(const AverageBuffer&&) = delete;

        // API
        // ------------------------------------------------------------------
        void addSample(T sample); // O(1)
        T getAverage();
        T getAverageForever(); // O(1)
        T getUpperQuarterAverage();
        T getLowerQuarterAverage(); 
        void clear(); // O(n)
        void print_buffer(); // O(n)

    private:
        // Auxiliary functions
        // ----------------------------------------------
        void update_number_and_sum_of_samples(T& sample);
        bool is_buffer_empty(); 
        bool is_buffer_at_maximum_capacity();
        size_t current_number_of_samples_in_buffer();
        size_t count_samples_in_quarter(size_t current_size_of_buffer);

        // managing variables 
        // ----------------------------------------------
        node_ptr m_head; // points to the newest sample in the buffer.
        node_ptr m_tail; // used as a reference point for the oldest sample.

        size_t m_buffer_size; // user defined at object creation.
        size_t m_total_number_of_samples;
        T m_sum_of_all_samples;
};

template <typename T>
struct AverageBuffer<T>::Node
{
    Node(T data):m_data(data), m_next_node(nullptr)
    {}

    T m_data;
    std::shared_ptr<Node> m_next_node;
};

    
/*============================================================================*/
/*                              Class AverageBuffer                           */
/*============================================================================*/
/*                               ~~~~~~~~~~~~~~~~~                            */
/*                               special functions                            */
/*                               ~~~~~~~~~~~~~~~~~                            */
/*                                                         Constructor / ctor */
/*                                                         ~~~~~~~~~~~~~~~~~~ */
template <typename T>
AverageBuffer<T>::AverageBuffer(size_t buffer_size):
               m_head(nullptr),
               m_tail(nullptr),
               m_buffer_size(buffer_size),
               m_total_number_of_samples(0),
               m_sum_of_all_samples(0)
{
    if (0 >= buffer_size)
    {
        throw std::runtime_error("invalid buffer_size");
    }
}

/*============================================================================*/
/*                     API functions / Public member functions                */
/*============================================================================*/
/*                                                                  addSample */
/*                                                                  ~~~~~~~~~ */
template <typename T>
void AverageBuffer<T>::addSample(T sample)
{
    // filling the buffer up to the maximum set capacity.
    if (false == is_buffer_at_maximum_capacity())
    {
        // if this is the first insert
        if (true == is_buffer_empty())
        {
            m_tail = std::make_shared<AverageBuffer<T>::Node>(sample);
            m_head = m_tail;
            update_number_and_sum_of_samples(sample);
            return;  
        }
        else
        {
            m_head->m_next_node = 
                               std::make_shared<AverageBuffer<T>::Node>(sample);
            m_head = m_head->m_next_node;
            update_number_and_sum_of_samples(sample);
            return;
        }
    }

    // buffer is already at maximum_capacity and oldest sample to be removed.
    if (m_total_number_of_samples >= m_buffer_size)
    {
        m_head->m_next_node = m_tail;
        m_head = m_tail;
        m_tail = m_tail->m_next_node;
        m_head->m_next_node = nullptr;
        m_head->m_data = sample;

        update_number_and_sum_of_samples(sample);
    }
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                                                                 getAverage */
/*                                                                 ~~~~~~~~~~ */
template <typename T>
T AverageBuffer<T>::getAverage()
{
    node_ptr runner = m_tail;
    float tot_sum_of_samples_in_quarter = 0;
    size_t num_of_samples_in_buffer = 0;

    while (nullptr != runner)
    {
        tot_sum_of_samples_in_quarter += runner->m_data;
        ++num_of_samples_in_buffer; 
        runner = runner->m_next_node;   
    }

    return ((tot_sum_of_samples_in_quarter / num_of_samples_in_buffer));
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                                                          getAverageForever */
/*                                                          ~~~~~~~~~~~~~~~~~ */
template <typename T>
T AverageBuffer<T>::getAverageForever()
{
    if (true == is_buffer_empty())
    {
        return (0);
    }

    return (m_sum_of_all_samples / m_total_number_of_samples);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                                                     getLowerQuarterAverage */
/*                                                     ~~~~~~~~~~~~~~~~~~~~~~ */
template <typename T>
T AverageBuffer<T>::getUpperQuarterAverage()
{

    if (true == is_buffer_empty())
    {
        return (0);
    }

    node_ptr runner = m_tail;
    size_t offset_counter = 0;
    float tot_sum_of_samples_in_quarter = 0; 
    size_t current_size_of_buffer = current_number_of_samples_in_buffer();
    size_t number_of_samples_in_quarter =
                               count_samples_in_quarter(current_size_of_buffer);
    size_t offset_to_upper_quarter = (current_size_of_buffer - 
                                      number_of_samples_in_quarter); 
    while (nullptr != runner)
    { 
        if (offset_counter >= offset_to_upper_quarter)
        {
            tot_sum_of_samples_in_quarter += runner->m_data;
        }

        ++offset_counter;
        runner = runner->m_next_node;   
    }
    
    return (tot_sum_of_samples_in_quarter / number_of_samples_in_quarter);    
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                                                     getLowerQuarterAverage */
/*                                                     ~~~~~~~~~~~~~~~~~~~~~~ */
template <typename T>
T AverageBuffer<T>::getLowerQuarterAverage()
{
    if (true == is_buffer_empty())
    {
        return (0);
    }

    node_ptr runner = m_tail;
    float tot_sum_of_samples_in_quarter = 0; 
    size_t current_size_of_buffer = current_number_of_samples_in_buffer();
    size_t number_of_samples_in_quarter = 
                               count_samples_in_quarter(current_size_of_buffer);

    for (size_t i = 0; i < number_of_samples_in_quarter; ++i)
    {
        tot_sum_of_samples_in_quarter += runner->m_data;
        runner = runner->m_next_node;
    }

    return (tot_sum_of_samples_in_quarter / number_of_samples_in_quarter);    
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                                                                      clear */
/*                                                                      ~~~~~ */
template <typename T>
void AverageBuffer<T>::clear()
{ 
    m_head = nullptr;
    node_ptr runner = m_tail;

    while (nullptr != m_tail)
    {
        m_tail = m_tail->m_next_node;
        runner->m_next_node = nullptr;
        runner = m_tail;
    }

    m_total_number_of_samples = 0;
    m_sum_of_all_samples = 0;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                                                               print_buffer */
/*                                                               ~~~~~~~~~~~~ */
template <typename T>
void AverageBuffer<T>::print_buffer()
{
    size_t current_size_of_buffer = current_number_of_samples_in_buffer();

    node_ptr runner = m_tail;
    std::cout << "max buffer capacity: " << m_buffer_size
              << ", current buffer capacity: " << current_size_of_buffer
              << ", total number of samples added: "<< m_total_number_of_samples
              << std::endl << std::endl;

    while (nullptr != runner)
    { 
        std::cout << runner->m_data << " -> "; 
        runner = runner->m_next_node;   
    }

    std::cout << "nullptr" <<std::endl <<std::endl;
}


/*============================================================================*/
/*                               Auxiliary functions                          */
/*============================================================================*/
/*                                           update_number_and_sum_of_samples */
/*                                           ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
template <typename T>
inline void AverageBuffer<T>::update_number_and_sum_of_samples(T& sample)
{
    ++m_total_number_of_samples;
    m_sum_of_all_samples += sample;    
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                                                            is_buffer_empty */
/*                                                            ~~~~~~~~~~~~~~~ */
template <typename T>
inline bool AverageBuffer<T>::is_buffer_empty()
{
    return ((nullptr == m_tail) && (nullptr == m_head));
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                                              is_buffer_at_maximum_capacity */
/*                                              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
template <typename T>
inline bool AverageBuffer<T>::is_buffer_at_maximum_capacity()
{
    return ((m_total_number_of_samples < m_buffer_size) ? false : true);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                                        current_number_of_samples_in_buffer */
/*                                        ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
template <typename T>
inline size_t AverageBuffer<T>::current_number_of_samples_in_buffer()
{
    return ((true == is_buffer_at_maximum_capacity()) ?
              m_buffer_size : m_total_number_of_samples);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                                                   count_samples_in_quarter */
/*                                                   ~~~~~~~~~~~~~~~~~~~~~~~~ */
template <typename T>
inline size_t AverageBuffer<T>::
count_samples_in_quarter(size_t current_size_of_buffer)
{
    size_t number_of_samples_in_quarter = (current_size_of_buffer / 4);
    if (0 == number_of_samples_in_quarter)
    {
        number_of_samples_in_quarter = 1;
    }

    return (number_of_samples_in_quarter);
}

} // namespace med
#endif // _AverageBuffer_