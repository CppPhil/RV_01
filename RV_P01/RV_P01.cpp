#include <cstdlib> // std::exit, EXIT_FAILURE
#include <ltiViewer.h>
#include <ltiBMPFunctor.h>
#include <ltiSplitImageToHSI.h>
#include <gtk.h>
#include <ltiGtkServer.h>
#include <ltiJPEGFunctor.h> // saveJPEG
#include "utils.h" // app::keepWindowOpen
#include "Median.h" // app::median
#include "Sobel.h"
#include "ClParams.h"
#include "RV_P01.h"

namespace app {
    void RvP01::operator()(int argc, O3_IN char **argv) {
        std::string resultsFolder(argv[0]);
        std::string::size_type pos = resultsFolder.find_last_of("\\/");
        resultsFolder = resultsFolder.substr(0, pos);
        resultsFolder += std::string("/results/");

        lti::saveJPEG imgSaver;

        // start the gtkServer
        lti::gtkServer server;
        server.start();

        lti::loadBMP loader;
        
        lti::viewer view("Original");

        lti::viewer viewTransformed("Filtered");
        
        lti::image img; // color image
        lti::channel8 src; // 8bit image

        // output image for median filter
        lti::channel8 dst;
        
        // used to extract the intensity channel only
        lti::splitImageToHSI splitter;

        Action action = parseClParams(argc, argv); // parse the command line parameters
        
        if (action.filter == Filter::Error) { // on error -> display error.
            std::cerr << "incorrect command line parameters:\n";
            keepWindowOpen(action.file);
            std::exit(EXIT_FAILURE);
        }

        // load the source image
        loader.load(action.file, img);

        // only get intensity channel (grayscale values)
        splitter.getIntensity(img, src);
        
        // output image for the gradient image generated by the sobel filter
        lti::channel8 gradient;

        // output image for the direction image generated by the sobel filter
        lti::channel8 direction;

        lti::viewer viewGradient("gradient");
        lti::viewer viewDirection("direction");
        
        // get the maskX
        int maskX = action.maskX; // mask x size

        // get the maskY
        int maskY = action.maskY; // mask y size

        std::string saveTo(resultsFolder + action.file);
        std::string::size_type saveToPos = saveTo.find_last_of(".");
        saveTo = saveTo.substr(0, saveToPos);
        
        switch (action.filter) {
            case Filter::Median :
                Median(src, dst, maskX, maskY); // run median
                viewTransformed.show(dst);      // show the result of median
                imgSaver.save(saveTo + std::string("_Median_") + toString(maskX) + std::string("x") + toString(maskY) + std::string(".jpg"),
                              dst);
                break;
            case Filter::Sobel :
                Sobel(src, gradient, direction); // run sobel
                viewGradient.show(gradient);     // show the resulting gradient image 
                viewDirection.show(direction);   // show the resulting direction image
                imgSaver.save(saveTo + "_Gradient.jpg",
                              gradient);
                imgSaver.save(saveTo + "_Direction.jpg",
                              direction);
                break;            
            default:
                break;
        } // END of switch (action.filter)
       
        view.show(src); // show the source image

        keepWindowOpen(); // keep the window open; wait for used hitting the enter key -> end of program
    } // END of function void RvP01::operator()(int argc, O3_IN char **argv)

    void RvP01::Median(O3_IN lti::channel8 const &sPic,
                       O3_OUT lti::channel8 &dPic,
                       int const MaskSizeX,
                       int const MaskSizeY) {

        resizeImage(dPic, sPic.rows(), sPic.columns()); // resize the destination image to be large enough

        int mx = fixedMedianParam(MaskSizeX); // fix the MaskSizeX
        int my = fixedMedianParam(MaskSizeY); // fix the MaskSizeY
        // mx and my have the correct values now

        median<Fast>(sPic, dPic, Mask(mx, my)); // run the fast histogram based median filter implementation.
    } // END of Median
    
    void RvP01::Sobel(O3_IN lti::channel8 const &sPic,
                      O3_OUT lti::channel8 &GradientPic,
                      O3_OUT lti::channel8 &DirectionPic) {

        int const rows = sPic.rows();
        int const columns = sPic.columns();

        // resize the output images so that they're large enough
        resizeImage(GradientPic, rows, columns);
        resizeImage(DirectionPic, rows, columns);

        sobelImpl(sPic, GradientPic, DirectionPic); // run the sobel filter
    } // END of Sobel
} // END of namespace app
