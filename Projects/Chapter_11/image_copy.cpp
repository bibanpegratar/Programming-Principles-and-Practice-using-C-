#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <chrono>

//This program uses the ios_base::binary to create copies of an image
//	- it openes an image in binary mode
//	- reads it bit by bit and puts each bit in a new file
//	- works with jpeg only

int main()
try{
    	int files = 1; // the number of copies of the image to create
	std::string image; // the name (or the full path) of the image
    	
	std::cout << "Name of the image to copy ( with extension ): ";
    	std::cin >> image;
	//Open an ostream file in binary mode
        std::ifstream fin {image, std::ios_base::binary};
    	if(!fin) throw std::runtime_error("failed to open image");

	std::cout << "How many copies of the image do you wanna create ? ";
    	std::cin >> files;

        auto t1 = std::chrono::high_resolution_clock::now();//The time at the start of execution
        char ch;

        for (int i = 1; i <= files; i++)
        {
		//Open image in binary read mode 
		std::ostringstream name;
            	name << "image_" << i << ".jpg";
            	std::ofstream fout {name.str(), std::ios_base::binary};

            	while (fin.get(ch)) fout << ch; 
            	//Must clear eof flag if using fin again
           	fin.clear();
            	fin.seekg(0);
        }

        std::ofstream log {"log_v1.txt", std::ios_base::app}; //Create a log file (append mode) 
        auto t2 = std::chrono::high_resolution_clock::now();//The time at the end of execution
        double diff = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
	std::cout << "Done!";
        log << files << " files - " << diff / 1000000 << " s\n"; // add the execution time and number of files copied to the log file
    return 0;

}
catch(std::runtime_error& e)
{
	std::cerr << "error: " << e.what() << '\n';
	return 1;
}

catch(...)
{
	std::cerr << "unknown error\n";
       	return 2;	
}
