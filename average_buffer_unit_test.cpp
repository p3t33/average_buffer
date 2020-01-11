/*******************************************************************************
*                          average_buffer_test.cpp
* 						=====================
* File Name: average_buffer_test.cpp
* Related files: main.cpp average_buffer.h
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
#include <iostream> // std::cout

/*============================================================================*/
/*                                                          local directories */
/*                                                          ~~~~~~~~~~~~~~~~~ */
#include "average_buffer.h"
using namespace med;

/*============================================================================*/
/*                                                                     Colors */
/*                                                                     ~~~~~~ */
const char* const green = "\033[1;32m";
const char* const red = "\033[1;31m";
const char* const reset = "\033[0m"; 
/*============================================================================*/
/*                             ~~~~~~~~~~~~~~~~~~~                            */
/*                             Forward declaration                            */
/*                             ~~~~~~~~~~~~~~~~~~~                            */
/*                                                                 Unit tests */
/*                                                                 ~~~~~~~~~~ */
static void unit_test_ddSample(void);
static void Unit_test_getAverage(void);
static void unit_test_getAverageForever(void);
static void unit_test_getLowerQuarterAverage(void);
static void unit_test_getUpperQuarterAverage(void);
static void unit_test_clear(void);

/*============================================================================*/
/*                                                              User function */
/*                                                              ~~~~~~~~~~~~~ */
float calculate_average(float* arr, float size_of_array);
/*============================================================================*/

int main()
{
    unit_test_ddSample();
    Unit_test_getAverage();
    unit_test_getAverageForever();
    unit_test_getLowerQuarterAverage();
    unit_test_getUpperQuarterAverage();
    unit_test_clear();

    return (0);
}

/*============================================================================*/
/*                                   unit_tests                               */
/*============================================================================*/
/*                                                        unit_test_ddSample */
/*                                                        ~~~~~~~~~~~~~~~~~~~ */

