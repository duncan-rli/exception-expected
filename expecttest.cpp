
#include "../external/expected/tl/expected.hpp"
#include "stats.h"
#include <memory>
#include <vector>
#include <chrono>
#include <iostream>
#include <exception>
#include <string>

const int vectorSize = 10;

void test01(){
    auto vec = std::vector<std::unique_ptr<int>>(vectorSize);

    for (int i=0; i < vectorSize; i++){
        vec[i] = std::make_unique<int>(i);
    }
    
}


class image_view{ 
    std::unique_ptr<int> iv;
    public:
    image_view(){
        iv = std::make_unique<int>(10);
    }
    image_view(const image_view& iv){}
    image_view operator=(const image_view& iv){return *this;}
};

int errPoint = 0;
enum error_code {no_cat_found, cannot_see_neck, cat_has_eyes_shut, that_is_a_dog};

//#define VERBOSE
#define EXCEP


tl::expected<image_view, error_code> find_cat(image_view v){
    test01();
    if (errPoint == 1)
        return tl::unexpected(that_is_a_dog);
#ifdef EXCEP
    else if (errPoint == 11)
        throw that_is_a_dog;
#endif        
    return v;
}
tl::expected<image_view, error_code> add_bow_tie(image_view v){
    test01();
    if (errPoint == 2)
        return tl::unexpected(that_is_a_dog);
#ifdef EXCEP
    else if (errPoint == 12)
        throw that_is_a_dog;
#endif        
    return v;
}
tl::expected<image_view, error_code> make_eyes_sparkle(image_view v){
    test01();
    if (errPoint == 3)
        return tl::unexpected(that_is_a_dog);
#ifdef EXCEP
    else if (errPoint == 13)
        throw that_is_a_dog;
#endif        
    return v;
}
image_view make_smaller(image_view v){
    auto vec = std::vector<std::unique_ptr<int>>(vectorSize);
    for (int i=0; i < vectorSize; i++){
        vec[i] = std::make_unique<int>(i);
    }
    return v;
}
image_view add_rainbow(image_view v){
    auto vec = std::vector<std::unique_ptr<int>>(vectorSize);
    for (int i=0; i < vectorSize; i++){
        vec[i] = std::make_unique<int>(i);
    }
    return v;
}


tl::expected<image_view, error_code> get_cute_cat (image_view img) {
    auto cropped = find_cat(img);
    if (!cropped) {
      return tl::make_unexpected(no_cat_found);
    }

    auto with_tie = add_bow_tie(*cropped);
    if (!with_tie) {
      return tl::make_unexpected(cannot_see_neck);
    }

    auto with_sparkles = make_eyes_sparkle(*with_tie);
    if (!with_sparkles) {
      return tl::make_unexpected(cat_has_eyes_shut);
    }

    return add_rainbow(make_smaller(*with_sparkles));
}

tl::expected<image_view, error_code> get_cute_cat2 (image_view img) {
    return find_cat(img)
           .and_then(add_bow_tie)
           .and_then(make_eyes_sparkle)
           .map(make_smaller)
           .map(add_rainbow);
}

#ifdef EXCEP
image_view get_cute_cat_seh (image_view img) {
    auto cropped = find_cat(img);
    if (!cropped) {
      throw(no_cat_found);
    }

    auto with_tie = add_bow_tie(*cropped);
    if (!with_tie) {
      throw (cannot_see_neck);
    }

    auto with_sparkles = make_eyes_sparkle(*with_tie);
    if (!with_sparkles) {
      throw cat_has_eyes_shut;
    }

    return add_rainbow(make_smaller(*with_sparkles));
}
#endif        


void this_works(){};



int main(void){

    image_view my_view; 

    tl::expected<image_view,error_code> full_view = my_view;
    tl::expected<image_view,error_code> empty_view = tl::unexpected(that_is_a_dog);

    int numberOfTests = 4;
    int repeatCount = 1000;
    Stats results1[numberOfTests];
    Stats results2[numberOfTests];
    Stats results3[numberOfTests];
    auto start1 = std::chrono::high_resolution_clock::now();
    auto diff1 = std::chrono::high_resolution_clock::now() - start1;
    auto t1 = std::chrono::duration_cast<std::chrono::nanoseconds>(diff1);
    auto start2 = std::chrono::high_resolution_clock::now();
    auto diff2 = std::chrono::high_resolution_clock::now() - start2;
    auto t2= std::chrono::duration_cast<std::chrono::nanoseconds>(diff2);
    auto start3 = std::chrono::high_resolution_clock::now();
    auto diff3 = std::chrono::high_resolution_clock::now() - start3;
    auto t3 = std::chrono::duration_cast<std::chrono::nanoseconds>(diff3);

    {
        for (int r=0; r< repeatCount; r++){
            for (int i=0; i<numberOfTests; i++){
                errPoint = i;

                start1 = std::chrono::high_resolution_clock::now();
                full_view = get_cute_cat(my_view);
                diff1 = std::chrono::high_resolution_clock::now() - start1;
                t1 = std::chrono::duration_cast<std::chrono::nanoseconds>(diff1);
                results1[i].addData(t1.count());

    #ifdef VERBOSE
                if (full_view){
                    std::cout << "ErrP: " << i << " EC: no error " << full_view.error() << std::endl;
                }
                if (!full_view){
                    std::cout << "ErrP: " << i << " EC: " << full_view.error() << std::endl;
                }
    #endif            
            }
        }
        std::cout << "Normal" << std::endl;
        for (auto r: results1){
            std::cout << r.getString() << std::endl;
        }
    }
    {
        for (int r=0; r< repeatCount; r++){
            for (int i=0; i<numberOfTests; i++){
                errPoint = i;

                start2 = std::chrono::high_resolution_clock::now();
                full_view = get_cute_cat2(my_view);
                diff2 = std::chrono::high_resolution_clock::now() - start2;
                t2 = std::chrono::duration_cast<std::chrono::nanoseconds>(diff2);
                results2[i].addData(t2.count());

    #ifdef VERBOSE
                if (full_view){
                    std::cout << "ErrP: " << i << " EC: no error " << full_view.error() << std::endl;
                }
                if (!full_view){
                    std::cout << "ErrP: " << i << " EC: " << full_view.error() << std::endl;
                }
    #endif            
            }
        }
        std::cout << "Monad" << std::endl;
        for (auto r: results2){
            std::cout << r.getString() << std::endl;
        }
    }
    #ifdef EXCEP
    {
        for (int r=0; r< repeatCount; r++){
            for (int i=0; i<numberOfTests; i++){
                error_code ec;
                errPoint = i + 10;

                start3 = std::chrono::high_resolution_clock::now();
                try{
                full_view = get_cute_cat_seh(my_view);
                }
                catch(error_code c){
                }
                diff3 = std::chrono::high_resolution_clock::now() - start3;
                t3 = std::chrono::duration_cast<std::chrono::nanoseconds>(diff3);
                results3[i].addData(t3.count());

    #ifdef VERBOSE
                if (full_view){
                    std::cout << "ErrP: " << i << " EC: no error " << ec << std::endl;
                }
                if (!full_view){
                    std::cout << "ErrP: " << i << " EC: " << ec << std::endl;
                }
    #endif            
            }
        }
        std::cout << "SEH" << std::endl;
        for (auto r: results3){
                std::cout << r.getString() << std::endl;
        }
    }
    #endif        

    return 0;   
}
