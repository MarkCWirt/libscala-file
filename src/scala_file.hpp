
#pragma once

#include <fstream>
#include <math.h>
#include <vector>


// Define this before compilation if you want a stricter adherence 
// to the specification.

// #define SCALA_STRICT

namespace scala {

    struct degree {

        double ratio;

        degree (int n, int d){
            // Two inputs: a ratio
            ratio  = static_cast <double> (n) / static_cast <double> (d);
        }

        explicit degree (double cents){
            // One input: cents
            ratio = pow(pow(2, 1.0 / 12.0), cents/100.0);
        }

        double get_ratio() {
            // Use to get the value
            return ratio;
        }
    };

    struct scale {
        
        std::vector <degree> degrees;

        scale () {
            // The first degree is a scala file is always implicit. Make it explicit.
            degrees.push_back( *(new degree(0.0)));
        }

        ~scale(){
            degrees.clear();
            std::vector<degree>().swap(degrees);
        }

        scale(const scale &s2) {
            for (size_t i = 0; i < s2.degrees.size(); i++) {
                degrees.push_back(s2.degrees[i]); 
            }
        }

        scale& operator=(const scale &s2){
            std::vector <degree> new_degrees;
            for (size_t i = 0; i < s2.degrees.size(); i++) {
                new_degrees.push_back(s2.degrees[i]);
            }
            degrees.swap(new_degrees);
            new_degrees.clear();
            return *this;
        }

        void add_degree(degree d) {
            degrees.push_back(d);
        }

        double get_ratio(size_t i){
            return degrees[i].get_ratio();
        }

        size_t get_scale_length() {
            return degrees.size();
        }

    };

    scale read_file(std::ifstream& input_file);
}
