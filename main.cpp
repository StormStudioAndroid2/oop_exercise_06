#include <iostream>
#include "Rectangle.h"
#include "./containers/list.h"
#include <string.h>
#include <algorithm>
#include "my_allocator.h"

int main() {
    char str[10];
         containers::list<Rectangle<int>,myal::my_allocator<Rectangle<int>,330>> l;
         

    while(std::cin >> str){
        if(strcmp(str,"push")==0){
            try {
            Rectangle<int> rectangle;
            rectangle.scan(std::cin);
            l.add(rectangle);
            } catch(std::bad_alloc& e) {
		std::cout << e.what() << std::endl;                                                                                                                                                                                                          
		std::cout << "memory limit\n";   
		continue; }
        }else if(strcmp(str,"delete")==0){
            try {
                int t;
                std::cin >> t;
                l.erase(l.begin()+t);
                std::cout << "\n";
            }catch (std::exception& ex){
                std::cout <<ex.what() << "\n";
            }
        }
        else if(strcmp(str,"front")==0) {
            try {
               l.front().print(std::cout);
                std::cout << "\n";
            }catch (std::exception& ex){
                std::cout <<ex.what() << "\n";
            }
        }if(strcmp(str,"get")==0) {
            try {
               int r;
               std::cin >> r;
                l[r].print(std::cout);
                std::cout << "\n";
            }catch (std::exception& ex){
                std::cout <<ex.what() << "\n";
            }
        } else if(strcmp(str,"end")==0){
            try {
               
                l.End().print(std::cout);
            }catch (std::exception& ex){
                std::cout <<ex.what() << "\n";
            }
        }else if(strcmp(str,"square")==0) {
            int g;
            std::cin >> g;
            long res=std::count_if(l.begin(),l.end(),[g](Rectangle<int> f){ return f.getSquare() < g;});
            std::cout << res << "\n";
        } else if(strcmp(str,"insert")==0){
            try {
            int r;
            std::cin >>r;
            Rectangle<int> rectangle;
            rectangle.scan(std::cin);
            l.insert(l.begin() + r,rectangle); }
            catch(std::bad_alloc& e) {
		std::cout << e.what() << std::endl;                                                                                                                                                                                                          
		std::cout << "memory limit\n";   
		continue; }
        }else if(strcmp(str,"all")==0){
            if (l.begin()!=nullptr) {
            std::for_each(l.begin(),l.end(),[](Rectangle<int> f){f.print(std::cout); });
            std::cout<< "\n";
            } else {
                std::cout << "Empty list!" << std::endl;
            }
        }

    }
    return 0;
}