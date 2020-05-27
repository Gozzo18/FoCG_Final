#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <experimental/filesystem>
using namespace cv;

int main(int argc, const char* argv[]) {

    bool ready_to_display = true;

    std::string image_names[10] = {"01_brick_1920_1080.jpg",
                                    "02_brick_1920_1080.jpg",
                                      "03_crystal_1920_1080.jpg",
                                       "04_blue_fabric_1920_1080.jpg",
                                        "06_grass_1920_1080.jpg",
                                         "07_leopard_1920_1080.jpg",
                                          "08_mud_1920_1080.jpg",
                                           "09_moon_1920_1080.jpg",
                                            "10_sand_1920_1080.jpg",
                                             "11_tree_1920_1080.jpg"};

    for (int i = 0; i<10; i++){
        auto current_path = std::string(std::experimental::filesystem::current_path().string().c_str());
        auto image_path = current_path.append("/out/lowres/");
        auto full_name = image_path.append(image_names[i]);
        FILE *file = fopen(full_name.c_str(), "r");

        if (file != NULL){
          fclose(file);
        }
        else{
          ready_to_display = false;
          std::cout<<"Some images need to be rendered first!"<<std::endl;
          break;
        }
    }

    if (ready_to_display){
        for(int i = 0; i<10; i++){
            auto current_path = std::string(std::experimental::filesystem::current_path().string().c_str());
            auto image_path = current_path.append("/out/lowres/");
            auto full_name = image_path.append(image_names[i]);

            Mat image;
            image = imread(full_name, CV_LOAD_IMAGE_COLOR);   // Read the file

            namedWindow( "Display window", WINDOW_AUTOSIZE );// Create a window for display.
            imshow( "Display window", image );                   // Show our image inside it.

            auto key = cv::waitKey(0); // Wait for a keystroke in the window
            if (key == 81){ //Left arrow key pressed
                if (i==0){
                    i = 8;
                }else{
                    i -= 2;
                }
            }else if (key==27 || key==255){ //Esc button pressed
                return 0;
            } 

            //If the last image is reached, restart from 0
            if(i==9){
                i=-1;
            }  
        }
    }else{
        return -1;
    }

    return 0;
}