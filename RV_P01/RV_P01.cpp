#include <iostream> // std::cin
#include <limits> // std::numeric_limits
#include <algorithm> // std::inner_product
#include <cstring> // std::memset
#include <new> // new
#include <cmath> // std::abs
// TODO: remove unnecessary includes below this line
#include <ltiViewer.h>
#include <ltiTimer.h>
#include <ltiBMPFunctor.h>
#include <ltiSplitImageToHSI.h>
#include <gtk.h>
#include <ltiGtkServer.h>
#include "O3/containers.h"
#include "O3/memory.h"
#include "O3/nullptr.h"
#include "O3/iterator.h"
#include "utils.h" // app::keepWindowOpen
#include "Median.h" // app::median
#include "Sobel.h"
#include "RV_P01.h"

#include <fstream>

#define DO_MEDIAN 0

std::ofstream file("LOG.TXT");

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
        loader.load("block.bmp", img);

        splitter.getIntensity(img, src);

        int const rows = src.rows();
        int const columns = src.columns();


        // TODO: extract the false and true out to make it more readable
        dst.resize(rows, columns, (int()), false, true);

        // TODO: configure whether to use Median or Sobel from command line parameters
        
        int maskX = 15; // mask x size
        int maskY = 15; // mask y size

#if DO_MEDIAN
        Median(src, dst, maskX, maskY);
#endif // DO_MEDIAN

        view.show(src);

#if DO_MEDIAN
        viewTransformed.show(dst);
#endif // DO_MEDIAN

        lti::channel8 gradient;
        lti::channel8 direction;

        lti::viewer viewGradient("gradient");
        lti::viewer viewDirection("direction");

        Sobel(src, gradient, direction);

        viewGradient.show(gradient);
        viewDirection.show(direction);
        
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
#if 0
        typedef o3::array<int, SobelMaskX * SobelMaskY> Array;
        typedef Array::const_iterator const_iterator;
        typedef Array::iterator iterator;
        typedef o3::scoped_array<int> ScopedAryInt;
        typedef o3::scoped_array<ScopedAryInt> ScopedAryOfScopedAryInt;
                
        static Array const maskX = { -1, 0, 1,
                                     -2, 0, 2,
                                     -1, 0, 1 };

        static Array const maskY = { -1, -2, -1,
                                      0,  0,  0,
                                      1,  2,  1 };

        int const rows = sPic.rows();
        int const columns = sPic.columns();

        ScopedAryOfScopedAryInt gs;
        ScopedAryOfScopedAryInt alphas;

        ScopedAryInt *p1 = new ScopedAryInt[rows];
        ScopedAryInt *p2 = new ScopedAryInt[rows];

        for (int i = 0; i < rows; ++i) {
            p1[i].reset(new int[columns]);
            std::memset(p1[i].get(), 0, columns * sizeof(int));
            p2[i].reset(new int[columns]);
            std::memset(p2[i].get(), 0, columns * sizeof(int));
        }

        gs.reset(p1);
        p1 = O3_NULLPTR;
        alphas.reset(p2);
        p2 = O3_NULLPTR;

        const_iterator xMaskBegin = o3::cbegin(maskX);
        const_iterator yMaskBegin = o3::cbegin(maskY);
        
        Array curVals = { 0 };
        iterator itBegin = o3::begin(curVals);
        iterator itEnd = o3::end(curVals);
        
        static int const xBegin = SobelMaskX / 2;
        static int const yBegin = SobelMaskY / 2;
        int const xEnd = columns - xBegin;
        int const yEnd = rows - yBegin;
        
        for (int x = xBegin; x < xEnd; ++x) {
            for (int y = yBegin; y < yEnd; ++y) {
                iterator it = itBegin;
                for (int i = x - xBegin; i <= x + xBegin; ++i) { // gather the elements
                    for (int j = y - yBegin; j <= y + yBegin; ++j) {
                        *it = sPic[y][x];
                        file << "*it: " << *it << '\n';
                        ++it;
                    }
                }

                int gx = 0;
                int gy = 0;

                
                const_iterator xIt = xMaskBegin;
                const_iterator yIt = yMaskBegin;
                for (iterator iter = itBegin, end = itEnd; iter != end; ++iter, ++xIt, ++yIt) {
                    file << "IM HERE BITCH\n";
                    file << "*iter: " << *iter
                        << '\n'
                        << "*xIt: " << *xIt
                        << '\n'
                        << "*yIt: " << *yIt
                        << '\n';
                    gx += (*iter) * (*xIt);
                    gy += (*iter) * (*yIt);
                }
            

                file << "fuckin gx is: " << gx
                    << "\nfuckin gy is: " << gy << '\n';
                                           
                gs[y][x] = getG(gx, gy);
                alphas[y][x] = std::atan2(static_cast<long double>(gy),
                                          static_cast<long double>(gx));
            }
        }
        
        GradientPic.resize(rows, columns, (int()), false, true);
        DirectionPic.resize(rows, columns, (int()), false, true);

        static int const maxGrayScaleValue = 256;

        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < columns; ++j) {
                GradientPic[i][j] = maxGrayScaleValue - sPic[i][j];
                DirectionPic[i][j] = maxGrayScaleValue - sPic[i][j];
            }
        }
        
        

        for (int row = 0; row < rows; ++row) {
            for (int column = 0; column < columns; ++column) {

                file      << "row: " << row 
                          << "\ncolumn: " << column
                          << "\ngs: " << gs[row][column]
                          << "\nalphas: " << alphas[row][column] << "\n\n";

                GradientPic[row][column] = gs[row][column];
                DirectionPic[row][column] = alphas[row][column];
            }
        }
        file << std::flush;
#endif // 0

        int const rows = sPic.rows();
        int const columns = sPic.columns();

        GradientPic.resize(rows, columns, (int()), false, true);
        DirectionPic.resize(rows, columns, (int()), false, true);

        int gx = 0;
        int gy = 0;
        int sum = 0;
        int alpha = 0;
        int srcPoint = 0;

        for (int y = 1; y < sPic.rows() - 1; ++y) {
            for (int x = 1; x < sPic.columns() - 1; ++x) {
                srcPoint = sPic[y][x];
                gx = riparoo::xGradient(sPic, x, y);
                gy = riparoo::yGradient(sPic, x, y);
                //sum = std::abs(gx) + std::abs(gy);
                sum = std::sqrt(std::pow(static_cast<double>(gx), 2.0) + std::pow(static_cast<double>(gy), 2.0));
                sum = o3::clamp(sum, 0, 255);
                GradientPic[y][x] = //o3::clamp(srcPoint - std::abs(sum), 0, 255);
                    //std::abs(sum);
                    o3::clamp(sum, 0, 255);
                alpha = std::atan2(static_cast<double>(gy),
                                   static_cast<double>(gy));
                DirectionPic[y][x] = alpha;
            }
        }

    } // END of Sobel
} // END of namespace app