static void unit_test_ddSample(void)
{   
    float source[16] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
    AverageBuffer<float> thirtytwo_units_buffer(32);
    AverageBuffer<float> sixteen_units_buffer(16);
    AverageBuffer<float> eight_units_buffer(8);
    AverageBuffer<float> four_units_buffer(4);
    AverageBuffer<float> two_units_buffer(2);
    AverageBuffer<float> one_unit_buffer(1);


    std::cout << "===================== unit_test_ddSample ==================="
              << std::endl;
    std::cout << "Source for the buffer:" << std::endl;
    for (size_t i = 0; i < 16; i++)
    {
        std::cout << source[i] << " " ;
    }
    std::cout << std::endl << std::endl;

    // Adding new samples to the the buffers
    for (int i = 0; i < 16; i++)
    {  
        thirtytwo_units_buffer.addSample(source[i]);
        sixteen_units_buffer.addSample(source[i]);
        eight_units_buffer.addSample(source[i]);
        four_units_buffer.addSample(source[i]);
        two_units_buffer.addSample(source[i]);
        one_unit_buffer.addSample(source[i]);
    }

    std::cout << "Buffer is twice the size of the source" << std::endl;
    thirtytwo_units_buffer.print_buffer();
    std::cout << std::endl << std::endl;

    std::cout << "Buffer is the same size as the source" << std::endl;
    sixteen_units_buffer.print_buffer();
    std::cout << std::endl << std::endl;

    std::cout << "Buffer is half the size of the source" << std::endl;
    eight_units_buffer.print_buffer();
    std::cout << std::endl << std::endl;

    std::cout << "Buffer is quarter the size of the source" << std::endl;
    four_units_buffer.print_buffer();
    std::cout << std::endl << std::endl;

    std::cout << "Buffer is 16/2 the size of the source" << std::endl;
    two_units_buffer.print_buffer();
    std::cout << std::endl << std::endl;

    std::cout << "Buffer is 16/1 the size of the source" << std::endl;
    one_unit_buffer.print_buffer();
    std::cout << std::endl << std::endl;;

    std::cout << "============================================================="
              << std::endl
              << std::endl
              << std::endl;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                                                       Unit_test_getAverage */
/*                                                       ~~~~~~~~~~~~~~~~~~~~ */
static void Unit_test_getAverage(void)
{
    float source[16] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
    AverageBuffer<float> thirtytwo_units_buffer(32);
    AverageBuffer<float> sixteen_units_buffer(16);
    AverageBuffer<float> eight_units_buffer(8);
    AverageBuffer<float> four_units_buffer(4);
    AverageBuffer<float> two_units_buffer(2);
    AverageBuffer<float> one_unit_buffer(1);
    std::cout << "================== Unit_test_getAverage ====================="
              << std::endl;    
    
    std::cout << "Source for the buffer:" << std::endl;
    for (size_t i = 0; i < 16; i++)
    {
        std::cout << source[i] << " " ;
    }
    std::cout << std::endl << std::endl;

    // Adding new samples to the the buffers
    for (int i = 0; i < 16; i++)
    {  
        thirtytwo_units_buffer.addSample(source[i]);
        sixteen_units_buffer.addSample(source[i]);
        eight_units_buffer.addSample(source[i]);
        four_units_buffer.addSample(source[i]);
        two_units_buffer.addSample(source[i]);
        one_unit_buffer.addSample(source[i]);
    }

    if (thirtytwo_units_buffer.getAverage() == calculate_average(source, 16))
    {
        std::cout << "thirtytwo units buffer average is: " 
                  << thirtytwo_units_buffer.getAverage() << " "
                  << green << "SUCCESS " << reset 
                  << std::endl;;
    }
    else
    {
        std::cout << "thirtytwo units buffer average: " 
                  << thirtytwo_units_buffer.getAverage() << " "
                  << red << "FAILURE" << reset << std::endl;
    }

    if (sixteen_units_buffer.getAverage() == calculate_average(source, 16))
    {
        std::cout << "sixteen units buffer average is: " 
                  << sixteen_units_buffer.getAverage() << " "
                  << green << "SUCCESS " << reset 
                  << std::endl;
    }
    else
    {
        std::cout << "sixteen units buffer average: " 
                  << sixteen_units_buffer.getAverage() << " "
                  << red << "FAILURE" << reset << std::endl;

    }

    if (eight_units_buffer.getAverage() == calculate_average((source + 8), 8))
    {
        std::cout << "eight units buffer average is: " 
                  << eight_units_buffer.getAverage() << " "
                  << green << "SUCCESS " << reset 
                  << std::endl;
    }
    else
    {
        std::cout << "eight units buffer average: " 
                  << eight_units_buffer.getAverage() << " "
                  << red << "FAILURE" << reset << std::endl;
    }

    if (four_units_buffer.getAverage() == calculate_average((source + 12), 4))
    {
        std::cout << "four units buffer average is: " 
                  << four_units_buffer.getAverage() << " "
                  << green << "SUCCESS " << reset 
                  << std::endl;;
    }
    else
    {
        std::cout << "four units buffer average: " 
                  << four_units_buffer.getAverage() << " "
                  << red << "FAILURE" << reset << std::endl;
    }

    if (two_units_buffer.getAverage() == calculate_average((source + 14), 2))
    {
        std::cout << "two units buffer average is: " 
                  << two_units_buffer.getAverage() << " "
                  << green << "SUCCESS " << reset 
                  << std::endl;
    }
    else
    {
        std::cout << "two units buffer average: " 
                  << two_units_buffer.getAverage() << " "
                  << red << "FAILURE" << reset << std::endl;
    }

    if (one_unit_buffer.getAverage() == calculate_average((source + 15), 1))
    {
        std::cout << "one units buffer average is: " 
                  << one_unit_buffer.getAverage() << " "
                  << green << "SUCCESS " << reset 
                  << std::endl;;
    }
    else
    {
        std::cout << "one units buffer average: " 
                  << one_unit_buffer.getAverage() << " "
                  << red << "FAILURE" << reset << std::endl;
    }
    
    std::cout << "============================================================="
              << std::endl
              << std::endl
              << std::endl;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                                                unit_test_getAverageForever */
/*                                                ~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
static void unit_test_getAverageForever(void)
{
    float source[16] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
    AverageBuffer<float> thirtytwo_units_buffer(32);
    AverageBuffer<float> sixteen_units_buffer(16);
    AverageBuffer<float> eight_units_buffer(8);
    AverageBuffer<float> four_units_buffer(4);
    AverageBuffer<float> two_units_buffer(2);
    AverageBuffer<float> one_unit_buffer(1);


    std::cout << "================= unit_test_getAverageForever ==============="
              << std::endl;    
   
    std::cout << "Source for the buffer:" << std::endl;
    for (size_t i = 0; i < 16; i++)
    {
        std::cout << source[i] << " " ;
    }
    std::cout << std::endl << std::endl;

    // Adding new samples to the the buffers
    for (int i = 0; i < 16; i++)
    {  
        thirtytwo_units_buffer.addSample(source[i]);
        sixteen_units_buffer.addSample(source[i]);
        eight_units_buffer.addSample(source[i]);
        four_units_buffer.addSample(source[i]);
        two_units_buffer.addSample(source[i]);
        one_unit_buffer.addSample(source[i]);
    }

    if (thirtytwo_units_buffer.getAverageForever() ==
        calculate_average(source, 16))
    {
        std::cout << "thirtytwo units buffer average is: " 
                  << thirtytwo_units_buffer.getAverageForever() << " "
                  << green << "SUCCESS " << reset 
                  << std::endl;;
    }
    else
    {
        std::cout << "thirtytwo units buffer average: "
                  << thirtytwo_units_buffer.getAverageForever() << " " 
                  << red << "FAILURE" << reset << std::endl;
    }

    if (sixteen_units_buffer.getAverageForever() ==
        calculate_average(source, 16))
    {
        std::cout << "sixteen units buffer average is: " 
                  << sixteen_units_buffer.getAverageForever() << " "
                  << green << "SUCCESS " << reset 
                  << std::endl;
    }
    else
    {
        std::cout << "sixteen units buffer average: " 
                  << sixteen_units_buffer.getAverageForever() << " "
                  << red << "FAILURE" << reset << std::endl;
    }

    if (eight_units_buffer.getAverageForever() == calculate_average(source, 16))
    {
        std::cout << "eight units buffer average is: " 
                  << eight_units_buffer.getAverageForever() << " "
                  << green << "SUCCESS " << reset 
                  << std::endl;
    }
    else
    {
        std::cout << "eight units buffer average: " 
                  << eight_units_buffer.getAverageForever() << " "
                  << red << "FAILURE" << reset << std::endl;
    }

    if (four_units_buffer.getAverageForever() == calculate_average(source, 16))
    {
        std::cout << "four units buffer average is: " 
                  << four_units_buffer.getAverageForever() << " "
                  << green << "SUCCESS " << reset 
                  << std::endl;;
    }
    else
    {
        std::cout << "four units buffer average: " 
                  << four_units_buffer.getAverageForever() << " "
                  << red << "FAILURE" << reset << std::endl;
    }

    if (two_units_buffer.getAverageForever() == calculate_average(source, 16))
    {
        std::cout << "two units buffer average is: " 
                  << two_units_buffer.getAverageForever() << " "
                  << green << "SUCCESS " << reset 
                  << std::endl;
    }
    else
    {
        std::cout << "two units buffer average: " 
                  << two_units_buffer.getAverageForever() << " "
                  << red << "FAILURE" << reset << std::endl;
    }

    if (one_unit_buffer.getAverageForever() == calculate_average(source, 16))
    {
        std::cout << "one units buffer average is: " 
                  << one_unit_buffer.getAverageForever() << " "
                  << green << "SUCCESS " << reset 
                  << std::endl;;
    }
    else
    {
        std::cout << "one units buffer average: " 
                  << one_unit_buffer.getAverageForever() << " "
                  << red << "FAILURE" << reset << std::endl;
    }



    std::cout << "============================================================="
              << std::endl
              << std::endl
              << std::endl;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                                           unit_test_getLowerQuarterAverage */
/*                                           ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
static void unit_test_getLowerQuarterAverage(void)
{
    float source[9] = {1,2,3,4,5,6,7,8,9};
    float expected_lower_quarter_average[9] = {1,1,1,1,1,1,1,1.5,2.5};

    AverageBuffer<float> eight_units_buffer(8);
    std::cout << "=========== unit_test_getLowerQuarterAverage ================"
              << std::endl;    
       
    std::cout << "sample source for eight units buffer is:" << std::endl;
    for (size_t i = 0; i < 9; i++)
    {
        std::cout << source[i] << " " ;
    }
    std::cout << std::endl << std::endl;


    if (0 == eight_units_buffer.getLowerQuarterAverage())
    {
        std::cout << "getLowerQuarterAverage on an empty buffer "  
                  << green << "SUCCESS " << reset  << std::endl;
    }
    else
    {
        std::cout << "getLowerQuarterAverage on an empty buffer "  
                  << red << "FAILURE " << reset  << std::endl;

    }


    for (int i = 0; i < 9; i++)
    {  
        eight_units_buffer.addSample(source[i]);

        if (expected_lower_quarter_average [i] ==
            eight_units_buffer.getLowerQuarterAverage())
        {
            std::cout << "number of samples: " << (i + 1) 
                      << ", lower quarter average is: "
                      << eight_units_buffer.getLowerQuarterAverage() << " "
                      << green << "SUCCESS " << reset  << std::endl;     
        }

        else
        {
            std::cout << "number of samples: " << (i + 1)
                      << ", lower quarter average is: "
                      << eight_units_buffer.getLowerQuarterAverage() << " "
                      << red << "FAILURE " << reset  << std::endl;  
        }
    }


    
    std::cout << "============================================================="
              << std::endl
              << std::endl
              << std::endl;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                                           unit_test_getUpperQuarterAverage */
/*                                           ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
static void unit_test_getUpperQuarterAverage(void)
{
    float source[9] = {1,2,3,4,5,6,7,8,9};
    float expected_lower_quarter_average[9] = {1,2,3,4,5,6,7,7.5,8.5};

    AverageBuffer<float> eight_units_buffer(8);
    std::cout << "=========== unit_test_getUpperQuarterAverage ================"
              << std::endl;    
       
    std::cout << "sample source for eight units buffer is:" << std::endl;
    for (size_t i = 0; i < 9; i++)
    {
        std::cout << source[i] << " " ;
    }
    std::cout << std::endl << std::endl;


    if (0 == eight_units_buffer.getUpperQuarterAverage())
    {
        std::cout << "getUpperQuarterAverage on an empty buffer "  
                  << green << "SUCCESS " << reset  << std::endl;
    }
    else
    {
        std::cout << "getUpperQuarterAverage on an empty buffer "  
                  << red << "FAILURE " << reset  << std::endl;

    }


    for (int i = 0; i < 9; i++)
    {  
        eight_units_buffer.addSample(source[i]);

        if (expected_lower_quarter_average [i] ==
            eight_units_buffer.getUpperQuarterAverage())
        {
            std::cout << "number of samples: " << (i + 1) 
                      << ", upper quarter average is: "
                      << eight_units_buffer.getUpperQuarterAverage() << " "
                      << green << "SUCCESS " << reset  << std::endl;     
        }

        else
        {
            std::cout << "number of samples: " << (i + 1)
                      << ", upper quarter average is: "
                      << eight_units_buffer.getUpperQuarterAverage() << " "
                      << red << "FAILURE " << reset  << std::endl;  
        }
    }


    std::cout << "============================================================="
              << std::endl
              << std::endl
              << std::endl;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                                                            unit_test_clear */
/*                                                            ~~~~~~~~~~~~~~~ */
static void unit_test_clear(void)
{
    float source[16] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
    AverageBuffer<float> thirtytwo_units_buffer(32);
    AverageBuffer<float> sixteen_units_buffer(16);
    AverageBuffer<float> eight_units_buffer(8);
    AverageBuffer<float> four_units_buffer(4);
    AverageBuffer<float> two_units_buffer(2);
    AverageBuffer<float> one_unit_buffer(1);


    std::cout << "===================== unit_test_clear ======================="
              << std::endl;    
   
    std::cout << "Source for the buffer:" << std::endl;
    for (size_t i = 0; i < 16; i++)
    {
        std::cout << source[i] << " " ;
    }
    std::cout << std::endl << std::endl;

    // Adding new samples to the the buffers
    for (int i = 0; i < 16; i++)
    {  
        thirtytwo_units_buffer.addSample(source[i]);
        sixteen_units_buffer.addSample(source[i]);
        eight_units_buffer.addSample(source[i]);
        four_units_buffer.addSample(source[i]);
        two_units_buffer.addSample(source[i]);
        one_unit_buffer.addSample(source[i]);
    }

    std::cout << "~~~~~~~~~ buffers printput after samples addition ~~~~~~~~~~~"
              << std::endl << std::endl;

    thirtytwo_units_buffer.print_buffer();
    sixteen_units_buffer.print_buffer();
    eight_units_buffer.print_buffer();
    four_units_buffer.print_buffer();
    two_units_buffer.print_buffer();
    one_unit_buffer.print_buffer();

    std::cout << std::endl;
              



    std::cout << "~~~~~~~~~~~ buffers printput after clear executed ~~~~~~~~~~~"
              << std::endl;

    thirtytwo_units_buffer.clear();
    sixteen_units_buffer.clear();
    eight_units_buffer.clear();
    four_units_buffer.clear();
    two_units_buffer.clear();
    one_unit_buffer.clear();

    thirtytwo_units_buffer.print_buffer();
    sixteen_units_buffer.print_buffer();
    eight_units_buffer.print_buffer();
    four_units_buffer.print_buffer();
    two_units_buffer.print_buffer();
    one_unit_buffer.print_buffer();

    std::cout << std::endl;

    std::cout << "~~~ buffers printout after second run of samples addition ~~~"
            << std::endl;


    for (int i = 0; i < 16; i++)
    {  
        thirtytwo_units_buffer.addSample(source[i]);
        sixteen_units_buffer.addSample(source[i]);
        eight_units_buffer.addSample(source[i]);
        four_units_buffer.addSample(source[i]);
        two_units_buffer.addSample(source[i]);
        one_unit_buffer.addSample(source[i]);
    }

    thirtytwo_units_buffer.print_buffer();
    sixteen_units_buffer.print_buffer();
    eight_units_buffer.print_buffer();
    four_units_buffer.print_buffer();
    two_units_buffer.print_buffer();
    one_unit_buffer.print_buffer();

    std::cout << "============================================================="
              << std::endl
              << std::endl
              << std::endl;
}


/*============================================================================*/
/*                                   User function                            */             
/*============================================================================*/
/*                                                                            */

float calculate_average(float* arr, float size_of_array)
{
    float tot_array_sum = 0;

    for (size_t i = 0; i < size_of_array; ++i)
    {
        tot_array_sum += *(arr + i);
    }

    return (tot_array_sum / size_of_array);
}