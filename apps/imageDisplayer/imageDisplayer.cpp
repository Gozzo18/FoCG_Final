#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <experimental/filesystem>
using namespace cv;

int main(int argc, const char* argv[]) {

    bool ready_to_display = true;

    std::vector<std::string> image_names;
    image_names.push_back("01_brick_720_256.jpg");
    image_names.push_back("02_brick_720_256.jpg");
    image_names.push_back("03_crystal_720_256.jpg");
    image_names.push_back("04_blue_fabric_720_256.jpg");
    image_names.push_back("05_grass_720_256.jpg");
    image_names.push_back("06_leopard_720_256.jpg");
    image_names.push_back("07_mud_720_256.jpg");
    image_names.push_back("08_moon_720_256.jpg");
    image_names.push_back("09_tree_720_256.jpg");

    for (int i = 0; i<image_names.size(); i++){
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
        for(int i = 0; i<image_names.size(); i++){
            auto current_path = std::string(std::experimental::filesystem::current_path().string().c_str());
            auto image_path = current_path.append("/out/lowres/");
            auto full_name = image_path.append(image_names[i]);

            Mat image;
            image = imread(full_name, CV_LOAD_IMAGE_COLOR);   // Read the file

            namedWindow( "Display window", WINDOW_AUTOSIZE );// Create a window for display.
            imshow( "Display window", image );                   // Show our image inside it.

            auto key = cv::waitKey(0); // Wait for a keystroke in the window
            std::cout<<key<<std::endl;
            if (key == 81){ //Left arrow key pressed
                if (i==0){
                    i = image_names.size()-2;
                }else{
                    i -= 2;
                }
            }else if (key==27 || key==255){ //Esc button pressed
                return 0;
            }else if (key!=83){//Any other button is pressed, stat on the same image
                i -= 1;
            }

            //If the last image is reached, restart from 0
            if(i==image_names.size()-1){
                i=-1;
            }  
        }
    }else{
        return -1;
    }

    return 0;
}