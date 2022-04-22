#include <iostream>
#include <vector>
#include "../../containers/vector.hpp"
#include <iterator>

void    print_vec(std::vector<int>  &vec, std::string name)
{
    std::cout << name << ".size() : " << vec.size() << ",\t";
    std::cout << name << ".capacity() : " << vec.capacity() << std::endl;
    for (const auto& elem : vec)
        std::cout << elem << " -> ";
    std::cout << "end" << std::endl;
}

void    print_vec(ft::vector<int>  &vec, std::string name)
{
    std::cout << name << ".size() : " << vec.size() << ",\t";
    std::cout << name << ".capacity() : " << vec.capacity() << std::endl;
    for (const auto& elem : vec)
        std::cout << elem << " -> ";
    std::cout << "end" << std::endl;
}

int main(void)
{
    std::vector<int>    vec1_std(7);
    std::vector<int>    vec2_std(4);
    std::vector<int>    vec3_std;
    std::vector<int>    vec4_std;
    ft::vector<int>    vec1_ft(7);
    ft::vector<int>    vec2_ft(4);
    ft::vector<int>    vec3_ft;
    ft::vector<int>    vec4_ft;
    
    for (unsigned long int i = 0; i < vec1_std.size(); ++i)
		vec1_std[i] = (vec1_std.size() - i) * 3;
    for (unsigned long int i = 0; i < vec1_ft.size(); ++i)
		vec1_ft[i] = (vec1_ft.size() - i) * 3;
    for (unsigned long int i = 0; i < vec2_std.size(); ++i)
		vec2_std[i] = (vec2_std.size() - i) * 5;
    for (unsigned long int i = 0; i < vec2_ft.size(); ++i)
		vec2_ft[i] = (vec2_ft.size() - i) * 5;
    print_vec(vec1_std, "vec1_std");
    print_vec(vec1_ft, "vec1_ft");
    print_vec(vec2_std, "vec2_std");
    print_vec(vec2_ft, "vec2_ft");

    vec3_std.assign(vec1_std.begin(), vec1_std.end());
	vec1_std.assign(vec2_std.begin(), vec2_std.end());
	vec2_std.assign(2, 42);
	vec4_std.assign(4, 21);

    vec3_ft.assign(vec1_ft.begin(), vec1_ft.end());
	vec1_ft.assign(vec2_ft.begin(), vec2_ft.end());
	vec2_ft.assign(2, 42);
	vec4_ft.assign(4, 21);

    std::cout << "===========================AFTER===========================" << std::endl;
    
    print_vec(vec1_std, "vec1_std");
    print_vec(vec1_ft, "vec1_ft");
    print_vec(vec2_std, "vec2_std");
    print_vec(vec2_ft, "vec2_ft");
    print_vec(vec3_std, "vec3_std");
    print_vec(vec3_ft, "vec3_ft");
    print_vec(vec4_std, "vec4_std");
    print_vec(vec4_ft, "vec4_ft");


	vec4_std.assign(6, 84);
    print_vec(vec4_std, "vec4_std");
	vec4_ft.assign(6, 84);
    print_vec(vec4_ft, "vec4_ft");

	std::cout << "\t### assign() on enough capacity and low size: ###" << std::endl;

	vec1_std.assign(5, 53);
	vec2_std.assign(vec3_std.begin(), vec3_std.begin() + 3);
	vec1_ft.assign(5, 53);
	vec2_ft.assign(vec3_ft.begin(), vec3_ft.begin() + 3);

    print_vec(vec1_std, "vec1_std");
    print_vec(vec1_ft, "vec1_ft");
    print_vec(vec2_std, "vec2_std");
    print_vec(vec2_ft, "vec2_ft");
    return (0);
}