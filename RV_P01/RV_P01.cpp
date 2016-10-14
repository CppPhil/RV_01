#include <iostream> // std::cin
#include <limits> // std::numeric_limits
// TODO: remove unnecessary includes below this line
#include <ltiViewer.h>
#include <ltiTimer.h>
#include <ltiBMPFunctor.h>
#include <ltiSplitImg.h>
#include <gtk.h>
#include <ltiGtkServer.h>
#include "utils.h" // app::keepWindowOpen
#include "Median.h" // app::median
#include "RV_P01.h"

namespace app {
    void RvP01::operator()(int argc, char **argv) {
        lti::loadBMP loader;
        
        lti::viewer view("Original");

        lti::viewer viewTransformed("Filtered");
        
        lti::image img;
        lti::channel8 src;
        lti::channel8 dst;

        lti::splitImageToHSI splitter;

        // TODO: make image to load be extracted from command line parameters
        loader.load("auge.bmp", img);

        splitter.getIntensity(img, src);

        int const rows = src.rows();
        int const columns = src.columns();


        // TODO: extract the false and true out to make it more readable
        dst.resize(rows, columns, (int()), false, true);

        // TODO: configure whether to use Median or Sobel from command line parameters
        
        int maskX = 15; // mask x size
        int maskY = 15; // mask y size

        Median(src, dst, maskX, maskY);

        view.show(src);
        viewTransformed.show(dst);
        
        keepWindowOpen();
    }

    void RvP01::Median(lti::channel8 const &sPic,
                       lti::channel8 &dPic,
                       int const MaskSizeX,
                       int const MaskSizeY) {

        static int const maxGrayScaleValue = 256;

        int const PicSizeY = sPic.rows();
        int const PicSizeX = sPic.columns();

        int x, y, mx, my;

        for (y = 0; y < PicSizeY; ++y) {
            for (x = 0; x < PicSizeX; ++x) {
                dPic[y][x] = maxGrayScaleValue - sPic[y][x];
            }
        }

        mx = fixedMedianParam(MaskSizeX);
        my = fixedMedianParam(MaskSizeY);
        // mx and my have the correct values now

        median<Fast>(sPic, dPic, Mask(mx, my));
    } // END of Median
    
    void RvP01::Sobel(lti::channel8 const &sPic,
                      lti::channel8 &GradientPic,
                      lti::channel8 &DirectionPic) {

        // TODO: implement Sobel

    } // END of Sobel
} // END of namespace app
